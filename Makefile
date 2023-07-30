CXX=g++
CFLAGS=-std=c++20 -g
LDFLAGS=
LDLIBS=

Graph: Graph.o Value.o
	$(CXX) $(LDFLAGS) $(LDLIBS) $^ -o $@

Graph.o: Graph.cpp
	$(CXX) $(CFLAGS) -c $^ -o $@

Value: Value.o
	$(CXX) $(LDFLAGS) $(LDLIBS) $^ -o $@

Value.o: Value.cpp
	$(CXX) $(CFLAGS) -c $^ -o $@

.PHONY: clean
clean:
	rm -rf main Value Graph core a.out *.o

.PHONY: all
all: clean Value