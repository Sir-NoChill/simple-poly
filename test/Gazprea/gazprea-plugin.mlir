// RUN: mlir-opt %s --load-dialect-plugin=%gazprea_libs/GazpreaPlugin%shlibext --pass-pipeline="builtin.module(gazprea-switch-bar-foo)" | FileCheck %s

module {
  // CHECK-LABEL: func @foo()
  func.func @bar() {
    return
  }

  // CHECK-LABEL: func @gazprea_types(%arg0: !gazprea.custom<"10">)
  func.func @gazprea_types(%arg0: !gazprea.custom<"10">) {
    return
  }
}
