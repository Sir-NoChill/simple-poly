// RUN: gazprea-opt %s --gazprea-to-standard > %t
// RUN: FileCheck %s < %t

module {
  // CHECK-LABEL: test_gazprea_add_op
  func.func @test_gazprea_add_op(%arg0: !gazprea.poly<5>, %arg1: !gazprea.poly<5>) -> !gazprea.poly<5> {
    // CHECK: arith.addi
    %0 = gazprea.add %arg0, %arg1 : (!gazprea.poly<5>, !gazprea.poly<5>) -> !gazprea.poly<5>
    return %0 : !gazprea.poly<5>
  }
}
