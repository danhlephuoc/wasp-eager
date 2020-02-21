

#ifndef INDENTATION_H
#define	INDENTATION_H
#include <ostream>

class Indentation {
    
public:
    Indentation(int depth);
    Indentation(const Indentation & ind);
    friend std::ostream & operator<<(std::ostream& o, const Indentation & i);
    Indentation operator++(int);
    Indentation & operator++();
    Indentation operator--(int);
    Indentation & operator--();
private:
    int depth;
};

#endif	/* INDENTATION_H */

