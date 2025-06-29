#include "Regex.h"

#include <memory>
#include <sstream>

#pragma once


class RegexParser {
    public:
    std::unique_ptr<Regex> parse(const std::string& regex);

    private:
    std::unique_ptr<Regex> literal();
    std::unique_ptr<Regex> repetition();
    std::unique_ptr<Regex> concat();
    std::unique_ptr<Regex> grouping();
    std::unique_ptr<Regex> alternation();

    char previous() const;
    char advance();
    char current() const;

    bool check(const char ch) const;
    bool atEnd() const;
    bool isCurrentLiteral() const;

    std::string regex;
    int idx = 0;
};