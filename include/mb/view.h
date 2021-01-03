#ifndef LIBMB_VIEW_H
#define LIBMB_VIEW_H
#include "int.h"
#include <vector>
#include <array>
#include <stdexcept>

namespace mb {

/*
 Basic array view class
*/
template<typename T>
class view {
    T *m_data;
    mb::size m_size;
public:
    view(T *data, mb::size size) : m_data(data), m_size(size) {}
    view(const std::vector<T> &vec) : m_data(const_cast<T *>(vec.data())), m_size(vec.size()) {}
    explicit view(const T &value) : m_data(&value), m_size(1) {}

    template<mb::size A_SZ>
    view(const std::array<T, A_SZ> &arr) : m_data(const_cast<T *>(arr.data())), m_size(A_SZ) {}

    [[nodiscard]] const T *data() const {
        return m_data;
    }

    [[nodiscard]] mb::size size() const {
        return m_size;
    }

    [[nodiscard]] const T &at(const mb::size p_index) const {
        if (p_index >= m_size) {
            throw std::runtime_error("index out of range");
        }
        return m_data[p_index];
    }

    [[nodiscard]] T &operator[](const mb::size p_index) {
        if (p_index >= m_size) {
            throw std::runtime_error("index out of range");
        }
        return m_data[p_index];
    }

    T &operator*() {
        return *m_data;
    }

    class iterator {
        T *m_at;
    public:
        typedef iterator self_type;
        typedef T value_type;
        typedef T& reference;
        typedef T* pointer;
        typedef std::forward_iterator_tag iterator_category;
        typedef mb::size difference_type;

        explicit iterator(T *at) : m_at(at) {}
        self_type operator++() {
            iterator tmp_it(*this);
            ++m_at;
            return tmp_it;
        }
        self_type operator++(int) {
            ++m_at;
            return *this;
        }
        reference operator*() {
            return *m_at;
        }
        pointer operator->() {
            return m_at;
        }
        bool operator==(const self_type &other) {
            return m_at == other.m_at;
        }
        bool operator!=(const self_type &other) {
            return m_at != other.m_at;
        }
    };

    [[nodiscard]] iterator begin() const {
        return iterator(m_data);
    }

    [[nodiscard]] iterator end() const {
        return iterator(m_data + m_size);
    }
};

}

#endif//LIBMB_VIEW_H
