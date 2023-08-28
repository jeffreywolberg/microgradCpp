#include <iostream>
#include <string>
#include "Graph.hpp"

using namespace std;

void sanity_check() {
    // x = Value(-4.0)
    // z = 2 * x + 2 + x
    // q = z.relu() + z * x
    // h = (z * z).relu()
    // y = h + q + q * x
    // y.forward/backward()
    Value two = Value(2.0);
    Graph g = Graph();

    Value *x = new Value(-4.0, "x");
    Value *z = *(*(*x * two) + two) + *x; 
    z->label = "z";
    // cout << *z << endl;
    Value *q = (*z->relu()) + *(*z * *x);
    q->label = "q";

    g.backward(q);
    assert(x->grad == -22);
    g.zeroGrad(q);
    cout << "Q.forward/backward() is a success" << endl;

    int l = 0;
    // cout << *q << endl;
    Value *h = (*z * *z)->relu();
    h->label = "h";
    // cout << *h << endl;
    Value *y = *(*h + *q) + *(*q * *x);
    y->label = "y";
    // cout << *y << endl;
    assert(y->data == -20);

    g.backward(y);
    assert(x->grad == 46);
    cout << "Y.forward/backward() is a success" << endl;
}

void test_more_ops() {
    // a = torch.Tensor([-4.0]).double()
    // b = torch.Tensor([2.0]).double()
    // a.requires_grad = True
    // b.requires_grad = True
    // c = a + b
    // c = c + c + 1
    // c = c + 1 + c + (-a)
    // d = a * b + b**3
    // d = d + d * 2 + (b + a).relu()
    // d = d + 3 * d + (b - a).relu()
    // e = c - d
    // f = e**2
    // g = f / 2.0
    // g = g + 10.0 / f
    // g.forward/backward()
    // apt, bpt, gpt = a, b, g

    Value negOne = Value(-1.0);
    Value one = Value(1.0);
    Value two = Value(2.0);
    Value three = Value(3.0);
    Value ten = Value(10.0);

    Graph graph = Graph();

    Value *a = new Value(-4.0);
    Value *b = new Value(2.0);
    Value *c = *a + *b;
    c = *(*c + *c) + one;
    c = (*(*c + one) + *c);
    c = *c + *(negOne * *a);
    c->label = "c";
    
    graph.backward(c);
    assert(c->data == -1);
    assert(a->grad == 3);
    assert(b->grad == 4);
    cout << "C.forward/backward() is a success" << endl;
    graph.zeroGrad(c);

    Value *d = *(*a * *b) + *b->power(3.0);
    d = *(*(two * *d) + *d) + *((*b + *a)->relu());
    d = *(*(three * *d) + *d) + *(*b - *a)->relu();

    graph.backward(d);
    assert(a->grad == 23);
    // cout << "A grad: " << a->grad << endl;
    // cout << "B grad: " << b->grad << endl;
    assert(b->grad == 97);
    assert(d->data == 6);
    cout << "D.forward/backward() is a success" << endl;
    graph.zeroGrad(d);

    Value *e = *c - *d;
    e->label = "e";

    graph.backward(e);
    // cout << "A grad: " << a->grad << endl;
    // cout << "B grad: " << b->grad << endl;
    // cout << "E data: " << e->data << endl;
    assert(a->grad == -20);
    assert(b->grad == -93);
    assert(e->data == -7);
    cout << "E.forward/backward() is a success" << endl;
    graph.zeroGrad(e);

    Value *f = e->power(2);
    graph.backward(f);
    assert(a->grad == 280);
    assert(b->grad == 1302);
    assert(f->data == 49);
    cout << "F.forward/backward() is a success" << endl;
    graph.zeroGrad(f);

    Value *g = *(*f / two) + *(ten / *f);
    graph.backward(g);
    
    double tol = 1e-6;
    // Got correct values by running karpathy's micrograd and pytorch.
    assert(abs(g->data - 24.70408163265306) < tol);
    assert(abs(a->grad - 138.83381924198252) < tol);
    assert(abs(g->data - 24.70408163265306) < tol);
    cout << "G.forward/backward() is a success" << endl;
}

int main() {
    sanity_check();
    cout << "Sanity check passes!" << endl;
    test_more_ops();
    cout << "More operations check passes!" << endl;

}