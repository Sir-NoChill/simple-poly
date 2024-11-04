add_llvm_library(GazpreaPlugin
        # BUILDTREE_ONLY is only for testing purposes
        MODULE BUILDTREE_ONLY
        gazprea-plugin.cpp

        DEPENDS
        MLIRGazprea
        PLUGIN_TOOL
        mlir-opt

        LINK_LIBS
	MLIRGazprea
        )
target_include_directories(
        GazpreaPlugin
        PRIVATE
        "${GAZPREA_BINARY_DIR}/include"
)
