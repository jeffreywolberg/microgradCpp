#include "Graph.hpp"

using namespace std;

extern map<Operator, string> operatorStringMap;

Graph::Graph() {}

void Graph::topo(Value *v, EdgeList &eList) {
    if (v == nullptr) return;
    for (int i=0; i<v->prev.size(); i++) {
        topo(v->prev[i], eList);
        if (v && v->op != Operator::NONE) {
            eList.push_back({v->prev[i]->getGraphName(), '"' + to_string((long) &v) + " [label=" + "'" + operatorStringMap[v->op] + "'" + "]" + '"'});
        }
    }
    // cout << "v label3: " << v->label << endl;
    if (v && v->op != Operator::NONE) {
        eList.push_back({'"' + to_string((long) &v) + " [label=" + "'" + operatorStringMap[v->op] + "'" + "]" + '"', v->getGraphName()});
    }

}

void Graph::visualizeGraph(Value terminal, filesystem::path imgname) {
    EdgeList eList;
    this->topo(&terminal, eList);
    cout << "Finished topo" << endl;
    for (int i=0; i<eList.size(); i++) {
        cout << i << ") " << eList[i].first << " -> " << eList[i].second << endl; 
    }
    filesystem::path dirname = "tmp";
    filesystem::path filename = "tmp.dot";
    filesystem::path filepath = dirname / filename;
    if (!filesystem::exists(dirname)) {filesystem::create_directory(dirname);}
    this->generateDotFile(eList, filepath);
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

void Graph::generateDotFile(const EdgeList &edges, const string &filename) {
    ofstream dot_file(filename);
    dot_file << "digraph DAG {\n";
    for (const auto &edge : edges) {
        dot_file << "    " << edge.first << " -> " << edge.second << ";\n";
    }
    dot_file << "}\n";
}


int main() {
    // Doesn't work if the same node is used multiple times for different ops
    // _backward attribute gets overwritten the second time
    // Value a = Value(2, "a");
    // Value b = Value(1, "b");
    
    // Value *c = a * b; c->label = "c";
    // Value *d = *c / b; d->label = "d";
    // for (Value *v : vector<Value*>{&a,&b,c,d})
    //     cout << *v << endl;
    // Graph g = Graph();
    // g.visualizeGraph(d, "graphs/graph.png");
    // d->grad = 1;
    // d->backward();
    // g.visualizeGraph(d, "graphs/graph2.png");

    // cout << "d value: " << d->data << endl;

    // works because _backward is not getting overwritten
    Value a = Value(2, "a");
    Value *b = a + a;
    Graph g = Graph();
    b->grad = 1;
    b->backward();
    g.visualizeGraph(*b, "graphs/graph_double.png");

    // does not work because _backward is getting overwritten by multiply
    // Value a = Value(3, "a");
    // Value *b = a + a;
    // Value *c = *b * a;
    // Graph g = Graph();
    // c->grad = 1;
    // c->backward();
    // g.visualizeGraph(*c, "graphs/graph_double2.png");


}
