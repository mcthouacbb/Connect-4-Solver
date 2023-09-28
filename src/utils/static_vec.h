#pragma once

#include <array>
#include <cassert>
#include <cstddef>

template<typename T, size_t S>
class StaticVector
{
public:
    StaticVector();

    T& operator[](size_t pos);
    const T& operator[](size_t pos) const;

    constexpr auto begin() noexcept;
    constexpr auto cbegin() const noexcept;

    constexpr auto end() noexcept;
    constexpr auto cend() const noexcept;

    size_t size() const;

    constexpr void push_back(const T& value);
    constexpr void push_back(T&& value);
private:
    std::array<T, S> m_Data;
    uint32_t m_Size;
};

template<typename T, size_t S>
StaticVector<T, S>::StaticVector()
    : m_Data(), m_Size(0)
{

}

template<typename T, size_t S>
inline T& StaticVector<T, S>::operator[](size_t pos)
{
    return m_Data[pos];
}

template<typename T, size_t S>
inline const T& StaticVector<T, S>::operator[](size_t pos) const
{
    return m_Data[pos];
}

template<typename T, size_t S>
constexpr auto StaticVector<T, S>::begin() noexcept
{
    return m_Data.begin();
}

template<typename T, size_t S>
constexpr auto StaticVector<T, S>::cbegin() const noexcept
{
    return m_Data.cbegin();
}

template<typename T, size_t S>
constexpr auto StaticVector<T, S>::end() noexcept
{
    return m_Data.begin() + m_Size;
}

template<typename T, size_t S>
constexpr auto StaticVector<T, S>::cend() const noexcept
{
    return m_Data.cend();
}

template<typename T, size_t S>
inline size_t StaticVector<T, S>::size() const
{
    return m_Size;
}

template<typename T, size_t S>
constexpr void StaticVector<T, S>::push_back(const T& value)
{
    assert(m_Size < S);
    m_Data[m_Size++] = value;
}

template<typename T, size_t S>
constexpr void StaticVector<T, S>::push_back(T&& value)
{
    assert(m_Size < S);
    m_Data[m_Size++] = std::move(value);
}
