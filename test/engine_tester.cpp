#include <memory>
#include <iostream>

#include "Regex/Regex.h"
#include "Regex/RegexTextVisitor.h"
#include "Regex/RegexHelper.h"

int main() {
    std::unique_ptr<Regex> regex = makeRegex<Regex::Alternation>(
        makeRegex<Regex::Concat>(
            makeRegex<Regex::Literal>('a'),
            makeRegex<Regex::Literal>('b')
        ),
        makeRegex<Regex::Concat>(
            makeRegex<Regex::Literal>('c'),
            makeRegex<Regex::Repetition>(
                makeRegex<Regex::Concat>(
                    makeRegex<Regex::Literal>('d'),
                    makeRegex<Regex::Repetition>(
                        makeRegex<Regex::Literal>('e')
                    )
                )
            )
        )
    );

    RegexTextVisitor textVisitor;
    std::cout << textVisitor.get(*regex) << std::endl;

    return 0;
}