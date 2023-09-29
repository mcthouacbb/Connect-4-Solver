#pragma once

#include <type_traits>
#include <cstddef>
#include <array>

template<typename T>
struct HistoryEntry
{
public:
    static_assert(std::is_integral_v<T>, "T must be an integral type");

    HistoryEntry& operator=(const T& t)
    {
        m_Value = t;
        return *this;
    }

    operator const T&() const
    {
        return m_Value;
    }

    void update(int bonus)
    {
        m_Value += bonus;
    }
private:
    T m_Value;
};

template<typename T, int Size, int... Sizes>
struct History
{
public:
    using ElemType = History<T, Sizes...>;
    void fill(T value)
    {
        for (auto& elem : m_Elems)
            elem.fill(value);
    }

    ElemType& operator[](size_t pos)
    {
        return m_Elems[pos];
    }

    const ElemType& operator[](size_t pos) const
    {
        return m_Elems[pos];
    }
private:
    std::array<ElemType, Size> m_Elems;
};

template<typename T, int Size>
struct History<T, Size>
{
public:
    using Elem = HistoryEntry<T>;
    void fill(T value)
    {
        for (auto& elem : m_Elems)
            elem = value;
    }

    Elem& operator[](size_t pos)
    {
        return m_Elems[pos];
    }

    const Elem& operator[](size_t pos) const
    {
        return m_Elems[pos];
    }
private:
    std::array<Elem, Size> m_Elems;
};

using ColorToHistory = History<int, 2, 56>;
