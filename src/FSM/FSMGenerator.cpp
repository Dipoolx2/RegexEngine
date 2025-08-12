#include "FSM/FSMGenerator.h"
#include "FSM/LambdaRemover.h"
#include "FSM/NFAConverterVisitor.h"
#include "FSM/NFADeterminizer.h"

std::optional<NFAPtr> FSMGenerator::generateNFA(Regex& regex) const {
    auto gen = NFAConverterVisitor();
    return std::move(gen.buildNFA(regex));
}

void FSMGenerator::removeLambda(NFA& nfa) const {
    auto gen = LambdaRemover();
    gen.removeLambdaTransitions(nfa);
}

void FSMGenerator::determinize(NFA& nfa) const {
    auto gen = NFADeterminizer();
    gen.determinize(nfa);
}