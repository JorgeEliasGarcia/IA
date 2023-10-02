/*
*   Declaración de la clase arbol.  
*
*
*   Autor: Jorge Elías García
*   Asignatura: Inteligencia Artificial
*
*/

#ifndef ARBOL_H
#define ARBOL_H

#include "grafo.h"

//Creamos la estructura Nodo, con el identificador del mismo y el coste hasta él desde el nodo padre
typedef struct {
  int id_{0}; 
  int coste_{0};     
  int padre_{0}; //Añadimos este campo para el recorrido en amplitud
  int pos_padre_{0}; //Al añadir este campo, identificamos en que posición estaba el padre, para distinguirlo inequívocamente. También podría hacerse con punteros
  unsigned profundidad_{0}; 

} Nodo; 

class Arbol {
 public: 
  Arbol(const Grafo& enunciado) { grafo.grafo_ = enunciado.grafo_; }

  //Función para mostrar el recorrido en profundidad entre 2 nodos
  void RecorridoProfundidad(const int, const int, const std::string& fichero_salida);  

  //Función para mostrar el recorrido en amplitud entre 2 nodos
  void RecorridoAmplitud(const int, const int, const std::string& fichero_salida); 

 private:    
  Grafo grafo; 
  int HijoAnadir(const std::vector<Nodo>& visitado, int id_nodo); 
  //Funciones que no acceden a los miembros privados, pero son necesarias para el correcto funcionamiento
  bool YaAnadido(const std::vector<Nodo>&, const int); 
  bool NodoEnLaRama(const std::vector<Nodo>&, const int, const int);  
  void MostrarCamino(const std::vector<Nodo>&, const std::vector<int>&, const std::vector<int>&, const std::string&); 
  void MostrarCamminoAmplitud(const std::vector<Nodo>&, const int, const std::string&); 
  
}; 

#endif