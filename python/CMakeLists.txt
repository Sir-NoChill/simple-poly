include(AddMLIRPython)

# Specifies that all MLIR packages are co-located under the `mlir_gazprea`
# top level package (the API has been embedded in a relocatable way).
# TODO: Add an upstream cmake param for this vs having a global here.
add_compile_definitions("MLIR_PYTHON_PACKAGE_PREFIX=mlir_gazprea.")


################################################################################
# Sources
################################################################################

declare_mlir_python_sources(StandalonePythonSources)

declare_mlir_dialect_python_bindings(
  ADD_TO_PARENT StandalonePythonSources
  ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/mlir_gazprea"
  TD_FILE dialects/StandaloneOps.td
  SOURCES
    dialects/gazprea.py
  DIALECT_NAME gazprea)

declare_mlir_python_extension(StandalonePythonSources.Extension
  MODULE_NAME _gazpreaDialects
  ADD_TO_PARENT StandalonePythonSources
  SOURCES
    StandaloneExtension.cpp
  EMBED_CAPI_LINK_LIBS
    StandaloneCAPI
)

################################################################################
# Common CAPI
################################################################################

add_mlir_python_common_capi_library(StandalonePythonCAPI
  INSTALL_COMPONENT StandalonePythonModules
  INSTALL_DESTINATION python_packages/gazprea/mlir_gazprea/_mlir_libs
  OUTPUT_DIRECTORY "${MLIR_BINARY_DIR}/python_packages/gazprea/mlir_gazprea/_mlir_libs"
  RELATIVE_INSTALL_ROOT "../../../.."
  DECLARED_SOURCES
    StandalonePythonSources
    # TODO: Remove this in favor of showing fine grained registration once
    # available.
    MLIRPythonExtension.RegisterEverything
    MLIRPythonSources.Core
)

################################################################################
# Instantiation of all Python modules
################################################################################

add_mlir_python_modules(StandalonePythonModules
  ROOT_PREFIX "${MLIR_BINARY_DIR}/python_packages/gazprea/mlir_gazprea"
  INSTALL_PREFIX "python_packages/gazprea/mlir_gazprea"
  DECLARED_SOURCES
    StandalonePythonSources
    # TODO: Remove this in favor of showing fine grained registration once
    # available.
    MLIRPythonExtension.RegisterEverything
    MLIRPythonSources
  COMMON_CAPI_LINK_LIBS
    StandalonePythonCAPI
  )
