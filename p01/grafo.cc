/*
*   Definición de la clase grafo y arbol.  
*
*
*   Autor: Jorge Elías García
*   Asignatura: Inteligencia Artificial
*
*/

#include "grafo.h"

bool YaAnadido(const std::vector<int>&, const int); 
bool NodoEnLaRama(const std::vector<Nodo>&, const int, const int); 
void MostrarCamino(const std::vector<Nodo>&, const std::vector<int>&, const std::vector<int>&, const std::string&); 
void MostrarCamminoAmplitud(const std::vector<Nodo>&, const int, const std::string&); 

//Constructor a partir del nombre del fichero entrada
Grafo::Grafo(const std::string& nombre_fichero) {
  std::ifstream fichero_entrada{nombre_fichero, std::ios_base::in}; 
  int numero_vertices{0};  
  int vertice_actual{0}; 
  int contador{0}; 
  std::string linea; 
  while(getline(fichero_entrada, linea)) {
    if(numero_vertices != 0) { //La primera linea no hace referencia a un coste, por eso no la añadimos como tal
      int coste = stoi(linea); 
      if(coste != -1) { //Solo añadimos el nodo en caso de que sea un hijo, es decir de que el coste no sea -1
        Nodo nodo_actual; //En la posición 0 del vector, añadimos los hijos del vértice 1 y el coste a cada uno de ellos
        nodo_actual.id_ = contador + 1; 
        nodo_actual.coste_ = coste;  
        grafo_[vertice_actual].push_back(nodo_actual); 
        //Si añadimos la arista [1 --> 2], debemos también añadir la arista [2 --> 1]
        Nodo segundo_nodo; 
        segundo_nodo.id_ = vertice_actual; 
        segundo_nodo.coste_ = coste;
        grafo_[contador + 1].push_back(segundo_nodo); 
      } 
      ++contador; 
      if(contador == numero_vertices - 1) { //En este caso, ya hemos inspeccionado todos los hijos del vertice acutal
        ++vertice_actual; 
        contador = vertice_actual; 
      }
    } else { 
        numero_vertices = stoi(linea); //Determinamos el número de vertices
        grafo_.resize(numero_vertices); 
      }   
  } 
}

//Creamos la función para mostrar el recorrido en profundidad entre 2 nodos
void Grafo::RecorridoProfundidad(const int id_inicial, const int id_final, const std::string& fichero_salida) {
  //En primer lugar, añadimos al recorrido el nodo inicial con un coste de 0 para llegar hasta él
  Nodo nodo_inicial; 
  nodo_inicial.id_ = id_inicial; 
  std::vector<Nodo> recorrido; 
  std::vector<int> pendiente; //USamos un vector de enteros, ya que solo nos interesa el id del nodo. Así ahorramos memoria. 
  std::vector<int> generados; 
  recorrido.push_back(nodo_inicial); 
  std::vector<int> visitado;
  visitado.push_back(nodo_inicial.id_);  
  generados.push_back(nodo_inicial.id_); 
  bool final{false}; 
  while(recorrido.size() != 0 && !final) {
    int id_nodo_actual = recorrido[recorrido.size() - 1].id_; //El nodo actual es el de la última posición del vector. 
    if(id_nodo_actual == id_final) {
      final = true; 
      break; 
    }
    //Añadimos los hijos a pendientes, si no tiene hijos o ya han pertenecen todos al recorrido lo eliminamos
    if(HijoAnadir(visitado, id_nodo_actual) != -1) {
      for(unsigned i{0}; i < grafo_[id_nodo_actual].size(); ++i) { //Añadimos los hijos al vector pendientes de estudio
        if(!YaAnadido(visitado, grafo_[id_nodo_actual][i].id_)) { //Si ya lo estudiamos, no lo añadimos
          pendiente.insert(pendiente.begin(), grafo_[id_nodo_actual][i].id_); //Añadimos el hijo a pendiente
          if(!YaAnadido(generados,grafo_[id_nodo_actual][i].id_)) { generados.push_back(grafo_[id_nodo_actual][i].id_);}
        }
      }
      //El último en ser añadido por el iniciio a pendiente lo añadimos al recorrido
      Nodo nuevo_nodo; 
      nuevo_nodo.id_ = pendiente[0]; 
      for(unsigned i{0}; i < grafo_[id_nodo_actual].size(); ++i) { //Para determinar el coste consultamos el grafo
        if(grafo_[id_nodo_actual][i].id_ == nuevo_nodo.id_) {
          nuevo_nodo.coste_ = grafo_[id_nodo_actual][i].coste_; 
        }
      }
      recorrido.push_back(nuevo_nodo); 
      visitado.push_back(nuevo_nodo.id_); 
      pendiente.erase(pendiente.begin()); 
  
    } else { //En este caso, el nodo no era el final y no tiene hijos, por lo que lo eliminamos
        recorrido.pop_back(); 
      }

    if(recorrido.size() == 0) { //Añado esta sentencia, ya que si el recorrido queda vacío se crea automáticamente un valor por defecto antes del inicio while y genera problemas
      break;  
    }
  } 
  //Mostramos el camino hallado, el coste, los nodos generados y visitados
  MostrarCamino(recorrido, visitado, generados, fichero_salida); 

}

//Función para mostrar el recorrido en amplitud entre 2 nodos
void Grafo::RecorridoAmplitud(const int id_inicial, const int id_final, const std::string& fichero_salida) {
  Nodo nodo_inicial; 
  nodo_inicial.id_ = id_inicial; //EL coste para llegar hasta él mismo será cero
  nodo_inicial.pos_padre_ = -1; 
  std::vector<Nodo> recorrido; 
  recorrido.push_back(nodo_inicial); 
  bool final{false}; 
  unsigned ultimo_anadido{0}; 
  //Los generados serán todos los presentes en recorrido. Los inspeccionados todos aquellos hasta la posición ultimo_añadido y 
  //el camino se realiza partiendo de la posicion ulitmo_añadadido y volviendo atrás gracias al campo padre_ del nodo
  unsigned pos_id_final{0};
  unsigned aux{ultimo_anadido}; 
  //Identificaremos un grafo no conexo en caso de que en alguna iteración no se añada ningún hijo. En ese caso, habremos estudiado todos los nodos alcanzables
  //y, al no añadir ningún hijo y ya haber estudiado todos los nodos alcanzables, sabemos que no hay solución.
  bool hijo_anadido{false}; 
  while(recorrido.size() != grafo_.size() && !final) { 
    hijo_anadido = false; 
    aux = ultimo_anadido;  
    long unsigned int kTamanyo{recorrido.size()}; 
    //Añadimos los hijos del último nivel inspeccionado
    for(unsigned i{aux}; i < kTamanyo; ++i) {
      //Si el nodo actual no es el final, generamos los hijos. En caso de que sea el nodo final, terminamos
      if(recorrido[i].id_ == id_final) {
        final = true; 
        pos_id_final = i; 
        break;  
      }
      //Si no era el nodo final, generamos los hijos que no estén en la rama. 
      for(unsigned j{0}; j < grafo_[recorrido[i].id_].size(); ++j) {
        Nodo nuevo_nodo;
        nuevo_nodo.id_ = grafo_[recorrido[i].id_][j].id_;
        if(!NodoEnLaRama(recorrido, nuevo_nodo.id_, i)) {  
          nuevo_nodo.pos_padre_ = i; //Almacenamos en qué posición está el padre. 
          nuevo_nodo.coste_ = grafo_[recorrido[i].id_][j].coste_; 
          nuevo_nodo.padre_ = recorrido[i].id_; 
          nuevo_nodo.profundidad_ = (recorrido[i].profundidad_ + 1); 
          recorrido.push_back(nuevo_nodo);
          hijo_anadido = true; 
        }
      }
      if(final) {break; }
      ++ultimo_anadido; 
    }
  
    if(final) {break; }
    if(!hijo_anadido) { break; } //No hay solución, no exisete camino

  }

  MostrarCamminoAmplitud(recorrido, pos_id_final, fichero_salida); 
}

//Función para determinar que hijo añadir al recorrido. Devolverá -1 en caso de no haber candidatos
int Grafo::HijoAnadir(const std::vector<int>& visitado, int id_nodo) {
  int id_hijo{-1}; 
  for(unsigned i{0}; i < grafo_[id_nodo].size(); ++i) {
    if(!YaAnadido(visitado, grafo_[id_nodo][i].id_)) {
      return grafo_[id_nodo][i].id_; 
    }
  }
  
  return id_hijo; 
}

//Función para comprobar si un nodo ya está añadido al vector recorrido
bool YaAnadido(const std::vector<int>& visitado, const int id) {
  for(unsigned i{0}; i < visitado.size(); ++i) {
    if(visitado[i] == id) {
      return true; 
    }
  }
  return false; 
}

//Función para mostrar el camino y el costo del mismo
void MostrarCamino(const std::vector<Nodo>& camino, const std::vector<int>& inspeccionados, const std::vector<int>& generados, 
                   const std::string& fichero) {
  std::ofstream fichero_salida{fichero, std::ios_base::out}; 
  if(camino.size() != 0) {
    int total{0}; 
    for(unsigned i{0}; i < camino.size() - 1; ++i) {
      fichero_salida << camino[i].id_ + 1 << "-->"; 
      total += camino[i].coste_; 
    }
    fichero_salida << camino[camino.size() - 1].id_+ 1 << std::endl; 
    total += camino[camino.size() - 1].coste_; 
    fichero_salida << "Coste del camino: " << total << std::endl << std::endl;
  } else {
      fichero_salida << "No se ha encontrado un camino" << std::endl << std::endl; 
    }

  fichero_salida << "Nodos inspeccionados: "; 
  for(unsigned j{0}; j < inspeccionados.size(); ++j) {
    if(j != inspeccionados.size() - 1) {
      fichero_salida << inspeccionados[j] + 1 << ", "; 
    } else { fichero_salida << inspeccionados[j] + 1 << std::endl << std::endl; }
  }

  fichero_salida << "Nodos generados     : "; 
  for(unsigned j{0}; j < generados.size(); ++j) {
    if(j != generados.size() - 1) {
      fichero_salida << generados[j] + 1 << ", "; 
    } else { fichero_salida << generados[j] + 1 << std::endl << std::endl; }
  }
}

void MostrarCamminoAmplitud(const std::vector<Nodo>& recorrido, const int pos_id_final, const std::string& fichero) {
  std::ofstream fichero_salida{fichero, std::ios_base::out}; 
  bool final{false}; 
  int coste{0}; 
  std::vector<int> camino; //Almacenamos aquí el recorrido en orden 
  int pos_nodo{pos_id_final}; 
  //Si pos_id_final == 0, significa que no exisite camino
  while(!final) {
    camino.insert(camino.begin(), recorrido[pos_nodo].id_); 
    coste += recorrido[pos_nodo].coste_; 
    if(recorrido[pos_nodo].pos_padre_ == -1) { //if(recorrido[pos_nodo].id_ == recorrido[0].id_) { 
      final = true;
    } else {  //Conocemos la posición en el vector del nodo padre
        pos_nodo = recorrido[pos_nodo].pos_padre_; 
      }
    if(final) {break; }
  }

  //Mostramos el camino y el coste
  if(pos_id_final != 0) {
    fichero_salida << "Camino: "; 
    for(unsigned i{0}; i < camino.size() - 1; ++i) {
      fichero_salida << camino[i] + 1 << "-->"; 
    }
    //Mostramos el último vértice del camino
    fichero_salida << camino[camino.size() - 1] + 1 << std::endl << "Coste del camino: " << coste << std::endl << std::endl; 
    } else {
        fichero_salida << "No existe camino" << std::endl << std::endl; 
      }

  //Mostramos los nodos inspeccionados
  fichero_salida << "Nodos inspeccionados: "; 
  if(pos_id_final == 0) { //Si no hay camino, los nodos inspeccionados son todos aquellos que hemos añadio a recorrido
    for(unsigned i{0}; i < recorrido.size() - 1; ++i) {
      fichero_salida << recorrido[i].id_ + 1 << ", "; 
    }
    fichero_salida << recorrido[recorrido.size() - 1].id_ + 1 << std::endl; 
  } else {
    for(unsigned i{0}; i < unsigned(pos_id_final); ++i) {
      fichero_salida << recorrido[i].id_ + 1 << ", "; 
    }
    fichero_salida << recorrido[pos_id_final].id_ + 1 << std::endl << std::endl; 
  }
  //Mostramos los nodos generados
  fichero_salida << "Nodos generados     : "; 
  for(unsigned i{0}; i < recorrido.size() - 1; ++i) {
    fichero_salida << recorrido[i].id_ + 1 << ", "; 
    // fichero_salida << "(" << recorrido[i].id_ + 1 << ", " << recorrido[i].profundidad_ << "), ";
  }
  fichero_salida << recorrido[recorrido.size() - 1].id_ + 1 << std::endl; 
 // fichero_salida << "(" << recorrido[recorrido.size() - 1].id_ + 1 << ", " << recorrido[recorrido.size() - 1].profundidad_ << ")";

} 

//Función para determinar si un nodo ya pertenece a la rama del árbol. El id, es el identificador del nodo a comprobar si está en la rama. Por otro lado, recibimos en 
//que posición está el padre para iniciar la búsqueda
bool NodoEnLaRama(const std::vector<Nodo>& recorrido, const int id, const int pos_padre) {
  bool salir{false}; 
  int pos_padre_actual{pos_padre}; 
  if(pos_padre == 0) {return false; } //En caso de que sea el nodo inicial, sabemos que los nodos hijos no están en la rama, porque solo está el nodo inicial en el árbol
  while(!salir) { //Mientras no lleguemos al inicio de la rama seguimos comprobando. SOlo el nodo inicial tiene como valor pos_padre_ = -1
    if(recorrido[pos_padre_actual].id_ == id) { //En ese caso, el nodo ya pertenece a la rama
      return true; 
    }
    if(recorrido[pos_padre_actual].pos_padre_ == -1) {salir = true; }
    pos_padre_actual  = recorrido[pos_padre_actual].pos_padre_; 
  }

  return false; 
} 

//FINALIZADÍSIMO