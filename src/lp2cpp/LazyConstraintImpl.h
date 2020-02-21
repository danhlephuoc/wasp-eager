
#ifndef LAZYCONSTRAINTIMPL_H
#define LAZYCONSTRAINTIMPL_H

#include "LazyConstraint.h"
#include <vector>
#include "language/Atom.h"
#include "ExecutionManager.h"
#include "CompilationManager.h"
#include "datastructures/DenseMap.h"
#include <unordered_map>


class LazyConstraintImpl: public LazyConstraint {
public: 
    LazyConstraintImpl();
    virtual void setFilename(const std::string & executablePath, const std::string & filename) override;
    virtual void addedVarName(int var, const std::string & atomString) override;
    virtual void onFact(int var) override;
    virtual bool checkAnswerSet(const std::vector<int> & interpretation) override;
    virtual void onCheckFail(std::vector<int> & constraints) override;
    virtual const std::vector<unsigned int> & getVariablesToFreeze() override;
    virtual const std::string & getFilepath() const;
    virtual ~LazyConstraintImpl();



private:
    void performCompilation();
    DenseMap<aspc::Literal*> literals;
    ExecutionManager executionManager;
    CompilationManager compilationManager;
    std::unordered_map<aspc::Literal, int, aspc::LiteralHash> literalsMap;
    std::vector<unsigned> watchedAtoms;
    std::vector<unsigned> idbWatchedAtoms;
    std::unordered_set<int> facts;
    std::string filepath;
    bool compilationDone = false;
    
    std::string fileDirectory;
    std::string filename;
    
};

#endif /* LAZYCONSTRAINTIMPL_H */

