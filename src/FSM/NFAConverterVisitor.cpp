#include "FSM/NFAConverterVisitor.h"
#include "FSM/FSM.h"

#include <iostream>

void NFAConverterVisitor::createLambdaTransition(NFAStatePtr from, NFAStatePtr to) {
    from->transitions['$'].push_back(to);
}

void NFAConverterVisitor::registerStates(const NFAStatePtr st1, const NFAStatePtr st2) {
    this->states.insert(st1);
    this->states.insert(st2);
}

NFAFragment NFAConverterVisitor::acceptNFA(Regex& node) {
    std::any result = node.accept(*this);
    return std::any_cast<NFAFragment>(result);
}

std::any NFAConverterVisitor::visitConcat(Regex::Concat& concat) {
    NFAFragment m0 = acceptNFA(*concat.left);
    NFAFragment m1 = acceptNFA(*concat.right);

    NFAStatePtr q0 = std::make_shared<NFAState>(false);
    NFAStatePtr q1 = std::make_shared<NFAState>(true);

    registerStates(q0, q1);

    if (!q0 || !q1) {
        std::cout << "q0 or q1 is nullptr" << std::endl;
        return nullptr;
    }

    this->createLambdaTransition(q0, m0.first);
    this->createLambdaTransition(m0.second, m1.first);
    this->createLambdaTransition(m1.second, q1);

    m0.second->definalize();
    m1.second->definalize();

    return NFAFragment{q0, q1};
}

std::any NFAConverterVisitor::visitAlternation(Regex::Alternation& alt) {
    auto m0 = acceptNFA(*alt.left);
    auto m1 = acceptNFA(*alt.right);

    auto q0 = std::make_shared<NFAState>(false);
    auto q1 = std::make_shared<NFAState>(true);

    registerStates(q0, q1);

    createLambdaTransition(q0, m0.first);
    createLambdaTransition(q0, m1.first);
    createLambdaTransition(m0.second, q1);
    createLambdaTransition(m1.second, q1);

    m0.second->definalize();
    m1.second->definalize();

    return NFAFragment{q0, q1};
}

std::any NFAConverterVisitor::visitRepetition(Regex::Repetition& rep) {
    auto m = acceptNFA(*rep.inner);

    auto q0 = std::make_shared<NFAState>(false);
    auto q1 = std::make_shared<NFAState>(true);

    registerStates(q0, q1);

    createLambdaTransition(q0, m.first);  // begin loop
    createLambdaTransition(q0, q1);       // accept empty string
    createLambdaTransition(m.second, q0); // repeat

    m.second->definalize();

    return NFAFragment{q0, q1};
}

std::any NFAConverterVisitor::visitLiteral(Regex::Literal& lit) {
    auto q0 = std::make_shared<NFAState>(false);
    auto q1 = std::make_shared<NFAState>(true);

    registerStates(q0, q1);

    q0->transitions[lit.c].push_back(q1);
    alphabet.insert(lit.c);

    return NFAFragment{q0, q1};
}

std::optional<std::unique_ptr<NFA>> NFAConverterVisitor::buildNFA(Regex& regex) {
    auto m = acceptNFA(regex);

    auto q0 = std::make_shared<NFAState>(false);
    auto q1 = std::make_shared<NFAState>(true);

    registerStates(q0, q1);

    this->createLambdaTransition(q0, m.first);
    this->createLambdaTransition(m.second, q1);

    m.second->definalize();

    return std::make_unique<NFA>(q0, std::move(states), std::move(alphabet));
}