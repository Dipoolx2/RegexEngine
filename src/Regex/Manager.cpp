#include <memory>
#include <string>
#include "Regex/Manager.h"
#include "Regex/RegexParser.h"

Manager::Manager() : parser(std::make_unique<RegexParser>()) {};

void Manager::load(const std::string regexStr) {
    std::unique_ptr<Regex> regex = this->parser->parse(regexStr);
    this->load(regexStr);
}

void Manager::load(std::unique_ptr<Regex> regex) {
    this->loadedRegex = std::move(regex);
}