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
  const std::string kFicheroSalida{argv[2]}; 
  Arbol arbol(laberinto, kFicheroSalida); 
  unsigned opcode{0}; 
  std::cout << "Si desea cambiar las casillas de entrada y salida introduzca un 1. Introduzca cualquier otro número natural para "
               "continuar con las casillas especificadas en el fichero" << std::endl; 
  std::cin >> opcode; 
  if(opcode == 1) {
    arbol.ModificarNodoInicialFinal(); 
  }
  arbol.BusquedaA(); 
  
  return 0;     
}