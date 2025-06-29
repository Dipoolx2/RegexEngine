#include <any>

#include <Regex/RegexTextVisitor.h>

std::any RegexTextVisitor::visitConcat(Regex::Concat& concat) {
    this->printAccordingTo(concat, *concat.left);
    this->printAccordingTo(concat, *concat.right);

    return nullptr;
}

std::any RegexTextVisitor::visitAlternation(Regex::Alternation& alternation) {
    this->printAccordingTo(alternation, *alternation.left);
    this->ss << "|";
    this->printAccordingTo(alternation, *alternation.right);

    return nullptr;
}

std::any RegexTextVisitor::visitRepetition(Regex::Repetition& repetition) {
    this->printAccordingTo(repetition, *repetition.inner);
    this->ss << "*";

    return nullptr;
}

std::any RegexTextVisitor::visitLiteral(Regex::Literal& literal) {
    this->ss << literal.c;

    return nullptr;
}

void RegexTextVisitor::printAccordingTo(Regex& parent, Regex& child) {
    if (child.precedence() <= parent.precedence())
        this->acceptWithParentheses(child);
    else child.accept(*this);
}

void RegexTextVisitor::acceptWithParentheses(Regex& regex) {
    this->ss << "(";
    regex.accept(*this);
    this->ss << ")";
}

[[nodiscard]] std::string RegexTextVisitor::get(Regex& regex) {
    this->ss.str("");
    this->ss.clear();

    regex.accept(*this);
    
    return this->ss.str();
}