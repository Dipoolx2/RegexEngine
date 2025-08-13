#pragma once

#include "FSM/FSM.h"
#include <memory>
#include <unordered_set>
#include <utility>

using StatePtr = std::shared_ptr<NFAState>;
using StatePtrSet = std::unordered_set<StatePtr>;
using StateSetPair = std::pair<StatePtr, StatePtrSet>;

class NFADeterminizer {
    public:
    virtual ~NFADeterminizer() = default;

    void determinize(NFA& nfa) const;
    StatePtr makeSinkState(std::unordered_set<char>& alphabet) const;
};