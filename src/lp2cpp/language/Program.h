
#ifndef PROGRAM_H_ASPC
#define PROGRAM_H_ASPC
#include <vector>
#include <map>
#include <list>
#include <set>
#include "Rule.h"


namespace aspc {

    class Program {
    public:
        Program();
        virtual ~Program();
        void addRule(const aspc::Rule & r);
        void addFact(const aspc::Atom & f);
        void addPredicate(const std::string& name, const unsigned ariety);
        const std::set< std::pair<std::string, unsigned> >& getPredicates() const;
        unsigned getRulesSize() const;
        const std::vector<aspc::Rule>& getRules() const;
        std::vector<aspc::Rule>& getRules();
        unsigned getFactsSize() const;
        const aspc::Rule & getRule(unsigned i) const;
        const aspc::Atom & getFact(unsigned i) const;
        const std::vector<aspc::Atom> & getFacts() const;
        const std::map<RuleType, std::map<std::string, std::set<unsigned> > > & getRulesByType() const;
        const std::set<unsigned> & getRulesByTypeAndPredicateName(const std::string & predicateName, RuleType type) const;
        void clearFacts();
        void print() const;
        std::set<std::string> getBodyPredicates() const;
        std::set<std::string> getHeadPredicates() const;
        bool hasConstraint() const;

    private:
        std::vector<aspc::Rule> rules; //only rules are compiled
        std::vector<aspc::Atom> facts; //not compiled
        std::set< std::pair<std::string, unsigned> > predicates;

        std::map<RuleType, std::map<std::string, std::set<unsigned> > > rules_by_type;

    };
}

#endif

