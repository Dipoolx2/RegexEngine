#include <any>
#include "Regex.h"

#ifndef REGEXVISITOR_H
#define REGEXVISITOR_H

class RegexVisitor {

    public:
    virtual std::any visitConcat(Regex::Concat& concat) = 0;
    virtual std::any visitAlternation(Regex::Alternation& alternation) = 0;
    virtual std::any visitRepetition(Regex::Repetition& repetition) = 0;
    virtual std::any visitLiteral(Regex::Literal& literal) = 0;
    
    virtual ~RegexVisitor() = default;
};

#endif