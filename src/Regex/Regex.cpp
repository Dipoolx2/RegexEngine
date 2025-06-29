#include "Regex/Regex.h"
#include "Regex/RegexVisitor.h"

unsigned char Regex::Concat::precedence() const {
    return Precedence::CONCAT;
}

unsigned char Regex::Alternation::precedence() const {
    return Precedence::ALTERNATION;
}

unsigned char Regex::Repetition::precedence() const {
    return Precedence::REPETITION;
}

unsigned char Regex::Literal::precedence() const {
    return Precedence::LITERAL;
}

std::any Regex::Concat::accept(RegexVisitor& visitor) {
    return visitor.visitConcat(*this);
}

std::any Regex::Alternation::accept(RegexVisitor& visitor) {
    return visitor.visitAlternation(*this);
}

std::any Regex::Repetition::accept(RegexVisitor& visitor) {
    return visitor.visitRepetition(*this);
}

std::any Regex::Literal::accept(RegexVisitor& visitor) {
    return visitor.visitLiteral(*this);
}

Regex::Concat::Concat(std::unique_ptr<Regex> left, std::unique_ptr<Regex> right) 
    : left(std::move(left)), right(std::move(right)) {}

Regex::Alternation::Alternation(std::unique_ptr<Regex> left, std::unique_ptr<Regex> right) 
    : left(std::move(left)), right(std::move(right)) {}

Regex::Repetition::Repetition(std::unique_ptr<Regex> inner) 
    : inner(std::move(inner)) {}

Regex::Literal::Literal(char c)
    : c(c) {}