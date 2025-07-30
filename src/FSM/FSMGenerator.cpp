#include "FSM/FSMGenerator.h"
#include "FSM/NFAConverterVisitor.h"
#include "Regex/Regex.h"
#include <memory>

FSMGenerator::FSMGenerator(std::shared_ptr<Regex> regex) : regex(regex) {};

std::shared_ptr<NFA> FSMGenerator::generateNFA() const {
    return nullptr;
}