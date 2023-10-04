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

#define TRACE(x) cout << (#x) << "= " << (x) << endl


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
#define START_CHR "A"
#define END_CHR "B"

using namespace AED;

typedef matrix_t<short> matrix_t_short;
typedef matrix_t<bool> matrix_t_bool;

// enumera las direcciones Norte, Este, Sur y Oeste (West)
enum direction_t { N, E, S, W };

// define vectores de desplazamiento en las 4 direcciones:
//                    N   E  S   W
const short i_d[] = {-1, 0, 1, 0};
const short j_d[] = {0, 1, 0, -1};

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

  // método para resolver el laberinto y que invoca al otro método recursivo
  bool solve(void);

  std::istream& read(std::istream& = cin);
  std::ostream& write(std::ostream& = cout) const;

 private:
  bool is_ok_(const int, const int) const;
  bool solve_(const int, const int);
  unsigned int contador_ = 0; 
};

std::istream& operator>>(std::istream&, Laberinto&);
std::ostream& operator<<(std::ostream&, const Laberinto&);


#endif