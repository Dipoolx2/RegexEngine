#include <cstddef>
#include <iostream>

#include "Regex/ParseException.h"
#include "Regex/Manager.h"

const std::string exceptFirstWord(const std::string& line) {
    size_t pos = line.find(' ');
    if (pos != std::string::npos) {
        return line.substr(pos + 1);
    }
    return "";
}

void attemptLoadRegex(const std::string& command, Manager& manager) {

    try {

        std::string regex = exceptFirstWord(command);
        if (regex.empty()) {
            std::cout << "No regex provided." << std::endl;
            return;
        }

        manager.load(regex);
        
    } catch (const ParseException& e) {
        std::cout << e.what() << std::endl;
    }
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