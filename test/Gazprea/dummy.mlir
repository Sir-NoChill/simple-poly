// RUN: gazprea-opt %s | gazprea-opt | FileCheck %s

module {
    // CHECK-LABEL: func @bar()
    func.func @bar() {
        %0 = arith.constant 1 : i32
        // CHECK: %{{.*}} = gazprea.foo %{{.*}} : i32
        %res = gazprea.foo %0 : i32
        return
    }

    // CHECK-LABEL: func @gazprea_types(%arg0: !gazprea.custom<"10">)
    func.func @gazprea_types(%arg0: !gazprea.custom<"10">) {
        return
    }
}
