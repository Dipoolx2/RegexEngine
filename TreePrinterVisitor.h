#include "RegexVisitor.h"

#ifndef TREEPRINTERVISITOR_H
#define TREEPRINTERVISITOR_H

class TreePrinterVisitor final : public RegexVisitor {
    public:
    void print(Regex& regex);

    std::any visitConcat(Regex::Concat& concat) override final;
    std::any visitAlternation(Regex::Alternation& alternation) override final;
    std::any visitRepetition(Regex::Repetition& repetition) override final;
    std::any visitLiteral(Regex::Literal& literal) override final;
};

#endif