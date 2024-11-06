//===- GazpreaPasses.cpp - Gazprea passes -----------------*- C++ -*-===//
//
// This file is licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
#include "Gazprea/GazpreaDialect.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/Func/Transforms/FuncConversions.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/IR/PatternMatch.h"
#include "mlir/Rewrite/FrozenRewritePatternSet.h"
#include "mlir/Support/LogicalResult.h"
#include "mlir/Transforms/DialectConversion.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"

#include "Gazprea/GazpreaPasses.h"

namespace mlir::gazprea {
#define GEN_PASS_DEF_GAZPREASWITCHBARFOO
#include "Gazprea/GazpreaPasses.h.inc"

namespace {
class GazpreaSwitchBarFooRewriter : public OpRewritePattern<func::FuncOp> {
public:
  using OpRewritePattern<func::FuncOp>::OpRewritePattern;
  LogicalResult matchAndRewrite(func::FuncOp op,
                                PatternRewriter &rewriter) const final {
    if (op.getSymName() == "bar") {
      rewriter.modifyOpInPlace(op, [&op]() { op.setSymName("foo"); });
      return success();
    }
    return failure();
  }
};

class GazpreaSwitchBarFoo
    : public impl::GazpreaSwitchBarFooBase<GazpreaSwitchBarFoo> {
public:
  using impl::GazpreaSwitchBarFooBase<
      GazpreaSwitchBarFoo>::GazpreaSwitchBarFooBase;
  void runOnOperation() final {
    RewritePatternSet patterns(&getContext());
    patterns.add<GazpreaSwitchBarFooRewriter>(&getContext());
    FrozenRewritePatternSet patternSet(std::move(patterns));
    if (failed(applyPatternsAndFoldGreedily(getOperation(), patternSet)))
      signalPassFailure();
  }
};
} // namespace

#define GEN_PASS_DEF_GAZPREATOSTANDARD
#include "Gazprea/GazpreaPasses.h.inc"

class GazpreaToStandardTypeConverter : public TypeConverter {
  public:
    GazpreaToStandardTypeConverter(MLIRContext *ctx) {
      addConversion([](Type type) {return type; });
      addConversion([ctx](PolynomialType type) -> Type {
        int degreeBound = type.getDegreeBound();
        IntegerType elementTy = IntegerType::get(ctx, 32, IntegerType::SignednessSemantics::Signless);
        return RankedTensorType::get({degreeBound}, elementTy);
      });
    }
};

  struct ConvertAdd : public OpConversionPattern<AddOp> {
      using OpConversionPattern::OpConversionPattern;

      LogicalResult matchAndRewrite(AddOp op, OpAdaptor adaptor, ConversionPatternRewriter &rewriter) const override {
        arith::AddIOp addOp = rewriter.create<arith::AddIOp>(op.getLoc(), adaptor.getLhs(), adaptor.getRhs());
        rewriter.replaceOp(op.getOperation(), addOp);
        return success();
      }
  };

struct GazpreaToStandard : impl::GazpreaToStandardBase<GazpreaToStandard> {
  using GazpreaToStandardBase::GazpreaToStandardBase;

  void runOnOperation() override {
    MLIRContext *context = &getContext();
    auto *module = getOperation();

    ConversionTarget target(*context);
    target.addLegalDialect<arith::ArithDialect>();
    target.addIllegalDialect<GazpreaDialect>();

    RewritePatternSet patterns(context);
    GazpreaToStandardTypeConverter typeConverter(context);
    patterns.add<ConvertAdd>(typeConverter, context);

    populateFunctionOpInterfaceTypeConversionPattern<func::FuncOp>(patterns, typeConverter);
    target.addDynamicallyLegalOp<func::FuncOp>([&](func::FuncOp op) {
      return typeConverter.isSignatureLegal(op.getFunctionType()) && typeConverter.isLegal(&op.getBody());
    });

    populateReturnOpTypeConversionPattern(patterns, typeConverter);
    target.addDynamicallyLegalOp<func::ReturnOp>([&](func::ReturnOp op) {
      return typeConverter.isLegal(op);
    });

    populateCallOpTypeConversionPattern(patterns, typeConverter);
    target.addDynamicallyLegalOp<func::CallOp>([&](func::CallOp op) {
      return typeConverter.isLegal(op);
    });

    populateBranchOpInterfaceTypeConversionPattern(patterns, typeConverter);
    target.markUnknownOpDynamicallyLegal([&](Operation *op) {
      return isNotBranchOpInterfaceOrReturnLikeOp(op) ||
        isLegalForBranchOpInterfaceTypeConversionPattern(op, typeConverter) ||
        isLegalForReturnOpTypeConversionPattern(op, typeConverter);
    });

    if (failed(applyPartialConversion(module, target, std::move(patterns)))) {
      signalPassFailure();
    }
  }
};


} // namespace mlir::gazprea
