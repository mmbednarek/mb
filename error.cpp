#include "error.h"

namespace mb {

error::error(std::string message) noexcept : m_message(std::move(message)) {}

error::error(status cl, std::string message) : m_message(std::move(message)), m_status(cl) {}

const std::string &error::msg() const {
    return m_message;
}

error::status error::err_class() const {
    return m_status;
}

}// namespace mb
