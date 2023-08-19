CXX = g++
CFLAGS = -std=c++17 -g
LDFLAGS =
LDLIBS =

SRC = Graph.cpp MLP.cpp Layer.cpp Operator.cpp Value.cpp Neuron.cpp
OBJ = $(SRC:.cpp=.o)

all: clean Graph

Graph: Graph.o MLP.o Layer.o Operator.o Value.o Neuron.o
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

clean:
	rm -rf main MLP Neuron Operator Value Graph core a.out *.o

.PHONY: clean