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
#include <math.h>

using namespace std ;

// *********************************************************************

C::C(){

  int i;

  Cuerpo *cuerpo = new Cuerpo();

  //Añadimos la cabeza

  Cabeza *cabeza = new Cabeza();

  cabeza->agregar(MAT_Traslacion(3, 0, 0));

  Esfera * esfera_cabeza = new Esfera(20,20);

  esfera_cabeza->ponerColor({0, 0, 0}); //Cabeza negra

  Textura * text_cabeza = new Textura("../trabajo/imgs/body.jpg");
  Material * mat_cabeza = new Material(text_cabeza, 0.8, 0.8, 0.8, 0.8);
  cabeza->agregar(mat_cabeza);
    
  cabeza->agregar(esfera_cabeza);

  cuerpo->agregar(cabeza);
  

  //Añadimos la lucecita

  Luz *luz = new Luz();
  
  i = luz->agregar(MAT_Traslacion(-3, 0, 0));
  mat_tra_luz = luz->leerPtrMatriz(i);
  
  i = luz->agregar(MAT_Escalado(1, 1, 1));
  mat_esc_luz = luz->leerPtrMatriz(i);

  Esfera * esfera_luz = new Esfera(20,20);

  esfera_luz->ponerColor({1, 1, 0}); //Lucecita amarilla

  Textura * text_luz = new Textura("../trabajo/imgs/light.jpg");
  Material * mat_luz = new Material(text_luz, 0.8, 0.8, 0.8, 0.8);

  luz->agregar(mat_luz);
  luz->agregar(esfera_luz);

  cuerpo->agregar(luz);

  //Añadimos el ala1

  Ala *ala1 = new Ala();

  i = ala1->agregar(MAT_Rotacion(0, 1, 0, 0));
  mat_rot_ala1 = ala1->leerPtrMatriz(i);

  ala1->agregar(MAT_Traslacion(0, 0, -2));
  
  ala1->agregar(MAT_Escalado(0.6, 0.05, 2));

  Esfera * esfera_ala1 = new Esfera(20,20);

  esfera_ala1->ponerColor({0.8, 1, 1});

  Textura * text_ala1 = new Textura("../trabajo/imgs/aa.jpg");
  Material * mat_ala1 = new Material(text_ala1, 0.8, 0.8, 0.8, 0.8);

  ala1->agregar(mat_ala1);
  ala1->agregar(esfera_ala1);

  cuerpo->agregar(ala1);

  //Añadimos el ala2

  Ala *ala2 = new Ala();

  i = ala2->agregar(MAT_Rotacion(0, 1, 0, 0));
  mat_rot_ala2 = ala2->leerPtrMatriz(i);

  ala2->agregar(MAT_Traslacion(0, 0, 2));
  
  ala2->agregar(MAT_Escalado(0.6, 0.05, 2));

  Esfera * esfera_ala2 = new Esfera(20,20);

  esfera_ala2->ponerColor({0.8, 1, 1});

  Textura * text_ala2 = new Textura("../trabajo/imgs/aa.jpg");
  Material * mat_ala2 = new Material(text_ala2, 0.8, 0.8, 0.8, 0.8);

  ala2->agregar(mat_ala2);
  ala2->agregar(esfera_ala2);

  cuerpo->agregar(ala2);

  //Añadimos pata1

  Pata *pata1 = new Pata();

  pata1->agregar(MAT_Traslacion(-1, -0.25, 0.25));

  pata1->agregar(MAT_Rotacion(-30, 1, 0, 0));

  i = pata1->agregar(MAT_Rotacion(0, 0, 0, 1));
  mat_rot_pata1 = pata1->leerPtrMatriz(i);

  //La ponemos en el origen para controlar mejor la rotación
  pata1->agregar(MAT_Traslacion(0, -1, 0));
  
  pata1->agregar(MAT_Escalado(0.15, 0.5, 0.15));

  Esfera * esfera_pata1 = new Esfera(20,20);

  esfera_pata1->ponerColor({0, 0, 0});

  Textura * text_pata1 = new Textura("../trabajo/imgs/pata.jpg");
  Material * mat_pata1 = new Material(text_pata1, 0.8, 0.8, 0.8, 0.8);

  pata1->agregar(mat_pata1);
  pata1->agregar(esfera_pata1);

  cuerpo->agregar(pata1);

  //Añadimos pata2

  Pata *pata2 = new Pata();

  pata2->agregar(MAT_Traslacion(-1, -0.25, -0.25));

  pata2->agregar(MAT_Rotacion(30, 1, 0, 0));

  i = pata2->agregar(MAT_Rotacion(0, 0, 0, 1));
  mat_rot_pata2 = pata2->leerPtrMatriz(i);

  //La ponemos en el origen para controlar mejor la rotación
  pata2->agregar(MAT_Traslacion(0, -1, 0));
  
  pata2->agregar(MAT_Escalado(0.15, 0.5, 0.15));

  Esfera * esfera_pata2 = new Esfera(20,20);

  esfera_pata2->ponerColor({0, 0, 0});

  Textura * text_pata2 = new Textura("../trabajo/imgs/pata.jpg");
  Material * mat_pata2 = new Material(text_pata2, 0.8, 0.8, 0.8, 0.8);

  pata2->agregar(mat_pata2);
  pata2->agregar(esfera_pata2);

  cuerpo->agregar(pata2);

  //Añadimos pata3

  Pata *pata3 = new Pata();

  pata3->agregar(MAT_Traslacion(1, -0.25, -0.25));

  pata3->agregar(MAT_Rotacion(30, 1, 0, 0));

  i = pata3->agregar(MAT_Rotacion(0, 0, 0, 1));
  mat_rot_pata3 = pata3->leerPtrMatriz(i);

  //La ponemos en el origen para controlar mejor la rotación
  pata3->agregar(MAT_Traslacion(0, -1, 0));
  
  pata3->agregar(MAT_Escalado(0.15, 0.5, 0.15));

  Esfera * esfera_pata3 = new Esfera(20,20);

  esfera_pata3->ponerColor({0, 0, 0});

  Textura * text_pata3 = new Textura("../trabajo/imgs/pata.jpg");
  Material * mat_pata3 = new Material(text_pata3, 0.8, 0.8, 0.8, 0.8);

  pata1->agregar(mat_pata3);
  pata3->agregar(esfera_pata3);

  cuerpo->agregar(pata3);

  //Añadimos pata4

  Pata *pata4 = new Pata();

  pata4->agregar(MAT_Traslacion(1, -0.25, 0.25));

  pata4->agregar(MAT_Rotacion(-30, 1, 0, 0));

  i = pata4->agregar(MAT_Rotacion(0, 0, 0, 1));
  mat_rot_pata4 = pata4->leerPtrMatriz(i);

  //La ponemos en el origen para controlar mejor la rotación
  pata4->agregar(MAT_Traslacion(0, -1, 0));
  
  pata4->agregar(MAT_Escalado(0.15, 0.5, 0.15));

  Esfera * esfera_pata4 = new Esfera(20,20);

  esfera_pata4->ponerColor({0, 0, 0});

  Textura * text_pata4 = new Textura("../trabajo/imgs/pata.jpg");
  Material * mat_pata4 = new Material(text_pata1, 0.8, 0.8, 0.8, 0.8);

  pata4->agregar(mat_pata4);
  pata4->agregar(esfera_pata4);

  cuerpo->agregar(pata4);

  //Añadimos ojo1 a la libélula

  Ojo *ojo1 = new Ojo();
  
  ojo1->agregar(MAT_Traslacion(3.9, 0.2,-0.4));

  i = ojo1->agregar(MAT_Traslacion(0, 0, 0));
  mat_tras_ojo1 = ojo1->leerPtrMatriz(i);

  i = ojo1->agregar(MAT_Escalado(1, 1, 1));
  mat_esc_ojo1 = ojo1->leerPtrMatriz(i);

  ojo1->agregar(MAT_Escalado(0.2,0.2,0.2));
  ojo1->agregar(MAT_Rotacion(180, 0, 0, 1));

  Esfera * esfera_ojo1 = new Esfera(20, 20);

  esfera_ojo1->ponerColor({1, 1, 1});

  Textura * text_ojo1 = new Textura("../trabajo/imgs/ojo.jpg");
  Material * mat_ojo1 = new Material(text_ojo1, 0.8, 0.8, 0.8, 0.8);

  ojo1->agregar(mat_ojo1);
  ojo1->agregar(esfera_ojo1);

  cuerpo->agregar(ojo1);

  //Añadimos ojo2

  Ojo *ojo2 = new Ojo();
  
  ojo2->agregar(MAT_Traslacion(3.9, 0.2, 0.4));

  i = ojo2->agregar(MAT_Traslacion(0, 0, 0));
  mat_tras_ojo2 = ojo2->leerPtrMatriz(i);

  i = ojo2->agregar(MAT_Escalado(1, 1, 1));
  mat_esc_ojo2 = ojo2->leerPtrMatriz(i);

  ojo2->agregar(MAT_Escalado(0.2,0.2,0.2));
  ojo2->agregar(MAT_Rotacion(180, 0, 0, 1));

  Esfera * esfera_ojo2 = new Esfera(20, 20);

  esfera_ojo2->ponerColor({1, 1, 1});
  Textura * text_ojo2 = new Textura("../trabajo/imgs/ojo.jpg");
  Material * mat_ojo2 = new Material(text_ojo2, 0.8, 0.8, 0.8, 0.8);

  ojo2->agregar(mat_ojo2);
  ojo2->agregar(esfera_ojo2);

  cuerpo->agregar(ojo2);
  
  //Añadimos el cuerpo de la libélula
  
  cuerpo->agregar(MAT_Escalado(2.5 , 1 , 1));

  Esfera * esfera_cuerpo = new Esfera(20,20);

  esfera_cuerpo->ponerColor({0.4, 0.4, 0.2});

  Textura * text_cuerpo = new Textura("../trabajo/imgs/body.jpg");
  Material * mat_cuerpo = new Material(text_cuerpo, 0.8, 0.8, 0.8, 0.8);

  cuerpo->agregar(mat_cuerpo);
  cuerpo->agregar(esfera_cuerpo);
  
  //Hacemos que se mueva la libélula alrededor del eje Y
  i = agregar(MAT_Rotacion(0, 0, 1, 0));
  mat_rot = leerPtrMatriz(i);

  i = agregar(MAT_Traslacion(0, 0, 0));
  mat_tras = leerPtrMatriz(i);
  
  agregar(MAT_Traslacion(0, 0, -3));

  agregar(cuerpo);  
  
}

unsigned C::leerNumParametros() const{
  return 13;
}

void C::actualizarEstadoParametro(const unsigned iParam, const float tSec ){

  double v;

  switch(iParam){
  case 0:
    //v = a + b*sen (a = posicion inicial, b = variación) 
    v = 1 + sin(2*M_PI*tSec)*0.5; //Radio de 1.5 a 0.5
    *mat_esc_luz = MAT_Escalado(v, v, v);
    *mat_tra_luz = MAT_Traslacion(-2-v, 0, 0);    
    break;
  case 1:
    v = sin(2*M_PI*tSec)*45; //Rotacion de -45 a 45 
    *mat_rot_ala1 = MAT_Rotacion(v, 1, 0, 0);
    break;
  case 2:
    v = -sin(2*M_PI*tSec)*45; //Rotacion de -45 a 45
    *mat_rot_ala2 = MAT_Rotacion(v, 1, 0, 0);
    break;
  case 3:
    v = sin(2*M_PI*tSec)*30; //Rotacion de -30 a 30
    *mat_rot_pata1 = MAT_Rotacion(v, 0, 0, 1);
    break;
  case 4:
    v = -sin(2*M_PI*tSec)*30; //Rotacion de -30 a 30
    *mat_rot_pata2 = MAT_Rotacion(v, 0, 0, 1);
    break;
  case 5:
    v = -sin(2*M_PI*tSec)*30; //Rotacion de -30 a 30
    *mat_rot_pata3 = MAT_Rotacion(v, 0, 0, 1);
    break;
  case 6:
    v = sin(2*M_PI*tSec)*30; //Rotacion de -30 a 30
    *mat_rot_pata4 = MAT_Rotacion(v, 0, 0, 1);
    break;
  case 7:
    v = sin(2*M_PI*tSec)*0.2; //Traslación 
    *mat_tras_ojo1 = MAT_Traslacion(0, 0, v);
    break;
  case 8:
    v = 1 + sin(2*M_PI*tSec)*0.2;; //Escalado
    *mat_esc_ojo1 = MAT_Escalado(v, v, v);
    break;
  case 9:
    v = sin(2*M_PI*tSec)*0.2; //Traslación 
    *mat_tras_ojo2 = MAT_Traslacion(0, 0, v);
    break;
  case 10:
    v = 1 + sin(2*M_PI*tSec)*0.2; //Escalado
    *mat_esc_ojo2 = MAT_Escalado(v, v, v);
    break;    
  case 11:
    v = -tSec*90; //Rotación 360
    *mat_rot = MAT_Rotacion(v, 0, 1, 0);
    break;
  case 12:
    v = sin(2*M_PI*tSec)*0.5; //Traslacion
    *mat_tras = MAT_Traslacion(0, v, 0);
    break; 
  }
  
}
