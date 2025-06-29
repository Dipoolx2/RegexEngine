#include <memory>
#include <any>

#ifndef REGEX_H
#define REGEX_H

class RegexVisitor;

enum Precedence {
    ALTERNATION = 1,
    CONCAT = 2,
    REPETITION = 3,
    LITERAL = 4
};

class Regex {
    public:
        virtual ~Regex() = default;

        virtual std::any accept(RegexVisitor& visitor) = 0;
        virtual unsigned char precedence() const = 0;
        
        class Concat;
        class Alternation;
        class Repetition;
        class Literal;
};

class Regex::Concat final : public Regex {
    public:
        Concat(std::unique_ptr<Regex> left, std::unique_ptr<Regex> right);

        std::any accept(RegexVisitor& visitor) override final;
        unsigned char precedence() const override final;

        std::unique_ptr<Regex> left;
        std::unique_ptr<Regex> right;
};

class Regex::Alternation final : public Regex {
    public:
        Alternation(std::unique_ptr<Regex> left, std::unique_ptr<Regex> right);

        std::any accept(RegexVisitor& visitor) override final;
        unsigned char precedence() const override final;

        std::unique_ptr<Regex> left;
        std::unique_ptr<Regex> right;
};

class Regex::Repetition final : public Regex {
    public:
        Repetition(std::unique_ptr<Regex> inner);

        std::any accept(RegexVisitor& visitor) override final;
        unsigned char precedence() const override final;

        std::unique_ptr<Regex> inner;
};

class Regex::Literal final : public Regex {
    public:
        Literal(const char c);

        std::any accept(RegexVisitor& visitor) override final;
        unsigned char precedence() const override final;
 
        const char c;
};

#endif