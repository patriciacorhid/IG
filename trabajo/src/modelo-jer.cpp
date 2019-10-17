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
#include <math.h>

using namespace std ;

// *********************************************************************

C::C(){

  int i;

  Cuerpo *cuerpo = new Cuerpo();

   //Añadimos la cabeza

  Cabeza *cabeza = new Cabeza();
  
  i = cabeza->agregar(MAT_Traslacion(0, 0, 0));
  mat_tra_cabeza = cabeza->leerPtrMatriz(i);
  
  i = cabeza->agregar(MAT_Escalado(1, 1, 1));
  mat_esc_cabeza = cabeza->leerPtrMatriz(i);

  cabeza->agregar(MAT_Traslacion(-3, 0, 0));

  Esfera * esfera = new Esfera(20,20);

  esfera->ponerColor({0, 1, 0}); //Cabeza verde
    
  cabeza->agregar(esfera);

  cuerpo->agregar(cabeza);
  
  //Añadimos el cuerpo de la libélula (cilindro tumbado)

  i = cuerpo->agregar(MAT_Traslacion(2 , 0 , 0));
  mat_tra_cuerpo = cuerpo->leerPtrMatriz(i);
  
  i = cuerpo->agregar(MAT_Escalado(4 , 1 , 1));
  mat_esc_cuerpo = cuerpo->leerPtrMatriz(i);

  i = cuerpo->agregar(MAT_Rotacion(90, 0, 0 , 1));
  mat_rot_cuerpo = cuerpo->leerPtrMatriz(i);

  Cilindro *cilindro= new Cilindro(20,20);

  cilindro->ponerColor({1, 1, 1});

  cuerpo->agregar(cilindro);

  agregar(cuerpo);

  cout<<"leerNumParametros()"<< leerNumParametros()<<endl;

  //Añadimos un ala
  //agregar(new Ala());
  
}

unsigned C::leerNumParametros() const{
  return 1;
}

void C::actualizarEstadoParametro(const unsigned iParam, const float tSec ){

  switch(iParam){
  case 0:
    cout<<"AEWRDSF"<<endl;
    double v = -3 + sin(2*M_PI*tSec)*0.5; //Radio de 1.5 a 0.5
    *mat_esc_cabeza = MAT_Escalado(v+4, v+4, v+4);
    *mat_tra_cabeza = MAT_Traslacion(-3-v, 0, 0);    
    break;
  }
  
}

//***********************************
//Alas
Ala::Ala(){

  int k = agregar(MAT_Traslacion(0 , 0 , 0));
  mat_tra_ala = leerPtrMatriz(k);

  int j = agregar(MAT_Rotacion(45, 1, 0 , 0));
  mat_rot_ala = leerPtrMatriz(j);

  int i = agregar(MAT_Escalado(0.5 , 2 , 0.5));
  mat_esc_ala = leerPtrMatriz(i);
  
  agregar(new Esfera(20, 20));
  entradas[3].objeto->ponerColor({1, 0.5, 0}); //Cuerpo azul
  
}

unsigned Ala::leerNumParametros() const{
  return 0;
}
