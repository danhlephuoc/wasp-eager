#ifndef EAGERCONSTRAINT_H
#define EAGERCONSTRAINT_H
#include <string>
#include <vector>

class EagerConstraint {
public:

    virtual ~EagerConstraint() {
    };
    virtual void setFilename(const std::string & executablePath, const std::string & filename) = 0;
    virtual void onLiteralTrue(int var, int decisionLevel, std::vector<int> & propagatedLiterals) = 0;
    virtual void onLiteralsUndefined(const std::vector<int> & lits) = 0;
    virtual void getReasonForLiteral(int lit, std::vector<int> & reason) = 0;
    virtual void addedVarName(int var, const std::string & atomString) = 0;
    virtual void onFact(int var) = 0;
    virtual const std::vector<unsigned int> & getVariablesToFreeze() = 0;
};

#endif /* EAGERCONSTRAINT_H */

