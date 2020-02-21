#ifndef AUXILIARY_MAP_H
#define AUXILIARY_MAP_H
#include <list>
#include <vector>
#include <unordered_map>
#include <cmath>
#include "TupleWithoutReasons.h"

const unsigned AUX_MAPS_TOTAL_MEMORY = (sizeof NULL) * 1 * 1024 * 1024; //8MB in size -> 1KB in size for ariety 1

struct VectorHash {

    inline size_t operator()(const std::vector<int>& v) const {
        size_t seed = 0;
        for (int i : v) {
            seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }

};

template<class T>
class AuxiliaryMap {
public:

    AuxiliaryMap(const std::vector<unsigned> & keyIndices) :
    keySize(keyIndices.size()), keyIndices(keyIndices), lookup_bases(keySize, 0) {
        unsigned total_size = AUX_MAPS_TOTAL_MEMORY / (sizeof NULL);
        if (keySize == 0) {
            lookup_size = total_size = 1;
        } else if (keySize == 1) {
            lookup_size = total_size = (unsigned) sqrt(total_size);
        } else {
            lookup_size = (unsigned) std::pow(total_size, 1.0 / keySize);
        }
        lookup = std::vector<std::vector<const T *>*>(total_size, NULL);

    }

    virtual ~AuxiliaryMap() {
    }

    inline const std::vector< const T* >& getValues(const std::vector<int>& key) const {
        if (canLookup(key)) {
            return lookup[valueToPos(key)] == NULL ? EMPTY_RESULT : *lookup[valueToPos(key)];
        }

        const auto it = tuples.find(key);
        if (it == tuples.end()) {
            return EMPTY_RESULT;
        }
        return it->second;
    }

    inline void insert2(const T & value) {
        std::vector<int> key(keySize);
        for (unsigned i = 0; i < keySize; i++) {
            key[i] = value[keyIndices[i]];
        }
        if (canLookup(key)) {
            unsigned pos = valueToPos(key);
            if (lookup[pos] == NULL) {
                lookupReferences.push_back(std::vector< const T* >());
                lookup[pos] = &lookupReferences.back();

            }
            lookup[pos]->push_back(&value);
            value.setCollisionListIndex(lookup[pos], (unsigned) (lookup[pos]->size()-1));
            return;
        }
        auto & collisionList = tuples[std::move(key)];
        value.setCollisionListIndex(&collisionList, collisionList.size());
        collisionList.push_back(&value);
    }

    void clear() {
        if (lookupReferences.size()) {
            std::fill(lookup.begin(), lookup.end(), (std::vector<const T *>*)NULL);
            lookupReferences.clear();
            std::fill(lookup_bases.begin(), lookup_bases.end(), 0);
        }
        tuples.clear();
    }
protected:

    inline bool canLookup(const std::vector<int> & key) const {
        for (unsigned i = 0; i < keySize; i++) {
            if ((key[i] - lookup_bases[i] >= lookup_size) || (key[i] - lookup_bases[i] < 0)) {
                return false;
            }
        }
        return true;
    }

    inline bool canLookup(const std::vector<int> & key) {
        for (unsigned i = 0; i < keySize; i++) {
            if ((key[i] - lookup_bases[i] >= lookup_size || key[i] - lookup_bases[i] < 0)) {
                if (lookupReferences.empty() && lookup_size > 0) {
                    lookup_bases[i] = key[i];
                } else {
                    return false;
                }
            }
        }
        return true;
    }

    inline unsigned valueToPos(const std::vector<int> & key) const {
        unsigned pos = 0;
        for (unsigned i = 0; i < keySize; i++) {
            pos += (key[i] - lookup_bases[i]) * std::pow(lookup_size, i);
        }
        return pos;
    }

    std::unordered_map<std::vector<int>, std::vector< const T* >, VectorHash > tuples;
    unsigned keySize;
    std::vector<unsigned> keyIndices;
    static const std::vector< const T* > EMPTY_RESULT;
    std::list<std::vector<const T *> > lookupReferences;
    std::vector<std::vector<const T *>*> lookup;
    int lookup_size;
    std::vector<int> lookup_bases;


};

template<class T>
const std::vector< const T* > AuxiliaryMap<T>::EMPTY_RESULT;


#endif /* AUXILIARYMAP_H */

