#include "Graph.hpp"

using namespace std;

Graph::Graph() {}

void Graph::topo(Value *v, vector<Value*> &list) {
    for (int i=0; i<v->prev.size(); i++) {
        topo(v->prev[i], list);
    }
    list.push_back(v);
}

int main() {
    Value a = Value(1, "a");
    Value b = Value(2, "b");
    Value c = a * b; c.label = "c";
    Value d = Value(3, "d");
    Value cd = c+d; cd.label="cd";
    Value e = cd + a;  e.label = "e";
    cout << e << endl;
    vector<Value*> l;
    Graph g = Graph();
    g.topo(&e, l);
    for (int i=0; i<l.size(); i++) {
        cout << i << ") " << *l[i]; 
    }
}
