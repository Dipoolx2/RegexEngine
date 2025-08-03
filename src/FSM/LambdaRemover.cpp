#include "FSM/LambdaRemover.h"
#include <queue>
#include <unordered_set>
#include <unordered_map>

using StatePtr = std::shared_ptr<NFAState>;
using StatePtrSet = std::unordered_set<StatePtr>;

void LambdaRemover::removeLambdaTransitions(NFA& nfa) const {
    std::unordered_map<StatePtr, StatePtrSet> lambdaClosures;
    StatePtrSet visited;

    std::queue<StatePtr> q;
    q.push(nfa.start);

    while (!q.empty()) {
        StatePtr current = q.front();
        q.pop();
        if (visited.count(current) > 0) continue;
        visited.insert(current);
        dynamicallyFindLambdaClosures(current, q, visited, lambdaClosures);
    }
    
    for (auto& state : visited) {
        transitionsToClosureUnion(state, lambdaClosures[state]);
    }
}

void LambdaRemover::dynamicallyFindLambdaClosures(
    StatePtr state, 
    std::queue<StatePtr>& q, 
    StatePtrSet& visited, 
    std::unordered_map<StatePtr, StatePtrSet>& lambdaClosures
) const {
    if (lambdaClosures.count(state)) return;

    lambdaClosures[state].insert(state);  // Closure includes the state itself

    for (const auto& [c, neighbours] : state->transitions) {
        if (c != '$') {
            for (const auto& neighbour : neighbours) {
                if (!visited.count(neighbour)) {
                    q.push(neighbour);
                }
            }
            continue;
        }

        for (const auto& neighbour : neighbours) {
            if (lambdaClosures.count(neighbour) == 0) {
                dynamicallyFindLambdaClosures(neighbour, q, visited, lambdaClosures);
            }

            for (const auto& closureState : lambdaClosures[neighbour]) {
                lambdaClosures[state].insert(closureState);
            }
        }
    }
}

void LambdaRemover::transitionsToClosureUnion(StatePtr state, StatePtrSet& closure) const {
    std::unordered_map<char, StatePtrSet> newTransitions;

    state->transitions.clear();

    for (const auto& closureState : closure) {
        for (const auto& [c, neighbours] : closureState->transitions) {
            if (c == '$') continue;

            for (const auto& neighbour : neighbours) {
                newTransitions[c].insert(neighbour);
            }
        }

        if (closureState->isAccepting()) {
            state->finalize();
        }
    }

    state->transitions.clear();
    for (const auto& [c, targetsSet] : newTransitions) {
        state->transitions[c] = std::vector<StatePtr>(targetsSet.begin(), targetsSet.end());
    }
}