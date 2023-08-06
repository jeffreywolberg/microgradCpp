CXX=g++
CFLAGS=-std=c++17 -g
LDFLAGS=
LDLIBS=

Graph: Graph.o Layer.o Operator.o Value.o Neuron.o
	$(CXX) $(LDFLAGS) $(LDLIBS) $^ -o $@

Graph.o: Graph.cpp
	$(CXX) $(CFLAGS) -c $^ -o $@

Layer: Layer.o Operator.o Value.o Neuron.o
	$(CXX) $(LDFLAGS) $(LDLIBS) $^ -o $@

Layer.o: Layer.cpp
	$(CXX) $(CFLAGS) -c $^ -o $@

Neuron: Operator.o Value.o Neuron.o
	$(CXX) $(LDFLAGS) $(LDLIBS) $^ -o $@

Neuron.o: Neuron.cpp
	$(CXX) $(CFLAGS) -c $^ -o $@

Value: Value.o Operator.o
	$(CXX) $(LDFLAGS) $(LDLIBS) $^ -o $@

Value.o: Value.cpp
	$(CXX) $(CFLAGS) -c $^ -o $@

Operator.o: Operator.cpp
	$(CXX) $(CFLAGS) -c $^ -o $@

.PHONY: clean
clean:
	rm -rf main MLP Neuron Operator Value Graph core a.out *.o

.PHONY: all
all: clean Value