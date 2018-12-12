ARGS = -std=c++11
CPP = g++
TEST_DIR = tests

# Redo this makefile as per http://nuclear.mutantstargoat.com/articles/make/

all: main.cpp tokens2edgelist.o edgelist2tokens.o vertex.o edgelist.o tokens.o
	$(CPP) $(ARGS) -o run main.cpp tokens2edgelist.o edgelist2tokens.o vertex.o edgelist.o tokens.o

tests:
	pushd $(TEST_DIR)
	make
	popd

tokens2edgelist.o: tokens2edgelist.cpp vertex.hpp
	$(CPP) $(ARGS) -c tokens2edgelist.cpp

tokens2edgelist.cpp: tokens2edgelist.hpp

edgelist2tokens.o: edgelist2tokens.cpp vertex.hpp
	$(CPP) $(ARGS) -c edgelist2tokens.cpp

edgelist2tokens.cpp: tokens2edgelist.hpp

edgelist.o: edgelist.cpp
	$(CPP) $(ARGS) -c edgelist.cpp

tokens.o: tokens.cpp
	$(CPP) $(ARGS) -c tokens.cpp

edgelist.cpp: edgelist.hpp

tokens.cpp: tokens.hpp

vertex.o: vertex.cpp
	$(CPP) $(ARGS) -c vertex.cpp

clean:
	rm -rf *.o run
