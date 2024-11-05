// RUN: gazprea-opt %s

module {
  func.func @main(%arg0: !gazprea.struct<!gazprea.poly<5> , i32>) -> !gazprea.struct<!gazprea.poly<5>, i32> {
    return %arg0 : !gazprea.struct<!gazprea.poly<5>, i32>
  }
}
