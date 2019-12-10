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
#include "malla-revol.h"
#include <math.h>

using namespace std ;

// *****************************************************************************




// Método que crea las tablas de vértices, triángulos, normales y cc.de.tt.
// a partir de un perfil y el número de copias que queremos de dicho perfil.
void MallaRevol::inicializar
(
   const std::vector<Tupla3f> & perfil,     // tabla de vértices del perfil original
   const unsigned               num_copias  // número de copias del perfil
)
{

  int m = perfil.size();
  int n = num_copias;
  
  //PRACTICA 4:
  //Cálculo de las coordenadas de texturas
  std::vector<float> d;

  for(int i = 0; i < m-1; i++){
    d.push_back(sqrt(pow(perfil[i+1][X]-perfil[i][X], 2) + pow(perfil[i+1][Y]-perfil[i][Y], 2)));
  }

  std::vector<float> t;

  float suma = 0;
  float total = 0;

  for(int i = 0; i < m-1; i++){
    total+=d[i];
  }
  
  for(int i = 0; i < m-1; i++){
    t.push_back(suma/total);
    suma+=d[i];
  }

  t.push_back(1.0);

  //Cálculo de las normales
  std::vector<Tupla3f> nor_arist;
  Tupla3f aux;

  for(int i = 0; i < m-1; i++){
    aux = perfil[i+1] - perfil[i];
    nor_arist.push_back({aux[Y], -aux[X], 0});
  }
  
  std::vector<Tupla3f> nor_ver_perfil;

  aux = nor_arist.front();
  if(aux[X] != 0 or aux[Y] != 0  or aux[Z] != 0)
      nor_ver_perfil.push_back(aux.normalized());
    else
      nor_ver_perfil.push_back({0.0, 0.0, 0.0});
  
  for(int i = 1; i < m-1; i++){
    aux = nor_arist[i-1]+ nor_arist[i];

    if(aux[X] != 0 or aux[Y] != 0  or aux[Z] != 0)
      nor_ver_perfil.push_back(aux.normalized());
    else
      nor_ver_perfil.push_back({0.0, 0.0, 0.0});
  }

  aux = nor_arist.back();
  if(aux[X] != 0 or aux[Y] != 0  or aux[Z] != 0)
      nor_ver_perfil.push_back(aux.normalized());
    else
      nor_ver_perfil.push_back({0.0, 0.0, 0.0});
  
  // COMPLETAR: Práctica 2: completar: creación de la malla....

  //Creación tabla de vértices:
  for (int i = 0; i < n; i++){
    for (int j = 0; j < m; j++){
      float alpha = 2*M_PI*i/(n-1);
      float c = cos(alpha);
      float s = sin(alpha);
      vertices.push_back({perfil[j][X]*c, perfil[j][Y], perfil[j][X]*s});
      //Añadimos las su normal
      nor_ver.push_back({nor_ver_perfil[j][X]*c, nor_ver_perfil[j][Y], nor_ver_perfil[j][X]*s});
      //Añadimos las coordenadas de textura
      cc_tt_ver.push_back({1 - (float) i/(n-1), 1-t[j]});
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

// -----------------------------------------------------------------------------
// constructor, a partir de un archivo PLY

MallaRevolPLY::MallaRevolPLY
(
   const std::string & nombre_arch, 
   const unsigned      nperfiles //numero de perfiles
)
{
   ponerNombre( std::string("malla por revolución del perfil en '"+ nombre_arch + "'" ));
   // COMPLETAR: práctica 2: crear la malla de revolución
   // Leer los vértice del perfil desde un PLY, después llamar a 'inicializar'

   std::vector<Tupla3f> perfil;
   LeerVerticesPLY(nombre_arch, perfil);
   inicializar(perfil, nperfiles);
   
}

//------------------------------------------------

Cilindro:: Cilindro(
   const int num_verts_per, //número de vértices del perfíl
   const unsigned int nperfiles) // número de perfiles
{
  ponerNombre( std::string("Cilindro"));
  std::vector<Tupla3f> perfil;

  for(int i=0; i < num_verts_per; i++){
    perfil.push_back({1, (float)i/(num_verts_per-1), 0});
  }

  inicializar(perfil, nperfiles);
}

Cono:: Cono(
   const int num_verts_per, //número de vértices del perfíl
   const unsigned int nperfiles) // número de perfiles
{
  
  ponerNombre( std::string("Cono"));
  
  std::vector<Tupla3f> perfil;

  for(int i=0; i < num_verts_per; i++){
    perfil.push_back({1-(float)i/(num_verts_per-1), (float)i/(num_verts_per-1), 0});
  }

  inicializar(perfil, nperfiles);
}

Esfera:: Esfera(
   const int num_verts_per, //número de vértices del perfíl
   const unsigned int nperfiles) // número de perfiles
{
  ponerNombre( std::string("Esfera"));
  
  std::vector<Tupla3f> perfil;
  
  for(int i=0; i < num_verts_per; i++){
    float alpha = M_PI*i/(num_verts_per-1);
    float s= sin(alpha);
    float c= cos(alpha);
    
    perfil.push_back({s, -c, 0});
    
  }

  inicializar(perfil, nperfiles);
}

Pesa:: Pesa(const unsigned int nperfiles) // número de perfiles
{
  ponerNombre( std::string("Reloj de arena"));
  
  std::vector<Tupla3f> perfil;
    
  perfil.push_back({0, 1.5, 0});
  perfil.push_back({1, 1.5, 0});
  perfil.push_back({1, 1, 0});
  perfil.push_back({0.5, 0.5, 0});
  perfil.push_back({0.5, 0, 0});
  perfil.push_back({0.5, -0.5, 0});
  perfil.push_back({1, -1, 0});
  perfil.push_back({1, -1.5, 0});
  perfil.push_back({0, -1.5, 0});

  inicializar(perfil, nperfiles);

  ponerColor({0.6, 0, 0.3});
}

Polea:: Polea(
   const int num_verts_per, //número de vértices del perfíl
   const unsigned int nperfiles) // número de perfiles
{
  ponerNombre( std::string("Polea"));
  
  std::vector<Tupla3f> perfil;

  perfil.push_back({0, -1.5, 0});
  perfil.push_back({1.5, -1.5, 0});
  perfil.push_back({1.5, -1, 0});
  
  for(int i=0; i < num_verts_per; i++){
    float alpha = M_PI*i/(nperfiles-1);
    float s= sin(alpha);
    float c= cos(alpha);
    
    perfil.push_back({-s+1.5, -c, 0});
    
    }

  perfil.push_back({1.5, 1, 0});
  perfil.push_back({1.5, 1.5, 0});
  perfil.push_back({0, 1.5, 0});

  inicializar(perfil, nperfiles);

  ponerColor({0, 1, 0});
}
