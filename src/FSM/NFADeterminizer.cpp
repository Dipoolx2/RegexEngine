#include "FSM/NFADeterminizer.h"
#include "FSM/FSM.h"
#include <unordered_set>

void NFADeterminizer::determinize(NFA& nfa) const {
    std::unordered_set<char>& alphabet = nfa.alphabet;

    NFAStatePtr initial = std::make_shared<NFAState>(false);
    NFAStatePtr sink = std::make_shared<NFAState>(false);

    // Creating complete transition for sink state
    for (char c : alphabet) {
        sink->transitions[c].push_back(sink);
    }
}