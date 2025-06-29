#include "Regex.h"

#include <memory>

#pragma once

class RegexParser {
    public:
    std::unique_ptr<Regex> parse(const std::string& regex);

};