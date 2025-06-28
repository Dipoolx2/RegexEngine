#include <memory>

#include "Regex.h"
#include "PrinterVisitor.h"

int main() {
    auto lit1 = std::make_unique<Regex::Lit>('5');
    auto lit2 = std::make_unique<Regex::Lit>('8');
    auto concat1 = std::make_unique<Regex::Concat>(std::move(lit1), std::move(lit2));
    
    PrinterVisitor printer;
    printer.print(*concat1);

    return 0;
}