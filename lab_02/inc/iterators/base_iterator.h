#pragma once

#include "concepts.h"

#include <iterator>
#include <memory>

template <CopyMoveAssignable T> class Set;

template <CopyMoveAssignable T> class BaseIterator
{
  public:
    BaseIterator() = default;
    virtual ~BaseIterator() = 0;

  protected:
    std::weak_ptr<typename Set<T>::SetNode> curr;
    friend class Set<T>;
};
