#include <iostream>
#include <vector>
#include <string>
#include "Value.hpp"

using namespace std;

class Graph {
    public: 
        Graph();
        void topo(Value *v, vector<Value*> &list);
};

