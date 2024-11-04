llvm_canonicalize_cmake_booleans(
        MLIR_ENABLE_BINDINGS_PYTHON
)

configure_lit_site_cfg(
        ${CMAKE_CURRENT_SOURCE_DIR}/lit.site.cfg.py.in
        ${CMAKE_CURRENT_BINARY_DIR}/lit.site.cfg.py
        MAIN_CONFIG
        ${CMAKE_CURRENT_SOURCE_DIR}/lit.cfg.py
)

set(GAZPREA_TEST_DEPENDS
        FileCheck count not
        gazprea-opt
        gazprea-translate
        GazpreaPlugin
        )
if(MLIR_ENABLE_BINDINGS_PYTHON)
  list(APPEND GAZPREA_TEST_DEPENDS StandalonePythonModules)
endif()

add_lit_testsuite(check-gazprea "Running the gazprea regression tests"
        ${CMAKE_CURRENT_BINARY_DIR}
        DEPENDS ${GAZPREA_TEST_DEPENDS}
        )
set_target_properties(check-gazprea PROPERTIES FOLDER "Tests")

add_lit_testsuites(GAZPREA ${CMAKE_CURRENT_SOURCE_DIR} DEPENDS ${GAZPREA_TEST_DEPENDS})

