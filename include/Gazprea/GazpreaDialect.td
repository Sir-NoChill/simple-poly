//===- GazpreaDialect.td - Gazprea dialect -----------*- tablegen -*-===//
//
// This file is licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef GAZPREA_DIALECT
#define GAZPREA_DIALECT

include "mlir/IR/OpBase.td"

//===----------------------------------------------------------------------===//
// Gazprea dialect definition.
//===----------------------------------------------------------------------===//

def Gazprea_Dialect : Dialect {
    let name = "gazprea";
    let summary = "A gazprea out-of-tree MLIR dialect.";
    let description = [{
        This dialect is an example of an out-of-tree MLIR dialect designed to
        illustrate the basic setup required to develop MLIR-based tools without
        working inside of the LLVM source tree.
    }];
    let cppNamespace = "::mlir::gazprea";

    let useDefaultTypePrinterParser = 1;
    let extraClassDeclaration = [{
        void registerTypes();
    }];
}

#endif // GAZPREA_DIALECT
