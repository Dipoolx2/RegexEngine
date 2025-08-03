#pragma once

#include "FSM/FSM.h"
#include <memory>
#include <queue>
#include <unordered_set>

using NFAPtr = std::unique_ptr<NFA>;
using StatePtr = std::shared_ptr<NFAState>;
using StatePtrSet = std::unordered_set<StatePtr>;

class LambdaRemover {
    public:
    virtual ~LambdaRemover() = default;

    void removeLambdaTransitions(NFA& nfa) const;

    private:
    void transitionsToClosureUnion(StatePtr state, StatePtrSet& closure) const;
    void dynamicallyFindEClosures(StatePtr state, std::queue<StatePtr>& q, StatePtrSet& visited, std::unordered_map<StatePtr, StatePtrSet>& eClosures) const;
};