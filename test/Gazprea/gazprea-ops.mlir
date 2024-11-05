// RUN: gazprea-opt %s > %t
// RUN: FileCheck %s < %t

module {
  func.func @test_gazprea_add_op(%arg0: !gazprea.poly<5>, %arg1: !gazprea.poly<5>) -> !gazprea.poly<5> {
    // CHECK: gazprea.add
    %0 = gazprea.add %arg0, %arg1 : (!gazprea.poly<5>, !gazprea.poly<5>) -> !gazprea.poly<5>

    // CHECK: gazprea.sub
    %1 = gazprea.sub %arg0, %arg1 : (!gazprea.poly<5>, !gazprea.poly<5>) -> !gazprea.poly<5>

    // CHECK: gazprea.mul
    %2 = gazprea.mul %arg0, %arg1 : (!gazprea.poly<5>, !gazprea.poly<5>) -> !gazprea.poly<5>

    // CHECK: gazprea.div
    %3 = gazprea.div %arg0, %arg1 : (!gazprea.poly<5>, !gazprea.poly<5>) -> !gazprea.poly<5>

    %4 = arith.constant dense<[1, 2, 3]> : tensor<3xi32>
    // CHECK: gazprea.from_tensor
    %5 = gazprea.from_tensor %4 : tensor<3xi32> -> !gazprea.poly<5>

    %6 = arith.constant 7 : i32
    // CHECK: gazprea.eval
    %7 = gazprea.eval %5, %6 : (!gazprea.poly<5>, i32) -> i32

    return %5 : !gazprea.poly<5>
  }
}
