#ifndef MODELO_JER_HPP
#define MODELO_JER_HPP

#include "matrices-tr.h"
#include "objeto3d.h"
#include "grafo-escena.h"

class C: public NodoGrafoEscena {

 protected:

  Matriz4f * mat_rot;
  
  Matriz4f * mat_esc_luz;
  Matriz4f * mat_tra_luz;

  Matriz4f * mat_rot_ala1;
  Matriz4f * mat_rot_ala2;

  Matriz4f * mat_rot_pata1;
  Matriz4f * mat_rot_pata2;
  Matriz4f * mat_rot_pata3;
  Matriz4f * mat_rot_pata4;
  
 public:
  C();
  unsigned leerNumParametros() const;
  void actualizarEstadoParametro(const unsigned iParam, const float tSec);

};

class Cuerpo: public NodoGrafoEscena {
};

class Luz: public NodoGrafoEscena {
};

class Cabeza: public NodoGrafoEscena {
};


class Ala: public NodoGrafoEscena{
};

class Pata: public NodoGrafoEscena{
};


#endif //MODELO_JER_HPP
