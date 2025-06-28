#include <any>
#include <iostream>

#include "PrinterVisitor.h"

std::any PrinterVisitor::visitConcat(Regex::Concat& concat) {
    std::cout << "(concat ";
    concat.left->accept(*this);
    std::cout << " ";
    concat.right->accept(*this);
    std::cout << ")";

    return nullptr;
}

std::any PrinterVisitor::visitUnion(Regex::Union& union_) {
    std::cout << "(union ";
    union_.left->accept(*this);
    std::cout << " ";
    union_.right->accept(*this);
    std::cout << ")";

    return nullptr;
}

std::any PrinterVisitor::visitRepetition(Regex::Repetition& repetition) {
    std::cout << "(rep ";
    repetition.inner->accept(*this);
    std::cout << ")";

    return nullptr;
}

std::any PrinterVisitor::visitLiteral(Regex::Lit& literal) {
    std::cout << literal.c;

    return nullptr;
}

void PrinterVisitor::print(Regex& regex) {
    regex.accept(*this);
    std::cout << std::endl;
}