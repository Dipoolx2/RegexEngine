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

std::any TreePrinterVisitor::visitAlternation(Regex::Alternation& alternation) {
    std::cout << "(union ";
    alternation.left->accept(*this);
    std::cout << " ";
    alternation.right->accept(*this);
    std::cout << ")";

    return nullptr;
}

std::any TreePrinterVisitor::visitRepetition(Regex::Repetition& repetition) {
    std::cout << "(rep ";
    repetition.inner->accept(*this);
    std::cout << ")";

    return nullptr;
}

std::any TreePrinterVisitor::visitLiteral(Regex::Literal& literal) {
    std::cout << literal.c;

    return nullptr;
}

void TreePrinterVisitor::print(Regex& regex) {
    regex.accept(*this);
    std::cout << std::endl;
}