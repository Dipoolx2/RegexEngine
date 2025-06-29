#include <any>
#include <iostream>

#include "TreePrinterVisitor.h"

// TODO: Introduce enum to keep track of precedence.
// TODO: Add abstraction for const/pure visitors.
//          ALTERNATIVELY: Instead of printing, do string gen.
// TODO: Switch names of this class and textprintervisitor (honest mistake).

std::any TreePrinterVisitor::visitConcat(Regex::Concat& concat) {
    this->printAccordingTo(concat, *concat.left);
    this->printAccordingTo(concat, *concat.right);

    return nullptr;
}

std::any TreePrinterVisitor::visitUnion(Regex::Union& union_) {
    this->printAccordingTo(union_, *union_.left);
    std::cout << "|";
    this->printAccordingTo(union_, *union_.right);

    return nullptr;
}

std::any TreePrinterVisitor::visitRepetition(Regex::Repetition& repetition) {
    this->printAccordingTo(repetition, *repetition.inner);
    std::cout << "*";

    return nullptr;
}

std::any TreePrinterVisitor::visitLiteral(Regex::Lit& literal) {
    std::cout << literal.c;

    return nullptr;
}

void TreePrinterVisitor::printAccordingTo(Regex& parent, Regex& child) {
    if (child.precedence() <= parent.precedence())
        this->acceptWithParentheses(child);
    else child.accept(*this);
}

void TreePrinterVisitor::acceptWithParentheses(Regex& regex) {
    std::cout << "(";
    regex.accept(*this);
    std::cout << ")";
}

void TreePrinterVisitor::print(Regex& regex) {
    regex.accept(*this);
    std::cout << std::endl;
}