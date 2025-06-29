#include "Regex/ParseException.h"

ParseException::ParseException(const std::string& regex) : 
    regex(regex), 
    message("Parse error when parsing regex `" + regex + "`.") 
{}

const char* ParseException::what() const noexcept {
    return this->message.c_str();
}