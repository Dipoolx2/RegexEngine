#include "RegexVisitor.h"

#ifndef TEXTPRINTERVISITOR_H
#define TEXTPRINTERVISITOR_H

class TextPrinterVisitor final : public RegexVisitor {
    public:
    void print(Regex& regex);

    std::any visitConcat(Regex::Concat& concat_) override final;
    std::any visitUnion(Regex::Union& union_) override final;
    std::any visitRepetition(Regex::Repetition& repetition_) override final;
    std::any visitLiteral(Regex::Lit& lit_) override final;

    private:
    void acceptWithParentheses(Regex& regex);
    void printAccordingTo(Regex& parent, Regex& child);
};

#endif