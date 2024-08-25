#pragma once

#include <iostream>

template <typename T>
class DynamicArray
{
private:
    T *m_data;
    size_t m_len;
    size_t m_cap;
    static constexpr size_t REALLOC_SIZE = 8;

public:
    static constexpr size_t NPOS = ULLONG_MAX;

    DynamicArray()
    {
        m_len = 0;
        m_cap = REALLOC_SIZE;
        m_data = new T[REALLOC_SIZE];
    }

    ~DynamicArray()
    {
        delete[] m_data;
    }

    constexpr inline bool is_empty() noexcept
    {
        return m_len == 0;
    }

    inline void push(const T value) noexcept
    {
        if (m_len >= m_cap)
            reserve(m_cap + REALLOC_SIZE);

        m_data[m_len++] = value;
    }

    inline T get(const size_t idx) const
    {
        if (idx > m_len - 1)
            throw std::out_of_range("Index out of range.");

        return m_data[idx];
    }

    inline void set(const size_t idx, const T new_value)
    {
        if (idx > m_len - 1)
            throw std::out_of_range("Index out of range.");

        m_data[idx] = new_value;
    }

    inline T pop(size_t idx = ULLONG_MAX)
    {
        if (idx != ULLONG_MAX && idx > m_len - 1)
            throw std::out_of_range("Index out of range.");

        if (idx == ULLONG_MAX)
            idx = m_len;

        T el = m_data[idx];
        for (size_t i = idx; i < m_len; i++)
        {
            m_data[i] = m_data[i + 1];
        }
        m_len--;

        return el;
    }

    inline void insert(const T item, const size_t &idx) noexcept
    {
        if (m_len >= m_cap)
            reserve(m_cap + REALLOC_SIZE);

        T *old_data = new T[m_len];
        for (size_t i = 0; i < m_len; i++)
        {
            old_data[i] = m_data[i];
        }

        for (size_t i = idx; i < m_len; i++)
        {
            m_data[i + 1] = old_data[i];
        }

        m_data[idx] = item;
        m_len++;

        delete[] old_data;
    }

    inline size_t search(const T &item) const noexcept
    {
        for (size_t i = 0; i < m_len; i++)
        {
            if (m_data[i] == item)
                return i;
        }

        return NPOS;
    }

    inline T operator[](const size_t idx) const
    {
        return get(idx);
    }

    inline void reserve(const size_t new_capacity) noexcept
    {
        if (m_cap >= new_capacity)
            return;

        resize(new_capacity);
    }

    inline size_t get_capacity() const noexcept
    {
        return m_cap;
    }

    inline size_t get_length() const noexcept
    {
        return m_len;
    }

private:
    inline void resize(const size_t new_capacity) noexcept
    {
        T *old_data = new T[new_capacity];
        for (size_t i = 0; i < m_len; i++)
        {
            old_data[i] = m_data[i];
        }

        delete[] m_data;

        m_data = old_data;
        m_cap = new_capacity;
    }
};