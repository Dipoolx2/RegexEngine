#include <memory>

#include "Regex.h"
#include "TreePrinterVisitor.h"
#include "RegexHelper.h"

int main() {
    std::unique_ptr<Regex> regex = makeRegex<Regex::Union>(
        makeRegex<Regex::Concat>(
            makeRegex<Regex::Lit>('a'),
            makeRegex<Regex::Lit>('b')
        ),
        makeRegex<Regex::Concat>(
            makeRegex<Regex::Lit>('c'),
            makeRegex<Regex::Repetition>(
                makeRegex<Regex::Concat>(
                    makeRegex<Regex::Lit>('d'),
                    makeRegex<Regex::Repetition>(
                        makeRegex<Regex::Lit>('e')
                    )
                )
            )
        )
    );

    TreePrinterVisitor treePrinter;
    treePrinter.print(*regex);

    return 0;
}