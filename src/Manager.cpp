#include "Manager.h"
#include "Regex/RegexTextVisitor.h"

Manager::Manager() : parser(std::make_unique<RegexParser>()) {};

void Manager::load(std::unique_ptr<Regex> regex) {
    this->loadedRegex = std::move(regex);
}

void Manager::load(const std::string& regexStr) {
    std::unique_ptr<Regex> regex = this->parser->parse(regexStr);
    this->load(std::move(regex));
}

bool Manager::loaded() const {
    return this->loadedRegex.get() != nullptr;
}

std::optional<std::string> Manager::extractRegexString() const {
    if (!loaded()) {
        return std::nullopt;
    }

    RegexTextVisitor visitor;
    return visitor.get(*(this->loadedRegex));
}