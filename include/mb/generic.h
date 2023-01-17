#ifndef LIBMB_GENERIC_H
#define LIBMB_GENERIC_H
#include <vector>

namespace mb {

template<typename T, typename ...ARGS>
void as_vector_internal(std::vector<T> &vec, T &&first, ARGS &&...args) {
    vec.emplace_back(std::forward<T>(first));
    if (sizeof...(ARGS) != 0) {
        as_vector_internal(vec, args...);
    }
}

template<typename T, typename ...ARGS>
std::vector<T> as_vector(ARGS &&...args) {
    std::vector<T> out_vec;
    out_vec.reserve(sizeof...(ARGS));
    as_vector_internal(out_vec, args...);
    return out_vec;
}

template<typename T, typename ARG, typename ...ARGS>
void as_vector_copy_internal(std::vector<T> &vec, const ARG &first, const ARGS &...args) {
    vec.emplace_back(first.copy());
    if constexpr (sizeof...(ARGS) != 0) {
        as_vector_copy_internal<T, ARG>(vec, args...);
    }
}

template<typename T, typename ARG, typename ...ARGS>
std::vector<T> as_vector_copy(const ARGS &...args) {
    std::vector<T> out_vec;
    out_vec.reserve(sizeof...(ARGS));
    if constexpr (sizeof...(ARGS) != 0) {
        as_vector_copy_internal<T, ARG>(out_vec, args...);
    }
    return out_vec;
}

}

#endif//LIBMB_GENERIC_H
