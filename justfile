alias r := refresh

build:
	#!/bin/bash
	mkdir -p build
	pushd build
	cmake -G Ninja .. \
	  -DMLIR_DIR=$HOME/Code/llvm/llvm-test/lib/cmake/mlir \
	  -DLLVM_DIR=$HOME/Code/llvm/llvm-test/lib/cmake/llvm \
	  -DLLVM_EXTERNAL_LIT=/usr/local/bin/lit -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
	cmake --build . --target check-gazprea -j$(nproc)
	cp compile_commands.json ../

clean:
	rm -rf build

refresh: clean build
