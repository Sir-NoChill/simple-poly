add_mlir_dialect(GazpreaOps gazprea)
add_mlir_doc(GazpreaDialect GazpreaDialect Gazprea/ -gen-dialect-doc)
add_mlir_doc(GazpreaOps GazpreaOps Gazprea/ -gen-op-doc)

set(LLVM_TARGET_DEFINITIONS GazpreaPasses.td)
mlir_tablegen(GazpreaPasses.h.inc --gen-pass-decls)
add_public_tablegen_target(MLIRGazpreaPassesIncGen)
