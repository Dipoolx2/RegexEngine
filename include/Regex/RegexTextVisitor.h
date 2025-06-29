#include "RegexVisitor.h"
#include <sstream>

#ifndef REGEXTEXTVISITOR_H
#define REGEXTEXTVISITOR_H

class RegexTextVisitor final : public RegexVisitor {
    public:
    [[nodiscard]] std::string get(Regex& regex);

    std::any visitConcat(Regex::Concat& concat) override final;
    std::any visitAlternation(Regex::Alternation& alternation) override final;
    std::any visitRepetition(Regex::Repetition& repetition) override final;
    std::any visitLiteral(Regex::Literal& literal) override final;

    private:
    void acceptWithParentheses(Regex& regex);
    void printAccordingTo(Regex& parent, Regex& child);

    std::stringstream ss;
};

#endif