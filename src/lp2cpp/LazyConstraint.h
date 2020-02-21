
#ifndef LAZYCONSTRAINT_H
#define LAZYCONSTRAINT_H
#include <string>
#include <vector>

class LazyConstraint {
public:

    virtual ~LazyConstraint() {
    };
    virtual void setFilename(const std::string & executablePath, const std::string & filename) = 0;
    virtual bool checkAnswerSet(const std::vector<int> & interpretation) = 0;
    virtual void onCheckFail(std::vector<int> & constraints) = 0;
    virtual void addedVarName(int var, const std::string & atomString) = 0;
    virtual void onFact(int var) = 0;
    virtual const std::vector<unsigned int> & getVariablesToFreeze() = 0;
};

#endif /* LAZYCONSTRAINT_H */

