#include "RegexVisitor.h"

#ifndef PRINTERVISITOR_H
#define PRINTERVISITOR_H

class PrinterVisitor final : public RegexVisitor {
    public:
    void print(Regex& regex);

    std::any visitConcat(Regex::Concat& concat_) override final;
    std::any visitUnion(Regex::Union& union_) override final;
    std::any visitRepetition(Regex::Repetition& repetition_) override final;
    std::any visitLiteral(Regex::Lit& lit_) override final;
};

#endif