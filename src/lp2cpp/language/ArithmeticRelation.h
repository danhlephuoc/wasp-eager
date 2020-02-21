
#ifndef ARITHMETICRELATION_H
#define ARITHMETICRELATION_H
#include "Formula.h"
#include "ArithmeticExpression.h"
#include <string>
#include <map>

namespace aspc {
    

    enum ComparisonType {
        GTE = 0, LTE, GT, LT, NE, EQ, UNASSIGNED
    };

    class ArithmeticRelation : public Formula {
    public:
        static std::map<aspc::ComparisonType, std::string> comparisonType2String;



    public:
        ArithmeticRelation(const aspc::ArithmeticExpression & left, const aspc::ArithmeticExpression & right, aspc::ComparisonType comparisonType);

        virtual bool isBoundedRelation(const std::unordered_set<std::string> &) const override;
        virtual bool isBoundedLiteral(const std::unordered_set<std::string> &) const override;
        virtual bool isBoundedValueAssignment(const std::unordered_set<std::string> &) const override;
        virtual void addVariablesToSet(std::unordered_set<std::string> &) const override;
        virtual bool isPositiveLiteral() const override;
        virtual void print() const override;
        virtual bool isLiteral() const override;
        virtual unsigned firstOccurrenceOfVariableInLiteral(const std::string &) const override;

        virtual ~ArithmeticRelation() {

        }
        
        aspc::ComparisonType getComparisonType() const {
            return comparisonType;
        }

        aspc::ArithmeticExpression getLeft() const {
            return left;
        }

        aspc::ArithmeticExpression getRight() const {
            return right;
        }

        std::string getStringRep() const;
        
        std::string getAssignmentStringRep(const std::unordered_set<std::string>& boundVariables) const;
        
        std::string getAssignedVariable(const std::unordered_set<std::string>& boundVariables) const;



    private:
        aspc::ArithmeticExpression left;
        aspc::ArithmeticExpression right;
        aspc::ComparisonType comparisonType;


    };
}

#endif /* ARITHMETICRELATION_H */

