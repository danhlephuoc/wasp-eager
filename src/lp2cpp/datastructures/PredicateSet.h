#ifndef PREDICATESET_H
#define PREDICATESET_H
#include <unordered_set>
#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <unordered_map>

const unsigned PREDICATE_SETS_TOTAL_MEMORY = (sizeof NULL) * 1 * 1024 * 1024; //8MB in size

template <class T, class H>
class PredicateSet : protected std::unordered_set<T, H> {
public:

    //Size of NULL is typically 8 byte, i.e. 32 bit

    PredicateSet(unsigned ariety) : ariety(ariety), lookup_bases(ariety, 0) {
        unsigned total_size = PREDICATE_SETS_TOTAL_MEMORY / (sizeof NULL);
        if (ariety == 0) {
            lookup_size = total_size = 1;
        } else if (ariety == 1) {
            lookup_size = total_size = (unsigned) sqrt(total_size);
        } else {
            lookup_size = (unsigned) std::pow(total_size, 1.0 / ariety);
        }
        lookup = std::vector<T*>(total_size, NULL);
        lookupIterators = std::vector<typename std::list<T>::iterator > (total_size);
    }

    virtual ~PredicateSet() {
    }

    void clear() {

        if (lookupReferences.size() > 0) {
            std::fill(lookup.begin(), lookup.end(), (T*) NULL);
            lookupReferences.clear();
            std::fill(lookup_bases.begin(), lookup_bases.end(), 0);
        }
        std::unordered_set<T, H>::clear();
        tuples.clear();
    }

    std::pair<const T *, bool> insert(T && value) {
        if (canLookup(value)) {
            unsigned pos = valueToPos(value);

            if (lookup[pos] == NULL) {
                lookupReferences.push_back(std::move(value));
                lookup[pos] = &lookupReferences.back();
                lookup[pos]->setId(tuples.size());
                tuples.push_back(lookup[pos]);
                lookupIterators[pos] = lookupReferences.end();
                lookupIterators[pos]--;

                return std::make_pair(&lookupReferences.back(), true);
            }
            return std::make_pair(lookup[pos], false);

        }
        value.setId(tuples.size());
        const auto & insertResult = std::unordered_set<T, H>::insert(std::move(value));
        if (insertResult.second) {
            tuples.push_back(&(*insertResult.first));
        }
        return std::make_pair(&(*insertResult.first), insertResult.second);
    }

    const T * find(const T & value) {
        if (canLookup(value)) {
            return lookup[valueToPos(value)];
        }
        const auto & findResult = std::unordered_set<T, H>::find(value);
        if (findResult == std::unordered_set<T, H>::end()) {
            return NULL;
        }
        return &*findResult;
    }


    //assuming its a copy   

    void erase(const T & value) {
        const T* realValue;
        if (canLookup(value)) {
            unsigned pos = valueToPos(value);
            realValue = lookup[pos];
            if (lookup[pos] == NULL) {
                return;
            }
            lookup[pos] = NULL;
            realValue->removeFromCollisionsLists();
            //tuples[tuples.size() - 1]->setId(realValue->getId());
            tuples[realValue->getId()] = tuples[tuples.size() - 1];
            tuples[realValue->getId()]->setId(realValue->getId());
            tuples.pop_back();
            lookupReferences.erase(lookupIterators[pos]);
        } else {
            const auto & findResult = std::unordered_set<T, H>::find(value);
            if (findResult == std::unordered_set<T, H>::end()) {
                return;
            }
            realValue = &*(findResult);
            realValue->removeFromCollisionsLists();
            //tuples[tuples.size() - 1]->setId(realValue->getId());
            tuples[realValue->getId()] = tuples[tuples.size() - 1];
            tuples[realValue->getId()]->setId(realValue->getId());
            tuples.pop_back();
            std::unordered_set<T, H>::erase(findResult);
        }


    }

    //    std::pair<const T &, bool> insert(T && value) {
    //        return insert(std::move(value));
    //    }

    const std::vector<const T*> & getTuples() const {
        return tuples;
    }

private:

    inline bool canLookup(const T & value) {
        for (unsigned i = 0; i < ariety; i++) {
            if ((value[i] - lookup_bases[i] >= lookup_size) || (value[i] - lookup_bases[i] < 0)) {
                if (lookupReferences.empty() && lookup_size > 0) {
                    lookup_bases[i] = value[i];
                } else {
                    return false;
                }
            }
        }
        return true;
    }

    inline unsigned valueToPos(const T & value) const {
        //Assuming canLookup is checked before
        unsigned pos = 0;
        for (unsigned i = 0; i < ariety; i++) {
            pos += (value[i] - lookup_bases[i]) * std::pow(lookup_size, i);
        }
        return pos;
    }

    std::vector<T*> lookup;
    //for preventing references invalidations
    std::list<T> lookupReferences;

    std::vector<typename std::list<T>::iterator> lookupIterators;

    unsigned ariety;
    int lookup_size;
    std::vector<int> lookup_bases;
    //fast iterations
    std::vector<const T* > tuples;

};

#endif /* PREDICATESET_H */

