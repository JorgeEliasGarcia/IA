CXX = g++						         
CXXFLAGS = -std=c++14 -g -Wall	 
LDFLAGS =	

all: laberinto 

laberinto: main.o laberinto.o arbol.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: all clean

	$(CXX) $(CXXFLAGS) -c $<

clean :
	rm -f *.o laberinto doc
	rm -rf *~ basura b i
	rm -rf laberinto
	find . -name '*~' -exec rm {} \;
	find . -name basura -exec rm {} \;