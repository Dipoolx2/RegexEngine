#include <any>
#include <iostream>

#include "TextPrinterVisitor.h"

std::any TextPrinterVisitor::visitConcat(Regex::Concat& concat) {
    std::cout << "(concat ";
    concat.left->accept(*this);
    std::cout << " ";
    concat.right->accept(*this);
    std::cout << ")";

    return nullptr;
}

std::any TextPrinterVisitor::visitUnion(Regex::Union& union_) {
    std::cout << "(union ";
    union_.left->accept(*this);
    std::cout << " ";
    union_.right->accept(*this);
    std::cout << ")";

    return nullptr;
}

std::any TextPrinterVisitor::visitRepetition(Regex::Repetition& repetition) {
    std::cout << "(rep ";
    repetition.inner->accept(*this);
    std::cout << ")";

    return nullptr;
}

std::any TextPrinterVisitor::visitLiteral(Regex::Lit& literal) {
    std::cout << literal.c;

    return nullptr;
}

void TextPrinterVisitor::print(Regex& regex) {
    regex.accept(*this);
    std::cout << std::endl;
}