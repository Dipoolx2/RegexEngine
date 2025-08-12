#include "Manager.h"
#include "FSM/FSMGenerator.h"
#include "Regex/RegexTextVisitor.h"

Manager::Manager() : parser(std::make_unique<RegexParser>()) {};

void Manager::load(std::unique_ptr<Regex> regex) {
    this->loadedRegex = std::move(regex);
}

void Manager::load(const std::string& regexStr) {
    std::unique_ptr<Regex> regex = this->parser->parse(regexStr);
    this->load(std::move(regex));
}

void Manager::prepareNFA() {
    if (!loaded()) return;

    auto gen = FSMGenerator();
    std::optional<std::unique_ptr<NFA>> generated = gen.generateNFA(*loadedRegex->get());
    if (!generated.has_value()) return;
    
    gen.removeLambda(**generated);
    if (!generated.has_value()) return;

    gen.determinize(**generated);
    if (!generated.has_value()) return;

    // Success
    this->nfa = std::move(generated);
}

bool Manager::loaded() const {
    return this->loadedRegex.has_value();
}

bool Manager::loadedNFA() const {
    return this->nfa.has_value();
}

std::optional<std::string> Manager::extractRegexString() const {
    if (!loaded()) {
        return std::nullopt;
    }

    RegexTextVisitor visitor;
    return visitor.get(*(this->loadedRegex->get()));
}

std::optional<std::string> Manager::extractNFAString() const {
    if (!loadedNFA()) return std::nullopt;

    return (*nfa)->getVisualizationString();
}