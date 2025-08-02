#include <optional>
#include <memory>
#include <string>

#include "FSM/FSM.h"
#include "Regex/Regex.h"
#include "Regex/RegexParser.h"

#pragma once

class Manager {
    public:
    Manager();

    bool loaded() const;
    bool loadedNFA() const;

    void load(std::unique_ptr<Regex> regex);
    void load(const std::string& regex);
    void prepareNFA();

    [[nodiscard]] std::optional<std::string> extractRegexString() const;
    [[nodiscard]] std::optional<std::string> extractNFAString() const;

    private:
    std::unique_ptr<RegexParser> parser;

    std::optional<std::unique_ptr<Regex>> loadedRegex;
    std::optional<std::unique_ptr<NFA>> nfa;
};