//===- GazpreaDialect.cpp - Gazprea dialect ---------------*- C++ -*-===//
//
// This file is licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "Gazprea/GazpreaDialect.h"
#include "Gazprea/GazpreaOps.h"
#include "Gazprea/GazpreaTypes.h"

using namespace mlir;
using namespace mlir::gazprea;

#include "Gazprea/GazpreaOpsDialect.cpp.inc"

//===----------------------------------------------------------------------===//
// Gazprea dialect.
//===----------------------------------------------------------------------===//

void GazpreaDialect::initialize() {
  addOperations<
#define GET_OP_LIST
#include "Gazprea/GazpreaOps.cpp.inc"
      >();
  registerTypes();
}
