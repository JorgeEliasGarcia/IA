/**
*  Autor: Jorge Elías García
*  Email: alu0101472294@ull.edu.es
*  Asignatura: Inteligencia Artificial
*
*  laberinto.cc: Contiene la definición de la clase laberinto,
*/

#include "laberinto.h"

//Constructor
Laberinto::Laberinto() : matrix_(), i_start_(-1), j_start_(-1), i_end_(-1), j_end_(-1) {}

//Destructor
Laberinto::~Laberinto() {}

//Función para determinar si una casilla es transitable
bool Laberinto::CasillaTransitable(const int i, const int j) const {
  return (i >= 1 && j >= 1 && i <= matrix_.get_m() && j <= matrix_.get_n() &&
          matrix_(i, j) != WALL_ID );
}



//Sobrecarga del operador de entrada
std::istream& operator>>(std::istream& is, Laberinto& laberinto) { return laberinto.read(is); }

//Función para leer el laberinto de entrada
std::istream& Laberinto::read(std::istream& is) {
  int m, n;
  is >> m >> n;
  assert(m > 0 && n > 0);

  matrix_.resize(m, n);

  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      short s;
      is >> s;

      // si el dato es un START_ID -> entrada al laberinto
      if (s == START_ID) {
        i_start_ = i;
        j_start_ = j;
      }
      // si el dato es un END_ID -> salida al laberinto
      else if (s == END_ID) {
        i_end_ = i;
        j_end_ = j;
      }

      matrix_(i, j) = s;
    }
  }

  // comprobamos que se han leído correctamente la entrada y la salida
  assert(i_start_ != -1 && j_start_ != -1 && i_end_ != -1 && j_end_ != -1);

  return is;
}

//Función para mostrar el laberinto por pantalla
std::ostream& Laberinto::write(std::ostream& os) const {
  os << matrix_.get_m() << "x" << matrix_.get_n() << endl;
  for (int i = 1; i <= matrix_.get_m(); i++) {
    for (int j = 1; j <= matrix_.get_n(); j++) switch (matrix_(i, j)) {
        case START_ID:
          os << START_CHR;
          break;
        case END_ID:
          os << END_CHR;
          break;
        case WALL_ID:
          os << WALL_CHR;
          break;
        case PASS_ID:
          os << PASS_CHR;
          break;
        case PATH_ID:
          os << PATH_CHR;
          break;
      }
    os << endl;
  }

  return os;
}


// Sobrecarga del operador de salida
std::ostream& operator<<(std::ostream& os, const Laberinto& M) { return M.write(os); }