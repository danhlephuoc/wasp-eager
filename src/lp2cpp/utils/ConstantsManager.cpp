
#include "ConstantsManager.h"
#include "SharedFunctions.h"
#include <climits>
#include <iostream>

using namespace std;

const int halfMaxInt = INT_MAX / 2;

ConstantsManager::ConstantsManager() : constantsCounter(halfMaxInt) {

}

int ConstantsManager::mapConstant(const std::string & key) {
    if (isInteger(key)) {
        return stoi(key);
    }
    if (!constantToIntMap.count(key)) {
        constantToIntMap[key] = constantsCounter;
        inverseMap.push_back(key);
        constantsCounter++;
        return constantsCounter - 1;
    }
    //TODO avoid duplicated access
    return constantToIntMap[key];
}

string ConstantsManager::unmapConstant(int mapped) const {
    if (mapped >= halfMaxInt) {
        return inverseMap[mapped - halfMaxInt];
    }
    return to_string(mapped);
}

const string& ConstantsManager::getPredicateName(const string& predicateName) {

    const auto & find = predicateNames.find(predicateName);
    if (find != predicateNames.end()) {
        return *find;
    }
    return *(predicateNames.insert(predicateName).first);
}
