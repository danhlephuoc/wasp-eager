#ifndef BOUNDANNOTATEDLITERAL_H
#define BOUNDANNOTATEDLITERAL_H
#include <vector>
#include <string>
#include <iostream>


class BoundAnnotatedLiteral {
public:
    virtual ~BoundAnnotatedLiteral();

    BoundAnnotatedLiteral();

    BoundAnnotatedLiteral(const std::string & predicateName, bool negated) :
    predicateName(predicateName), negated(negated) {
    }

    BoundAnnotatedLiteral(const std::string & predicateName, const std::vector<bool> & boundIndexes, bool negated) :
    predicateName(predicateName), boundIndexes(boundIndexes), negated(negated) {
       
    }

    const std::vector<bool> & getBoundIndexes() const {
        return boundIndexes;
    }

    void addBoundInformation(bool v) {
        boundIndexes.push_back(v);
    }

    const std::string & getPredicateName() const {
        return predicateName;
    }
    
    bool isNegated() const {
        return negated;
    }
    
    std::string getStringRep() const {
        std::string res = "";
        if(negated) {
            res+="not_";
        }
        res+=predicateName+"_";
        for(unsigned i=0; i<boundIndexes.size();i++) {
            if(boundIndexes[i]) {
                res+=std::to_string(i)+"_";
            }
        }
        return res;
    } 
   
    bool operator==(const BoundAnnotatedLiteral& right) const {
        return predicateName==right.predicateName && negated == right.negated && boundIndexes == right.boundIndexes;
    }
    
    void print() {
        std::cout<<predicateName<<"(";
        for(unsigned i=0;i<boundIndexes.size();i++) {
            if(boundIndexes[i]) {
                std::cout<<"B";
            } else {
                std::cout<<"_";
            }
            if(i<boundIndexes.size()-1) {
                std::cout<<",";
            }
        }
        std::cout<<")"<<std::endl;
    }

    bool isGround() const {
        for(bool v:boundIndexes) {
            if(!v) {
                return false;
            }
        }
        return true;
    }

private:
    std::string predicateName;
    std::vector<bool> boundIndexes;
    bool negated;
};

#endif /* BOUNDANNOTATEDLITERAL_H */

