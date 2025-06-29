#include <exception>
#include <string>

#pragma once

class ParseException final : public std::exception {
    public:
    ParseException(const std::string& regex, const std::string& reason);
    const char* what() const noexcept override;

    private:
    const std::string regex;
    const std::string reason;
    const std::string message;
};