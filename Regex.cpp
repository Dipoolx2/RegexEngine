#include "Regex.h"
#include "RegexVisitor.h"

std::any Regex::Concat::accept(RegexVisitor& visitor) {
    return visitor.visitConcat(*this);
}

std::any Regex::Union::accept(RegexVisitor& visitor) {
    return visitor.visitUnion(*this);
}

std::any Regex::Repetition::accept(RegexVisitor& visitor) {
    return visitor.visitRepetition(*this);
}

std::any Regex::Lit::accept(RegexVisitor& visitor) {
    return visitor.visitLiteral(*this);
}

Regex::Concat::Concat(std::unique_ptr<Regex> left, std::unique_ptr<Regex> right) 
    : left(std::move(left)), right(std::move(right)) {}

Regex::Union::Union(std::unique_ptr<Regex> left, std::unique_ptr<Regex> right) 
    : left(std::move(left)), right(std::move(right)) {}

Regex::Repetition::Repetition(std::unique_ptr<Regex> inner) 
    : inner(std::move(inner)) {}

Regex::Lit::Lit(const char c)
    : c(c) {}