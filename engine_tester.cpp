#include <memory>

#include "Regex.h"
#include "TextPrinterVisitor.h"
#include "RegexHelper.h"

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

    TextPrinterVisitor textPrinter;
    textPrinter.print(*regex);

    return 0;
}