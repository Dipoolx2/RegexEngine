#include "RegexVisitor.h"

#ifndef TEXTPRINTERVISITOR_H
#define TEXTPRINTERVISITOR_H

class TextPrinterVisitor final : public RegexVisitor {
    public:
    void print(Regex& regex);

    std::any visitConcat(Regex::Concat& concat) override final;
    std::any visitAlternation(Regex::Alternation& alternation) override final;
    std::any visitRepetition(Regex::Repetition& repetition) override final;
    std::any visitLiteral(Regex::Literal& literal) override final;

    private:
    void acceptWithParentheses(Regex& regex);
    void printAccordingTo(Regex& parent, Regex& child);
};

#endif