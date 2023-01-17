#pragma once
#include <algorithm>
#include <mb/error.h>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

namespace mb {

struct empty {};
constexpr const empty ok{};

template<typename TValue, typename TErr = std::unique_ptr<basic_error>>
    requires(!std::is_convertible_v<TValue, TErr>)
class result {
public:
    using value_type = TValue;
    using raw_type = std::remove_reference_t<value_type>;
    using container_type = std::conditional_t<std::is_reference_v<value_type>, std::reference_wrapper<raw_type>, value_type>;
    using error_type = TErr;

private:
    std::variant<container_type, error_type> m_payload;

    result() = default;

public:
#pragma clang diagnostic push
#pragma ide diagnostic ignored "google-explicit-constructor"
#pragma ide diagnostic ignored "bugprone-forwarding-reference-overload"
    template<typename TOtherErr>
        requires std::convertible_to<TOtherErr, error_type>
    result(TOtherErr &&err) : m_payload{static_cast<error_type>(std::forward<TOtherErr>(err))} {}

    template<typename TOtherValue>
        requires std::convertible_to<TOtherValue, value_type>
    result(TOtherValue &&value) : m_payload{static_cast<value_type>(std::forward<TOtherValue>(value))} {}
#pragma clang diagnostic pop

    template<typename TOtherErr>
        requires std::convertible_to<TOtherErr, error_type>
    result &operator=(TOtherErr &&err) {
        m_payload = static_cast<error_type>(std::forward<TOtherErr>(err));
        return *this;
    }

    template<typename TOtherValue>
        requires std::convertible_to<TOtherValue, value_type>
    result &operator=(TOtherValue &&value) {
        m_payload = static_cast<value_type>(std::forward<TOtherValue>(value));
        return *this;
    }

    result(result &&other) noexcept = default;
    result &operator=(result &&other) noexcept = default;

    result(const result &other) : result([](const result &other) -> result<value_type, error_type> {
                                      static_assert(std::is_copy_constructible_v<raw_type> || std::is_reference_v<value_type>, "object must be copiable");
                                      if (other.has_failed()) {
                                          if constexpr (std::is_copy_constructible_v<error_type>) {
                                              return {other.err()};
                                          } else {
                                              return {other.err()->copy()};
                                          }
                                      }
                                      return {other.unwrap()};
                                  }(other)) {
    }

    result &operator=(const result &other) {
        static_assert(std::is_copy_constructible_v<raw_type> || std::is_reference_v<value_type>, "object must be copiable");
        if (other.has_failed()) {
            m_payload = other.copy_error();
        }
        m_payload = other.copy_unwrap();
    }

    [[nodiscard]] bool has_failed() const {
        return !ok();
    }

    [[nodiscard]] raw_type &get() {
        return std::get<container_type>(m_payload);
    }

    [[nodiscard]] const raw_type &get() const {
        return std::get<container_type>(m_payload);
    }

    [[nodiscard]] raw_type &get(value_type &&alt) {
        if (has_failed()) {
            return std::forward<value_type>(alt);
        }
        return get();
    }

    [[nodiscard]] const raw_type &get(value_type &&alt) const {
        if (has_failed()) {
            return std::forward<value_type>(alt);
        }
        return get();
    }

    [[nodiscard]] value_type unwrap() const {
        if constexpr (std::is_reference_v<value_type>) {
            return std::get<container_type>(m_payload).get();
        } else {
            return std::get<container_type>(m_payload);
        }
    }

    [[nodiscard]] value_type unwrap(value_type &&alt) const {
        if (has_failed()) {
            return std::forward<value_type>(alt);
        }
        return unwrap();
    }

    [[nodiscard]] bool ok() const {
        return std::holds_alternative<container_type>(m_payload);
    }

    [[nodiscard]] error_type &err() {
        return std::get<error_type>(m_payload);
    }

    [[nodiscard]] const error_type &err() const {
        return std::get<error_type>(m_payload);
    }

    [[nodiscard]] constexpr raw_type &operator*() {
        return get();
    }

    [[nodiscard]] constexpr raw_type *operator->() {
        return &(get());
    }
};

template<typename TInIt, typename TOutIt>
[[nodiscard]] basic_error::ptr unpack(TInIt beg, TInIt end, TOutIt out) {
    try {
        for (; beg != end; ++beg, ++out) {
            if (beg->has_failed()) {
                throw *(beg->err());
            }

            *out = beg->unwrap();
        }
    } catch (const basic_error &e) {
        return e.copy();
    }

    return nullptr;
}

template<typename T>
struct forward_container {
    T contained;
};

using emptyres = result<empty>;

#define MB_TRY(stmt)                                                                         \
    ({                                                                                       \
        auto __mb_res = stmt;                                                                \
        if (!__mb_res.ok())                                                                  \
            return std::move(__mb_res.err());                                                \
        ::mb::forward_container<typename decltype(__mb_res)::value_type>{__mb_res.unwrap()}; \
    }).contained

#define MB_VERIFY(result_value)    \
    if (result_value.has_failed()) \
        return std::move(result_value.err());

#define MB_ESCAPE(stmt)                                                                      \
    ({                                                                                       \
        auto __mb_res = stmt;                                                                \
        if (!__mb_res.ok())                                                                  \
            return;                                                                          \
        ::mb::forward_container<typename decltype(__mb_res)::value_type>{__mb_res.unwrap()}; \
    }).contained

}// namespace mb
