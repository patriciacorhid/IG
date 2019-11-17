// *********************************************************************
// **
// ** Informática Gráfica, curso 2019-20
// ** Implementación de la clase 'MallaRevol'
// **
// *********************************************************************

#include "ig-aux.h"
#include "tuplasg.h"
#include "lector-ply.h"
#include "matrices-tr.h"
#include "malla-barrido.h"
#include <math.h>

using namespace std ;

// *****************************************************************************




// Método que crea las tablas de vértices, triángulos, normales y cc.de.tt.
// a partir de un perfil y el número de copias que queremos de dicho perfil.
void MallaBarrido::inicializar
(
   const std::vector<Tupla3f> & perfil,     // tabla de vértices del perfil original
   const unsigned num_copias,  // número de copias del perfil
   const float inicio,
   const float fin
)
{
   // COMPLETAR: Práctica 2: completar: creación de la malla....
  int m = perfil.size();
  int n = num_copias;
  float sep = (fin-inicio)/(num_copias-1);

  //Creación tabla de vértices:
  for (int i = 0; i < n; i++){ //para cada copia
    for (int j = 0; j < m; j++){ //para cada vertice del perfil
      vertices.push_back({perfil[j][X], perfil[j][Y], inicio+i*sep});
    }
  }

  //Creación tabla de triangulos:
  for (int i = 0; i < n-1; i++){
    for (int j = 0; j < m-1; j++){
      int k = i*m+j;
      triangulos.push_back({k, k+m, k+m+1});
      triangulos.push_back({k, k+m+1, k+1});
    }
  }
  
}

//------------------------------------

// constructor, a partir de un archivo PLY

MallaBarridoPLY::MallaBarridoPLY
(
   const std::string & nombre_arch, 
   const unsigned      nperfiles, //numero de perfiles
   const float inicio,
   const float fin
)
{
   ponerNombre( std::string("malla por revolución del perfil en '"+ nombre_arch + "'" ));
   // COMPLETAR: práctica 2: crear la malla de revolución
   // Leer los vértice del perfil desde un PLY, después llamar a 'inicializar'

   std::vector<Tupla3f> perfil;
   LeerVerticesPLY(nombre_arch, perfil);
   inicializar(perfil, nperfiles, inicio, fin);
   
}

//------------------------------------------------

Tunel:: Tunel(
   const int num_verts_per, //número de vértices del perfíl
   const unsigned int nperfiles, // número de perfiles
   const float inicio,
   const float fin)
{
  ponerNombre( std::string("Tunel"));
  std::vector<Tupla3f> perfil;

  perfil.push_back({-1,0,0});
  perfil.push_back({-0.5,0,0});
  
  for(int i=0; i < num_verts_per; i++){
    float alpha = M_PI*i/(num_verts_per-1);
    float s= sin(alpha);
    float c= cos(alpha);
    
    perfil.push_back({-0.5*c, 0.5*s, 0});
  }

  perfil.push_back({0.5,0,0});
  perfil.push_back({1,0,0});
  perfil.push_back({1,1,0});
  perfil.push_back({-1,1,0});
  perfil.push_back({-1,0,0});

  ponerColor({1, 1, 0});

  inicializar(perfil, nperfiles, inicio, fin);
}
