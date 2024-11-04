//===- GazpreaTypes.cpp - Gazprea dialect types -----------*- C++ -*-===//
//
// This file is licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "Gazprea/GazpreaTypes.h"

#include "Gazprea/GazpreaDialect.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/DialectImplementation.h"
#include "llvm/ADT/TypeSwitch.h"

using namespace mlir::gazprea;

#define GET_TYPEDEF_CLASSES
#include "Gazprea/GazpreaOpsTypes.cpp.inc"

void GazpreaDialect::registerTypes() {
  addTypes<
#define GET_TYPEDEF_LIST
#include "Gazprea/GazpreaOpsTypes.cpp.inc"
      >();
}
