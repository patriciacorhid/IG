#ifndef LATA_PEONES_HPP
#define LATA_PEONES_HPP

#include "matrices-tr.h"
#include "objeto3d.h"
#include "grafo-escena.h"
#include "malla-revol.h"
#include "materiales-luces.h"


class LataPeones: public NodoGrafoEscena {

 protected:

  Matriz4f * mat_rot;
  Matriz4f * mat_tras;
 
  
 public:
  LataPeones();

};

class Lata: public NodoGrafoEscena{
 public:
  Lata();
};

#endif //LATA_PEONES_HPP
