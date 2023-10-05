/**
*  Autor: Jorge Elías García
*  Email: alu0101472294@ull.edu.es
*  Asignatura: Inteligencia Artificial
*
*  laberinto.h: Programa cliente para resolver el problema del laberinto utilziando una búsqueda
                A*
*/

#include "arbol.h"

int main(int argc, char* argv[]) {

  Laberinto laberinto;
  std::ifstream fichero_entrada{argv[1], std::ios_base::in}; 

  fichero_entrada >> laberinto;
  std::cout << laberinto << endl;

  Arbol arbol(laberinto); 
  arbol.BusquedaA(); 
  
  return 0;     
}