#pragma once
#include "compile_time.h"
#include <string_view>
#include <type_traits>
#include <optional>

namespace mb {

template<typename TUnder, const_string... Fields>
class enum_wrapper {
public:
    using wrapped_type = TUnder;
    using underlying_type = std::underlying_type_t<wrapped_type>;

    constexpr enum_wrapper() : m_value(wrapped_type{}) {}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "google-explicit-constructor"
    constexpr enum_wrapper(wrapped_type index) : m_value(index) {}
#pragma clang diagnostic pop

    static constexpr std::optional<wrapped_type> from_string(const std::string_view identifier) {
        if constexpr (sizeof...(Fields) == 0) {
            return std::nullopt;
        } else {
            auto index = find_index<underlying_type, Fields...>(identifier);
            if (not index.has_value())
                return std::nullopt;
            return static_cast<wrapped_type>(*index);
        }
    }

    [[nodiscard]] constexpr wrapped_type index() const {
        return m_value;
    }

    [[nodiscard]] constexpr std::string_view to_string() const {
        return const_string_from_index<underlying_type, Fields...>(static_cast<underlying_type>(m_value));
    }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "google-explicit-constructor"
    constexpr operator wrapped_type() const {
        return m_value;
    }
#pragma clang diagnostic pop

private:
    wrapped_type m_value;

    template<typename TWrapped, std::size_t CSize, std::underlying_type_t<TWrapped> CIndex>
    static constexpr void get_iota_array_internal(std::array<TWrapped, CSize>& arr) {
        arr[CIndex] = static_cast<TWrapped>(CIndex);
        if constexpr (CIndex < CSize - 1) {
            get_iota_array_internal<TWrapped, CSize, CIndex+1>(arr);
        }
    }

    template<typename TWrapped, std::size_t CSize>
    static constexpr std::array<TWrapped, CSize> get_iota_array() {
        std::array<TWrapped, CSize> result{};
        get_iota_array_internal<TWrapped, CSize, 0>(result);
        return result;
    }

public:
    static constexpr std::array<wrapped_type, sizeof...(Fields)> Values{get_iota_array<wrapped_type, sizeof...(Fields)>()};
};

#define MB_ENUM_FIELD(identifier) constexpr static wrapped_type identifier = wrapped_type::identifier;
#define MB_ENUM_TRAITS(name)                                  \
    using self_type = name;                                   \
    using base_type = name##_Base;                            \
    using wrapped_type = base_type::wrapped_type ; \
    using underlying_type = base_type::underlying_type;       \
    constexpr name() = default;  \
    constexpr name(wrapped_type value) : base_type(value) {}  \
    explicit constexpr name(::std::string_view identifier) : name##_Base(*from_string(identifier)) {}
#define MB_E(Type, Value) Type{Type::Value}
}// namespace mb
