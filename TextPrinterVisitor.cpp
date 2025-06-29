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

std::any TextPrinterVisitor::visitUnion(Regex::Union& union_) {
    this->printAccordingTo(union_, *union_.left);
    std::cout << "|";
    this->printAccordingTo(union_, *union_.right);

    return nullptr;
}

std::any TextPrinterVisitor::visitRepetition(Regex::Repetition& repetition) {
    this->printAccordingTo(repetition, *repetition.inner);
    std::cout << "*";

    return nullptr;
}

std::any TextPrinterVisitor::visitLiteral(Regex::Lit& literal) {
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