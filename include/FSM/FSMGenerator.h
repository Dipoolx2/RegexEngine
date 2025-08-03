#include "FSM/FSM.h"
#include "Regex/Regex.h"

#include <optional>
#include <memory>

#pragma once

using NFAPtr = std::unique_ptr<NFA>;

class FSMGenerator final {
    public:
    virtual ~FSMGenerator() = default;
    [[nodiscard]] std::optional<NFAPtr> generateNFA(Regex& regex) const;
    void removeLambda(NFA& nfa) const;
};