#pragma once

#include "base_iterator.h"
#include "concepts.h"
#include "const_iterator.h"
#include "exceptions.h"

template <CopyMoveAssignable T> BaseIterator<T>::~BaseIterator()
{
}

#pragma region Constructors

template <CopyMoveAssignable T> ConstIterator<T>::ConstIterator() noexcept
{
    this->curr.lock() = nullptr;
}

template <CopyMoveAssignable T>
ConstIterator<T>::ConstIterator(const std::shared_ptr<typename Set<T>::SetNode> &node) noexcept
{
    this->curr = node;
}

template <CopyMoveAssignable T> ConstIterator<T>::ConstIterator(const ConstIterator<T> &other)
{
    other.checkExpired();
    this->curr = other.curr.lock();
}

#pragma endregion

template <CopyMoveAssignable T> typename Set<T>::SetNode &ConstIterator<T>::getCurr() const
{
    this->checkExpired();

    return *this->curr.lock();
}

template <CopyMoveAssignable T> void ConstIterator<T>::next() noexcept
{
    if (!this->curr.expired() && this->curr.lock() != nullptr)
        this->curr = this->getCurr().getNext();
}

template <CopyMoveAssignable T> void ConstIterator<T>::checkExpired() const
{
    if (this->curr.expired() && this->curr.lock())
        throw new IteratorException("Итератор истек");
}

#pragma region Operators

template <CopyMoveAssignable T> ConstIterator<T> &ConstIterator<T>::operator++() noexcept
{
    this->next();
    return *this;
}

template <CopyMoveAssignable T> ConstIterator<T> ConstIterator<T>::operator++(int) noexcept
{
    ConstIterator<T> iter = *this;
    this->next();
    return iter;
}

template <CopyMoveAssignable T> ConstIterator<T> ConstIterator<T>::operator+(int n) const noexcept
{
    ConstIterator<T> iter = *this;
    while (n-- > 0)
        ++iter;

    return iter;
}

template <CopyMoveAssignable T> ConstIterator<T>::operator bool() const noexcept
{
    return !this->curr.expired() && this->curr.lock() != nullptr;
}

template <CopyMoveAssignable T> ConstIterator<T> &ConstIterator<T>::operator=(const ConstIterator<T> &other) noexcept
{
    this->curr = other.curr.lock();
    return *this;
}

template <CopyMoveAssignable T> ConstIterator<T> &ConstIterator<T>::operator=(ConstIterator<T> &&other) noexcept
{
    this->curr = std::move(other.curr.lock());
    return *this;
}

template <CopyMoveAssignable T> const T &ConstIterator<T>::operator*() const
{
    this->checkExpired();
    return getCurr().value();
}

template <CopyMoveAssignable T> const std::shared_ptr<T> ConstIterator<T>::operator->() const
{
    this->checkExpired();

    return this->curr.lock()->get();
}

template <CopyMoveAssignable T> bool ConstIterator<T>::operator==(const ConstIterator<T> &other) const noexcept
{
    return this->curr.lock() == other.curr.lock();
}

template <CopyMoveAssignable T> bool ConstIterator<T>::operator!=(const ConstIterator<T> &other) const noexcept
{
    return this->curr.lock() != other.curr.lock();
}

#pragma endregion
