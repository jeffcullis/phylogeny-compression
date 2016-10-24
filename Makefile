ARGS = -std=c++0x
GPP = g++ $(ARGS)

all: main.cpp tokens2edgelist.o edgelist2tokens.o vertex.o edgelist.o tokens.o
	$(GPP) -o run main.cpp tokens2edgelist.o edgelist2tokens.o vertex.o edgelist.o tokens.o

tokens2edgelist.o: tokens2edgelist.cpp vertex.hpp
	$(GPP) -c tokens2edgelist.cpp

tokens2edgelist.cpp: tokens2edgelist.hpp

edgelist2tokens.o: edgelist2tokens.cpp vertex.hpp
	$(GPP) -c edgelist2tokens.cpp

edgelist2tokens.cpp: tokens2edgelist.hpp

edgelist.o: edgelist.cpp
	$(GPP) -c edgelist.cpp

tokens.o: tokens.cpp
	$(GPP) -c tokens.cpp

edgelist.cpp: edgelist.hpp

tokens.cpp: tokens.hpp

vertex.o: vertex.cpp
	$(GPP) -c vertex.cpp

clean:
	rm -rf *.o run
