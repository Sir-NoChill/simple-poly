//===- GazpreaOps.td - Gazprea dialect ops -----------*- tablegen -*-===//
//
// This file is licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef GAZPREA_OPS
#define GAZPREA_OPS

include "Gazprea/GazpreaTypes.td"
include "Gazprea/GazpreaDialect.td"
include "mlir/Interfaces/InferTypeOpInterface.td"
include "mlir/Interfaces/SideEffectInterfaces.td"

//===----------------------------------------------------------------------===//
// Base gazprea operation definition.
//===----------------------------------------------------------------------===//

class Gazprea_Op<string mnemonic, list<Trait> traits = []> :
        Op<Gazprea_Dialect, mnemonic, traits>;

def Gazprea_FooOp : Gazprea_Op<"foo", [Pure, SameOperandsAndResultType]> {
    let summary = "Illustrates how to define an operation.";
    let description = [{
        The `gazprea.foo` operation illustrates how to define a new
        operation in a dialect. It uses an operation trait to declare that it
        has no side effects.

        This operation takes an integer argument and returns an integer.

        Example:

        ```mlir
        %0 = arith.constant 2 : i32
        // Apply the foo operation to %0
        %1 = gazprea.foo %0 : i32
        ```
    }];

    let arguments = (ins I32:$input);
    let results = (outs I32:$res);

    let assemblyFormat = [{
        $input attr-dict `:` type($input)
    }];
}

class Gazprea_PolyBinOp<string mnemonic> : Gazprea_Op<mnemonic,
    [Pure] > {
  let arguments = (ins Gazprea_Polynomial:$lhs, Gazprea_Polynomial:$rhs);
  let results = (outs Gazprea_Polynomial:$out);
  let assemblyFormat = "$lhs `,` $rhs attr-dict `:` `(` type($lhs) `,` type($rhs) `)` `->` type($out)";
}

def Gazprea_AddOp : Gazprea_PolyBinOp<"add"> {
  let summary = "Simple add op for gazprea poly";
  let description = [{
    A simmple add op
  }];
}

def Gazprea_SubOp : Gazprea_PolyBinOp<"sub"> {
  let summary = "Simple subtraction op for gazprea poly";
  let description = [{
    A simmple add op
  }];
}

def Gazprea_MulOp : Gazprea_PolyBinOp<"mul"> {
  let summary = "Simple multiplication op for gazprea poly";
  let description = [{
    A simmple add op
  }];
}

def Gazprea_DivOp : Gazprea_PolyBinOp<"div"> {
  let summary = "Simple division op for gazprea poly";
  let description = [{
    A simmple add op
  }];
}

def Gazprea_EvalOp : Gazprea_Op<"eval", []> {
  let summary = "Evaluate a polynomial at a given input value";
  let description = [{ some description }];
  let arguments = (ins Gazprea_Polynomial:$input, AnyInteger:$point);
  let results = (outs AnyInteger:$output);
  let assemblyFormat = "$input `,` $point attr-dict `:` `(` type($input) `,` type($point) `)` `->` type($output)";
}

def Gazprea_FromTensorOp : Gazprea_Op<"from_tensor", []> {
  let summary = "Convert a list of coefficients to a polynomial";
  let description = [{ Some description }];
  let arguments = (ins TensorOf<[AnyInteger]>:$input);
  let results = (outs Gazprea_Polynomial:$output);
  let assemblyFormat = "$input attr-dict `:` type($input) `->` type($output)";
}

#endif // GAZPREA_OPS
