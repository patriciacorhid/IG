#ifndef MODELO-JER_HPP
#define MODELO-JER_HPP

#include "matrices-tr.h"
#include "objeto3d.h"
#include "grafo-escena.h"

class C: public NodoGrafoEscena {

 protected:

  Matriz4f * mat_esc_cuerpo;
  Matriz4f * mat_rot_cuerpo;
  Matriz4f * mat_tra_cuerpo;
  
  Matriz4f * mat_esc_cabeza;
  Matriz4f * mat_tra_cabeza;
  
 public:
  C();
  unsigned leerNumParametros() const;
  void actualizarEstadoParametro(const unsigned iParam, const float tSec);

};

class Cuerpo: public NodoGrafoEscena {
};

class Cabeza: public NodoGrafoEscena {

};


class Ala: public NodoGrafoEscena{

  protected:
  Matriz4f * mat_esc_ala;
  Matriz4f * mat_rot_ala;
  Matriz4f * mat_tra_ala;
  
 public:
  Ala();
  unsigned leerNumParametros() const;
};


#endif //MODELO-JER_HPP
