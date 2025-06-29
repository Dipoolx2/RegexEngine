#include <memory>
#include "Regex.h"

#ifndef REGEXHELPERS_H
#define REGEXHELPERS_H

template <typename T, typename... Args>
std::unique_ptr<Regex> makeRegex(Args&&... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}

#endif