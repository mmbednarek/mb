#pragma once
#include <memory>
#include <string>

namespace mb {

class basic_error {
public:
    using ptr = std::unique_ptr<basic_error>;

private:
    std::string m_message;
public:
    explicit basic_error(std::string message) noexcept;
    bool operator==(const basic_error &other) const;

    [[nodiscard]] virtual const std::string &msg() const;

    ptr copy() const;
};

basic_error::ptr error(std::string message);



}// namespace mb
