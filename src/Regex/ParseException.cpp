#include "Regex/ParseException.h"

ParseException::ParseException(const std::string& regex, const std::string& reason) : 
    regex(regex), 
    message("Parse error when parsing `" + regex + "`: " + reason)
{}

const char* ParseException::what() const noexcept {
    return this->message.c_str();
}