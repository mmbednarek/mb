#include <mb/error.h>

namespace mb {

basic_error::basic_error(std::string message) noexcept : m_message(std::move(message)) {
}

const std::string &basic_error::msg() const {
    return m_message;
}

bool basic_error::operator==(const basic_error &other) const {
    return m_message == other.m_message;
}

basic_error::ptr basic_error::copy() const {
    return std::make_unique<basic_error>(m_message);
}

basic_error::ptr error(std::string message) {
    return std::make_unique<basic_error>(std::move(message));
}
}// namespace mb
