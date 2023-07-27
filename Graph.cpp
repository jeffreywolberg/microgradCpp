#include "Graph.hpp"


using namespace std;

Graph::Graph() {}

void Graph::topo(Value *v, vector<Value*> &list, EdgeList &eList) {
    for (int i=0; i<v->prev.size(); i++) {
        topo(v->prev[i], list, eList);
        eList.push_back({v->prev[i]->label, v->label});
    }
    list.push_back(v);
}

void Graph::visualizeGraph(Value terminal) {
    EdgeList eListTmp;
    vector<Value*> list;
    this->topo(&terminal, list, eListTmp);
    EdgeList eList;
    // for (int i=eListTmp.size(); i>=0; i--) eList.push_back(eListTmp[i]);
    for (int i=0; i<eListTmp.size(); i++) eList.push_back(eListTmp[i]);
    for (int i=0; i<eList.size(); i++) {
        cout << i << ") " << eList[i].first << " -> " << eList[i].second << endl; 
    }
    // this->generateDotFile()
} 

void Graph::generateDotFile(const EdgeList &edges, const string &filename) {
    ofstream dot_file(filename);
    dot_file << "digraph DAG {\n";
    for (const auto &edge : edges) {
        dot_file << "    " << edge.first << " -> " << edge.second << ";\n";
    }
    dot_file << "}\n";
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
    // g.topo(&e, l);
    g.visualizeGraph(e);
    // for (int i=0; i<l.size(); i++) {
        // cout << i << ") " << *l[i]; 
    // }
}
