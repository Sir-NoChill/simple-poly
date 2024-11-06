//===- gazprea-opt.cpp ---------------------------------------*- C++ -*-===//
//
// This file is licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "mlir/Conversion/ControlFlowToLLVM/ControlFlowToLLVM.h"
#include "mlir/Conversion/FuncToLLVM/ConvertFuncToLLVMPass.h"
#include "mlir/Conversion/MemRefToEmitC/MemRefToEmitCPass.h"
#include "mlir/Conversion/MemRefToLLVM/MemRefToLLVM.h"
#include "mlir/Conversion/SCFToControlFlow/SCFToControlFlow.h"
#include "mlir/Dialect/Bufferization/Pipelines/Passes.h"
#include "mlir/Dialect/Bufferization/Transforms/Passes.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/MemRef/Transforms/Passes.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/InitAllDialects.h"
#include "mlir/InitAllPasses.h"
#include "mlir/Support/FileUtilities.h"
#include "mlir/Tools/mlir-opt/MlirOptMain.h"

#include "Gazprea/GazpreaDialect.h"
#include "Gazprea/GazpreaPasses.h"
#include "mlir/Transforms/Passes.h"
#include "mlir/Conversion/ArithToLLVM/ArithToLLVM.h"
#include "mlir/Dialect/Linalg/Passes.h"

void customPipelineBuilder(mlir::OpPassManager &pm) {
  pm.addNestedPass<mlir::func::FuncOp>(mlir::createCanonicalizerPass());
  pm.addNestedPass<mlir::func::FuncOp>(mlir::createCSEPass());
}

void gazpreaPipelineManager(mlir::OpPassManager &pm) {
  pm.addPass(mlir::gazprea::createGazpreaToStandard());
  pm.addPass(mlir::createCanonicalizerPass());
  pm.addPass(mlir::createConvertTensorToLinalgPass());
  pm.addPass(mlir::createConvertElementwiseToLinalgPass());
  pm.addPass(mlir::createArithToLLVMConversionPass());

  // One-shot bufferize, from
  // https://mlir.llvm.org/docs/Bufferization/#ownership-based-buffer-deallocation
  mlir::bufferization::OneShotBufferizationOptions bufferizationOptions;
  bufferizationOptions.bufferizeFunctionBoundaries = true;
  // bufferizationOptions.setFunctionBoundaryTypeConversion(mlir::bufferization::LayoutMapOption::IdentityLayoutMap);
  //bufferizationOptions.testAnalysisOnly = true;
  //bufferizationOptions.printConflicts = true;
  //bufferizationOptions.dumpAliasSets = true;
  pm.addPass(mlir::bufferization::createOneShotBufferizePass(bufferizationOptions));
  mlir::bufferization::BufferDeallocationPipelineOptions deallocationOptions;
  pm.addPass(mlir::bufferization::createBufferResultsToOutParamsPass());
  mlir::bufferization::buildBufferDeallocationPipeline(pm, deallocationOptions);
  /**
  */

  pm.addPass(mlir::createConvertLinalgToLoopsPass());
  pm.addPass(mlir::memref::createExpandStridedMetadataPass());
  pm.addPass(mlir::createConvertSCFToCFPass());
  pm.addPass(mlir::createConvertControlFlowToLLVMPass());
  pm.addPass(mlir::createArithToLLVMConversionPass());
  pm.addPass(mlir::createConvertFuncToLLVMPass());
  pm.addPass(mlir::createFinalizeMemRefToLLVMConversionPass());
  pm.addPass(mlir::createReconcileUnrealizedCastsPass());
  /**
  pm.addPass(mlir::createCanonicalizerPass());
  */

  // pm.addPass(mlir::createFinalizeMemRefToLLVMConversionPass());
  // pm.addPass(mlir::createReconcileUnrealizedCastsPass());

  /**
  pm.addPass(mlir::createSCCPPass());
  pm.addPass(mlir::createCSEPass());
  pm.addPass(mlir::createSymbolDCEPass());
*/
  // One-shot bufferize, from
  // https://mlir.llvm.org/docs/Bufferization/#ownership-based-buffer-deallocation
  //mlir::bufferization::OneShotBufferizationOptions bufferizationOptions;
  //bufferizationOptions.bufferizeFunctionBoundaries = true;
  //pm.addPass(
  //    mlir::bufferization::createOneShotBufferizePass(bufferizationOptions));
  //pm.addPass(mlir::memref::createExpandReallocPass());
  //pm.addPass(mlir::bufferization::createOwnershipBasedBufferDeallocationPass());
  //pm.addPass(mlir::createCanonicalizerPass());
  //pm.addPass(mlir::bufferization::createBufferDeallocationSimplificationPass());
  //pm.addPass(mlir::bufferization::createLowerDeallocationsPass());
  //pm.addPass(mlir::createCSEPass());
  //pm.addPass(mlir::createCanonicalizerPass());
}

int main(int argc, char **argv) {
  mlir::registerAllPasses();
  mlir::gazprea::registerPasses();
  // TODO: Register gazprea passes here.
  mlir::gazprea::registerGazpreaToStandardPass();

  mlir::DialectRegistry registry;
  mlir::registerAllDialects(registry);
  registry.insert<mlir::gazprea::GazpreaDialect,
                  mlir::arith::ArithDialect, mlir::func::FuncDialect>();
  // Add the following to include *all* MLIR Core dialects, or selectively
  // include what you need like above. You only need to register dialects that
  // will be *parsed* by the tool, not the one generated
  // registerAllDialects(registry);

  mlir::PassPipelineRegistration<>("my-pipeline", "Custom Pipeline", customPipelineBuilder);
  mlir::PassPipelineRegistration<>("gazprea-to-llvm", "Run passes to lower to llvm", gazpreaPipelineManager);

  return mlir::asMainReturnCode(
      mlir::MlirOptMain(argc, argv, "Gazprea optimizer driver\n", registry));
}
