#ifndef LIBMB_VECTOR_H
#define LIBMB_VECTOR_H
#include <algorithm>
#include <vector>
#include <cstdint>
#include <functional>

namespace mb {

template<typename TIterator>
struct slice {
    TIterator from, to;
    using difference_type = ssize_t;

    [[nodiscard]] constexpr TIterator begin() const {
        return from;
    }

    [[nodiscard]] constexpr TIterator end() const {
        return to;
    }

    template<typename TDest, typename TFunc>
    constexpr void transform(TDest dest, TFunc &&func) const {
        std::transform(begin(), end(), dest.begin(), func);
    }

    slice<TIterator> sub(difference_type from, difference_type to) {
        return {iterator_index(this->begin(), this->end(), from), iterator_index(this->begin(), this->end(), to)};
    }

    slice<TIterator> sub(difference_type from) {
        return {iterator_index(this->begin(), this->end(), from), this->end()};
    }

    slice<TIterator> sub() {
        return {this->begin(), this->end()};
    }
};

template<typename TIterator, typename TDifference>
constexpr TIterator iterator_index(TIterator beg, TIterator end, TDifference index) {
    if (index >= 0) {
        return beg + index;
    }
    return end + index;
}

template<typename TValue, typename TAlloc = std::allocator<TValue>>
class vector : public std::vector<TValue, TAlloc> {
public:
    using value_type = TValue;
    using iterator = typename std::vector<TValue>::iterator;
    using difference_type = typename std::vector<TValue>::difference_type;
    using size_type = typename std::vector<TValue>::size_type;
    using allocator_type = TAlloc;

    vector() = default;

    explicit vector(const allocator_type &allocator) noexcept
        : std::vector<TValue, TAlloc>(allocator) {}

    explicit vector(size_type count, const allocator_type &allocator = allocator_type())
        : std::vector<TValue, TAlloc>(count, allocator) {}

    vector(size_type count, const value_type &value,
           const allocator_type &allocator = allocator_type())
        : std::vector<TValue, TAlloc>(count, value, allocator) {}

    template<typename... TArgs>
    vector(TArgs... args) : std::vector<TValue, TAlloc>{args...} {}

    operator slice<iterator>() {
        return {this->begin(), this->end()};
    }

    slice<iterator> sub(difference_type from, difference_type to) {
        return {iterator_index(this->begin(), this->end(), from), iterator_index(this->begin(), this->end(), to)};
    }

    slice<iterator> sub(difference_type from) {
        return {iterator_index(this->begin(), this->end(), from), this->end()};
    }

    slice<iterator> sub() {
        return {this->begin(), this->end()};
    }

    template<typename TFunc>
    constexpr auto transform(TFunc &&func) -> vector<decltype(func(value_type()))> {
        vector<decltype(func(value_type()))> result(this->size());
        std::transform(this->begin(), this->end(), result.begin(), func);
        return result;
    }
};

template<typename TSource, typename TDest, typename TFunc>
void transform(TSource source, TDest dest, TFunc &&func) {
    std::transform(source.begin(), source.end(), dest.begin(), func);
}

}// namespace mb

#endif//LIBMB_VECTOR_H
