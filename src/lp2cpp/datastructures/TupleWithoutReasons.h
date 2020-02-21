#ifndef TUPLE_WITHOUT_REASONS_H
#define TUPLE_WITHOUT_REASONS_H
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
struct TuplesHash;

class TupleWithoutReasons : public std::vector<int> {
public:

    TupleWithoutReasons() : predicateName(NULL) {

    }

    TupleWithoutReasons(const std::string* predicateName, bool negated = false) : predicateName(predicateName), negated(negated) {
    }

    TupleWithoutReasons(const TupleWithoutReasons& orig) : std::vector<int>(orig), predicateName(orig.predicateName), negated(orig.negated), id(orig.id) {
    }

    virtual ~TupleWithoutReasons() {

    }

    TupleWithoutReasons(const std::initializer_list<int> & l, bool negated = false) :
    std::vector<int>(l), predicateName(NULL), negated(negated) {
    }

    TupleWithoutReasons(const std::initializer_list<int> & l, const std::string * predicateName, bool negated = false) :
    vector<int>(l), predicateName(predicateName), negated(negated) {
    }

    TupleWithoutReasons(const std::vector<int> & l, const std::string * predicateName, bool negated = false) :
    vector<int>(l), predicateName(predicateName), negated(negated) {
    }

    const std::string* getPredicateName() const {
        return predicateName;
    }

    bool isNegated() const {
        return negated;
    }

    void setNegated(bool negated) {
        this->negated = negated;
    }

    //    void addPositiveReason(const Tuple* r) const {
    //        positiveReasons.push_back(r);
    //    }
    //    
    //    void addNegativeReason(const Tuple & r) const {
    //        negativeReasons.push_back(r);
    //    }
    //
    //    
    //    const vector<const Tuple*> & getPositiveReasons() const {
    //        return positiveReasons;
    //    }
    //    
    //    const vector<Tuple> & getNegativeReasons() const {
    //        return negativeReasons;
    //    }

    unsigned getId() const {
        return id;
    }

    void setId(unsigned id) const {
        this->id = id;
    }

    void setCollisionListIndex(std::vector<const TupleWithoutReasons *>* collisionList, unsigned index) const {
        collisionsLists[collisionList] = index;
    }

    void removeFromCollisionsLists() const {
        for (auto & collisionListAndIndex : collisionsLists) {
            std::vector<const TupleWithoutReasons *> & collisionList = *(collisionListAndIndex.first);
            unsigned index = collisionListAndIndex.second;
            collisionList[index] = collisionList[collisionList.size() - 1];
            collisionList[index]->setCollisionListIndex(&collisionList, index);
            collisionList.pop_back();

        }
    }

    bool operator==(const TupleWithoutReasons& right) const {
        if (predicateName != right.predicateName || size() != right.size()) {
            return false;
        }
        for (unsigned i = 0; i < size(); i++) {
            if (operator[](i) != right[i]) {
                return false;
            }
        }
        return true;
    }

    TupleWithoutReasons& operator=(const TupleWithoutReasons& right) {
        if (this == &right)
            return *this;
        predicateName = right.predicateName;
        collisionsLists = right.collisionsLists;
        id = right.id;
        negated = right.negated;
        std::vector<int>::operator=(right);
        return *this;
    }

    void print() const {
        if (negated) {
            std::cout << "-";
        }
        std::cout << *predicateName << "(";
        for (unsigned i = 0; i < size(); i++) {
            if (i > 0) {
                std::cout << ",";
            }
            std::cout << operator[](i);
        }
        std::cout << ")";
    }




private:
    const std::string * predicateName;
    bool negated;
    mutable unsigned id;
    mutable std::unordered_map<std::vector<const TupleWithoutReasons *>*, unsigned> collisionsLists;
    //    mutable vector<const Tuple*> positiveReasons;
    //    mutable vector<Tuple> negativeReasons;

};

struct TuplesHash {

    inline std::size_t operator()(const TupleWithoutReasons & v) const {
        std::size_t seed = 0;
        for (int i : v) {
            seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }

};



#endif /* TUPLE_H */

