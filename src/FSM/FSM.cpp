#include "FSM/FSM.h"
#include <queue>

bool NFAState::isAccepting() {
    return this->accepting;
};

NFA::NFA(std::shared_ptr<NFAState> start, std::unordered_set<char>&& alphabet) : start(start), alphabet(alphabet) {}

std::string getCorrespondingName(int nr) {
    return "q" + std::to_string(nr);
}

[[nodiscard]] ReadableFSA NFA::generateReadableNFA() const {
    // Initialize relevant containers
    std::unordered_map<std::shared_ptr<NFAState>, std::string> namedStates;
    std::unordered_set<std::string> acceptingStates;
    std::unordered_set<std::shared_ptr<NFAState>> visited;
    std::unordered_set<char> alphabet;
    std::queue<std::shared_ptr<NFAState>> q;

    std::unordered_map<std::string, std::unordered_map<char, std::vector<std::string>>> transitions; 

    // Initialize starting state
    q.push(this->start);
    namedStates[this->start] = "q0";
    visited.insert(start);

    if (this->start->isAccepting())
        acceptingStates.insert("q0");

    int nextNameNumber = 1;

    // BFS
    while (!q.empty()) {
        std::shared_ptr<NFAState> current = q.front();
        std::string currentName = namedStates[current]; // Assume it's already added to namedStates if in q.

        q.pop();

        auto& stateTransitions = transitions[currentName];

        // Visit all neighbours.
        for (const auto& [transitionChar, neighbours] : current->transitions) {
            auto& stateCharTransition = stateTransitions[transitionChar];
            if (transitionChar != '$')
                alphabet.insert(transitionChar);
            
            for (const auto& neighbour : neighbours) {
                // Register name
                auto [it, inserted] = namedStates.emplace(neighbour, getCorrespondingName(nextNameNumber));
                if (inserted) nextNameNumber++;
                auto neighbourName = it->second;

                // Register transition
                stateCharTransition.push_back(neighbourName);

                // Mark accepting and visited
                auto [it2, unvisited] = visited.emplace(neighbour);
                if (!unvisited) continue;

                if (neighbour->isAccepting()) 
                    acceptingStates.insert(neighbourName);
                q.push(neighbour);
            }
        }
    }

    // Construct final struct
    struct ReadableFSA result;
    result.acceptingStates = acceptingStates;
    for (const auto& [_, name] : namedStates) 
        result.states.insert(name);
    result.start = "q0";
    result.transitions = transitions;
    result.alphabet = alphabet;

    return result;
}

std::string NFA::getVisualizationString() {
    ReadableFSA readable = this->generateReadableNFA();

    std::string result = std::string("#states\n");
    for (const std::string& st : readable.states) {
        result += st + "\n";
    }

    result += "#initial\n" + readable.start + "\n";

    result += "#accepting\n";
    for (const std::string& st : readable.acceptingStates) {
        result += st + "\n";
    }

    result += "#alphabet\n";
    for (char c : readable.alphabet) {
        result += c;
        result += "\n";
    }

    result += "#transitions\n";
    for (const auto& [state, transitions] : readable.transitions) {
        for (const auto& [c, targets] : transitions) {
            result += state + ":" + std::string(1, c) + ">" + targets[0];
            for (size_t targetIndex = 1; targetIndex < targets.size(); targetIndex++) {
                result += "," + targets[targetIndex];
            }
            result += "\n";
        }
    }
    return result;
}

NFAState::NFAState(bool accepting, 
                    std::unordered_map<char, std::vector<std::shared_ptr<NFAState>>>&& transitions) 
        : accepting(accepting), transitions(std::move(transitions)) {};

NFAState::NFAState(bool accepting) : accepting(accepting), 
            transitions(std::unordered_map<char, std::vector<std::shared_ptr<NFAState>>>{}) {};

void NFAState::definalize() {
    this->accepting = false;
}

void NFAState::finalize() {
    this->accepting = true;
}

void NFAState::clearLambdaTransitions() {
    this->transitions.erase('$');
}