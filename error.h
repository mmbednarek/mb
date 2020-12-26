#pragma once
#include <memory>

namespace mb {

class error {
public:
    enum class status {
        Internal = 0,
        InvalidArgument = 1,
        NotFound = 2,
        NotImplemented = 3,
        AlreadyExists = 4,
    };
    using ptr = std::unique_ptr<error>;

private:
    std::string m_message;
    status m_status = status::InvalidArgument;

public:
    explicit error(std::string message) noexcept;
    error(status cl, std::string message);

    [[nodiscard]] virtual const std::string &msg() const;

    [[nodiscard]] virtual status err_class() const;
};

}// namespace mb
