
#include "AspCore2InstanceBuilder.h"

AspCore2InstanceBuilder::AspCore2InstanceBuilder() {
}

void AspCore2InstanceBuilder::onAggregate(bool) {

}

void AspCore2InstanceBuilder::onAggregateElement() {

}

void AspCore2InstanceBuilder::onAggregateFunction(char*) {

}

void AspCore2InstanceBuilder::onAggregateGroundTerm(char*, bool) {

}

void AspCore2InstanceBuilder::onAggregateLowerGuard() {

}

void AspCore2InstanceBuilder::onAggregateNafLiteral() {

}

void AspCore2InstanceBuilder::onAggregateUnknownVariable() {

}

void AspCore2InstanceBuilder::onAggregateUpperGuard() {

}

void AspCore2InstanceBuilder::onAggregateVariableTerm(char*) {

}

void AspCore2InstanceBuilder::onArithmeticOperation(char) {

}

void AspCore2InstanceBuilder::onAtom(bool) {
}

void AspCore2InstanceBuilder::onBody() {

}

void AspCore2InstanceBuilder::onBodyLiteral() {
}

void AspCore2InstanceBuilder::onBuiltinAtom() {

}

void AspCore2InstanceBuilder::onChoiceAtom() {

}

void AspCore2InstanceBuilder::onChoiceElement() {

}

void AspCore2InstanceBuilder::onChoiceElementAtom() {

}

void AspCore2InstanceBuilder::onChoiceElementLiteral() {

}

void AspCore2InstanceBuilder::onChoiceLowerGuard() {

}

void AspCore2InstanceBuilder::onChoiceUpperGuard() {

}

void AspCore2InstanceBuilder::onConstraint() {

}

void AspCore2InstanceBuilder::onDirective(char*, char*) {

}

void AspCore2InstanceBuilder::onEqualOperator() {

}

void AspCore2InstanceBuilder::onExistentialAtom() {

}

void AspCore2InstanceBuilder::onExistentialVariable(char*) {

}

void AspCore2InstanceBuilder::onFunction(char*, int) {

}

void AspCore2InstanceBuilder::onGreaterOperator() {
}

void AspCore2InstanceBuilder::onGreaterOrEqualOperator() {
}

void AspCore2InstanceBuilder::onHead() {
}

void AspCore2InstanceBuilder::onHeadAtom() {
    problemInstance.push_back(new aspc::Literal(false, aspc::Atom(predicateName, buildingTerms)));
    buildingTerms.clear();
}

void AspCore2InstanceBuilder::onLessOperator() {
}

void AspCore2InstanceBuilder::onLessOrEqualOperator() {
}

void AspCore2InstanceBuilder::onNafLiteral(bool) {
}

void AspCore2InstanceBuilder::onPredicateName(char* predicateName) {
    //why the following does not work?
    //this->predicateName = predicateName;
    this->predicateName = predicateName;



}

void AspCore2InstanceBuilder::onQuery() {

}

void AspCore2InstanceBuilder::onRule() {

}

void AspCore2InstanceBuilder::onTerm(int) {

}

void AspCore2InstanceBuilder::onTerm(char* value) {
    buildingTerms.push_back(value);
}

void AspCore2InstanceBuilder::onTermDash() {

}

void AspCore2InstanceBuilder::onTermParams() {

}

void AspCore2InstanceBuilder::onTermRange(char*, char*) {

}

void AspCore2InstanceBuilder::onUnequalOperator() {
}

void AspCore2InstanceBuilder::onUnknownVariable() {
}

void AspCore2InstanceBuilder::onWeakConstraint() {

}

void AspCore2InstanceBuilder::onWeightAtLevels(int, int, int) {

}

const  std::vector<aspc::Literal*> & AspCore2InstanceBuilder::getProblemInstance() {
    return problemInstance;
}

AspCore2InstanceBuilder::~AspCore2InstanceBuilder() {
    for(aspc::Literal* a: problemInstance) {
        delete a;
    }
}


