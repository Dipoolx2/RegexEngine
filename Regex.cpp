#include "Regex.h"
#include "RegexVisitor.h"

unsigned char Regex::Concat::precedence() {
    return 2;
}

unsigned char Regex::Union::precedence() {
    return 1;
}

unsigned char Regex::Repetition::precedence() {
    return 3;
}

unsigned char Regex::Lit::precedence() {
    return 4;
}

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

Regex::Lit::Lit(char c)
    : c(c) {}