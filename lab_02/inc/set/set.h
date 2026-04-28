#pragma once

#include "base_container.h"
#include "concepts"
#include "exceptions.h"
#include "const_iterator.h"
#include <initializer_list>

#include <compare>
#include <concepts>
#include <memory>

template <CopyMoveAssignable T>
class Set : public BaseContainer
{

public:

#pragma region Alianses
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using iterator = ConstIterator<value_type>;
    using const_iterator = ConstIterator<value_type>;
    using difference_type = ptrdiff_t;
    using size_type = size_t;
#pragma endregion

#pragma region Constructors
    Set() = default;

    template <Convertible<T> U>
    Set(const size_t size, const U *array); // на основе массива
    
    template <Convertible<T> U>
    Set(std::initializer_list<U> ilist); // по списку инициализации

    explicit Set(const Set<T> &other); // копирования
    Set(Set<T> &&other) noexcept; // переноса

    template <ConvertibleInputIterator<T> It, Sentinel<It> S>
    explicit Set(const It &begin, const S &end); // по итераторам

    template <ConvertibleContainer<T> C>
    explicit Set(const C &container); // от контейнера

    template <ConvertibleRange<T> R>
    explicit Set(const R &range); // от диапазона

#pragma endregion

    ~Set() override;

#pragma region Assignment
    // От множества
    template <Convertible<T> U>
    Set<T> &assign(const Set<U> &other);
    Set<T> &operator = (const Set<T> &other);

    template <Convertible<T> U>
    Set<T> &assign(Set<U> &&other) noexcept;
    Set<T> &operator = (Set<T> &&other) noexcept;

    // От списка инициализации
    template <Convertible<T> U>
    Set<T> &assign(std::initializer_list<U> ilist);
    template <Convertible<T> U>
    Set<T> &operator = (std::initializer_list<U> ilist);

    template <ConvertibleContainer<T> C>
    Set<T> &assign(const C &container);
    template <ConvertibleContainer<T> C>
    Set<T> &operator = (const C &container);

    // От контейнера
    template <ConvertibleContainer<T> C>
    Set<T> &assign(C &&container);
    template <ConvertibleContainer<T> C>
    Set<T> &operator = (C &&container);

    // От диапазона
    template <ConvertibleRange<T> R>
    Set<T> &assign(const R &range);
    template <ConvertibleRange<T> R>
    Set<T> &operator = (const R &range);

    template <ConvertibleRange<T> R>
    Set<T> &assign(R &&range);
    template <ConvertibleRange<T> R>
    Set<T> &operator=(R &&range);
#pragma endregion

#pragma region Functions

    // базовые функции
    template <Convertible<T> U>
    bool add(const U &value);

    template <Convertible<T> U>
    bool add(U &&value);

    template <EqualityComparable<T> U>
    bool in(const U &value) const noexcept;

    template <EqualityComparableInputIterator<T> It>
    bool in(const It &it) const noexcept;

    template <EqualityComparable<T> U>
    ConstIterator<T> find(const U &value) const;

    size_t size() const noexcept override;

    bool empty() const noexcept override;

    void clear() noexcept override;

    // удаление элемента
    template <EqualityComparable<T> U>
    bool erase(const U &value) noexcept;

    template <EqualityComparableInputIterator<T> It>
    bool erase(It &pos) noexcept;
#pragma endregion

#pragma region Iterators

    ConstIterator<T> begin() const noexcept;
    ConstIterator<T> end() const noexcept;
    ConstIterator<T> cbegin() const noexcept;
    ConstIterator<T> cend() const noexcept;

#pragma endregion

#pragma region MathOperations

    // Объединение
    template <HasCommon<T> U>
    Set<std::common_type_t<T, U>> make_union(const Set<U> &other) const;
    
    template <CommonContainer<T> C>
    Set<std::common_type_t<T, typename C::value_type>> make_union(const C &container) const;
    
    template <CommonRange<T> R>
    Set<std::common_type_t<T, typename std::ranges::range_value_t<R>>> make_union(const R &range) const;

    template <Convertible<T> U>
    Set<T> &unite(const Set<U> &other);

    template <ConvertibleContainer<T> C>
    Set<T> &unite(const C &container);

    template <ConvertibleRange<T> R>
    Set<T> &unite(const R &range);

    // Пересечение
    template <HasCommon<T> U>
    Set<std::common_type_t<T, U>> make_intersection(const Set<U> &other) const;
    
    template <CommonContainer<T> C>
    Set<std::common_type_t<T, typename C::value_type>> make_intersection(const C &container) const;
    
    template <CommonRange<T> R>
    Set<std::common_type_t<T, typename std::ranges::range_value_t<R>>> make_intersection(const R &range) const;
    
    template <Convertible<T> U>
    Set<T> &intersect(const Set<U> &other) noexcept;
    
    template <ConvertibleContainer<T> C>
    Set<T> &intersect(const C &container) noexcept;
    
    template <ConvertibleRange<T> R>
    Set<T> &intersect(const R &range) noexcept;

    // Разность
    template <HasCommon<T> U>
    Set<std::common_type_t<T, U>> make_difference(const Set<U> &other) const;
    template <CommonContainer<T> C>
    Set<std::common_type_t<T, typename C::value_type>> make_difference(const C &container) const;
    template <CommonRange<T> R>
    Set<std::common_type_t<T, typename std::ranges::range_value_t<R>>> make_difference(const R &range) const;

    template <Convertible<T> U>
    Set<T> &subtract(const Set<U> &other) noexcept;
    template <ConvertibleContainer<T> C>
    Set<T> &subtract(const C &container) noexcept;
    template <ConvertibleRange<T> R>
    Set<T> &subtract(const R &range) noexcept;

    // Симметрическая разость
    template <HasCommon<T> U>
    Set<std::common_type_t<T, U>> make_symm_difference(const Set<U> &other) const;
    
    template <CommonContainer<T> C>
    Set<std::common_type_t<T, typename C::value_type>> make_symm_difference(const C &container) const;
    
    template <CommonRange<T> R>
    Set<std::common_type_t<T, typename std::ranges::range_value_t<R>>> make_symm_difference(const R &range) const;

    template <Convertible<T> U>
    Set<T> &symm_subtract(const Set<U> &other);

    template <ConvertibleContainer<T> C>
    Set<T> &symm_subtract(const C &container);

    template <ConvertibleRange<T> R>
    Set<T> &symm_subtract(const R &range);

#pragma endregion

#pragma region MathOperators

    // +
    template <HasCommon<T> U>
    Set<std::common_type_t<T, U>> operator+(const Set<U> &other) const;
    template <CommonContainer<T> C>
    Set<std::common_type_t<T, typename C::value_type>> operator+(const C &container) const;
    template <CommonRange<T> R>
    Set<std::common_type_t<T, typename std::ranges::range_value_t<R>>> operator+(const R &range) const;

    // +=
    template <Convertible<T> U>
    Set<T> &operator+=(const Set<U> &other);
    template <ConvertibleContainer<T> C>
    Set<T> &operator+=(const C &container);
    template <ConvertibleRange<T> R>
    Set<T> &operator+=(const R &range);

    // |
    template <HasCommon<T> U>
    Set<std::common_type_t<T, U>> operator|(const Set<U> &other) const;
    template <CommonContainer<T> C>
    Set<std::common_type_t<T, typename C::value_type>> operator|(const C &container) const;
    template <CommonRange<T> R>
    Set<std::common_type_t<T, typename std::ranges::range_value_t<R>>> operator|(const R &range) const;

    // |=
    template <Convertible<T> U>
    Set<T> &operator|=(const Set<U> &other);
    template <ConvertibleContainer<T> C>
    Set<T> &operator|=(const C &container);
    template <ConvertibleRange<T> R>
    Set<T> &operator|=(const R &range);

    // &
    template <HasCommon<T> U>
    Set<std::common_type_t<T, U>> operator&(const Set<U> &other) const;
    template <CommonContainer<T> C>
    Set<std::common_type_t<T, typename C::value_type>> operator&(const C &container) const;
    template <CommonRange<T> R>
    Set<std::common_type_t<T, typename std::ranges::range_value_t<R>>> operator&(const R &range) const;

    // &=
    template <Convertible<T> U>
    Set<T> &operator&=(const Set<U> &other) noexcept;
    template <ConvertibleContainer<T> C>
    Set<T> &operator&=(const C &container) noexcept;
    template <ConvertibleRange<T> R>
    Set<T> &operator&=(const R &range) noexcept;

    // -
    template <HasCommon<T> U>
    Set<std::common_type_t<T, U>> operator-(const Set<U> &other) const;
    template <CommonContainer<T> C>
    Set<std::common_type_t<T, typename C::value_type>> operator-(const C &container) const;
    template <CommonRange<T> R>
    Set<std::common_type_t<T, typename std::ranges::range_value_t<R>>> operator-(const R &range) const;

    // -=
    template <Convertible<T> U>
    Set<T> &operator-=(const Set<U> &other) noexcept;
    template <ConvertibleContainer<T> C>
    Set<T> &operator-=(const C &container) noexcept;
    template <ConvertibleRange<T> R>
    Set<T> &operator-=(const R &range) noexcept;

    // ^
    template <HasCommon<T> U>
    Set<std::common_type_t<T, U>> operator^(const Set<U> &other) const;
    template <CommonContainer<T> C>
    Set<std::common_type_t<T, typename C::value_type>> operator^(const C &container) const;
    template <CommonRange<T> R>
    Set<std::common_type_t<T, typename std::ranges::range_value_t<R>>> operator^(const R &range) const;

    // ^=
    template <Convertible<T> U>
    Set<T> &operator^=(const Set<U> &other);
    template <ConvertibleContainer<T> C>
    Set<T> &operator^=(const C &container);
    template <ConvertibleRange<T> R>
    Set<T> &operator^=(const R &range);

#pragma endregion

#pragma region CompareOperators

    // <=>
    template <EqualityComparable<T> U>
    std::partial_ordering operator<=>(const Set<U> &other) const noexcept;
    template <EqualityComparableContainer<T> C>
    std::partial_ordering operator<=>(const C &container) const noexcept;
    template <EqualityComparableRange<T> R>
    std::partial_ordering operator<=>(const R &range) const noexcept;

    // ==
    template <EqualityComparable<T> U>
    bool operator==(const Set<U> &other) const noexcept;
    template <EqualityComparableContainer<T> C>
    bool operator==(const C &container) const noexcept;
    template <EqualityComparableRange<T> R>
    bool operator==(const R &range) const noexcept;


#pragma endregion

#pragma region CompareFunctions

    // Пересекаются
    template <EqualityComparable<T> U>
    bool comparable(const Set<U> &other) const noexcept;
    template <EqualityComparableContainer<T> C>
    bool comparable(const C &container) const noexcept;
    template <EqualityComparableRange<T> R>
    bool comparable(const R &range) const noexcept;

    // Не пересекаются
    template <EqualityComparable<T> U>
    bool nonComparable(const Set<U> &other) const noexcept;
    template <EqualityComparableContainer<T> C>
    bool nonComparable(const C &container) const noexcept;
    template <EqualityComparableRange<T> R>
    bool nonComparable(const R &range) const noexcept;

    // Является ли подмножеством
    template <EqualityComparable<T> U>
    bool subsetOf(const Set<U> &other) const noexcept;
    template <EqualityComparableContainer<T> C>
    bool subsetOf(const C &container) const noexcept;
    template <EqualityComparableRange<T> R>
    bool subsetOf(const R &range) const noexcept;

    // Является ли надмножеством
    template <EqualityComparable<T> U>
    bool supersetOf(const Set<U> &other) const noexcept;
    template <EqualityComparableContainer<T> C>
    bool supersetOf(const C &container) const noexcept;
    template <EqualityComparableRange<T> R>
    bool supersetOf(const R &range) const noexcept;

    // Строгое подмножество
    template <EqualityComparable<T> U>
    bool less(const Set<U> &other) const noexcept;
    template <EqualityComparableContainer<T> C>
    bool less(const C &container) const noexcept;
    template <EqualityComparableRange<T> R>
    bool less(const R &range) const noexcept;

    // Нестрогое подмножество(включая равенство)
    template <EqualityComparable<T> U>
    bool lessOrEqual(const Set<U> &other) const noexcept;
    template <EqualityComparableContainer<T> C>
    bool lessOrEqual(const C &container) const noexcept;
    template <EqualityComparableRange<T> R>
    bool lessOrEqual(const R &range) const noexcept;

    // Строгое надмножество
    template <EqualityComparable<T> U>
    bool greater(const Set<U> &other) const noexcept;
    template <EqualityComparableContainer<T> C>
    bool greater(const C &container) const noexcept;
    template <EqualityComparableRange<T> R>
    bool greater(const R &range) const noexcept;

    // Нестрогое надмножество(включая равенство)
    template <EqualityComparable<T> U>
    bool greaterOrEqual(const Set<U> &other) const noexcept;
    template <EqualityComparableContainer<T> C>
    bool greaterOrEqual(const C &container) const noexcept;
    template <EqualityComparableRange<T> R>
    bool greaterOrEqual(const R &range) const noexcept;

    // Полное равенство
    template <EqualityComparable<T> U>
    bool equal(const Set<U> &other) const noexcept;
    template <EqualityComparableContainer<T> C>
    bool equal(const C &container) const noexcept;
    template <EqualityComparableRange<T> R>
    bool equal(const R &range) const noexcept;

    // Полное неравенство
    template <EqualityComparable<T> U>
    bool notEqual(const Set<U> &other) const noexcept;
    template <EqualityComparableContainer<T> C>
    bool notEqual(const C &container) const noexcept;
    template <EqualityComparableRange<T> R>
    bool notEqual(const R &range) const noexcept;

#pragma endregion


#pragma region SetNode
protected:

    class SetNode : public std::enable_shared_from_this<SetNode>
    {
    private:
        T data;
        std::shared_ptr<SetNode> next;

        // Конструкторы
        explicit SetNode(const T &value) noexcept;
        explicit SetNode(T &&value) noexcept;
        SetNode(const std::shared_ptr<SetNode> next, const T &value) noexcept;

    public:
        SetNode() = delete;
        SetNode(const SetNode &other) = delete;
        SetNode(SetNode &&other) = delete;

        template <typename... Args>
        static std::shared_ptr<SetNode> create(Args &&...params);

        ~SetNode() = default;

        void set(const T &value) noexcept;
        void setNull() noexcept;

        void setNext(const SetNode &node);
        void setNext(const std::shared_ptr<SetNode> &node) noexcept;
        void setNextNull() noexcept;

        const T &value() const noexcept;
        std::shared_ptr<T> get();

        std::shared_ptr<SetNode> getNext() const noexcept;

        bool operator==(const std::shared_ptr<SetNode> &other) const noexcept;
    };

#pragma endregion

    bool add(const std::shared_ptr<SetNode> &node);

#pragma region Friends
    friend class BaseIterator<T>;
    friend class ConstIterator<T>;
#pragma endregion

private:
    std::shared_ptr<SetNode> head;
    std::shared_ptr<SetNode> tail;
};

#include "set.hpp"
#include "set_node.hpp"