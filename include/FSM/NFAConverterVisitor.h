#pragma once

#include <any>
#include <memory>
#include <unordered_set>
#include <utility>
#include <optional>

#include "Regex/Regex.h"
#include "Regex/RegexVisitor.h"
#include "FSM.h"

using NFAStatePtr = std::shared_ptr<NFAState>;
using NFAFragment = std::pair<NFAStatePtr, NFAStatePtr>;

class NFAConverterVisitor : public RegexVisitor {
public:
    std::any visitConcat(Regex::Concat& concat);
    std::any visitAlternation(Regex::Alternation& alternation);
    std::any visitRepetition(Regex::Repetition& repetition);
    std::any visitLiteral(Regex::Literal& literal);

    std::optional<std::unique_ptr<NFA>> buildNFA(Regex& regex);

private:
    void createLambdaTransition(NFAStatePtr from, NFAStatePtr to);
    void registerStates(const NFAStatePtr st1, const NFAStatePtr st2);

    [[nodiscard]] NFAFragment acceptNFA(Regex& node);

    std::unordered_set<char> alphabet;
    std::unordered_set<NFAStatePtr> states;
};
