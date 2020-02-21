#ifndef EAGERCONSTRAINIMPL_H
#define EAGERCONSTRAINIMPL_H

#include "EagerConstraint.h"
#include <vector>
#include "language/Atom.h"
#include "ExecutionManager.h"
#include "CompilationManager.h"
#include "datastructures/DenseMap.h"
#include <unordered_map>


class EagerConstraintImpl : public EagerConstraint {
public:
    EagerConstraintImpl();
    virtual ~EagerConstraintImpl();
    virtual void setFilename(const std::string & executablePath, const std::string & filename);
    virtual void onLiteralTrue(int var, int decisionLevel, std::vector<int> & propagatedLiterals);
    virtual void onLiteralsUndefined(const std::vector<int> & lits);
    virtual void getReasonForLiteral(int lit, std::vector<int> & reason);
    virtual void addedVarName(int var, const std::string & atomString);
    virtual void onFact(int var);
    virtual void simplifyAtLevelZero(std::vector<int> & output);
    virtual const std::vector<unsigned int> & getVariablesToFreeze();
    virtual const std::string & getFilepath() const;
private:
    
    void performCompilation();
    ExecutionManager executionManager;
    CompilationManager compilationManager;
    std::vector<unsigned> watchedAtoms;
    std::unordered_set<unsigned> watchedAtomsSet;
    std::vector<unsigned> idbWatchedAtoms;
    std::unordered_set<int> facts;
    std::string filepath;
    bool compilationDone = false;
    std::string fileDirectory;
    std::string filename;
};

#endif /* EAGERCONSTRAINIMPL_H */

