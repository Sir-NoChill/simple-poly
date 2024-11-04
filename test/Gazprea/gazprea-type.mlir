// RUN: gazprea-opt %s

module {
  func.func @main(%arg0: !gazprea.gazpoly<5>) -> !gazprea.gazpoly<5> {
    return %arg0 : !gazprea.gazpoly<5>
  }
}
