
#ifndef TUPLE_WITH_REASONS_H
#define TUPLE_WITH_REASONS_H
#include <vector>
#include <string>
#include <unordered_set>
#include "TupleWithoutReasons.h"
#include <iostream>

class TupleWithReasons : public TupleWithoutReasons {
public:

    TupleWithReasons() {

    }

    TupleWithReasons(const std::string* predicateName, bool negated = false) : TupleWithoutReasons(predicateName, negated) {
    }

    TupleWithReasons(const TupleWithReasons& orig) : TupleWithoutReasons(orig), positiveReasons(orig.positiveReasons),
    negativeReasons(orig.negativeReasons) {
    }

    virtual ~TupleWithReasons() {

    }

    TupleWithReasons(const std::initializer_list<int> & l, bool negated = false) : TupleWithoutReasons(l, negated) {
    }

    TupleWithReasons(const std::initializer_list<int> & l, const std::string * predicateName, bool negated = false) :
    TupleWithoutReasons(l, predicateName, negated) {
    }

    TupleWithReasons(const std::vector<int> & l, const std::string * predicateName, bool negated = false) :
    TupleWithoutReasons(l, predicateName, negated) {
    }

    void addPositiveReason(const TupleWithReasons* r) const {
        positiveReasons.push_back(r);
    }

    void addNegativeReason(const TupleWithReasons & r) const {
        negativeReasons.push_back(r);
    }

    const vector<const TupleWithReasons*> & getPositiveReasons() const {
        return positiveReasons;
    }

    const vector<TupleWithReasons> & getNegativeReasons() const {
        return negativeReasons;
    }

    void setCollisionListIndex(std::vector<const TupleWithReasons *>* collisionList, unsigned index) const {
        collisionsLists[collisionList] = index;
    }

    void removeFromCollisionsLists() const {
        for (auto & collisionListAndIndex : collisionsLists) {
            std::vector<const TupleWithReasons *> & collisionList = *(collisionListAndIndex.first);
            unsigned index = collisionListAndIndex.second;
            collisionList[index] = collisionList[collisionList.size() - 1];
            collisionList[index]->setCollisionListIndex(&collisionList, index);
            collisionList.pop_back();

        }
    }

    bool operator==(const TupleWithReasons& right) const {
        return TupleWithoutReasons::operator==(right);
    }
    
    TupleWithReasons& operator=(const TupleWithReasons& right) {
        if (this == &right) 
            return *this; 
        TupleWithoutReasons::operator =(right);
        positiveReasons = right.positiveReasons;
        negativeReasons = right.negativeReasons;
        collisionsLists = right.collisionsLists;
        
        return *this;
    }



private:
    mutable std::unordered_map<std::vector<const TupleWithReasons *>*, unsigned> collisionsLists;
    mutable vector<const TupleWithReasons*> positiveReasons;
    mutable vector<TupleWithReasons> negativeReasons;

};



#endif /* TUPLE_H */

