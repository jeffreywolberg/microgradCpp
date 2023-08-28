#ifndef _GRAPH_
#define _GRAPH_

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <unistd.h>
#include <sys/wait.h>
#include <filesystem>
#include <set>

#include "MLP.hpp"

using namespace std;

typedef pair<string, string> Edge;
typedef vector<Edge> EdgeList;

class Graph {
    public: 
        Graph();
        void topo(Value *v, vector<Value*> &list, set<Value*> &visited);
        void generateDotFile(vector<Value*> topoList, const EdgeList &edges, const string &filename);
        void visualizeGraph(vector<Value *> terminalNodes, filesystem::path);
        void generateEdgeList(Value *v, EdgeList &eList, set<Value*> &visited);
        void backward(Value *terminal);
        void zeroGrad(Value *terminal);
};

#endif
