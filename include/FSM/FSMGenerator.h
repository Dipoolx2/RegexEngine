#include "../Regex/Regex.h"
#include "FSM.h"

#include <memory>

#pragma once

class FSMGenerator final {
    public:
    virtual ~FSMGenerator() = default;
    FSMGenerator(std::shared_ptr<Regex> regex);

    [[nodiscard]] std::shared_ptr<NFA> generateNFA() const;

    private:
    std::shared_ptr<Regex> regex;
};