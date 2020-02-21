
#ifndef ATOM_H_ASPC
#define ATOM_H_ASPC
#include <string>
#include <vector>
#include <iostream>
#include "../datastructures/TupleWithoutReasons.h"
#include "../datastructures/TupleWithReasons.h"
#include "../utils/ConstantsManager.h"



namespace aspc {

    class Atom {


    public:

        Atom(const std::string & predicateName) : predicateName(ConstantsManager::getInstance().getPredicateName(predicateName)) {
        }

        Atom(const std::string & predicateName, const std::vector<std::string> & terms);
        Atom(const Atom &);
        virtual ~Atom();
        const std::string & getPredicateName() const;
        const std::string & getTermAt(unsigned) const;
        void addTerm(const std::string &);
        unsigned getTermsSize() const;
        const std::vector<std::string> & getTerms() const;
        unsigned getAriety() const;
        bool isVariableTermAt(unsigned) const;
        std::vector<unsigned> getIntTuple() const;
        TupleWithReasons getTupleWithReasons(bool) const;
        TupleWithoutReasons getTupleWithoutReasons(bool) const;
        void print() const;
        std::string toString() const;
        bool unifies(const Atom & right) const;
        std::string getCanonicalRepresentation(const std::unordered_set<std::string> & litBoundVariables) const;
        void transformToCanonicalRep();
        void getCoveredVariables(const std::unordered_set<std::string> & variables, std::vector<unsigned> & output) const;
        void getBoundTermsMask(const std::unordered_set<std::string> & boundVariables, std::vector<bool> & output) const;
        bool operator==(const Atom& right) const {
                
            return predicateName == (right.predicateName) && terms == right.terms;
            //TODO shared singleton for compiler and compiled
            //return &predicateName == &(right.predicateName) && terms == right.terms;
        }

        
    private:
        const std::string & predicateName;
        std::vector<std::string> terms;
    };

}
#endif

