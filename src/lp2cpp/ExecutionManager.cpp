#include "ExecutionManager.h"
#include "DLV2libs/input/InputDirector.h"
#include "parsing/AspCore2InstanceBuilder.h"
#include "Executor.h"
#include <dlfcn.h>
#include <stdlib.h>
#include "language/Program.h"
#include "utils/FilesManagement.h"
#include <cassert>

using namespace std;

ExecutionManager::ExecutionManager() {
}

ExecutionManager::~ExecutionManager() {
#ifndef LP2CPP_DEBUG
    if (executor)
        destroy(executor);
#else 
    delete executor;
#endif
}

void ExecutionManager::launchExecutorOnFile(const char *filename) {
    executor->executeFromFile(filename);
    //print failed constraints
    if (!executor->getFailedConstraints().empty()) {
        cout << "failed constraints:" << endl;
    }
    for (unsigned i = 0; i < executor->getFailedConstraints().size(); i++) {
        for (unsigned j = 0; j < executor->getFailedConstraints()[i].size(); j++) {
            executor->getFailedConstraints()[i][j].print();
            cout << " ";
        }
        cout << "\n";
    }
}

void ExecutionManager::parseFactsAndExecute(const char *filename) {
    DLV2::InputDirector director;
    AspCore2InstanceBuilder* builder = new AspCore2InstanceBuilder();
    director.configureBuilder(builder);
    vector<const char*> fileNames;
    fileNames.push_back(filename);
    director.parse(fileNames);
    executeProgramOnFacts(builder->getProblemInstance());
    delete builder;
}

#ifndef LP2CPP_DEBUG

void ExecutionManager::compileDynamicLibrary(const string & executablePath, bool fileHasChanged) {

    string executorFile = executablePath + "/Executor.so";
    FilesManagement fileManagement;
    if (fileHasChanged || !fileManagement.exists(executorFile)) {
        string command = "cd " + executablePath + " && make -f DynamicLibraryMake -s";
        //cout<<command<<endl;
        int commandReturn = system(command.c_str());
        if (commandReturn) {
            throw std::runtime_error("Failed to execute command " + command);
        }
    }

    void* handle = dlopen(executorFile.c_str(), RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    aspc::Executor * (*create)();


    create = (aspc::Executor * (*)())dlsym(handle, "create_object");

    destroy = (void (*)(aspc::Executor*))dlsym(handle, "destroy_object");

    executor = (aspc::Executor*) create();
}
#else 

void ExecutionManager::compileDynamicLibrary(const string &, bool) {
    executor = new aspc::Executor();
}
#endif

void ExecutionManager::executeProgramOnFacts(const std::vector<aspc::Literal*> & facts) {
    executor->executeProgramOnFacts(facts);

}

void ExecutionManager::executeProgramOnFacts(const std::vector<int> & facts) {
    if(executor) {
        executor->executeProgramOnFacts(facts);
    }

}

const std::vector<std::vector<aspc::Literal> > & ExecutionManager::getFailedConstraints() {
    return executor->getFailedConstraints();
}

const aspc::Executor & ExecutionManager::getExecutor() {
    return *executor;
}

void ExecutionManager::shuffleFailedConstraints() {
    executor-> shuffleFailedConstraints();

}

void ExecutionManager::onLiteralTrue(int var) {
    executor->onLiteralTrue(var);
}

void ExecutionManager::onLiteralUndef(int var) {
    executor->onLiteralUndef(var);
}


void ExecutionManager::onLiteralTrue(const aspc::Literal* l) {
    executor->onLiteralTrue(l);
}

void ExecutionManager::onLiteralUndef(const aspc::Literal* l) {
    executor->onLiteralUndef(l);
}

const std::unordered_map<int, std::vector<int> > & ExecutionManager::getPropagatedLiteralsAndReasons() const {
    return executor->getPropagatedLiteralsAndReasons();
}

void ExecutionManager::initCompiled() {
    executor->init();
}

void ExecutionManager::addedVarName(int var, const std::string& literalString) {
    executor->addedVarName(var, literalString);
}


void ExecutionManager::simplifyAtLevelZero(std::vector<int>& output) {
#ifdef EAGER_DEBUG
    std::cout<<"simplifyAtLevelZero"<<endl;
#endif
    if(!executor) {
        //no constraints and no variables
        return;
    }
    for(auto & e: executor->getPropagatedLiteralsAndReasons()) {
#ifdef EAGER_DEBUG
        std::cout<<"derived at level 0 "<<-e.first<<endl;
#endif
        output.push_back(-e.first);
    }
    
}

void ExecutionManager::clearPropagations() {
    executor->clearPropagations();
}
