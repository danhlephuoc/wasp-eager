#ifndef COMPILATIONMANAGER_H
#define	COMPILATIONMANAGER_H

#include "language/Program.h"
#include "parsing/AspCore2ProgramBuilder.h"
#include "utils/Indentation.h"
#include <string>
#include <set>
#include "datastructures/BoundAnnotatedLiteral.h"

const int LAZY_MODE = 0; 
const int EAGER_MODE = 1;

class CompilationManager {
public:
    CompilationManager(int mode);
    void lp2cpp();
    void generateStratifiedCompilableProgram(aspc::Program & program, AspCore2ProgramBuilder* builder);
    void setOutStream(std::ostream* outputTarget);
    const std::set<std::string> & getBodyPredicates();
    void insertModelGeneratorPredicate(const std::string & p) {
        modelGeneratorPredicates.insert(p);
    }
    void loadProgram(const std::string & filename);
    void setIdbs(std::unordered_set<std::string> && idbs) {
        this->idbs = std::move(idbs);
    }
    const std::unordered_set<std::string> & getIdbs() const {
        return idbs;
    }



    
private:
    
    void compileRule(const aspc::Rule& r,unsigned start, const aspc::Program& p) ;
    void declareDataStructures(const aspc::Rule& r, unsigned start);
    bool matchConstants(const aspc::Rule & rule, const aspc::Atom & atom, Indentation & ind);
    void generateHeadTupleAndMatchConstants(const aspc::Rule & rule, Indentation & ind, const std::set<std::string> & bodyPredicates);
    void setHeadVariables(Indentation & ind, const aspc::Rule & rule);
    bool checkInequalities(const aspc::Rule & rule, Indentation & ind);
    void declareArithmeticVariables(const aspc::Rule & rule, Indentation & ind);
    bool handleEqualCardsAndConstants(const aspc::Rule & r,unsigned i,const std::vector<unsigned>& joinOrder);
    bool handleExpression(const aspc::Rule& r, const aspc::ArithmeticRelation &, unsigned, const std::unordered_set<std::string> &);
    void writeNegativeTuple(const aspc::Rule & rule, std::vector<unsigned> & joinOrder, unsigned start, unsigned i);
    void declareDataStructuresForReasonsOfNegative(const aspc::Program & program);
    void declareDataStructuresForReasonsOfNegative(const aspc::Program & program, const aspc::Literal & lit, std::unordered_set<std::string> & litBoundVariables, std::unordered_set<std::string> & openSet);
    void writeNegativeReasonsFunctions(aspc::Program & program);
    void writeNegativeReasonsFunctionsPrototypes(aspc::Program & program);
    void writeNegativeReasonsFunctions(const aspc::Program & program, const BoundAnnotatedLiteral & lit,
        std::list<BoundAnnotatedLiteral> & toProcessLiterals, std::list<BoundAnnotatedLiteral> & processedLiterals, std::unordered_map <std::string, std::string> & functionsMap);
    void writeNegativeReasonsFunctionsPrototypes(const aspc::Program & program, const BoundAnnotatedLiteral & lit,
        std::list<BoundAnnotatedLiteral> & toProcessLiterals, std::list<BoundAnnotatedLiteral> & processedLiterals, std::unordered_map <std::string, std::string> & functionsMap);
    void initRuleBoundVariables(std::unordered_set<std::string> & ruleBoundVariables, const BoundAnnotatedLiteral & lit, const aspc::Atom & head, bool printVariablesDeclaration);
    void printLiteralTuple(const aspc::Literal* l, const std::vector<bool> & coveredMask) ;
    void printLiteralTuple(const aspc::Literal* l, const std::unordered_set<std::string> & boundVariables);
    void printLiteralTuple(const aspc::Literal* l);
    
    
    std::ostream* out;
    
    std::set<std::string> bodyPredicates;
    
    std::set<std::string> headPredicates;
    
    Indentation ind;
    
    std::set<std::string> declaredMaps;
    
    AspCore2ProgramBuilder* builder;
    
    std::unordered_map<std::string, std::set<std::string> > predicateToAuxiliaryMaps;
    
    std::unordered_map<std::string, std::set<std::string> > predicateToUndefAuxiliaryMaps;

    std::unordered_map<std::string, std::set<std::string> > predicateToFalseAuxiliaryMaps;
    
    std::unordered_set<std::string> modelGeneratorPredicates;
    
    std::unordered_set<std::string> modelGeneratorPredicatesInNegativeReasons;
    
    std::unordered_map<std::string, unsigned> predicateArieties;
    
    std::unordered_set<std::string> idbs;
    
    int mode;
    
};

#endif	/* COMPILATIONMANAGER_H */

