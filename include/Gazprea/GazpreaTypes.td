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

def Gazprea_Polynomial : Gazprea_Type<"Polynomial", "poly"> {
  let summary = "Some polynomial";
  let description = [{
    A type for polynomials with some integer coefficients in
    a single variable polynomial ring
  }];

  // Add an attribute for overflow semantics
  let parameters = (ins "int":$degreeBound);
  let assemblyFormat = "`<` $degreeBound `>`";
}

def Gazprea_Struct : Gazprea_Type<"Structure", "struct"> {
  let summary = "A collection of arbitrary typed elements";
  let description = [{ some description }];
  let parameters = (ins ArrayRefParameter<"Type">:$types);
  let builders = [
    TypeBuilder<(ins "TypeRange":$elementTypes), [{
      return $_get($_ctxt, elementTypes);
    }]>
  ];
  let skipDefaultBuilders = 1;
  let genStorageClass = 0;
  let extraClassDeclaration = [{
    /// Accumulate the types contained in this tuple and tuples nested within
    /// it. Note that this only flattens nested tuples, not any other container
    /// type, e.g. a tuple<i32, tensor<i32>, tuple<f32, tuple<i64>>> is
    /// flattened to (i32, tensor<i32>, f32, i64)
    void getFlattenedTypes(SmallVectorImpl<Type> &types);

    /// Return the number of held types.
    size_t size() const;

    /// Iterate over the held elements.
    using iterator = ArrayRef<Type>::iterator;
    iterator begin() const { return getTypes().begin(); }
    iterator end() const { return getTypes().end(); }

    /// Return the element type at index 'index'.
    Type getType(size_t index) const {
      assert(index < size() && "invalid index for tuple type");
      return getTypes()[index];
    }
  }];
  let assemblyFormat = "`<` $types `>`";
  // let hasCustomAssemblyFormat = 1;
}

#endif // GAZPREA_TYPES
