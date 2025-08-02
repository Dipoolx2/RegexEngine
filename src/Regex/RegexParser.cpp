#include "Regex/RegexParser.h"
#include "Regex/ParseException.h"
#include <memory>

// regex -> alternation
// alternation -> concat | concat \| alternation
// concat -> repetition | repetition concat
// repetition -> grouping | grouping*
// grouping -> literal | (regex)
// literal -> ALPHANUM

std::unique_ptr<Regex> RegexParser::parse(const std::string& regex) {
    this->regex = regex;
    this->idx = 0;

    return alternation();
}

std::unique_ptr<Regex> RegexParser::alternation() {
    std::unique_ptr<Regex> regexp = concat();

    if (check('|')) {
        advance();
        std::unique_ptr<Regex> right = alternation();
        regexp = std::make_unique<Regex::Alternation>(std::move(regexp), std::move(right));
    }

    return regexp;
}

std::unique_ptr<Regex> RegexParser::concat() {
    std::unique_ptr<Regex> regexp = repetition();

    if (!atEnd() && (isCurrentLiteral() || check('('))) {
        std::unique_ptr<Regex> right = concat();
        regexp = std::make_unique<Regex::Concat>(std::move(regexp), std::move(right));
    }

    return regexp;
}



std::unique_ptr<Regex> RegexParser::repetition() {
    std::unique_ptr<Regex> regexp = grouping();

    if (check('*')) {
        advance();
        regexp = std::make_unique<Regex::Repetition>(std::move(regexp));
    }

    return regexp;
}

std::unique_ptr<Regex> RegexParser::grouping() {
    if (check('(')) {
        // Grouping
        advance();

        std::unique_ptr<Regex> inner = alternation();

        if (!check(')')) 
            throw ParseException(this->regex, "close groupings with ')'!");

        advance();
        return inner;
    }

    return literal();
}

bool RegexParser::isCurrentLiteral() const {
    return !(current() == '|' || current() == '*' || current() == '(' || current() == ')'); 
}

std::unique_ptr<Regex> RegexParser::literal() {
    if (atEnd()) throw ParseException(this->regex, "Unexpected end of input; expected literal.");
    char ch = current();
    if (!isCurrentLiteral())
        throw ParseException(this->regex, std::string("Expected a literal (a-z), found '") + ch + "'");

    advance();
    return std::make_unique<Regex::Literal>(ch);
}

char RegexParser::previous() const {
    if (idx == 0)
        throw ParseException(this->regex, "Tried to access character before start of input.");
    return this->regex.at(idx-1);
}

bool RegexParser::atEnd() const {
    return this->idx >= this->regex.size();
}

bool RegexParser::check(const char ch) const {
    return current() == ch;
}

char RegexParser::current() const {
    if (atEnd()) return '\0';
    return this->regex.at(this->idx);
}

char RegexParser::advance() {
    if (!this->atEnd()) {
        // End of expression
        this->idx++;
    }
    
    return this->previous();
}