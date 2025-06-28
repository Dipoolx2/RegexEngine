#include <any>
#include "Regex.h"

#ifndef REGEXVISITOR_H
#define REGEXVISITOR_H

class RegexVisitor {

    public:
    virtual std::any visitConcat(Regex::Concat& concat_) = 0;
    virtual std::any visitUnion(Regex::Union& union_) = 0;
    virtual std::any visitRepetition(Regex::Repetition& rep_) = 0;
    virtual std::any visitLiteral(Regex::Lit& lit_) = 0;
    
    virtual ~RegexVisitor() = default;
};

#endif