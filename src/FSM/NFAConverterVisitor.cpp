#include "FSM/NFAConverterVisitor.h"

void NFAConverterVisitor::createLambdaTransition(NFAStatePtr from, NFAStatePtr to) {
    from->transitions['$'].push_back(to);
}

NFAFragment* NFAConverterVisitor::acceptNFA(Regex* node) {
    std::any result = node->accept(*this);
    return cast<NFAFragment>(result);
}

std::any NFAConverterVisitor::visitConcat(Regex::Concat& concat) {
    auto m0 = acceptNFA(concat.left.get());
    auto m1 = acceptNFA(concat.right.get());
    if (!m0 || !m1) return nullptr;

    auto q0 = std::make_shared<NFAState>(false);
    auto q1 = std::make_shared<NFAState>(true);

    createLambdaTransition(q0, m0->first);
    createLambdaTransition(m0->second, m1->first);
    createLambdaTransition(m1->second, q1);

    m0->second->definalize();
    m1->second->definalize();

    return NFAFragment{q0, q1};
}

std::any NFAConverterVisitor::visitAlternation(Regex::Alternation& alt) {
    auto m0 = acceptNFA(alt.left.get());
    auto m1 = acceptNFA(alt.right.get());
    if (!m0 || !m1) return nullptr;

    auto q0 = std::make_shared<NFAState>(false);
    auto q1 = std::make_shared<NFAState>(true);

    createLambdaTransition(q0, m0->first);
    createLambdaTransition(q0, m1->first);
    createLambdaTransition(m0->second, q1);
    createLambdaTransition(m1->second, q1);

    m0->second->definalize();
    m1->second->definalize();

    return NFAFragment{q0, q1};
}

std::any NFAConverterVisitor::visitRepetition(Regex::Repetition& rep) {
    auto m = acceptNFA(rep.inner.get());
    if (!m) return nullptr;

    auto q0 = std::make_shared<NFAState>(false);
    auto q1 = std::make_shared<NFAState>(true);

    createLambdaTransition(q0, m->first); // begin loop
    createLambdaTransition(q0, q1);       // accept empty string
    createLambdaTransition(m->second, q0); // repeat

    m->second->definalize();

    return NFAFragment{q0, q1};
}

std::any NFAConverterVisitor::visitLiteral(Regex::Literal& lit) {
    auto q0 = std::make_shared<NFAState>(false);
    auto q1 = std::make_shared<NFAState>(true);

    q0->transitions[lit.c].push_back(q1);

    return NFAFragment{q0, q1};
}

std::optional<NFA> NFAConverterVisitor::buildNFA(Regex& regex) {
    auto m = acceptNFA(&regex);
    if (!m) return std::nullopt;
    
    auto q0 = std::make_shared<NFAState>(false);
    auto q1 = std::make_shared<NFAState>(true);

    this->createLambdaTransition(q0, m->first);
    this->createLambdaTransition(m->second, q1);

    m->second->definalize();

    return NFA(q0);
}