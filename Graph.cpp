#include "Graph.hpp"

using namespace std;

extern map<Operator, string> operatorStringMap;

Graph::Graph() {}

void Graph::topo(Value *v, vector<Value*> &list, set<Value*> &visited) {
    if (v == nullptr) return;
    if (visited.find(v) != visited.end()) return;
    visited.insert(v);
    for (int i=0; i<v->prev.size(); i++) {
        topo(v->prev[i], list, visited);
    }
    list.push_back(v);
}

void Graph::generateEdgeList(Value *v, EdgeList &eList, set<Value*> &visited) {
    if (v == nullptr) return;
    if (visited.find(v) != visited.end()) return;
    visited.insert(v);
    for (Value *ch : v->prev) {
        generateEdgeList(ch, eList, visited);
        if (v && v->op != Operator::NONE) {
            eList.push_back({ch->getGraphName(), v->getGraphOpName()});
        }
    }
    if (v && v->op != Operator::NONE) {
        eList.push_back({v->getGraphOpName(), v->getGraphName()});
    }
}

void Graph::visualizeGraph(vector<Value *>terminalNodes, filesystem::path imgname) {
    vector<Value*> topoList;
    set<Value*> visited;
    EdgeList eList;
    for (Value *terminal : terminalNodes) {
        visited.clear();
        this->topo(terminal, topoList, visited);
        cout << "Finished topo" << endl;
        for (int i=0; i<topoList.size(); i++) {
            cout << i << ") " << *topoList[i];
        }
        visited.clear();
        generateEdgeList(terminal, eList, visited);
    }
    filesystem::path dirname = imgname.parent_path();
    filesystem::path filename = imgname.stem();
    filename.replace_extension(".dot");
    filesystem::path filepath = dirname / filename;
    if (!filesystem::exists(dirname)) {filesystem::create_directory(dirname);}
    this->generateDotFile(topoList, eList, filepath);
    pid_t pid = fork();
    if (pid == 0) {
        char *args[] = {(char *)"/opt/homebrew/bin/dot", (char *)"-Tpng", (char*) filepath.c_str(), (char *)"-o", (char *) imgname.c_str(), nullptr};
        execvp(args[0], args);
        cout << "Exec failed";
    } else {
        int status;
        waitpid(pid, &status, 0);
        cout << "Wrote computational graph to: " << imgname << endl;
    }
} 

void Graph::generateDotFile(vector<Value*> topoList, const EdgeList &edges, const string &filename) {
    ofstream dot_file(filename);
    dot_file << "digraph DAG {\n";
    for (const auto &node : topoList) {
        dot_file << "    " << node->getGraphName() << ";" << endl;
        if (node->op != Operator::NONE) {
            dot_file << "    " << node->getGraphOpName() << " [label=" << '"' << operatorStringMap[node->op] << '"' << "];" << endl;
        }
    }
    dot_file << "\n";

    for (const auto &edge : edges) {
        dot_file << "    " << edge.first << " -> " << edge.second << ";\n";
    }
    dot_file << "}\n";
}

void Graph::backward(Value *terminal) {
    vector<Value*> topoList;
    set<Value*> visited;
    this->topo(terminal, topoList, visited);
    terminal->grad = 1;
    assert(topoList.back() == terminal);
    for (int i=topoList.size()-1; i>=0; i--) {
        if (topoList[i]->_backward != nullptr) topoList[i]->_backward();
    }
}

int main() {
    // Value a = Value(2, "a");
    // Value b = Value(3, "b");
    // Value *c = a * b; c->label="c";
    // Value d = Value(4, "d");
    // Value *e = *c / d; e->label="e";
    // Value *f = d.power(*e); f->label="f";
    // Graph g = Graph();
    // g.backward(f);
    // g.visualizeGraph(*f, "graphs/graph_double3.png");

    Layer l = Layer(2, 4, "l0", false);
    for (Value *v : l.paramaters()) {
        cout << *v;
    }
    vector<Value *> data;
    data.push_back(new Value(.5, "d0"));
    data.push_back(new Value(.25, "d1"));
    // data.push_back(new Value(.75, "d2"));
    // data.push_back(new Value(.05, "d3"));


    vector<Value *> res = l.call(data);
    for (Value *v : res) {
        cout << *v << endl;
    }

    // Graph g = Graph();
    // g.backward(res);
    // g.visualizeGraph(res, "graphs/graph_double3.png");
    Graph g = Graph();
    for (Value *v : res) {
        g.backward(v);
    }
    g.visualizeGraph(res, "graphs/graph_double3.png");
    cout << l;
}