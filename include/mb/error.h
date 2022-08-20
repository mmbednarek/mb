#pragma once
#include <memory>
#include <string>

namespace mb {

class basic_error {
public:
    using ptr = std::unique_ptr<basic_error>;

    explicit basic_error(std::string message) noexcept;
    virtual ~basic_error() = default;

    bool operator==(const basic_error &other) const;

    [[nodiscard]] virtual const std::string &msg() const;

    [[nodiscard]] ptr copy() const;

private:
    std::string m_message;
};

basic_error::ptr error(std::string message);


}// namespace mb
