/**
*  Autor: Jorge Elías García
*  Email: alu0101472294@ull.edu.es
*  Asignatura: Inteligencia Artificial
*
*  arbol.h: Contiene la declaración de la clase arbol
*/

#ifndef ARBOL_H
#define ARBOL_H

#include "laberinto.h"
#include <vector>
#include <cmath>

//Creamos la estructura Nodo, para poder implementar el recorrido
typedef struct {
  unsigned f{0}; //f(n) = h(n) + g(n)
  unsigned h{0}; //Función heurística
  unsigned g{0}; //Coste para llegar hasta el nodo n
  int i{0}; //Número de fila
  int j{0}; //Número de columna
  int pos_padre_{0}; //Almacenamos la posición del madre en el vector, para mostrar el recorrido. Será int, para poner -1 al nodo inicial
  unsigned pos_v_{0}; 

} Nodo; 

class Arbol {
 public: 
  Arbol(const Laberinto& laberinto, const std::string& fichero) : laberinto_{laberinto}, nombre_fichero_salida_{fichero} { 
    nodo_inicial_.i = laberinto_.i_start_; 
    nodo_inicial_.j = laberinto.j_start_; 
    nodo_inicial_.pos_padre_ = -1; 
    nodo_final_.i = laberinto_.i_end_; 
    nodo_final_.j = laberinto.j_end_; //Solo almacenamos las coordenadas finales para compararlo durante el recorrido

    nodo_inicial_.f = FuncionHeuristica(nodo_inicial_); //Es igual a la función heurística, ja que g(n) = 0. 
    
  }
  
  //Función para cambiar el nodo inicial y final
  void ModificarNodoInicialFinal(); 
  
  void BusquedaA();
  void MostrarResultado(const int); 

 private: 
  Laberinto laberinto_;
  std::vector<Nodo> camino_;  
  std::vector<Nodo> abiertos_; 
  std::vector<Nodo> cerrados_; 
  std::vector<Nodo> borrados_; 
  Nodo nodo_inicial_; 
  Nodo nodo_final_;  
  unsigned FuncionHeuristica(const Nodo&) const; 
  unsigned FuncionHeuristicaAlternativa(const Nodo&) const; 
  bool NodoEnLaRama(const Nodo&) const; 
  void AnadirNodoAbierto(const Nodo&); 
  bool NodoDescartado(const Nodo&) const; 
  const Nodo DeterminarNuevoNodoActual() const; 
  unsigned PosicionNodoEnAbiertos(const Nodo&) const; 
  std::string nombre_fichero_salida_;  

}; 


#endif