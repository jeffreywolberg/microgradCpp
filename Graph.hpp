#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Value.hpp"

using namespace std;

typedef pair<string, string> Edge;
typedef vector<Edge> EdgeList;

class Graph {
    public: 
        Graph();
        void topo(Value *v, vector<Value*> &list, EdgeList &eList);
        void generateDotFile(const EdgeList &edges, const string &filename);
        void visualizeGraph(Value terminal);
};

