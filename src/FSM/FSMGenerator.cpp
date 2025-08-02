#include "FSM/FSMGenerator.h"
#include "FSM/NFAConverterVisitor.h"
#include "Regex/Regex.h"
#include <memory>

std::optional<std::unique_ptr<NFA>> FSMGenerator::generateNFA(Regex& regex) const {
    auto gen = NFAConverterVisitor();
    return std::move(gen.buildNFA(regex));
}