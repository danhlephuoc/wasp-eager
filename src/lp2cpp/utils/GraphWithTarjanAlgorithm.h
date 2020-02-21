

#ifndef GRAPHWITHTARJANALGORITHM_H
#define GRAPHWITHTARJANALGORITHM_H

// A C++ program to find strongly connected components in a given
// directed graph using Tarjan's algorithm (single DFS)
#include <iostream>
#include <list>
#include <stack>
#include <vector>
#include <string>
#define NIL -1
 
struct Vertex
{
    int id;
    std::string name;
    std::vector <unsigned int> rules;
    Vertex():id(-1),name("Invalid vertex"){};
    Vertex(int _id, std::string name_):id(_id),name(name_){};
    void addRule (int ruleID){
        rules.push_back(ruleID);
    }
};

// A class that represents an directed graph
class GraphWithTarjanAlgorithm
{
    std::vector< std::list<int>  > adj;  
 
    // A Recursive DFS based function used by SCC()
    void SCCUtil(int u, int disc[], int low[],
                 std::stack<int>& st, bool stackMember[], std::vector< std::vector<int> >& scc);
public:
    GraphWithTarjanAlgorithm(){}
    void addEdge(unsigned int v, unsigned int w);   // function to add an edge to graph
    const std::vector< std::vector <int> > SCC() ;    // prints strongly connected components
};



#endif /* GRAPHWITHTARJANALGORITHM_H */

