

#include "Indentation.h"

Indentation::Indentation(int depth) :depth(depth){
}

Indentation::Indentation(const Indentation & ind) :depth(ind.depth){
}

std::ostream& operator<<(std::ostream& o, const Indentation& ind) {
    for(int i=0;i<ind.depth;i++) {
        o<<"    ";
    }
    return o;
}



Indentation& Indentation::operator++() {
    depth++;
    return *this;
}

Indentation& Indentation::operator--() {
    depth--;
    return *this;
}

Indentation Indentation::operator++(int) {
    Indentation ind(*this);
    depth++;
    return ind;
}

Indentation Indentation::operator--(int) {
    Indentation ind(*this);
    depth--;
    return ind;
}




