//===- GazpreaTypes.td - Gazprea dialect types -------*- tablegen -*-===//
//
// This file is licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef GAZPREA_TYPES
#define GAZPREA_TYPES

include "mlir/IR/AttrTypeBase.td"
include "Gazprea/GazpreaDialect.td"

//===----------------------------------------------------------------------===//
// Gazprea type definitions
//===----------------------------------------------------------------------===//

class Gazprea_Type<string name, string typeMnemonic, list<Trait> traits = []>
    : TypeDef<Gazprea_Dialect, name, traits> {
  let mnemonic = typeMnemonic;
}

def Gazprea_CustomType : Gazprea_Type<"Custom", "custom"> {
  let summary = "Gazprea custom type";
  let description = "Custom type in gazprea dialect";
  let parameters = (ins StringRefParameter<"the custom value">:$value);
  let assemblyFormat = "`<` $value `>`";
}

def Gazprea_Polynomial : Gazprea_Type<"GazPoly", "gazpoly"> {
  let summary = "Some polynomial";
  let description = [{
    A type for polynomials with some integer coefficients in
    a single variable polynomial ring
  }];

  // Add an attribute for overflow semantics
  let parameters = (ins "int":$degreeBound);
  let assemblyFormat = "`<`$degreeBound`>`";
}

#endif // GAZPREA_TYPES
