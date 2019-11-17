// *********************************************************************
// **
// ** Informática Gráfica, curso 2016-17
// ** Declaraciones de la clase MallaRevol
// **
// *********************************************************************

#ifndef IG_VARIANTEREVOL_HPP
#define IG_VARIANTEREVOL_HPP

#include <vector>          // usar std::vector
#include <string>

#include "malla-ind.h"   // declaración de 'Objeto3D'
// ---------------------------------------------------------------------
// clase para mallas indexadas obtenidas a partir de la revolución de un perfil

class MallaBarrido : public MallaInd
{
   private:

   protected: //

   MallaBarrido() {} // solo usable desde clases derivadas con constructores especificos

   // Método que crea las tablas de vértices, triángulos, normales y cc.de.tt.
   // a partir de un perfil y el número de copias que queremos de dicho perfil.
   void inicializar
   (
      const std::vector<Tupla3f> & perfil,     // tabla de vértices del perfil original
      const unsigned num_copias,  // número de copias del perfil
      const float inicio,
      const float fin
   ) ;
} ;

//---------------------------------------------------------------------------

class MallaBarridoPLY : public MallaBarrido
{
   public:
   MallaBarridoPLY( const std::string & nombre_arch,
                  const unsigned nperfiles,
		  const float inicio,
		  const float fin) ;
} ;

//---------------------------------------------------------------------------------

class Tunel : public MallaBarrido
{
   public:
  Tunel( const int num_verts_per, //número de vértices del perfil
	 const unsigned nperfiles, //número de perfiles
	 const float inicio,
	 const float fin);
   
} ;

#endif
