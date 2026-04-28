#pragma once

#include "base_iterator.h"
#include "concepts.h"

#include <iterator>
#include <memory>

template <CopyMoveAssignable T> class Set;

template <CopyMoveAssignable T> class ConstIterator : public BaseIterator<T>
{

  public:
    using pointer = std::shared_ptr<T>;
    using reference = T &;
    using value_type = T;
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;

    // Конструкторы
    ConstIterator() noexcept;
    explicit ConstIterator(const std::shared_ptr<typename Set<T>::SetNode> &node) noexcept;
    ConstIterator(const ConstIterator<T> &other);

    ~ConstIterator() override = default;

    void next() noexcept;
    operator bool() const noexcept;
    void checkExpired() const;

    // Операторы
    bool operator==(const ConstIterator<T> &other) const noexcept;
    bool operator!=(const ConstIterator<T> &other) const noexcept;

    ConstIterator<T> &operator=(const ConstIterator<T> &other) noexcept;
    ConstIterator<T> &operator=(ConstIterator<T> &&other) noexcept;

    const T &operator*() const;
    const std::shared_ptr<T> operator->() const;

    ConstIterator<T> operator+(int n) const noexcept;
    ConstIterator<T> &operator++() noexcept;
    ConstIterator<T> operator++(int) noexcept;

  private:
    typename Set<T>::SetNode &getCurr() const;
};

#include "const_iterator.hpp"
