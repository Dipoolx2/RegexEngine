#include <any>
#include <iostream>

#include "TreePrinterVisitor.h"

std::any TreePrinterVisitor::visitConcat(Regex::Concat& concat) {
    std::cout << "(concat ";
    concat.left->accept(*this);
    std::cout << " ";
    concat.right->accept(*this);
    std::cout << ")";

    return nullptr;
}

std::any TreePrinterVisitor::visitUnion(Regex::Union& union_) {
    std::cout << "(union ";
    union_.left->accept(*this);
    std::cout << " ";
    union_.right->accept(*this);
    std::cout << ")";

    return nullptr;
}

std::any TreePrinterVisitor::visitRepetition(Regex::Repetition& repetition) {
    std::cout << "(rep ";
    repetition.inner->accept(*this);
    std::cout << ")";

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