//===- GazpreaTypes.h - Gazprea dialect types -------------*- C++ -*-===//
//
// This file is licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef GAZPREA_GAZPREATYPES_H
#define GAZPREA_GAZPREATYPES_H

#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/TypeRange.h"

namespace mlir {
    namespace gazprea {
        namespace detail {
            struct StructureTypeStorage;
        }
    }
}

#define GET_TYPEDEF_CLASSES
#include "Gazprea/GazpreaOpsTypes.h.inc"
#include "llvm/Support/TrailingObjects.h"

namespace mlir {
namespace gazprea {
namespace detail {

/// A type representing a collection of other types.
struct StructureTypeStorage final
    : public TypeStorage,
      public llvm::TrailingObjects<StructureTypeStorage, Type> {
  using KeyTy = TypeRange;

  StructureTypeStorage(unsigned numTypes) : numElements(numTypes) {}

  /// Construction.
  static StructureTypeStorage *construct(TypeStorageAllocator &allocator,
                                     TypeRange key) {
    // Allocate a new storage instance.
    auto byteSize = StructureTypeStorage::totalSizeToAlloc<Type>(key.size());
    auto *rawMem = allocator.allocate(byteSize, alignof(StructureTypeStorage));
    auto *result = ::new (rawMem) StructureTypeStorage(key.size());

    // Copy in the element types into the trailing storage.
    std::uninitialized_copy(key.begin(), key.end(),
                            result->getTrailingObjects<Type>());
    return result;
  }

  bool operator==(const KeyTy &key) const { return key == getTypes(); }

  /// Return the number of held types.
  unsigned size() const { return numElements; }

  /// Return the held types.
  ArrayRef<Type> getTypes() const {
    return {getTrailingObjects<Type>(), size()};
  }

  KeyTy getAsKey() const { return getTypes(); }

  /// The number of tuple elements.
  unsigned numElements;
};
}
}
}

#endif // GAZPREA_GAZPREATYPES_H
