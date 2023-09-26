/*
*   Declaración de la clase grafo.  
*
*
*   Autor: Jorge Elías García
*   Asignatura: Inteligencia Artificial
*
*/

#ifndef GRAFO_H
#define GRAFO_H 

#include <fstream>
#include <vector>
#include <string>
#include <iostream>

class Arbol; 

typedef struct {
  int id_{0}; 
  int coste_{0};  //Coste para llegar a ese vértice 
} Vertice;

class Grafo {
 public: 
  Grafo(const std::string&); //Recibimos el nombre del fichero entrada

  Grafo() {}

  friend class Arbol; 
  
 private: 
  std::vector<std::vector<Vertice>> grafo_; //El grafo será un vector de vectores, como una matriz
}; 





#endif