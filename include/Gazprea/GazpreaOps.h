//===- GazpreaOps.h - Gazprea dialect ops -----------------*- C++ -*-===//
//
// This file is licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef GAZPREA_GAZPREAOPS_H
#define GAZPREA_GAZPREAOPS_H

#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/Dialect.h"
#include "mlir/IR/OpDefinition.h"
#include "mlir/Interfaces/InferTypeOpInterface.h"
#include "mlir/Interfaces/SideEffectInterfaces.h"


#define GET_OP_CLASSES
#include "Gazprea/GazpreaTypes.h"
#include "Gazprea/GazpreaOps.h.inc"

#endif // GAZPREA_GAZPREAOPS_H
