#pragma once

#include "FSM/FSM.h"

using NFAStatePtr = std::shared_ptr<NFAState>;

class NFADeterminizer {
    public:
    virtual ~NFADeterminizer() = default;

    void determinize(NFA& nfa) const;
};