CXX=g++
CFLAGS=-std=c++20 -g
LDFLAGS=
LDLIBS=

Value: Value.o
	$(CXX) $(LDFLAGS) $(LDLIBS) $^ -o $@

Value.o: Value.cpp
	$(CXX) $(CFLAGS) -c $^ -o $@

.PHONY: clean
clean:
	rm -rf main Value core a.out *.o

.PHONY: all
all: clean Value