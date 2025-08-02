#include "FSM/FSM.h"
#include "Regex/Regex.h"

#include <optional>
#include <memory>

#pragma once

class FSMGenerator final {
    public:
    virtual ~FSMGenerator() = default;
    [[nodiscard]] std::optional<std::unique_ptr<NFA>> generateNFA(Regex& regex) const;
};