#include <optional>
#include <memory>
#include <string>

#include "Regex/Regex.h"
#include "Regex/RegexParser.h"

#pragma once

class Manager {
    public:
    Manager();

    bool loaded() const;

    void load(std::unique_ptr<Regex> regex);
    void load(const std::string& regex);

    std::optional<std::string> extractRegexString() const;

    private:
    std::unique_ptr<Regex> loadedRegex;
    std::unique_ptr<RegexParser> parser;
};