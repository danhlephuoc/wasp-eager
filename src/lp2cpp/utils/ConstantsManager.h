
#ifndef CONSTANTSMANAGER_H
#define	CONSTANTSMANAGER_H

#include <unordered_map>
#include <vector>
#include <string>
#include <unordered_set>

class ConstantsManager {
public:
    static ConstantsManager& getInstance() {
        static ConstantsManager instance;
        return instance;
    }
    ConstantsManager();
    int mapConstant(const std::string & constant);
    std::string unmapConstant(int mapped) const;
    const std::string & getPredicateName(const std::string & predicateName);

private:
    std::unordered_map<std::string, int> constantToIntMap;
    std::vector<std::string> inverseMap;
    int constantsCounter;
    std::unordered_set<std::string> predicateNames;
};

#endif	/* CONSTANTSMANAGER_H */

