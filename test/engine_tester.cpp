#include <cstddef>
#include <iostream>

#include "Manager.h"
#include "Regex/ParseException.h"

const std::string exceptFirstWord(const std::string& line) {
    size_t pos = line.find(' ');
    if (pos != std::string::npos) {
        return line.substr(pos + 1);
    }
    return "";
}

void attemptPrepareNFA(Manager& manager) {
    if (!manager.loaded()) {
        std::cout << "No regex loaded. Load one first with `load <regex>`.\n";
        return;
    }

    manager.prepareNFA();
    std::cout << "Prepared NFA.\n";
}

void attemptPrintNFA(Manager& manager) {
    if (!manager.loadedNFA()) {
        std::cout << "No NFA loaded. Load one first with `prep`.\n";
        return;
    }

    std::optional<std::string> nfaString = manager.extractNFAString();
    if (!nfaString.has_value()) {
        std::cout << "Something went wrong whilst stringifying NFA. Please try again.\n";
        return;
    }

    std::cout << *nfaString << std::endl;
}

void attemptLoadRegex(const std::string& command, Manager& manager) {
    try {
        std::string regex = exceptFirstWord(command);
        if (regex.empty()) {
            std::cout << "No regex provided." << std::endl;
            return;
        }

        manager.load(regex);
        std::cout << "Loaded `" << regex << "`.\n";

    } catch (const ParseException& e) {
        std::cout << e.what() << std::endl;
    }
}

void attemptPrintRegex(Manager& manager) {
    if (!manager.loaded()) {
        std::cout << "No regex loaded. Load one first with `load <regex>`.\n";
        return;
    }

    std::cout << *std::move(manager.extractRegexString()) << std::endl;
}

void startRepl(Manager& manager) {

    for (;;) {
        std::string line;

        std::cout << ">>> ";
        std::getline(std::cin, line);

        if (line == "exit") {
            std::cout << "Shutting down REPL..." << std::endl;
            break;
        } else if (line.substr(0, 4) == "load") {
            attemptLoadRegex(line, manager);
        } else if (line.substr(0, 4) == "show") {
            if (line.size() <= 5) {
                std::cout << "Usage: `show <regex|nfa>`.\n";
            } else if (line.substr(5, 8) == "nfa") {
                attemptPrintNFA(manager);
            } else if (line.substr(5, 10) == "regex") {
                attemptPrintRegex(manager);
            } else {
                std::cout << "Usage: `show <regex|nfa>`.\n";
            }
        } else if (line.substr(0, 4) == "prep") {
            attemptPrepareNFA(manager);
        }
    }
}

int main() {
    // std::unique_ptr<Regex> regex = makeRegex<Regex::Alternation>(
    //     makeRegex<Regex::Concat>(
    //         makeRegex<Regex::Literal>('a'),
    //         makeRegex<Regex::Literal>('b')
    //     ),
    //     makeRegex<Regex::Concat>(
    //         makeRegex<Regex::Literal>('c'),
    //         makeRegex<Regex::Repetition>(
    //             makeRegex<Regex::Concat>(
    //                 makeRegex<Regex::Literal>('d'),
    //                 makeRegex<Regex::Repetition>(
    //                     makeRegex<Regex::Literal>('e')
    //                 )
    //             )
    //         )
    //     )
    // );

    Manager manager;
    std::cout << "REPL session started. Type `exit` to quit.\n";
    startRepl(manager);


    // RegexTextVisitor textVisitor;
    // std::cout << textVisitor.get(*regex) << std::endl;

    return 0;
}