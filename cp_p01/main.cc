/*
*   Programa cliente para el recorrido en profundidad y amplitud del grafo
*   presente en el fichero de entrada, indicando en la línea de comandos. 
*
*
*   Autor: Jorge Elías García
*   Asignatura: Inteligencia Artificial
*
*/

#include "arbol.h"

int main(int argc, char* argv[]) {
  const std::string kFicheroEntrada{argv[1]}; 
  Grafo grafo(kFicheroEntrada); 
  Arbol arbol(grafo); 
  std::cout << "Introduzca un 0 para recorrido en profundidad. Introduzca cualquier otro "
               "número para recorrido en amplitud" << std::endl; 
  unsigned opcode; 
  std::cin >> opcode; 
  int nodo_inicial, nodo_final; 
  std::cout << std::endl << "Introduzca el nodo inicial: " << std::endl; 
  std::cin >> nodo_inicial; 
  std::cout << "Introduzca el nodo final: " << std::endl; 
  std::cin >> nodo_final;  
  const std::string kFicheroSalida{argv[2]}; 
  if(opcode == 0) {
    arbol.RecorridoProfundidad(nodo_inicial - 1, nodo_final - 1, kFicheroSalida); //Le restamos uno, ya que el grafo trabaja con vectores, que comienzan en la posición cero
  } else {
      arbol.RecorridoAmplitud(nodo_inicial -1, nodo_final - 1, kFicheroSalida);
    }
   
  
  return 0;     
}