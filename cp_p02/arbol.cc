/**
*  Autor: Jorge Elías García
*  Email: alu0101472294@ull.edu.es
*  Asignatura: Inteligencia Artificial
*
*  arbol.cc: Contiene la definición de la clase arbol
*/

#include "arbol.h"

//Función para poder determinar si dos nodos son iguales
bool MismoNodo(const Nodo& a, const Nodo& nodo) {
  return (a.f == nodo.f && a.h == nodo.h && a.g==nodo.g && a.i == nodo.i && a.j == nodo.j && a.pos_padre_ == nodo.pos_padre_ && a.pos_v_ == nodo.pos_v_); 
}

//Implementación de la función heurístca de Manhattan
unsigned  Arbol::FuncionHeuristica(const Nodo& nodo) const {
  int recorrido_horizontal = nodo_final_.i - nodo.i;
  int recorrido_vertical = nodo_final_.j - nodo.j; 
  return (abs(recorrido_horizontal) + abs(recorrido_vertical)) * 3; 
}

//Implementación de la función heurística alternativa. Para ello tendremos en cuenta también los movimientos diagonales. Realizaremos tantos movimientos
//diagonales como podamos para acercanos lo máximo a la casilla de final. También le agregaremos el costo de los movimientos laterales/horizontales necesarios. Dará el
//mayor h(n) existente, siendo admisible. 
unsigned Arbol::FuncionHeuristicaAlternativa(const Nodo& nodo) const {
  int i_actual = nodo.i; 
  int j_actual = nodo.j; 
  unsigned mov_diagonales{0}; 
  unsigned mov_lat_ver{0};  
  while(i_actual != nodo_final_.i || j_actual != nodo_final_.j) {
    if(i_actual != nodo_final_.i && j_actual != nodo_final_.j) {
      ++mov_diagonales; 
    } else { ++mov_lat_ver; } 
    //Actualizamos el movimiento
    if(i_actual < nodo_final_.i) {++i_actual; }
    if(i_actual > nodo_final_.i) {--i_actual; }
    if(j_actual < nodo_final_.j) {++j_actual; }
    if(j_actual > nodo_final_.j) {--j_actual; } 
  }

  return unsigned((mov_diagonales * 7) + (mov_lat_ver * 5)); 
}

//Función para cambiar el nodo inicial y final
void Arbol::ModificarNodoInicialFinal() {

  std::cout << "Introduzca la fila del nodo incial: "; 
  int inicio_i{0};
  std::cin >> inicio_i; 
  std::cout << "Introduzca la columna del nodo incial: "; 
  int inicio_j{0};
  std::cin >> inicio_j; 
  if(inicio_i <= 0 || inicio_j<= 0 || inicio_i > laberinto_.matrix_.get_m() || inicio_j > laberinto_.matrix_.get_n()) {
    std::cout << "ERROR. Casilla no existente, se resolverá con las casillas especificadas en el fichero" << std::endl; 
    return; 
  }

  std::cout << "Introduzca la fila del nodo final: "; 
  int final_i{0}; 
  std::cin >> final_i; 
  std::cout << "Introduzca la columna del nodo final: "; 
  int final_j{0};
  std::cin >> final_j; 
  if(final_i <= 0 || final_j<= 0 || final_i > laberinto_.matrix_.get_m() || final_j > laberinto_.matrix_.get_n()) {
    std::cout << "ERROR. Casilla no existente, se resolverá con las casillas especificadas en el fichero" << std::endl; 
    return; 
  }
  
  if(final_i == inicio_i && final_j == inicio_j) { //La casilla inicio no puede ser la de salida
    std::cout << "ERROR. Casilla no existente, se resolverá con las casillas especificadas en el fichero" << std::endl; 
    return; 
  }

  //En este caso las casillas son correctas, por lo que modificamos el laberinto. Donde se encontraban las anteriores entrada y salida se colocará un obstáculo
  laberinto_.matrix_(laberinto_.i_start_, laberinto_.j_start_) = 1; 
  laberinto_.matrix_(laberinto_.i_end_, laberinto_.j_end_) = 1;
  laberinto_.matrix_(inicio_i, inicio_j) = 3; //Modificamos el laberinto 
  laberinto_.matrix_(final_i, final_j) = 4; 
  laberinto_.i_start_ = inicio_i; 
  laberinto_.j_start_ = inicio_j; 
  laberinto_.i_end_ = final_i; 
  laberinto_.j_end_ = final_j; 
  //Modificamos el nodo inicial y final
  nodo_inicial_.i = laberinto_.i_start_; 
  nodo_inicial_.j = laberinto_.j_start_; 
  nodo_inicial_.pos_padre_ = -1; 
  nodo_final_.i = laberinto_.i_end_; 
  nodo_final_.j = laberinto_.j_end_; //Solo almacenamos las coordenadas finales para compararlo durante el recorrido
   
  nodo_inicial_.f = FuncionHeuristica(nodo_inicial_); //Es igual a la función heurística, ja que g(n) = 0. 
}

//Fución para implementar la búsqueda A* y resolver el laberinto
void Arbol::BusquedaA()  {
  abiertos_.push_back(nodo_inicial_); 
  camino_.push_back(nodo_inicial_); 
  bool final{false}; 
  Nodo nodo_actual = nodo_inicial_; 
  int pos_nodo_final{0}; 

  while(abiertos_.size() != 0 && !final) {
    //Inspeccionamos el nodo actual es el nodo final
    if(nodo_actual.i == nodo_final_.i && nodo_actual.j == nodo_final_.j) { //En este caso, hemos llegado a la casilla de salida
      final = true; 
      pos_nodo_final = nodo_actual.pos_v_; 
      cerrados_.push_back(nodo_actual); 
      abiertos_.erase(abiertos_.begin() + PosicionNodoEnAbiertos(nodo_actual)); 
      break; 
    }
    //En este caso no era el nodo final, asi que generamos los hijos. Para ello, debe tener alguna casilla a la que moverse que no pertenezca ja a la rama
    for (int k{N}; k <= SW; ++k) { //Inspeccionamos las 8 alternativas: Norte, Sur, Este, Oeste, NorEste, NorOeste, SurEste y SurOeste
      Nodo nodo_hijo; 
      nodo_hijo.i = nodo_actual.i + i_d[k]; 
      nodo_hijo.j = nodo_actual.j + j_d[k];
      nodo_hijo.pos_padre_ = nodo_actual.pos_v_; 
      if(laberinto_.CasillaTransitable(nodo_hijo.i, nodo_hijo.j) && !NodoEnLaRama(nodo_hijo) && !NodoDescartado(nodo_hijo)) { //Hemos encontrado un hijo que no pertenece a la rama
        //Añadimos a camino_ el nodo
        nodo_hijo.h = FuncionHeuristica(nodo_hijo); 
      //  nodo_hijo.h = FuncionHeuristicaAlternativa(nodo_hijo); 
        if(nodo_hijo.i != nodo_actual.i && nodo_hijo.j != nodo_actual.j) { //En este caso, nos hemos movido en diagonal
          nodo_hijo.g = camino_[nodo_hijo.pos_padre_].g + 7; 
        } else { 
            nodo_hijo.g = camino_[nodo_hijo.pos_padre_].g + 5; 
          }
        nodo_hijo.f = nodo_hijo.g + nodo_hijo.h; 
        nodo_hijo.pos_v_ = camino_.size(); 
        camino_.push_back(nodo_hijo); 
        //A continucación, analizamos si añadirlo a nodos Abiertos. También se encargará de añadirlo a cerrados si hace falta
        AnadirNodoAbierto(nodo_hijo); //En caso de que el mismo nodo ya esté con menor f(n) no lo añadimos. En caso de que ya esté pero con menor f(n) lo añadimos y eliminamos el otro 
      }
    }
    //Hemos añadido los hijos del nodo actual al árbol, por lo que lo cerramos
    cerrados_.push_back(nodo_actual); 
    abiertos_.erase(abiertos_.begin() + PosicionNodoEnAbiertos(nodo_actual)); 
    if(abiertos_.size() != 0) { 
      nodo_actual = DeterminarNuevoNodoActual(); 
    }       
  }

  MostrarResultado(pos_nodo_final); 
}

//Función para mostrar el resultado de la búqueda. Recibimos en que posición del vector camino tenemos al nodo final
void Arbol::MostrarResultado(const int pos_nodo_final) {
  std::ofstream fichero_salida{nombre_fichero_salida_, std::ios_base::out}; 
  if(pos_nodo_final == 0) {
    fichero_salida << "No hay camino" << std::endl; 
    fichero_salida << laberinto_ << std::endl; 
  } else {
      bool final{false}; 
      std::vector<Nodo> camino_final; //Almacenamos aquí el recorrido en orden 
      int pos_nodo{pos_nodo_final}; 
        while(!final) {
          camino_final.insert(camino_final.begin(), camino_[pos_nodo]); 
          if(camino_[pos_nodo].pos_padre_ == -1) { //if(recorrido[pos_nodo].id_ == recorrido[0].id_) { 
            final = true;
          } else {  //Conocemos la posición en el vector del nodo padre
              pos_nodo = camino_[pos_nodo].pos_padre_; 
            }

          if(final) {break; }
        }
      for(unsigned i{0}; i < camino_final.size() - 1; ++i) {
        fichero_salida << "(" << camino_final[i].i << "," << camino_final[i].j << ") --> "; 
        if(i != 0) { laberinto_.matrix_(camino_final[i].i, camino_final[i].j) = PATH_ID; }
      }  
      fichero_salida << "(" << camino_final[camino_final.size() - 1].i << "," << camino_final[camino_final.size() - 1].j << ")" << std::endl;   
      fichero_salida << "Coste del camino: " << camino_final[camino_final.size() - 1].g << std::endl << std::endl; 
      fichero_salida << laberinto_ << std::endl << std::endl; 
    }
  
  //Mostramos los nodos visitados. Estos cerán los nodos cerrados
  fichero_salida << "Nodos visitados: "; 
  for(unsigned i{0}; i < cerrados_.size() - 1; ++i) {
    fichero_salida << "(" << cerrados_[i].i << "," << cerrados_[i].j << "), "; 
  }
  fichero_salida<< "(" << cerrados_[cerrados_.size() - 1].i << "," << cerrados_[cerrados_.size() - 1].j << ")" << std::endl; 
  fichero_salida << "Número de nodos visitados: " << cerrados_.size() << std::endl << std::endl; 

  //Finalmente, mostramos los nodos generados. Estos serán los nodos cerrados más los nodos abiertos más descartados
  fichero_salida << "Nodos generados: "; 
  for(unsigned i{0}; i < cerrados_.size() - 1; ++i) {
    fichero_salida << "(" << cerrados_[i].i << "," << cerrados_[i].j << "), "; 
  }
  fichero_salida << "(" << cerrados_[cerrados_.size() - 1].i << "," << cerrados_[cerrados_.size() - 1].j << ")"; 

  if(abiertos_.size() > 0) {
    for(unsigned i{0}; i < abiertos_.size() - 1; ++i) {
      fichero_salida << ", (" << abiertos_[i].i << "," << abiertos_[i].j << ")"; 
    }
    fichero_salida << ", (" << abiertos_[abiertos_.size() - 1].i << ", " << abiertos_[abiertos_.size() - 1].j << ")"; 
  }
  for(unsigned i{0}; i < borrados_.size() - 1; ++i) {
    fichero_salida << ", (" << borrados_[i].i << "," << borrados_[i].j << ")"; 
  }
  if(borrados_.size() != 0) { fichero_salida<< ", (" << cerrados_[cerrados_.size() - 1].i << "," << cerrados_[cerrados_.size() - 1].j << ")" << std::endl; } 
  fichero_salida << "Número de nodos generados: " << (cerrados_.size() + abiertos_.size() + borrados_.size()) << std::endl << std::endl; 
}

//Función para determinar si un nodo ja pertenece a la rama
bool Arbol::NodoEnLaRama(const Nodo& nodo_hijo) const {
  bool salir{false}; 
  int pos_padre_actual{nodo_hijo.pos_padre_}; 
  if( pos_padre_actual == 0) {return false; } //En caso de que sea el nodo inicial, sabemos que los nodos hijos no están en la rama, porque solo está el nodo inicial en el árbol
  while(!salir) { //Mientras no lleguemos al inicio de la rama seguimos comprobando. SOlo el nodo inicial tiene como valor pos_padre_ = -1
    if(camino_[pos_padre_actual].i == nodo_hijo.i && camino_[pos_padre_actual].j == nodo_hijo.j ) { //En ese caso, el nodo ja pertenece a la rama
      return true; 
    }
    if(camino_[pos_padre_actual].pos_padre_ == -1) {salir = true; }
    pos_padre_actual  = camino_[pos_padre_actual].pos_padre_; 
  }

  return false; 
}

//Función para determinar si añadir un nodo a la lista de nodos abiertos
void Arbol::AnadirNodoAbierto(const Nodo& nodo) {
  bool anadir{true}; 
  for(unsigned i{0}; i < abiertos_.size(); ++i) {
    if(abiertos_[i].i == nodo.i && abiertos_[i].j == nodo.j) { //Se trata del mismo nodo
     if(abiertos_[i].f <= nodo.f) { //El nodo ya estaba en abiertos con una f(n) menor. No lo añadimos a abiertos pero sí a borrados, para constar que ha sido generado. No lo añadimos directamente a cerrados_ para mostrar la salida de manera más fácil de comprobar si está bien
      borrados_.push_back(nodo); 
     } else {
         borrados_.push_back(abiertos_[i]); 
         abiertos_.push_back(nodo); 
         abiertos_.erase(abiertos_.begin() + i); //Borramos la posición i
       }
     anadir = false; 
     i = abiertos_.size(); //Para salir del bucle
    }
  }
  if(anadir) { //En este caso, no estaba dentro de los nodos añadidos
    abiertos_.push_back(nodo); 
  }

}

//Consideraremos que un nodo ha quedado descartado cuando este nodo esté cerrado. En ese caso, ya se ha expandido con un f(n) menor o igual
bool Arbol::NodoDescartado(const Nodo& nodo) const {
  for(unsigned i{0}; i < cerrados_.size(); ++i) {
    if(nodo.i == cerrados_[i].i && nodo.j == cerrados_[i].j) {
      return true; 
    }
  } 

  return false; 
} 

//Función para determinar el nuevo nodo a expandir. Será aquel abierto con menor f(n)
const Nodo Arbol::DeterminarNuevoNodoActual() const {
  Nodo nodo; 
  if(abiertos_.size() != 0) { nodo = abiertos_[0]; } 
  for(unsigned i{1}; i < abiertos_.size(); ++i) {
    if(nodo.f > abiertos_[i].f) {
      nodo = abiertos_[i]; 
    }
  }

  return nodo; 
}

//Función para encontrar la posición del nodo en el vector de abiertos
unsigned Arbol::PosicionNodoEnAbiertos(const Nodo& nodo) const {
  unsigned i{0};  
  for(; i < abiertos_.size(); ++i) {
    if(MismoNodo(abiertos_[i], nodo)) {
      return i; 
    }
  }

  return i; 
} 