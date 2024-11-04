get_property(dialect_libs GLOBAL PROPERTY MLIR_DIALECT_LIBS)
get_property(conversion_libs GLOBAL PROPERTY MLIR_CONVERSION_LIBS)
set(LIBS
        ${dialect_libs}
        ${conversion_libs}
        MLIRArithDialect
        MLIROptLib
        MLIRGazprea
        )
add_llvm_executable(gazprea-opt gazprea-opt.cpp)

llvm_update_compile_flags(gazprea-opt)
target_link_libraries(gazprea-opt PRIVATE ${LIBS})

mlir_check_all_link_libraries(gazprea-opt)
