#pragma once
#include "compile_time.h"
#include <string_view>
#include <type_traits>

namespace mb {

template<typename TUnder, const_string... Fields>
class enum_base {
public:
    using wrapped_type = TUnder;
    using underlying_type = std::underlying_type_t<wrapped_type>;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "google-explicit-constructor"
    constexpr enum_base(wrapped_type index) : m_value(index) {}
#pragma clang diagnostic pop

    static constexpr wrapped_type from_string(const std::string_view identifier) {
        if constexpr (sizeof...(Fields) == 0) {
            return static_cast<wrapped_type>(underlying_type{-1});
        } else {
            return static_cast<wrapped_type>(find_index<underlying_type, Fields...>(identifier));
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
};

#define MB_ENUM_FIELD(identifier) constexpr static wrapped_type identifier = wrapped_type::identifier;
#define MB_ENUM_TRAITS(name)                                  \
    using self_type = name;                                   \
    using base_type = name##_Base;                            \
    using wrapped_type = base_type::wrapped_type ; \
    using underlying_type = base_type::underlying_type;       \
    constexpr name(wrapped_type value) : base_type(value) {}  \
    explicit constexpr name(::std::string_view identifier) : name##_Base(from_string(identifier)) {}
#define MB_E(Type, Value) Type{Type::Value}
}// namespace mb
