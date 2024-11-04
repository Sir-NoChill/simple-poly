// RUN: mlir-opt %s --load-pass-plugin=%gazprea_libs/GazpreaPlugin%shlibext --pass-pipeline="builtin.module(gazprea-switch-bar-foo)" | FileCheck %s

module {
  // CHECK-LABEL: func @foo()
  func.func @bar() {
    return
  }

  // CHECK-LABEL: func @abar()
  func.func @abar() {
    return
  }
}
