#pragma once
#include <algorithm>
#include <mb/error.h>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <variant>
#include <vector>

namespace mb {

struct empty_T {};
constexpr const empty_T ok{};

using empty = const empty_T &;

template<typename T>
class result {
    struct container {
        T m_value;
    };
    std::variant<container, std::unique_ptr<error>> m_payload;

    result() = default;

public:
    result(error e);
    result(error::ptr e);
    result(T &&value);
    result(result &&other) noexcept = default;
    result &operator=(result &&other) noexcept = default;
    result(const result &other);
    result &operator=(const result &other);
    result &operator=(T &&value);

    [[nodiscard]] T unwrap();
    [[nodiscard]] T unwrap(T &&alt);
    [[nodiscard]] T copy_unwrap();
    [[nodiscard]] T copy_unwrap(T &&alt);
    [[nodiscard]] bool ok() const;
    [[nodiscard]] std::string msg() const;
    [[nodiscard]] error::ptr err();
    [[nodiscard]] error::ptr copy_error() const;
};

template<typename T>
result<T>::result(T &&value) : m_payload(container{std::forward<T>(value)}) {}

template<typename T>
result<T>::result(error e) : m_payload(std::make_unique<error>(e)) {}

template<typename T>
result<T>::result(error::ptr e) : m_payload(std::move(e)) {}

template<typename T>
result<T>::result(const result &other) : m_payload([&other]() -> std::variant<container, std::unique_ptr<error>> {
                                             if (!other.ok())
                                                 return std::move(other.copy_error());

                                             if constexpr (std::is_copy_constructible_v<T>) {
                                                 // if can be copied copy it
                                                 return container{T(std::get<container>(other.m_payload).m_value)};
                                             } else {
                                                 // if a reference forward a reference
                                                 static_assert(std::is_reference_v<T>, "cannot copy noncopyable object");
                                                 return container{std::forward<T>(std::get<container>(other.m_payload))};
                                             }
                                         }()) {}


template<typename T>
result<T> &result<T>::operator=(const result &other) {
    if (!other.ok())
        m_payload = std::move(other.copy_error());

    if constexpr (std::is_copy_constructible_v<T>) {
        // if can be copied copy it
        m_payload = container{T(std::get<container>(other.m_payload))};
    } else {
        // if a reference forward a reference
        static_assert(std::is_reference_v<T>, "cannot copy noncopyable object");
        m_payload = container{std::forward<T>(std::get<container>(other.m_payload))};
    }
    return *this;
}

template<typename T>
result<T> &result<T>::operator=(T &&val) {
    m_payload = container{std::forward<T>(val)};
    return *this;
}

template<typename T>
T result<T>::unwrap() {
    if (ok()) {
        if constexpr (std::is_reference<T>::value) {
            return std::get<container>(m_payload).m_value;
        } else {
            return std::move(std::get<container>(m_payload).m_value);
        }
    }
    throw std::runtime_error(msg());
}

template<typename T>
T result<T>::copy_unwrap() {
    if (ok()) {
        static_assert(std::is_copy_constructible_v<T>, "called copy_unwrap on noncopyable object");
        return T(std::get<container>(m_payload).m_value);
    }
    throw std::runtime_error(msg());
}

template<typename T>
T result<T>::unwrap(T &&alt) {
    if (ok()) {
        return std::move(std::get<container>(m_payload).m_value);
    }
    return std::forward<T>(alt);
}

template<typename T>
T result<T>::copy_unwrap(T &&alt) {
    if (ok()) {
        static_assert(std::is_copy_constructible_v<T>, "called copy_unwrap on noncopyable object");
        return T(std::get<container>(m_payload).m_value);
    }
    return std::forward<T>(alt);
}

template<typename T>
bool result<T>::ok() const { return std::holds_alternative<container>(m_payload); }

template<typename T>
std::string result<T>::msg() const {
    if (ok()) {
        return std::string();
    }
    return std::get<error::ptr>(m_payload)->msg();
}

template<typename T>
error::ptr result<T>::err() {
    if (ok()) {
        return error::ptr(nullptr);
    }
    return std::move(std::get<error::ptr>(m_payload));
}

template<typename T>
[[nodiscard]] error::ptr result<T>::copy_error() const {
    if (ok()) {
        return error::ptr(nullptr);
    }
    return std::make_unique<error>(*std::get<error::ptr>(m_payload));
}

template<typename T>
[[nodiscard]] result<std::vector<T>> unpack(std::vector<result<T>> packaged) {
    try {
        std::vector<T> out_vec;
        out_vec.reserve(packaged.size());
        std::transform(packaged.begin(), packaged.end(), std::back_inserter(out_vec), [](result<T> &res) {
            if (res.ok()) {
                return std::move(res.unwrap());
            }
            throw *res.copy_error();
        });
        return out_vec;
    } catch (const error &e) {
        return e;
    }
}

#define mb_pass(stmt) ({  \
    auto res = stmt;      \
    if (!res.ok())        \
        return res.err(); \
    res.unwrap();         \
})

#define MB_TRY(stmt) ({   \
    auto res = stmt;      \
    if (!res.ok())        \
        return res.err(); \
    res.unwrap();         \
})

}// namespace mb
