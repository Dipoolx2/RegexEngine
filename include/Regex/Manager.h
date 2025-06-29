#include <memory>
#include <string>
#include "Regex.h"
#include "Regex/RegexParser.h"

#pragma once

class Manager {
    public:
    Manager();
    void load(std::unique_ptr<Regex> regex);
    void load(const std::string regex);

    private:
    std::unique_ptr<Regex> loadedRegex;
    std::unique_ptr<RegexParser> parser;
};