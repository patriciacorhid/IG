// *********************************************************************
// **
// ** Informática Gráfica
// ** Definición de los métodos del Modelo Jerrquico
// **
// *********************************************************************

#include <iostream>
#include "modelo-jer.h"
#include "ig-aux.h"
#include "matrices-tr.h"
#include "grafo-escena.h"
#include "malla-ind.h"
#include "malla-revol.h"
#include "practicas.h"
#include "materiales-luces.h"
#include "latapeones.h"
#include <math.h>

using namespace std ;

// *********************************************************************

LataPeones::LataPeones(){

  ponerNombre("Lata y Peones");

  //Añadir Lata
  agregar(new Lata());

  //Añadir Peon madera
  agregar(MAT_Traslacion(0, 0, 5));
  agregar(MAT_Traslacion(0, 1.4, 0));
    
  NodoGrafoEscena * nodo_peon1 = new NodoGrafoEscena;

  Textura * tex_peon1 = new Textura("../recursos/imgs/text-madera.jpg");
  Material * mat_peon1 = new Material(tex_peon1, 0.5, 0.5, 0.5, 0.5);

  MallaRevol * peon1 = new MallaRevolPLY("../recursos/plys/peon.ply", 20);

  nodo_peon1->agregar(mat_peon1);
  nodo_peon1->agregar(peon1);
  agregar(nodo_peon1);

  //Añadir Peon difuso

  agregar(MAT_Traslacion(3, 0, 0));

  NodoGrafoEscena * nodo_peon2 = new NodoGrafoEscena;

  Material * mat_peon2 = new Material(0.5, 0.5, 0.5, 0.5);
  MallaRevol * peon2 = new MallaRevolPLY("../recursos/plys/peon.ply", 20);

  peon2->ponerColor({0.6, 0.6, 0.6});
  nodo_peon2->agregar(mat_peon2);
  nodo_peon2->agregar(peon2);
  agregar(nodo_peon2);

  //Añadir Peon semidifuso

  agregar(MAT_Traslacion(3, 0, 0));

  NodoGrafoEscena * nodo_peon3 = new NodoGrafoEscena;

  Material * mat_peon3 = new Material(0.5, 0.5, 0.5, 0.5);
  MallaRevol * peon3 = new MallaRevolPLY("../recursos/plys/peon.ply", 20);

  peon3->ponerColor({0.3, 0.3, 0.3});
  nodo_peon3->agregar(mat_peon3);
  nodo_peon3->agregar(peon3);
  agregar(nodo_peon3);
  
}

Lata::Lata(){

  ponerNombre("Lata");

  //Parte superior de la lata
  
  NodoGrafoEscena * nodo_psup = new NodoGrafoEscena;

  Material * mat_psup = new Material(0.2, 0.8, 0.8, 0.5);
  //Material * mat_psup = new Material(0, 0, 1, 0);

  MallaRevol * psup = new MallaRevolPLY("../recursos/plys/lata-psup.ply", 20);

  psup->ponerColor({0.4, 0.4, 0.4});

  agregar(MAT_Escalado(5, 5, 5));

  nodo_psup->agregar(mat_psup);
  nodo_psup->agregar(psup);
  agregar(nodo_psup);

  //Parte inferior de la lata

  NodoGrafoEscena * nodo_pinf = new NodoGrafoEscena;

  Material * mat_pinf = new Material(0.2, 0.8, 0.8, 0.5);

  MallaRevol * pinf = new MallaRevolPLY("../recursos/plys/lata-pinf.ply", 20);

  pinf->ponerColor({0.4, 0.4, 0.4});

  nodo_pinf->agregar(mat_pinf);
  nodo_pinf->agregar(pinf);
  agregar(nodo_pinf);

  //Parte central de la lata

  NodoGrafoEscena * nodo_pcue = new NodoGrafoEscena;

  Textura * tex_pcue = new Textura("../recursos/imgs/lata-coke.jpg");
  Material * mat_pcue = new Material(tex_pcue, 0.2, 0.8, 0.8, 0.5);

  MallaRevol * pcue = new MallaRevolPLY("../recursos/plys/lata-pcue.ply", 20);

  nodo_pcue->agregar(mat_pcue);
  nodo_pcue->agregar(pcue);
  agregar(nodo_pcue);
}