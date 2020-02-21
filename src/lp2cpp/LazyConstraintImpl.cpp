#include "LazyConstraintImpl.h"
#include <fstream>
#include "CompilationManager.h"
#include "ExecutionManager.h"
#include "language/Literal.h"
#include "../util/WaspOptions.h"
#include "utils/FilesManagement.h"


#ifdef PRINT_EXEC_TIMES
#include <chrono>
using namespace std::chrono;
#endif

LazyConstraintImpl::LazyConstraintImpl(): compilationManager(LAZY_MODE) {

}


void LazyConstraintImpl::performCompilation() {
    string executablePathAndName = wasp::Options::arg0;
    string executablePath = executablePathAndName;
    for (int i = executablePath.size() - 1; i >= 0; i--) {
        if (executablePath[i] == '/') {
            executablePath = executablePath.substr(0, i);
            break;
        }
    }

    FilesManagement fileManagement;
    string executorPath = executablePath + "/src/lp2cpp/Executor.cpp";
    int fd = fileManagement.tryGetLock(executorPath);
    string hash = fileManagement.computeMD5(executorPath);
    std::ofstream outfile(executorPath);
    compilationManager.setOutStream(&outfile);
    compilationManager.lp2cpp();
    outfile.close();
    string newHash = fileManagement.computeMD5(executorPath);
    executionManager.compileDynamicLibrary(executablePath, newHash != hash);
    fileManagement.releaseLock(fd, executorPath);
    compilationDone = true;
}

void LazyConstraintImpl::setFilename(const std::string & fileDirectory, const std::string & filename) {
    this-> fileDirectory = fileDirectory;
    this -> filename = filename;
    this -> filepath = fileDirectory + "/" + filename;
    FilesManagement fileManagement;
    if (!fileManagement.exists(filepath)) {
        throw std::runtime_error("Failed to compile lazy program: file " + filepath + " does not exist.");
    }
    compilationManager.loadProgram(filepath);



}

aspc::Literal* parseLiteral(const std::string & literalString) {
    string predicateName;
    unsigned i = 0;
    for (i = 0; i < literalString.size(); i++) {
        if (literalString[i] == '(') {
            predicateName = literalString.substr(0, i);
            break;
        }
        if (i == literalString.size() - 1) {
            predicateName = literalString.substr(0);
        }
    }
    aspc::Literal* literal = new aspc::Literal(predicateName);
    for (; i < literalString.size(); i++) {
        char c = literalString[i];
        if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_') {
            int start = i;
            int openBrackets = 0;
            while ((c != ' ' && c != ',' && c != ')') || openBrackets > 0) {
                if (c == '(') {
                    openBrackets++;
                } else if (c == ')') {
                    openBrackets--;
                }
                i++;
                c = literalString[i];
            }
            literal->addTerm(literalString.substr(start, i - start));
        }
    }
    return literal;

}

void LazyConstraintImpl::addedVarName(int var, const std::string & literalString) {
    //cout<<atomString<<endl;
    aspc::Literal * atom = parseLiteral(literalString);
    //atom.print();
    //cout<<endl;
    this->literals[var] = atom;
    literalsMap[*atom] = var;
    compilationManager.insertModelGeneratorPredicate(atom->getPredicateName());
    if (compilationManager.getBodyPredicates().count(atom->getPredicateName())) {
        watchedAtoms.push_back(var);
    }

}

void LazyConstraintImpl::onFact(int var) {
    facts.insert(var);
}


#ifdef PRINT_EXEC_TIMES
long prop_time = 0;
long solv_time = 0;

high_resolution_clock::time_point t1;
high_resolution_clock::time_point t2 = high_resolution_clock::now();
#endif

bool LazyConstraintImpl::checkAnswerSet(const std::vector<int> & interpretation) {
#ifdef PRINT_EXEC_TIMES
    t1 = high_resolution_clock::now();
    auto solve_duration = duration_cast<microseconds>(t1 - t2).count();
    solv_time += solve_duration;
    cout << "START lazy evaluation" << endl;
#endif


    std::vector<aspc::Literal*> inputInterpretation;
    inputInterpretation.reserve(idbWatchedAtoms.size());
    if (!compilationDone) {
        unordered_set<string> idbs;
        for (int i : interpretation) {
            if (!facts.count(i)) {
                if (i > 0 && literals.count(i)) {
                    idbs.insert(literals[i]->getPredicateName());
                } else if (literals.count(-i)) {
                    idbs.insert(literals[-i]->getPredicateName());
                }
            }
        }
        //move, don't use idbs later on
        compilationManager.setIdbs(std::move(idbs));

        cout << "Writing executor file" << endl;
        performCompilation();
        cout << "Compilation done" << endl;


        for (int i : facts) {
            aspc::Literal* lit;
            if (i > 0 && literals.count(i)) {
                lit = literals[i];
                lit->setNegated(false);

            } else if (literals.count(-i)) {
                lit = literals[-i];
                lit->setNegated(true);
            }
            if (compilationManager.getBodyPredicates().count(lit->getPredicateName())) {
                inputInterpretation.push_back(lit);
            }
        }

        for (const auto & entry : literals) {
            if (compilationManager.getBodyPredicates().count(entry.second->getPredicateName())) {
                watchedAtoms.push_back(entry.first);
                if (compilationManager.getIdbs().count(entry.second->getPredicateName())) {
                    idbWatchedAtoms.push_back(entry.first);
                }
            }
        }

    }

    //add only needed atoms

    for (unsigned atomId : idbWatchedAtoms) {
        aspc::Literal* lit = literals[atomId];
        if (interpretation[atomId] > 0) {
            lit->setNegated(false);
        } else {
            lit->setNegated(true);
        }
        inputInterpretation.push_back(lit);
    }
#ifdef PRINT_EXEC_TIMES
    cout << "Answer set check" << endl;
#endif    
    executionManager.executeProgramOnFacts(inputInterpretation);
#ifdef PRINT_EXEC_TIMES
    cout << "Violations: " << executionManager.getFailedConstraints().size() << endl;
#endif   
#ifdef PRINT_EXEC_TIMES
    cout << "END lazy evaluation" << endl;
    t2 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(t2 - t1).count();

    prop_time += duration;

    cout << "tot_propr " << prop_time / 1000 << endl;
    cout << "tot_solv " << solv_time / 1000 << endl;
#endif
    return executionManager.getFailedConstraints().empty();


}

const std::vector<unsigned int> & LazyConstraintImpl::getVariablesToFreeze() {
    return watchedAtoms;
}

void LazyConstraintImpl::onCheckFail(std::vector<int> & constraints) {
    //For every failed constraint, the list of atoms that failed the constraint
    constraints.push_back(0);
    //executionManager.shuffleFailedConstraints();
    for (unsigned i = 0; i < executionManager.getFailedConstraints().size(); i++) {
        //cout << "reasons: \n";
        for (const aspc::Literal & literal : executionManager.getFailedConstraints()[i]) {
            //TODO avoid double access
            const auto& atomIt = literalsMap.find(literal);
            if (!literal.isNegated()) {
                //cerr << literal.getAtom().getTermAt(0) << " ";
            } else {
                //cerr << literal.getAtom().getTermAt(1) << " ";
            }

            if (atomIt != literalsMap.end()) {
                //literal.print();
                //cout<<" ";
                if (literal.isNegated()) {
                    constraints.push_back(atomIt->second);
                } else {
                    constraints.push_back(-atomIt->second);
                }
            } else {
                //                cerr<<"literal not found\n";
            }
        }
        //cout << endl;
        constraints.push_back(0);
    }
    if (constraints.size() > 2) {
        //cerr << " bad " << executionManager.getFailedConstraints().size() << endl;
    }
}

const string& LazyConstraintImpl::getFilepath() const {
    return filepath;
}

LazyConstraintImpl::~LazyConstraintImpl() {
    for (auto & a : literals) {
        delete a.second;
    }
}

