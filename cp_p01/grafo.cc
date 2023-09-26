/*
*   Definición de la clase grafo y arbol.  
*
*
*   Autor: Jorge Elías García
*   Asignatura: Inteligencia Artificial
*
*/

#include "grafo.h"

//Constructor a partir del nombre del fichero entrada
Grafo::Grafo(const std::string& nombre_fichero) {
  std::ifstream fichero_entrada{nombre_fichero, std::ios_base::in}; 
  int numero_vertices{0};  
  int vertice_actual{0}; 
  int contador{0}; 
  std::string linea; 
  while(getline(fichero_entrada, linea)) {
    if(numero_vertices != 0) { //La primera linea no hace referencia a un coste, por eso no la añadimos como tal
      int coste = stoi(linea); 
      if(coste != -1) { //Solo añadimos el Vertice en caso de que sea un hijo, es decir de que el coste no sea -1
        Vertice Vertice_actual; //En la posición 0 del vector, añadimos los hijos del vértice 1 y el coste a cada uno de ellos
        Vertice_actual.id_ = contador + 1; 
        Vertice_actual.coste_ = coste;  
        grafo_[vertice_actual].push_back(Vertice_actual); 
        //Si añadimos la arista [1 --> 2], debemos también añadir la arista [2 --> 1]
        Vertice segundo_Vertice; 
        segundo_Vertice.id_ = vertice_actual; 
        segundo_Vertice.coste_ = coste;
        grafo_[contador + 1].push_back(segundo_Vertice); 
      } 
      ++contador; 
      if(contador == numero_vertices - 1) { //En este caso, ya hemos inspeccionado todos los hijos del vertice acutal
        ++vertice_actual; 
        contador = vertice_actual; 
      }
    } else { 
        numero_vertices = stoi(linea); //Determinamos el número de vertices
        grafo_.resize(numero_vertices); 
      }   
  } 
}