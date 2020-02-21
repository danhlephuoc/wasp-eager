#ifndef EXECUTIONMANAGER_H
#define EXECUTIONMANAGER_H

#include "language/Program.h"
#include <map>
#include "datastructures/AuxiliaryMap.h"
#include <iostream>
#include "Executor.h"

class ExecutionManager {
public:
    ExecutionManager();
    ~ExecutionManager();
    void compileDynamicLibrary(const std::string & executablePath, bool fileHasChanged);
    void parseFactsAndExecute(const char *filename);
    void launchExecutorOnFile(const char *filename);
    const std::vector<std::vector<aspc::Literal> > & getFailedConstraints();
    void executeProgramOnFacts(const std::vector<aspc::Literal*> & facts);
    void executeProgramOnFacts(const std::vector<int> & facts);
    const aspc::Executor & getExecutor();
    void shuffleFailedConstraints();
    void onLiteralTrue(const aspc::Literal* l);
    void onLiteralUndef(const aspc::Literal* l);
    void onLiteralTrue(int var);
    void onLiteralUndef(int var);
    void addedVarName(int var, const std::string & literalString);
    const std::unordered_map<int, std::vector<int> > & getPropagatedLiteralsAndReasons() const;
    void initCompiled();
    void simplifyAtLevelZero(std::vector<int>& output);
    void clearPropagations();
private:
    aspc::Executor* executor;
    void (*destroy)(aspc::Executor*);

};

#endif /* EXECUTIONMANAGER_H */

