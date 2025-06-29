#include <any>
#include <iostream>

#include "TextPrinterVisitor.h"

// TODO: Add abstraction for const/pure visitors.
//          ALTERNATIVELY: Instead of printing, do string gen.

std::any TextPrinterVisitor::visitConcat(Regex::Concat& concat) {
    this->printAccordingTo(concat, *concat.left);
    this->printAccordingTo(concat, *concat.right);

    return nullptr;
}

std::any TextPrinterVisitor::visitAlternation(Regex::Alternation& alternation) {
    this->printAccordingTo(alternation, *alternation.left);
    std::cout << "|";
    this->printAccordingTo(alternation, *alternation.right);

    return nullptr;
}

std::any TextPrinterVisitor::visitRepetition(Regex::Repetition& repetition) {
    this->printAccordingTo(repetition, *repetition.inner);
    std::cout << "*";

    return nullptr;
}

std::any TextPrinterVisitor::visitLiteral(Regex::Literal& literal) {
    std::cout << literal.c;

    return nullptr;
}

void TextPrinterVisitor::printAccordingTo(Regex& parent, Regex& child) {
    if (child.precedence() <= parent.precedence())
        this->acceptWithParentheses(child);
    else child.accept(*this);
}

void TextPrinterVisitor::acceptWithParentheses(Regex& regex) {
    std::cout << "(";
    regex.accept(*this);
    std::cout << ")";
}

void TextPrinterVisitor::print(Regex& regex) {
    regex.accept(*this);
    std::cout << std::endl;
}