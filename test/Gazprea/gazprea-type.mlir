// RUN: gazprea-opt %s

module {
  func.func @main(%arg0: !gazprea.poly<5>) -> !gazprea.poly<5> {
    return %arg0 : !gazprea.poly<5>
  }
}
