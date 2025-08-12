#include <memory>
#include <unordered_set>
#include <vector>
#include <unordered_map>
#include <string>

#pragma once

class NFAState {
    public:
    virtual ~NFAState() = default;

    NFAState(bool accepting, 
                std::unordered_map<char, std::vector<std::weak_ptr<NFAState>>>&& transitions);
    NFAState(bool accepting);

    bool isAccepting();
    std::unordered_map<char, std::vector<std::weak_ptr<NFAState>>> transitions;

    void definalize();
    void finalize();
    void clearLambdaTransitions();

    private:
    bool accepting;
};

struct ReadableFSA {
    std::unordered_set<char> alphabet;
    std::unordered_set<std::string> states;
    std::unordered_set<std::string> acceptingStates;
    std::string start;
    std::unordered_map<std::string, std::unordered_map<char, std::vector<std::string>>> transitions; 
};

class NFA {
    public:
    std::shared_ptr<NFAState> start;
    std::unordered_set<char> alphabet;
    std::unordered_set<std::shared_ptr<NFAState>> states;

    NFA(std::shared_ptr<NFAState> start, 
        std::unordered_set<std::shared_ptr<NFAState>>&& states, 
        std::unordered_set<char>&& alphabet);

    std::string getVisualizationString();
    [[nodiscard]] ReadableFSA generateReadableNFA() const;

    virtual ~NFA() = default;
};