# RUN: %python %s | FileCheck %s

from mlir_gazprea.ir import *
from mlir_gazprea.dialects import builtin as builtin_d, gazprea as gazprea_d

with Context():
    gazprea_d.register_dialect()
    module = Module.parse(
        """
    %0 = arith.constant 2 : i32
    %1 = gazprea.foo %0 : i32
    """
    )
    # CHECK: %[[C:.*]] = arith.constant 2 : i32
    # CHECK: gazprea.foo %[[C]] : i32
    print(str(module))
