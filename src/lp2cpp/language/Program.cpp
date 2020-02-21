
#include <map>
#include <list>
#include <set>
#include <iostream>
#include "Program.h"

using namespace std;

aspc::Program::Program() {

}

aspc::Program::~Program() {

}

void aspc::Program::addRule(const Rule & r) {
    rules.push_back(r);
    for (const Literal & literal : r.getBodyLiterals()) {
        rules_by_type[r.getType()][literal.getPredicateName()].insert(rules.size()-1);
    }

}

void aspc::Program::addFact(const aspc::Atom & r) {
    facts.push_back(r);
}

const aspc::Rule & aspc::Program::getRule(unsigned i) const {
    return rules[i];
}

unsigned aspc::Program::getRulesSize() const {
    return rules.size();
}

const vector<aspc::Rule>& aspc::Program::getRules() const{
    return rules;
}

vector<aspc::Rule>& aspc::Program::getRules() {
    return rules;
}

const aspc::Atom & aspc::Program::getFact(unsigned i) const {
    return facts[i];
}

const vector<aspc::Atom>& aspc::Program::getFacts() const {
    return facts;
}

unsigned aspc::Program::getFactsSize() const {
    return facts.size();
}

const map<RuleType, map<string, set<unsigned> > >& aspc::Program::getRulesByType() const {
    return rules_by_type;
}


const set<unsigned> & aspc::Program::getRulesByTypeAndPredicateName(const string & predicateName, RuleType type) const {
    return rules_by_type.at(type).at(predicateName);
}

void aspc::Program::clearFacts() {
    facts.clear();
}

void aspc::Program::print() const {
    for (const Rule & rule : rules) {
        rule.print();
    }
}

void aspc::Program::addPredicate(const string& name, const unsigned ariety) {
    predicates.insert(pair<string, unsigned>(name,ariety));
}

const set<pair<string, unsigned> >& aspc::Program::getPredicates() const {
    return predicates;
}

set<string> aspc::Program::getBodyPredicates() const {

    set<string> res;
    for(const Rule & r:rules) {
       for(const Literal & l: r.getBodyLiterals()) {
           res.insert(l.getPredicateName());
       }
    }
    return res;
}

set<string> aspc::Program::getHeadPredicates() const {

    set<string> res;
    for(const Rule & r:rules) {
       for(const Atom & a: r.getHead()) {
           res.insert(a.getPredicateName());
       }
    }
    return res;
}

bool aspc::Program::hasConstraint() const {
    for(const Rule & r: rules) {
        if(r.isConstraint()) {
            return true;
        }
    }
    return false;

}
