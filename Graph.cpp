#include "Graph.hpp"


using namespace std;

Graph::Graph() {}

void Graph::topo(Value *v, EdgeList &eList) {
    for (int i=0; i<v->prev.size(); i++) {
        topo(v->prev[i], eList);
        eList.push_back({v->prev[i]->getGraphName(), '"' + to_string((long) &v) + " [label=" + "'" + v->op + "'" + "]" + '"'});
    }
    if (v->op.size() > 0) eList.push_back({'"' + to_string((long) &v) + " [label=" + "'" + v->op + "'" + "]" + '"', v->getGraphName()});

}

void Graph::visualizeGraph(Value terminal) {
    EdgeList eList;
    this->topo(&terminal, eList);
    for (int i=0; i<eList.size(); i++) {
        cout << i << ") " << eList[i].first << " -> " << eList[i].second << endl; 
    }
    filesystem::path dirname = "tmp";
    filesystem::path filename = "tmp.dot";
    if (!filesystem::exists(dirname)) {filesystem::create_directory(dirname);}
    filesystem::path imgname = "graph.png";
    this->generateDotFile(eList, filename);
    pid_t pid = fork();
    if (pid == 0) {
        char *args[] = {(char *)"/opt/homebrew/bin/dot", (char *)"-Tpng", (char*) filename.c_str(), (char *)"-o", (char *) imgname.c_str(), nullptr};
        execvp(args[0], args);
        cout << "Exec failed";
    } else {
        int status;
        waitpid(pid, &status, 0);
        cout << "Wrote computational graph to: " << imgname << endl;
    }
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
    Value d = Value(257, "d");
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
