#pragma once

#include <any>
#include <memory>
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

    [[nodiscard]] NFAFragment acceptNFA(Regex& node);
};
