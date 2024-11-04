add_mlir_dialect_library(MLIRGazprea
        GazpreaTypes.cpp
        GazpreaDialect.cpp
        GazpreaOps.cpp
        GazpreaPasses.cpp

        ADDITIONAL_HEADER_DIRS
        ${PROJECT_SOURCE_DIR}/include/Gazprea

        DEPENDS
        MLIRGazpreaOpsIncGen
        MLIRGazpreaPassesIncGen

        LINK_LIBS PUBLIC
        MLIRIR
        MLIRInferTypeOpInterface
        MLIRFuncDialect
        )
