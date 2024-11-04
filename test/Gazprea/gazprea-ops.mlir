// RUN: gazprea-opt %s

module {
  func.func @test_gazprea_add_op(%arg0: !gazprea.gazpoly<5>, %arg1: !gazprea.gazpoly<5>) -> !gazprea.gazpoly<5> {
    // CHECK: gazprea.add
    %ret = gazprea.add %arg0, %arg1 : (!gazprea.gazpoly<5>, !gazprea.gazpoly<5>) -> !gazprea.gazpoly<5>
    return %ret : !gazprea.gazpoly<5>
  }

  func.func @test_gazprea_sub_op(%arg0: !gazprea.gazpoly<5>, %arg1: !gazprea.gazpoly<5>) -> !gazprea.gazpoly<5> {
    // CHECK: gazprea.sub
    %ret = gazprea.sub %arg0, %arg1 : (!gazprea.gazpoly<5>, !gazprea.gazpoly<5>) -> !gazprea.gazpoly<5>
    return %ret : !gazprea.gazpoly<5>
  }

  func.func @test_gazprea_mul_op(%arg0: !gazprea.gazpoly<5>, %arg1: !gazprea.gazpoly<5>) -> !gazprea.gazpoly<5> {
    // CHECK: gazprea.mul
    %ret = gazprea.mul %arg0, %arg1 : (!gazprea.gazpoly<5>, !gazprea.gazpoly<5>) -> !gazprea.gazpoly<5>
    return %ret : !gazprea.gazpoly<5>
  }

  func.func @test_gazprea_div_op(%arg0: !gazprea.gazpoly<5>, %arg1: !gazprea.gazpoly<5>) -> !gazprea.gazpoly<5> {
    // CHECK: gazprea.div
    %ret = gazprea.div %arg0, %arg1 : (!gazprea.gazpoly<5>, !gazprea.gazpoly<5>) -> !gazprea.gazpoly<5>
    return %ret : !gazprea.gazpoly<5>
  }
}
