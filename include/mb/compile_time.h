#pragma once
#include <algorithm>
#include <array>
#include <string_view>

namespace mb {

template<typename std::array<char, 0>::size_type CSize>
struct const_string {
    using size_type = typename std::array<char, 0>::size_type;

    std::array<char, CSize> m_data;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "google-explicit-constructor"
    constexpr const_string(const char (&value)[CSize]) {
        std::copy_n(value, CSize, m_data.begin());
    }
#pragma clang diagnostic pop

    [[nodiscard]] constexpr auto begin() const {
        return m_data.begin();
    }

    [[nodiscard]] constexpr auto end() const {
        return m_data.end();
    }

    [[nodiscard]] constexpr bool operator==(const std::string_view other) const {
        if (other.size() != (CSize - 1))
            return false;
        return std::all_of(m_data.begin(), m_data.end(), [at = other.begin()](char c) mutable { return c == *(at++); });
    }

    template<size_type COtherSize>
    [[nodiscard]] constexpr bool operator==(const const_string<COtherSize>& other) const {
        if (COtherSize != CSize)
            return false;
        return std::all_of(begin(), end(), [at = other.begin()](char c) mutable { return c == *(at++); });
    }

    [[nodiscard]] constexpr std::string_view to_string_view() const {
        return std::string_view{m_data.data(), CSize - 1};
    }
};

template<typename TInt, mb::const_string CFirst, mb::const_string... COther>
std::optional<TInt> find_index(std::string_view pattern, TInt base = TInt{0}) {
    if (CFirst == pattern)
        return base;

    if constexpr (sizeof...(COther) > 0) {
        return find_index<TInt, COther...>(pattern, base + 1);
    } else {
        return std::nullopt;
    }
}

template<typename TInt, mb::const_string CFirst, mb::const_string... COther>
std::string_view const_string_from_index(TInt index = TInt{0}) {
    if (index == 0)
        return CFirst.to_string_view();

    if constexpr (sizeof...(COther) > 0) {
        return const_string_from_index<TInt, COther...>(index - 1);
    } else {
        return {};
    }
}

}