
#include "ArithmeticRelation.h"
#include "../utils/SharedFunctions.h"
#include "Rule.h"
#include <iostream>
#include <cassert>

using namespace std;

std::map<aspc::ComparisonType, std::string> aspc::ArithmeticRelation::comparisonType2String = {
    {GT, ">"},
    {EQ, "=="},
    {LT, "<"},
    {GTE, ">="},
    {LTE, "<="},
    {NE, "!="}

};


aspc::ArithmeticRelation::ArithmeticRelation(const aspc::ArithmeticExpression& left, const aspc::ArithmeticExpression& right, aspc::ComparisonType comparisonType) : left(left), right(right), comparisonType(comparisonType) {

}

void aspc::ArithmeticRelation::addVariablesToSet(std::unordered_set<std::string>& set) const {
    //assert(isBoundedValueAssignment(set));
    if(isBoundedValueAssignment(set)) {
        set.insert(getAssignedVariable(set));
    }

}

bool aspc::ArithmeticRelation::isBoundedRelation(const std::unordered_set<std::string>& set) const {
    for (const std::string & t : left.getAllTerms()) {
        if (isVariable(t) && !set.count(t)) {
            return false;
        }
    }
    for (const std::string & t : right.getAllTerms()) {
        if (isVariable(t) && !set.count(t)) {
            return false;
        }
    }
    return true;
}

bool aspc::ArithmeticRelation::isBoundedLiteral(const std::unordered_set<std::string>&) const {
    return false;
}

bool aspc::ArithmeticRelation::isBoundedValueAssignment(const std::unordered_set<std::string>& boundVariables) const {

    //    if (comparisonType == aspc::EQ && left.isSingleTerm() && isVariable(left.getTerm1()) && !set.count(left.getTerm1())) {
    //        for (const string & t : right.getAllTerms()) {
    //            if (isVariable(t) && !set.count(t)) {
    //                return false;
    //            }
    //        }
    //        return true;
    //    }
    //    return false;
    if (comparisonType != aspc::EQ) {
        return false;
    }
    unsigned unassignedVariables = 0;
    for (const std::string & v : left.getAllTerms()) {
        if (!boundVariables.count(v) && isVariable(v)) {
            unassignedVariables++;
        }
    }
    for (const std::string & v : right.getAllTerms()) {
        if (!boundVariables.count(v) && isVariable(v)) {
            unassignedVariables++;
        }
    }
    return unassignedVariables == 1;
}

std::string aspc::ArithmeticRelation::getAssignedVariable(const unordered_set<std::string>& boundVariables) const {
    assert(isBoundedValueAssignment(boundVariables));
    for (const std::string & v : left.getAllTerms()) {
        if (!boundVariables.count(v) && isVariable(v)) {
            return v;
        }
    }
    for (const std::string & v : right.getAllTerms()) {
        if (!boundVariables.count(v) && isVariable(v)) {
            return v;
        }
    }
    throw std::runtime_error("error in assignment");
    
}


void aspc::ArithmeticRelation::print() const {
    std::cout << left << " " << comparisonType2String[comparisonType] << " " << right;

}

bool aspc::ArithmeticRelation::isPositiveLiteral() const {
    return false;
}

bool aspc::ArithmeticRelation::isLiteral() const {
    return false;
}

unsigned aspc::ArithmeticRelation::firstOccurrenceOfVariableInLiteral(const string &) const {
    return -1;
}

string aspc::ArithmeticRelation::getStringRep() const {
    return left.getStringRep() + " " + comparisonType2String[comparisonType] + " " + right.getStringRep();
}


string invertOperation(char op) {
    switch(op) {
        case '+':
            return "-";
        case '-':
            return "+";
        case '*':
            return "/";
        case '/':
            return "*";
    }
    throw std::runtime_error("unsupported operation "+op);
}

string aspc::ArithmeticRelation::getAssignmentStringRep(const unordered_set<string>& boundVariables) const {
    //    return left.getStringRep() + " = " + right.getStringRep();
    string res = "";
    bool leftContainsUnassigned = true;
    string unassigned;
    for (const string & v : left.getAllTerms()) {
        if (!boundVariables.count(v) && isVariable(v)) {
            res += v;
            unassigned = v;
        }
    }
    for (const string & v : right.getAllTerms()) {
        if (!boundVariables.count(v) && isVariable(v)) {
            res += v;
            unassigned = v;
            leftContainsUnassigned = false;
        }
    }

    res += " = ";



    ArithmeticExpression evalLeft = left;
    ArithmeticExpression evalRight = right;

    if (!leftContainsUnassigned) {
        evalLeft = right;
        evalRight = left;
    }

    //don't use right and left anymore
    if (evalLeft.isSingleTerm()) {
        return evalLeft.getStringRep() + " = " + evalRight.getStringRep();
    }


    if (!evalLeft.isSingleTerm()) {
        if (evalLeft.getOperation() == '+') {
            if (evalLeft.getTerm1() == unassigned) {
                return res + evalRight.getStringRep() + " - " + evalLeft.getTerm2();
            }
            else {
                return res + evalRight.getStringRep() + " - " + evalLeft.getTerm1();
            }
        }
        else if (evalLeft.getOperation() == '-') {
            if (evalLeft.getTerm1() == unassigned) {
                return res + evalRight.getStringRep() + " + " + evalLeft.getTerm2();
            }
            else {
                return res + " -"+evalRight.getTerm1() + " + " + evalLeft.getTerm1();
            }
            //TODO implement assignment on / and *
        } else {
            throw std::runtime_error("unsupported assignment "+getStringRep());
        }
    }



    throw std::runtime_error("unable to getAssignmentStringRep");

}
