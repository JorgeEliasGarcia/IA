CXX = g++						         
CXXFLAGS = -std=c++14 -g -Wall	 
LDFLAGS =	

all: recorrido 

recorrido: main.o grafo.o arbol.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: all clean

	$(CXX) $(CXXFLAGS) -c $<

clean :
	rm -f *.o recorrido doc
	rm -rf *~ basura b i
	rm -rf recorrido
	find . -name '*~' -exec rm {} \;
	find . -name basura -exec rm {} \;