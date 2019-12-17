// *********************************************************************
// **
// ** Gestión de una grafo de escena (implementación)
// ** Copyright (C) 2016 Carlos Ureña
// **
// ** This program is free software: you can redistribute it and/or modify
// ** it under the terms of the GNU General Public License as published by
// ** the Free Software Foundation, either version 3 of the License, or
// ** (at your option) any later version.
// **
// ** This program is distributed in the hope that it will be useful,
// ** but WITHOUT ANY WARRANTY; without even the implied warranty of
// ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// ** GNU General Public License for more details.
// **
// ** You should have received a copy of the GNU General Public License
// ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
// **
// *********************************************************************

#include "ig-aux.h"
#include "matrices-tr.h"
#include "grafo-escena.h"
#include "malla-ind.h"

using namespace std ;

// *********************************************************************
// Entrada del nodo del Grafo de Escena

// ---------------------------------------------------------------------
// Constructor para entrada de tipo sub-objeto

EntradaNGE::EntradaNGE( Objeto3D * pObjeto )
{
   assert( pObjeto != NULL );
   tipo   = TipoEntNGE::objeto ;
   objeto = pObjeto ;
}
// ---------------------------------------------------------------------
// Constructor para entrada de tipo "matriz de transformación"

EntradaNGE::EntradaNGE( const Matriz4f & pMatriz )
{
   tipo    = TipoEntNGE::transformacion ;
   matriz  = new Matriz4f() ; // matriz en el heap, puntero propietario
   *matriz = pMatriz ;
}

// ---------------------------------------------------------------------
// Constructor para entrada de tipo "matriz de transformación"

EntradaNGE::EntradaNGE( Material * pMaterial )
{
   assert( pMaterial != NULL );
   tipo     = TipoEntNGE::material ;
   material = pMaterial ;
}

// -----------------------------------------------------------------------------
// Destructor de una entrada

EntradaNGE::~EntradaNGE()
{
   /**  no fnciona debido a que se hacen copias (duplicados) de punteros
   if ( tipo == TipoEntNGE::transformacion )
   {
      assert( matriz != NULL );
      delete matriz ;
      matriz = NULL ;
   }
   * **/
}

// *****************************************************************************
// Nodo del grafo de escena: contiene una lista de entradas
// *****************************************************************************

// -----------------------------------------------------------------------------
// Visualiza usando OpenGL

void NodoGrafoEscena::visualizarGL( ContextoVis & cv )
{
   // COMPLETAR: práctica 3: recorrer las entradas y visualizar cada nodo.

  const Tupla4f color_previo = leerFijarColVertsCauce( cv );
  Material * mat_previo;

  if(cv.iluminacion){
    mat_previo = cv.material_act;
  }

  if(cv.modo_seleccion){
     //cv.iluminacion = false;
     //cv.modo_visu = ModosVisu::relleno;
     //cv.visualizando_normales = false;
     //cv.dibujar_ejes = false;
     //* Se configura en la función selección*

     int id = leerIdentificador();

     if(id != -1){
       float r, g, b;
       r = (float)((id&0xFF0000) >> 16) /255.0;
       g = (float)((id&0xFF00) >> 8) /255.0;
       b = (float)(id&0xFF) /255.0;

       ponerColor({r, g, b});

       //std::cout << "Leyendo identificador para poner colores en grafo-escena.cpp: " << leerColor() <<std::endl;
     }
   }
  
  //guarda modelview actual
  cv.cauce_act->pushMM();
  
  //recorrer todas las entradas del array que hay en el nodo
  for(unsigned i = 0; i< entradas.size(); i++){
    switch( entradas[i].tipo ){
    case TipoEntNGE::objeto:
      entradas[i].objeto->visualizarGL(cv);
      break;
    case TipoEntNGE::transformacion:
      cv.cauce_act->compMM( *(entradas[i].matriz));
      break;
    case TipoEntNGE::material:
      if(cv.iluminacion){
	cv.material_act = entradas[i].material;
	entradas[i].material->activar(*cv.cauce_act);
      }
      break;
    }
  }

  //restuara modelview guardada
  cv.cauce_act->popMM();

  if(cv.iluminacion){
    cv.material_act = mat_previo;
    cv.material_act->activar(*cv.cauce_act);
  }
  
  glColor4fv( color_previo );

}

// *****************************************************************************
// visualizar pura y simplemente la geometría, sin colores, normales, coord. text. etc...
// ignora el colo o identificador del nodo, ignora las entradas de tipo material
// (se supone que el estado de OpenGL está fijado antes de esta llamada de alguna forma adecuada)




// -----------------------------------------------------------------------------

NodoGrafoEscena::NodoGrafoEscena()
{

}

// -----------------------------------------------------------------------------
// Añadir una entrada (al final).
// genérica (de cualqiuer tipo de entrada)

unsigned NodoGrafoEscena::agregar( const EntradaNGE & entrada )
{
   // COMPLETAR: práctica 3: agregar la entrada al nodo, devolver índice de la entrada agregada

  entradas.push_back(entrada);
  
  return entradas.size()-1 ;

}
// -----------------------------------------------------------------------------
// construir una entrada y añadirla (al final)
// objeto (copia solo puntero)

unsigned NodoGrafoEscena::agregar( Objeto3D * pObjeto )
{
   return agregar( EntradaNGE( pObjeto ) );
}
// ---------------------------------------------------------------------
// construir una entrada y añadirla (al final)
// matriz (copia objeto)

unsigned NodoGrafoEscena::agregar( const Matriz4f & pMatriz )
{
   return agregar( EntradaNGE( pMatriz ) );
}
// ---------------------------------------------------------------------
// material (copia solo puntero)
unsigned NodoGrafoEscena::agregar( Material * pMaterial )
{
   return agregar( EntradaNGE( pMaterial ) );
}

// devuelve el puntero a la matriz en la i-ésima entrada
Matriz4f * NodoGrafoEscena::leerPtrMatriz( unsigned indice )
{
   // COMPLETAR: práctica 3: devolver puntero la matriz en ese índice
   //   (debe de dar error y abortar si no hay una matriz en esa entrada)

  assert( indice < entradas.size() );
  assert(entradas[indice].tipo==TipoEntNGE::transformacion);
  assert( entradas[indice].matriz != nullptr );

  return entradas[indice].matriz;;

}
// -----------------------------------------------------------------------------
// si 'centro_calculado' es 'false', recalcula el centro usando los centros
// de los hijos (el punto medio de la caja englobante de los centros de hijos)

void NodoGrafoEscena::calcularCentroOC()
{

   // COMPLETAR: práctica 5: calcular y guardar el centro del nodo
   //    en coordenadas de objeto (hay que hacerlo recursivamente)
   //   (si el centro ya ha sido calculado, no volver a hacerlo)
   // ........
  
  if(centro_calculado)
    return;

  std::vector<Tupla3f> centros;
  Matriz4f matriz = MAT_Ident();

  for(unsigned i = 0; i< entradas.size(); i++){
    switch( entradas[i].tipo ){
    case TipoEntNGE::objeto:
      entradas[i].objeto->calcularCentroOC();
      centros.push_back(matriz*entradas[i].objeto->leerCentroOC());
      break;
    case TipoEntNGE::transformacion:
      matriz = matriz*(*entradas[i].matriz);
      break;
    }
  }

  Tupla3f centro={0.0, 0.0, 0.0};

  for(unsigned i = 0; i< centros.size(); i++){
    centro = centro + centros[i];
  }

  centro = centro/(float)centros.size();

  ponerCentroOC(centro); 
  centro_calculado=true;
  
}
// -----------------------------------------------------------------------------
// método para buscar un objeto con un identificador y devolver un puntero al mismo

bool NodoGrafoEscena::buscarObjeto
(
   const int         ident_busc, // identificador a buscar
   const Matriz4f &  mmodelado,  // matriz de modelado
   Objeto3D       ** objeto,     // (salida) puntero al puntero al objeto
   Tupla3f &         centro_wc   // (salida) centro del objeto en coordenadas del mundo
)
{

  std::cout<<"BUSCANDO OBJETO"<<std::endl;
   assert( 0 < ident_busc );

   // COMPLETAR: práctica 5: buscar un sub-objeto con un identificador
   // Se deben de dar estos pasos:

   // 1. calcula el centro del objeto, (solo la primera vez)
   // ........
   calcularCentroOC();

   // 2. si el identificador del nodo es el que se busca, ya está (terminar)
   // ........

   if(ident_busc == leerIdentificador()){
     centro_wc = mmodelado*leerCentroOC();
     *objeto = this;
     
     return true;
   }

   // 3. El nodo no es el buscado: buscar recursivamente en los hijos
   //    (si alguna llamada para un sub-árbol lo encuentra, terminar y devolver 'true')
   // ........

   bool encontrado = false;
   Matriz4f matriz = mmodelado;

   for(unsigned i = 0; i< entradas.size() and !encontrado; i++){
     switch( entradas[i].tipo ){
     case TipoEntNGE::objeto:
       if(entradas[i].objeto->buscarObjeto(ident_busc, matriz, objeto, centro_wc)){
	 encontrado = true;
       }
       break;
     case TipoEntNGE::transformacion:
       matriz = matriz*(*entradas[i].matriz);
       break;
     }
   }

   // ni este nodo ni ningún hijo es el buscado: terminar
   return encontrado ;
}


//---------------------------------------------------------------------------

NodoCubo24::NodoCubo24(){

  Textura * logo_ugr = new Textura("../recursos/imgs/window-icon.jpg");
  Material * material = new Material(logo_ugr, 0.5, 0.5, 0.5, 0.5);
  agregar(material);
  agregar(new Cubo24());
}
