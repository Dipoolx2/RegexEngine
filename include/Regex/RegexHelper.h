#include <memory>
#include "Regex.h"

#pragma once

template <typename T, typename... Args>
std::unique_ptr<Regex> makeRegex(Args&&... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}