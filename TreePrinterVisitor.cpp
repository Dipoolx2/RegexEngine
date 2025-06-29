#include <any>
#include <iostream>

#include "TreePrinterVisitor.h"

// TODO: Introduce enum to keep track of precedence.
// TODO: Add abstraction for const/pure visitors.
//          ALTERNATIVELY: Instead of printing, do string gen.
// TODO: Switch names of this class and textprintervisitor (honest mistake).

std::any TreePrinterVisitor::visitConcat(Regex::Concat& concat) {
    std::cout << "(";
    concat.left->accept(*this);
    concat.right->accept(*this);
    std::cout << ")";

    return nullptr;
}

std::any TreePrinterVisitor::visitUnion(Regex::Union& union_) {
    std::cout << "(";
    union_.left->accept(*this);
    std::cout << "|";
    union_.right->accept(*this);
    std::cout << "(";

    return nullptr;
}

std::any TreePrinterVisitor::visitRepetition(Regex::Repetition& repetition) {
    std::cout << "(";
    repetition.inner->accept(*this);
    std::cout << ")*";

    return nullptr;
}

std::any TreePrinterVisitor::visitLiteral(Regex::Lit& literal) {
    std::cout << literal.c;

    return nullptr;
}

void TreePrinterVisitor::print(Regex& regex) {
    regex.accept(*this);
    std::cout << std::endl;
}