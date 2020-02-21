
#ifndef LITERAL_H_ASPC
#define LITERAL_H_ASPC

#include "Atom.h"
#include "Formula.h"

namespace aspc {

    class Literal : public aspc::Formula {
    public:
        Literal(const std::string & predicateName);
        Literal(const std::string & predicateName, bool negated);
        Literal(bool negated, const aspc::Atom & atom);
        Literal(const Literal &);
        virtual ~Literal();

        void negate();
        bool isNegated() const;
        const std::string & getTermAt(unsigned i) const;
        bool isVariableTermAt(unsigned i) const;
        const std::string & getPredicateName() const;
        unsigned getAriety() const;
        const aspc::Atom & getAtom() const;
        const std::vector<std::string>& getTerms() const;
        void addTerm(const std::string &);
        bool operator==(const Literal& right) const;
        TupleWithReasons getTupleWithReasons() const;
        TupleWithoutReasons getTupleWithoutReasons() const;
        void setNegated(bool);
        std::unordered_set<std::string> getVariables() const;
        bool unifies(const aspc::Literal & right) const;
        bool unifies(const aspc::Atom & right) const;
        std::string getCanonicalRepresentation(const std::unordered_set<std::string> & litBoundVariables) const;
        void transformToCanonicalRep();
        bool isGround() const;

        virtual bool isBoundedRelation(const std::unordered_set<std::string> &) const override;
        virtual bool isBoundedLiteral(const std::unordered_set<std::string> &) const override;
        virtual bool isBoundedValueAssignment(const std::unordered_set<std::string> &) const override;
        virtual void addVariablesToSet(std::unordered_set<std::string> &) const override;
        virtual bool isPositiveLiteral() const override;
        virtual void print() const override;
        virtual bool isLiteral() const override;
        virtual unsigned firstOccurrenceOfVariableInLiteral(const std::string & v) const override;




    private:
        aspc::Atom atom;
        bool negated;

    };
}

#endif
