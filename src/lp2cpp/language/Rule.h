
#ifndef RULE_H_ASPC
#define RULE_H_ASPC
#include <vector>
#include <map>
#include <unordered_map>
#include <list>
#include <tuple>
#include "Atom.h"
#include "Literal.h"
#include "ArithmeticRelation.h"

enum RuleType {
    GENERATIVE_RULE, CONSTRAINT
};




namespace aspc {
    

    class Rule {
    public:
        static unsigned rulesCounter;
        static std::string inequalityStrings[];
        Rule(const std::vector<aspc::Atom> & head, const std::vector<aspc::Literal> & body, const std::vector<ArithmeticRelation> & arithmeticRelation);
        Rule(const std::vector<aspc::Atom> & head, const std::vector<aspc::Literal> & body, const std::vector<ArithmeticRelation> & inequalities, bool reorderBody);
        Rule(const Rule& other);

        virtual ~Rule();
        const std::vector<aspc::Atom> & getHead() const;
        const std::vector<aspc::Literal> & getBodyLiterals() const;
        const std::vector<ArithmeticRelation> & getArithmeticRelations() const;
        RuleType getType() const;
        unsigned getRuleId() const;
        std::vector<std::map<unsigned, std::pair<unsigned, unsigned> > > getJoinIndicesWithJoinOrder(const std::vector<unsigned> & order) const;
        std::map<unsigned, std::pair<unsigned, unsigned> > getBodyToHeadVariablesMap() const;
        unsigned getBodySize() const;
        void print() const;
        bool containsNegation() const;
        bool isConstraint() const;
        std::pair<int, int> findFirstOccurrenceOfVariableByStarter(const std::string & var, unsigned starter) const;

        void bodyReordering();
        void bodyReordering(const std::vector<unsigned> & starters);
        void printOrderedBodies() const;


        const std::vector<unsigned> & getOrderedBodyIndexesByStarter(unsigned start) const;
        const std::vector<const aspc::Formula*>& getOrderedBodyByStarter(unsigned start) const;
        std::vector<unsigned> getStarters() const;

        const std::vector<const aspc::Formula*> & getFormulas() const;
        std::vector<const aspc::Formula*> getOrderedBodyForReasons(std::unordered_set<std::string> boundVariables) const;


    private:
        std::vector<aspc::Atom> head;
        std::vector<aspc::Literal> bodyLiterals;
        int ruleId;
        std::vector<ArithmeticRelation> arithmeticRelations;
        std::vector<const aspc::Formula*> formulas;

        std::unordered_map<unsigned, std::vector<const aspc::Formula*> > orderedBodyByStarters;
        std::unordered_map<unsigned, std::vector<unsigned> > orderedBodyIndexesByStarters;

    };
}

#endif

