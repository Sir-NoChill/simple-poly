// RUN: gazprea-opt --loop-invariant-code-motion %s > %t
// RUN: FileCheck %s < %t

module {
  // CHECK-LABEL: func.func @test_loop_invariant_code_motion
  func.func @test_loop_invariant_code_motion() -> !gazprea.poly<10> {
    %0 = arith.constant dense<[1, 2, 3]> : tensor<3xi32>
    %p0 = gazprea.from_tensor %0 : tensor<3xi32> -> !gazprea.poly<10>

    %1 = arith.constant dense<[9, 8, 16]> : tensor<3xi32>
    %p1 = gazprea.from_tensor %1 : tensor<3xi32> -> !gazprea.poly<10>
    // CHECK: gazprea.mul

    // CHECK: affine.for
    %ret_val = affine.for %i = 0 to 100 iter_args(%sum_iter = %p0) -> !gazprea.poly<10> {
      // The poly.mul should be hoisted out of the loop.
      // CHECK-NOT: gazprea.mul
      %2 = gazprea.mul %p0, %p1 : (!gazprea.poly<10>, !gazprea.poly<10>) -> !gazprea.poly<10>
      %sum_next = gazprea.add %sum_iter, %2 : (!gazprea.poly<10>, !gazprea.poly<10>) -> !gazprea.poly<10>
      affine.yield %sum_next : !gazprea.poly<10>
    }

    return %ret_val : !gazprea.poly<10>
  }
}
