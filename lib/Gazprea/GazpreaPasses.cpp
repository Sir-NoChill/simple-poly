//===- GazpreaPasses.cpp - Gazprea passes -----------------*- C++ -*-===//
//
// This file is licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/IR/PatternMatch.h"
#include "mlir/Rewrite/FrozenRewritePatternSet.h"
#include "mlir/Support/LogicalResult.h"
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
struct GazpreaToStandard : impl::GazpreaToStandardBase<GazpreaToStandard> {
  using GazpreaToStandardBase::GazpreaToStandardBase;

  void runOnOperation() override {
    MLIRContext *context = &getContext();
    auto *module = getOperation();
  }
};
} // namespace mlir::gazprea
