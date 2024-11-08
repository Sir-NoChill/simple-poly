//===- GazpreaPsss.td - Gazprea dialect passes -------*- tablegen -*-===//
//
// This file is licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef GAZPREA_PASS
#define GAZPREA_PASS

include "mlir/Pass/PassBase.td"

def GazpreaSwitchBarFoo: Pass<"gazprea-switch-bar-foo", "::mlir::ModuleOp"> {
  let summary = "Switches the name of a FuncOp named `bar` to `foo` and folds.";
  let description = [{
    Switches the name of a FuncOp named `bar` to `foo` and folds.
    ```
    func.func @bar() {
      return
    }
    // Gets transformed to:
    func.func @foo() {
      return
    }
    ```
  }];
}

def GazpreaToStandard : Pass<"gazprea-to-standard"> {
  let summary = "Lower `gazprea` to standard mlir, affine and arith";

  let description = [{ Some description }];

  let dependentDialects = [
    "mlir::arith::ArithDialect",
    "mlir::gazprea::GazpreaDialect",
    "mlir::tensor::TensorDialect"
  ];
}

#endif // GAZPREA_PASS
