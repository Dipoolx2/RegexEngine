#include "FSM/NFADeterminizer.h"
#include "FSM/FSM.h"
#include <memory>
#include <queue>
#include <unordered_set>

StatePtr NFADeterminizer::makeSinkState(std::unordered_set<char>& alphabet) const {
    StatePtr sink = std::make_shared<NFAState>(false);

    // Creating complete transition for sink state
    for (char c : alphabet) {
        sink->transitions[c].push_back(sink);
    }

    return sink;
}

void NFADeterminizer::determinize(NFA& nfa) const {
    std::unordered_set<char>& alphabet = nfa.alphabet;

    StatePtr initial = std::make_shared<NFAState>(false);
    StatePtr sink = makeSinkState(alphabet);

    //std::unordered_set<StatePtrSet> visited;
    // TODO: CREATE A HASHABLE SUBSET WRAPPER
    // -- FOR SMALL SIZES USE BITWISE OPS
    // -- FOR LARGER SIZES USE SORTED ARRAYS
    std::queue<StateSetPair> q;

    q.push({initial, {nfa.start}});

    while (!q.empty()) {

    }

}