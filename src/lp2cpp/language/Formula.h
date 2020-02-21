#ifndef FORMULA_H
#define FORMULA_H
#include <unordered_set>
#include <string>

namespace aspc {

    class Formula {
    public:
        virtual bool isBoundedRelation(const std::unordered_set<std::string> &) const = 0;
        virtual bool isBoundedLiteral(const std::unordered_set<std::string> &) const = 0;
        virtual bool isBoundedValueAssignment(const std::unordered_set<std::string> &) const = 0;
        virtual bool isPositiveLiteral() const = 0;
        virtual void addVariablesToSet(std::unordered_set<std::string> &) const = 0;
        virtual void print() const = 0;
        virtual bool isLiteral() const = 0;
        virtual unsigned firstOccurrenceOfVariableInLiteral(const std::string &) const = 0;
        virtual ~Formula(){};


    };
}

#endif /* FORMULA_H */

