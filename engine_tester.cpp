#include <memory>

#include "Regex.h"
#include "TreePrinterVisitor.h"
#include "RegexHelper.h"

int main() {
    std::unique_ptr<Regex> regex = makeRegex<Regex::Concat>(
        makeRegex<Regex::Union>(
            makeRegex<Regex::Lit>('a'),
            makeRegex<Regex::Lit>('b')
        ),
        makeRegex<Regex::Repetition>(
            makeRegex<Regex::Lit>('c')
        )
    );

    TreePrinterVisitor treePrinter;
    treePrinter.print(*regex);

    return 0;
}