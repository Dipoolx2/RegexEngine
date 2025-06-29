#include <memory>
#include <any>

#ifndef REGEX_H
#define REGEX_H

class RegexVisitor;

class Regex {
    public:
        virtual ~Regex() = default;
        virtual std::any accept(RegexVisitor& visitor) = 0;
        
        class Concat;
        class Union;
        class Repetition;
        class Lit;
};

class Regex::Concat final : public Regex {
    public:
        Concat(std::unique_ptr<Regex> left, std::unique_ptr<Regex> right);
        std::any accept(RegexVisitor& visitor) override final;
    
        std::unique_ptr<Regex> left;
        std::unique_ptr<Regex> right;
};

class Regex::Union final : public Regex {
    public:
        Union(std::unique_ptr<Regex> left, std::unique_ptr<Regex> right);
        std::any accept(RegexVisitor& visitor) override final;

        const std::unique_ptr<Regex> left;
        const std::unique_ptr<Regex> right;
};

class Regex::Repetition final : public Regex {
    public:
        Repetition(std::unique_ptr<Regex> inner);
        std::any accept(RegexVisitor& visitor) override final;

        std::unique_ptr<Regex> inner;
};

class Regex::Lit final : public Regex {
    public:
        Lit(const char c);
        std::any accept(RegexVisitor& visitor) override final;
 
        const char c;
};

#endif