//===- GazpreaPasses.h - Gazprea passes  ------------------*- C++ -*-===//
//
// This file is licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
#ifndef GAZPREA_GAZPREAPASSES_H
#define GAZPREA_GAZPREAPASSES_H

#include "Gazprea/GazpreaDialect.h"
#include "Gazprea/GazpreaOps.h"
#include "mlir/Pass/Pass.h"
#include <memory>

namespace mlir {
namespace gazprea {
#define GEN_PASS_DECL
#include "Gazprea/GazpreaPasses.h.inc"

#define GEN_PASS_REGISTRATION
#include "Gazprea/GazpreaPasses.h.inc"
} // namespace gazprea
} // namespace mlir

#endif
