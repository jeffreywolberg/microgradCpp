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
#include <compare>
#include <alloca.h>

#include "Value.hpp"

using namespace std;

typedef pair<string, string> Edge;
typedef vector<Edge> EdgeList;

class Graph {
    public: 
        Graph();
        void topo(Value *v, EdgeList &eList);
        void generateDotFile(const EdgeList &edges, const string &filename);
        void visualizeGraph(Value terminal);
};

#endif
