/**
*  Autor: Jorge Elías García
*  Email: alu0101472294@ull.edu.es
*  Asignatura: Inteligencia Artificial
*
*  laberinto.h: Contiene la declaración de la clase laberinto, empleada para almacenar la información del 
*               fichero de entrada
*/

#ifndef LABERINTO_H
#define LABERINTO_H

#include "matrix_t.h"
#include <fstream>

//Forward declaration
class Arbol; 

// indica que no hay obstáculo
#define PASS_ID 0
// indica obstáculo
#define WALL_ID 1
// indica camino de salida
#define PATH_ID 2
// indica inicio del laberinto
#define START_ID 3
// indica la salida del laberinto
#define END_ID 4

// caracteres usados para mostrar el laberinto por pantalla
#define WALL_CHR "█"
#define PASS_CHR " "
#define PATH_CHR "·"
#define START_CHR "3"
#define END_CHR "4"

using namespace AED;

typedef matrix_t<short> matrix_t_short;

// enumera las direcciones Norte, Este, Sur, Oeste (West), Noreste, Noroeste, Sureste y Suroeste
enum direction_t { N, E, S, W, NE, NW, SE, SW };

// define vectores de desplazamiento en las 4 direcciones:
//                    N  E  S  W  NE  NW  SE SW
const short i_d[] = {-1, 0, 1, 0, -1, -1, 1, 1};
const short j_d[] = {0, 1, 0, -1, 1, -1, 1, -1};

class Laberinto {
 private:
  // matriz que guarda los valores leídos de la entrada
  matrix_t_short matrix_;

  // guarda las filas y columnas de entrada (start) y salida (end)
  int i_start_, j_start_, i_end_, j_end_;

 public:
  // constructor y destructor
  Laberinto(void);
  ~Laberinto();

  std::istream& read(std::istream& = cin);
  std::ostream& write(std::ostream& = cout) const;

  friend class Arbol; 

 private:
  bool CasillaTransitable(const int, const int) const;
};

std::istream& operator>>(std::istream&, Laberinto&);
std::ostream& operator<<(std::ostream&, const Laberinto&);


#endif
