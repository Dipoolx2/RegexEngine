#include "Regex/RegexParser.h"
#include "Regex/ParseException.h"

std::unique_ptr<Regex> RegexParser::parse(const std::string& regex) {
    throw ParseException(regex);
    return std::make_unique<Regex::Literal>('a');
}