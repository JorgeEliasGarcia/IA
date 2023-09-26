/*
*   Declaración de la clase grafo y arbol.  
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

//Creamos la estructura Nodo, con el identificador del mismo y el coste hasta él desde el nodo padre
typedef struct {
  int id_{0}; 
  int coste_{0};     
  int padre_{0}; //Añadimos este campo para el recorrido en amplitud
  int pos_padre_{0}; //Al añadir este campo, identificamos en que posición estaba el padre, para distinguirlo inequívocamente. También podría hacerse con punteros
  unsigned profundidad_{0}; 

} Nodo; 

class Grafo {
 public: 
  Grafo(const std::string&); //Recibimos el nombre del fichero entrada
  
  //Función para mostrar el recorrido en profundidad entre 2 nodos
  void RecorridoProfundidad(const int, const int, const std::string& fichero_salida);  

  //Función para mostrar el recorrido en amplitud entre 2 nodos
  void RecorridoAmplitud(const int, const int, const std::string& fichero_salida); 

 private: 
  std::vector<std::vector<Nodo>> grafo_; //El grafo será un vector de vectores, como una matriz
  int HijoAnadir(const std::vector<int>&, int); 

}; 





#endif