#ifndef DENSEMAP_H
#define DENSEMAP_H
#include <unordered_map>
#include <iostream>
#include <vector>
#include <list>

const unsigned DENSE_MAP_TOTAL_MEMORY = (sizeof NULL) * 1 * 100 * 1024; //100KB in si

template <class T>
class DenseMap {
    static_assert(std::is_pointer<T>::value, "Expected a pointer");

public:

    //Size of NULL is typically 8 byte, i.e. 32 bit

    DenseMap() {
        lookup_size = DENSE_MAP_TOTAL_MEMORY / (sizeof NULL);
        fastLookup = std::vector<T*>(lookup_size, NULL);
    }

    virtual ~DenseMap() {
    }

    void clear() {

        std::fill(fastLookup.begin(), fastLookup.end(), (T*) NULL);
        elements.clear();
        std::unordered_map<unsigned, T*>::clear();
    }

    T& operator[](unsigned key) {
        if (key < lookup_size) {
            if(!fastLookup[key]) {
                elements.push_back(std::make_pair(key, T()));
                fastLookup[key] = &elements.back().second;
            }            
            return *(fastLookup[key]);
        }
        if(!slowLookup.count(key)) {
            elements.push_back(std::make_pair(key, T()));
            slowLookup[key] = &elements.back().second;
        }
        return *(slowLookup[key]);

    }

    unsigned count(unsigned key) {
        if (key < lookup_size) {
            return fastLookup[key] != NULL ? 1 : 0;
        }
        return slowLookup.count(key);
    }
    
    typename std::list<std::pair<unsigned, T> >::const_iterator begin() const {
        return elements.begin();
    }
    
    typename std::list<std::pair<unsigned, T> >::const_iterator end() const {
        return elements.end();
    }
    


private:

    std::unordered_map<unsigned, T*> slowLookup;
    std::vector<T*> fastLookup;
    std::list<std::pair<unsigned, T> > elements;
    unsigned lookup_size;

};

#endif /* DENSEMAP_H */


