// *********************************************************************
// **
// ** Informática Gráfica, curso 2019-20
// ** Declaraciones de la clase Objeto3D.hpp
// **
// *********************************************************************

//#include <set>   // std::set
#include "ig-aux.h"
#include "tuplasg.h"
#include "malla-ind.h"   // declaración de 'ContextoVis'
#include "lector-ply.h"
#include <math.h>


// *****************************************************************************
// funciones auxiliares

// *****************************************************************************
// métodos de la clase MallaInd.

MallaInd::MallaInd()
{
   // nombre por defecto
   ponerNombre("malla indexada, anónima");
}
// -----------------------------------------------------------------------------

MallaInd::MallaInd( const std::string & nombreIni )
{
   // 'identificador' puesto a 0 por defecto, 'centro_oc' puesto a (0,0,0)
   ponerNombre(nombreIni) ;
}

//-----------------------------------------------------------------------------
// calcula la tabla de normales de triángulos una sola vez, si no estaba calculada

void MallaInd::calcularNormalesTriangulos()
{

   // si ya está creada la tabla de normales de triángulos, no es necesario volver a crearla
   const unsigned nt = triangulos.size() ;
   assert( 1 <= nt );
   if ( 0 < nor_tri.size() )
   {
      assert( nt == nor_tri.size() );
      return ;
   }

   // COMPLETAR: Práctica 4: creación de la tabla de normales de triángulos
   // ....

   Tupla3f a, b, m;
   
   for(int i = 0; i < triangulos.size(); i++){
     a = vertices[triangulos[i][1]] - vertices[triangulos[i][0]];
     b = vertices[triangulos[i][2]] - vertices[triangulos[i][0]];
     m = a.cross(b);

     if(m[X] != 0 or m[Y] != 0  or m[Z] != 0)
       nor_tri.push_back(m.normalized());
     else
       nor_tri.push_back({0.0, 0.0, 0.0});
   }

}


// -----------------------------------------------------------------------------
// calcula las dos tablas de normales

void MallaInd::calcularNormales()
{
   // COMPLETAR: en la práctica 4: calculo de las normales de la malla
   // se debe invocar en primer lugar 'calcularNormalesTriangulos'
   // .......

  calcularNormalesTriangulos();

  for(int i = 0; i<vertices.size(); i++){
    nor_ver.push_back({0.0, 0.0, 0.0});
  }

  for(int i = 0; i<triangulos.size(); i++){
    for(int j = 0; j<3; j++){
      nor_ver[triangulos[i][j]] = nor_ver[triangulos[i][j]] + nor_tri[i];
    }
  }

  for(int i = 0; i<nor_ver.size(); i++){
    if(nor_ver[i][X] != 0 or nor_ver[i][Y] != 0  or nor_ver[i][Z] != 0)
       nor_ver[i] = nor_ver[i].normalized();
     else
       nor_ver[i]={0.0, 0.0, 0.0};
  }

}


//----------------------------------------------------------------------------
// comprueba que los valores de 'tipo' y 'tabla' son valores legales.

void Comprobar( GLuint tipo, GLuint tabla )
{
   assert( tipo == GL_ARRAY_BUFFER || tipo == GL_ELEMENT_ARRAY_BUFFER );
   if ( tipo == GL_ARRAY_BUFFER )
      assert(  tabla == GL_VERTEX_ARRAY || tabla == GL_COLOR_ARRAY ||
               tabla == GL_NORMAL_ARRAY || tabla == GL_TEXTURE_COORD_ARRAY ) ;
}
//----------------------------------------------------------------------------
// crea un VBO, devuelve:
//  ** 0 si 'num_elems' es 0, o
//  ** el identificador de VBO, si num_elems > 0
//
// deja activado el VBO 0

GLuint CrearVBO( GLuint tipo, GLuint tabla, GLuint cuenta, GLvoid * puntero )
{
   Comprobar( tipo, tabla );
   // COMPLETAR: práctica 1
   // Crear un VBO para esta tabla y enviar datos a la GPU, devolver id de VBO
   // Si 'cuenta' es 0, la tabla está vacía: devuelve 0 y no hace nada.
   if( cuenta == 0)
     return 0;

   //calcular tamaño de cada elemento en bytes (teb) y de toda la tabla (ttb)
   GLuint teb = (tipo == GL_ELEMENT_ARRAY_BUFFER) ? sizeof( unsigned int ) : (tabla == GL_TEXTURE_COORD_ARRAY ) ? sizeof ( Tupla2f ) : sizeof ( Tupla3f);

   unsigned long ttb = (unsigned long)teb * (unsigned long) cuenta;
   GLuint id_vbo = 0;

   glGenBuffers(1, &id_vbo); //crear nuevo identifecador de VBO
   glBindBuffer(tipo, id_vbo); // activar nuevo VBO
   glBufferData( tipo, ttb, puntero, GL_STATIC_DRAW); // trans. RAM -> GPU
   glBindBuffer( tipo, 0); // no dejar activado VBO
   
   return id_vbo;

}

//----------------------------------------------------------------------------
// Especifica localización y estructura de una tabla

void LocForTabla( GLuint tipo_tabla, GLuint tabla, GLuint id_vbo,
                  GLvoid * p )
{
   // COMPLETAR: práctica 1
   // especificar localización y formato de la tabla

  glBindBuffer( tipo_tabla, id_vbo); //activar VBO (id_vbo==0 si está en RAM)

  if( tipo_tabla == GL_ARRAY_BUFFER){ // especificar estructura y puntero
    switch(tabla){
    case GL_VERTEX_ARRAY : //tabla de vértices
      glVertexPointer(3, GL_FLOAT, 0, p);
      break;
    case GL_TEXTURE_COORD_ARRAY: //tabla de coordenadas
      glTexCoordPointer(2, GL_FLOAT, 0, p);
      break;
    case GL_COLOR_ARRAY: //tabla de color
      glColorPointer(3, GL_FLOAT, 0, p);
      break;
    case GL_NORMAL_ARRAY: //tabla de normal
      glNormalPointer( GL_FLOAT, 0, p);
      break;
    default: //error
      assert (false);
      break;
    }
  }

}


//----------------------------------------------------------------------------
// habilita o deshabilita una tabla, si la habilita, especifica localización
// y estructura

void RegistrarTabla( GLuint tipo_tabla, GLuint tabla, GLsizei cuenta,
                     GLuint id_vbo, GLvoid * puntero_offset )
{
   // COMPLETAR: Práctica 1: implementar según el comportamiento descrito arriba:
   // usar 'glBindBuffer', 'glEnableClientState', 'glDisableClientState' y 'FijarPunteroTabla'
   // (al llamar a 'FijarPunteroTabla' (LocForTabla), se asume que el puntero es el offset nulo)
   // ....
  if( cuenta == 0 && tipo_tabla == GL_ARRAY_BUFFER)
    glDisableClientState(tabla); //deshabilitar tabla vacía
  else{
    LocForTabla( tipo_tabla, tabla, id_vbo, puntero_offset);
    if( tipo_tabla == GL_ARRAY_BUFFER)
      glEnableClientState(tabla); //para uso de tabla
  }

}
// -----------------------------------------------------------------------------
// crea todos los VBOs

void MallaInd::crearVBOs()
{
   if ( vbos_creados )
      return ;

   CError();
   // COMPLETAR: práctica 1
   // Crear los VBOs de las 5 tablas posibles (llamar a 'CrearVBO')
   // almacenar los identificadores en las variables de instancia 'id_vbo_...'

   id_vbo_col = CrearVBO( GL_ARRAY_BUFFER, GL_COLOR_ARRAY, col_ver.size(), col_ver.data());
   
   id_vbo_nor = CrearVBO( GL_ARRAY_BUFFER, GL_NORMAL_ARRAY, nor_ver.size(), nor_ver.data());
   
   id_vbo_cct = CrearVBO( GL_ARRAY_BUFFER, GL_TEXTURE_COORD_ARRAY, cc_tt_ver.size(), cc_tt_ver.data());
   
   id_vbo_ver = CrearVBO( GL_ARRAY_BUFFER, GL_VERTEX_ARRAY, vertices.size(), vertices.data());
   
   id_vbo_tri = CrearVBO( GL_ELEMENT_ARRAY_BUFFER, 0, 3*triangulos.size(), triangulos.data());
   

   CError();

   vbos_creados = true ;
}

// -----------------------------------------------------------------------------
// Registrar tablas en modo inmediato

void MallaInd::registrarTablas_MI()
{
   CError();
   // COMPLETAR: práctica 1
   // registrar las 4 tablas en modo inmediato (llamar a 'RegistrarTabla')

   RegistrarTabla(GL_ARRAY_BUFFER, GL_VERTEX_ARRAY, vertices.size(), 0, vertices.data());
   RegistrarTabla(GL_ARRAY_BUFFER, GL_COLOR_ARRAY, col_ver.size(), 0, col_ver.data());
   RegistrarTabla(GL_ARRAY_BUFFER, GL_NORMAL_ARRAY, nor_ver.size(), 0, nor_ver.data());
   RegistrarTabla(GL_ARRAY_BUFFER, GL_TEXTURE_COORD_ARRAY, cc_tt_ver.size(), 0, cc_tt_ver.data());
   

   CError();
}

//--------------------------------------------------------------------------------
// Registrar tablas en modo diferido

void MallaInd::registrarTablas_MD()
{
   CError();
   // COMPLETAR: práctica 1
   // crear VBOs y registrar las 5 tablas en modo diferido (llamar a 'RegistrarTabla')
   crearVBOs();

   RegistrarTabla(GL_ARRAY_BUFFER, GL_VERTEX_ARRAY, vertices.size(), id_vbo_ver, 0);
   RegistrarTabla( GL_ELEMENT_ARRAY_BUFFER, 0, 3*triangulos.size(), id_vbo_tri, 0);
   RegistrarTabla(GL_ARRAY_BUFFER, GL_COLOR_ARRAY, col_ver.size(), id_vbo_col, 0);
   RegistrarTabla(GL_ARRAY_BUFFER, GL_NORMAL_ARRAY, nor_ver.size(), id_vbo_nor, 0);
   RegistrarTabla(GL_ARRAY_BUFFER, GL_TEXTURE_COORD_ARRAY, cc_tt_ver.size(), id_vbo_cct, 0);

   CError();
}


// -----------------------------------------------------------------------------
// crear los dos VAOS: 'id_vao_attr' e 'id_vao_geom' , solo si no estaban creados

void MallaInd::crearActivarVAO_MD( )
{
   CError();
   // COMPLETAR: práctica 1
   // Crear (si no lo estaba) el VAO del M.D., y activarlo.
   if( id_vao_md == 0){ //Si el VAO no estaba creado
     glGenVertexArrays(1, &id_vao_md); // crear VAO nuevo
     glBindVertexArray( id_vao_md); //activar VAO
     registrarTablas_MD(); //registrar loc. 
   } else{
     glBindVertexArray (id_vao_md); // activar VAO ya creado
   }

   CError();
}



// -----------------------------------------------------------------------------

void MallaInd::visualizarGL_MI_DE( ContextoVis & cv )
{
   CError();
   using namespace std ;

   // COMPLETAR: Práctica 1: visualizar en modo inmediato (glDrawElements)
   // es necesario asegurarnos antes de que el VAO para M.I. está creado
   // (usando crearActivarVAO_MI), y luego llamar a 'glDrawElements')
   // al final, dejar activado el VAO por defecto

   glBindVertexArray(0);
   registrarTablas_MI();

   glDrawElements(GL_TRIANGLES, 3*triangulos.size(), GL_UNSIGNED_INT, triangulos.data());

   CError();

}
// ----------------------------------------------------------------------------

void MallaInd::visualizarGL_MD_VAO( ContextoVis & cv )
{
   // COMPLETAR: Práctica 1: visualizar en modo diferido (glDrawElements)
   // es necesario asegurarnos antes de que el VAO para M.D. está creado
   // (usando crearActivarVAO_MD), y luego llamar a 'glDrawElements')
   // al final, dejar activado el VAO por defecto

  crearActivarVAO_MD(); //asegurarnos que el VAO está creado y activo

  //visualizar secuencia
  glDrawElements( GL_TRIANGLES, 3*triangulos.size(), GL_UNSIGNED_INT, 0);

  glBindVertexArray(0); //dejar activado el VAO
}

// -----------------------------------------------------------------------------
// visualizar con begin/end (modo inmediato), enviando normales de triángulos y
// cc.tt. (adecuado para modo de sombreado plano)

void MallaInd::visualizarGL_MI_BE( ContextoVis & cv )
{
   // COMPLETAR: Práctica 1:
   // Visualizacion en modo inmediato usando begin/end
   // usar 'glBegin/glVertex/glEnd'

  const long nv = triangulos.size(); //numero de vértices

  glBegin(GL_TRIANGLES);
  
  for( unsigned long i = 0; i<nv; i++){

    const int j = triangulos[i][0];
    if (col_ver.size()>0) glColor3fv(col_ver[j]);
    if (nor_ver.size()>0) glNormal3f(nor_ver[j][0], nor_ver[j][1], nor_ver[j][2]);
    if (cc_tt_ver.size()>0) glTexCoord2f(cc_tt_ver[j][0], cc_tt_ver[j][1]);
    glVertex3fv(vertices[j]);

    const int k = triangulos[i][1];
    if (col_ver.size()>0) glColor3fv(col_ver[k]);
    if (nor_ver.size()>0) glNormal3f(nor_ver[k][0], nor_ver[k][1], nor_ver[k][2]);
    if (cc_tt_ver.size()>0) glTexCoord2f(cc_tt_ver[k][0], cc_tt_ver[k][1]);
    glVertex3fv(vertices[k]);

    const int l = triangulos[i][2];
    if (col_ver.size()>0) glColor3fv(col_ver[l]);
    if (nor_ver.size()>0) glNormal3f(nor_ver[l][0], nor_ver[l][1], nor_ver[l][2]);
    if (cc_tt_ver.size()>0) glTexCoord2f(cc_tt_ver[l][0], cc_tt_ver[l][1]);
    glVertex3fv(vertices[l]);
    
  }
  glEnd();

}
// ----------------------------------------------------------------------------



// ----------------------------------------------------------------------------


void MallaInd::visualizarGL( ContextoVis & cv )
{

   using namespace std ;
   assert( cv.cauce_act != nullptr );

   if ( triangulos.size() == 0 || vertices.size() == 0 )
   {  cout << "advertencia: intentando dibujar malla vacía '" << leerNombre() << "'" << endl << flush ;
      return ;
   }

   // guardar el color previamente fijado
   const Tupla4f color_previo = leerFijarColVertsCauce( cv );

   if(cv.modo_seleccion){
     //cv.iluminacion = false;
     //cv.modo_visu = ModosVisu::relleno;
     //cv.visualizando_normales = false;
     //cv.dibujar_ejes = false;
     //* Se configura en la función selección*

     int id = leerIdentificador();

     if(id != -1){
       float r, g, b;
       r = (float)((id & 0xFF0000) >> 16) /255.0;
       g = (float)((id & 0xFF00) >> 8) /255.0;
       b = (float)(id & 0xFF) /255.0;

       ponerColor({r, g, b});
     }
   }
   
   if(cv.visualizando_normales)
     visualizarNormales();

   // COMPLETAR: práctica 1: visualizar según el modo (en 'cv.modo_envio')
   //   ** inmediato begin/end                   : usar 'visualizarGL_MI_BE'
   //   ** inmediato con un VAO (glDrawElements) : usar 'visualizarGL_MI_VAO'
   //   ** diferido con un VAO  (glDrawElements) : usar 'visualizarGL_MD_VAO'

   switch(cv.modo_envio){
   case ModosEnvio::inmediato_begin_end:
     visualizarGL_MI_BE(cv);
     break;
   case ModosEnvio::inmediato_drawelements:
     visualizarGL_MI_DE(cv);
     break;
   case ModosEnvio::diferido_vao:
     visualizarGL_MD_VAO(cv);
     break;
   }

   // restaurar el color previamente fijado
   glColor4fv( color_previo );
}


void MallaInd::visualizarNormales()
{
   using namespace std ;
   CError();
   if ( nor_ver.size() == 0 )
   {
      cout << "Advertencia: intentando dibujar normales de una malla que no tiene tabla (" << leerNombre() << ")." << endl ;
      return ;
   }
   std::vector<Tupla3f> segmentos ;
   for( unsigned i = 0 ; i < vertices.size() ; i++ )
   {  segmentos.push_back( vertices[i] );
      segmentos.push_back( vertices[i]+ 0.35f*(nor_ver[i]) );
   }
   CError();
   glVertexPointer( 3, GL_FLOAT, 0, segmentos.data() );
   glDrawArrays( GL_LINES,  0, segmentos.size() );
   CError();
}


// *****************************************************************************


// ****************************************************************************
// Clase 'MallaPLY'

MallaPLY::MallaPLY( const std::string & nombre_arch )
{
   ponerNombre( std::string("malla leída del archivo '") + nombre_arch + "'" );

   // COMPLETAR: práctica 2: leer archivo PLY e inicializar la malla
   //Copia la info en las tabls vertices y triangulos
   LeerPLY(nombre_arch, vertices, triangulos);
   // llamar a 'calcularNormales' para el cálculo de normales
   // ..........................
   calcularNormales();

}

// ****************************************************************************
// Clase Cubo

Cubo::Cubo()
:  MallaInd( "cubo 8 vértices" )
{

   vertices =
      {  { -1.0, -1.0, -1.0 }, // 0
         { -1.0, -1.0, +1.0 }, // 1
         { -1.0, +1.0, -1.0 }, // 2
         { -1.0, +1.0, +1.0 }, // 3
         { +1.0, -1.0, -1.0 }, // 4
         { +1.0, -1.0, +1.0 }, // 5
         { +1.0, +1.0, -1.0 }, // 6
         { +1.0, +1.0, +1.0 }, // 7
      } ;


   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         {0,5,1}, {0,4,5}, // Y-
         {2,3,7}, {2,7,6}, // Y+ (+2)

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3}  // Z+ (+1)
      } ;

   calcularNormales();

}
// -----------------------------------------------------------------------------------------------

//Clase Tetraedro

Tetraedro::Tetraedro() : Tetraedro({1.0,1.0,1.0}){}


Tetraedro::Tetraedro( Tupla3f nuevo_color)
:  MallaInd( "Tetraedro de 4 vértices" )
{

   vertices =
     {// Rojo X, Verde Y, Azul Z
         { 0.0, 1.0, 0.0 }, // 0
         { 1.0, -0.5, 0.0 }, // 1
         { -0.8, -0.5, -0.8 }, // 2
         { -0.8, -0.5, 0.8 }, // 3
      } ;

   triangulos =
      {  {0,1,2}, {0,1,3}, 
         {1,2,3}, {0,2,3}, 
      } ;

   ponerColor( nuevo_color );

   calcularNormales();

}

// ****************************************************************************
// Clase Cubo

CuboColores::CuboColores()
:  MallaInd( "Cubo de colores de 8 vértices" )
{

   vertices =
      {  { -1.0, -1.0, -1.0 }, // 0
         { -1.0, -1.0, +1.0 }, // 1
         { -1.0, +1.0, -1.0 }, // 2
         { -1.0, +1.0, +1.0 }, // 3
         { +1.0, -1.0, -1.0 }, // 4
         { +1.0, -1.0, +1.0 }, // 5
         { +1.0, +1.0, -1.0 }, // 6
         { +1.0, +1.0, +1.0 }, // 7
      } ;

   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         {0,5,1}, {0,4,5}, // Y-
         {2,3,7}, {2,7,6}, // Y+ (+2)

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3}  // Z+ (+1)
      } ;

   
   col_ver =
     {   { 0, 0, 0 }, // 0
         { 0, 0, 1 }, // 1
         { 0, 1, 0 }, // 2
         { 0, 1, 1 }, // 3
         { 1, 0, 0 }, // 4
         { 1, 0, 1 }, // 5
         { 1, 1, 0 }, // 6
         { 1, 1, 1 }, // 7

     } ;

   calcularNormales();
   
}
// -----------------------------------------------------------------------------------------------

// Clase Cubo24

Cubo24::Cubo24()
:  MallaInd( "cubo 24 vértices" )
{

   vertices =
      {
	{ -1.0, -1.0, -1.0 }, // 0
	{ -1.0, -1.0, +1.0 }, // 1
	{ -1.0, +1.0, -1.0 }, // 2
	{ -1.0, +1.0, +1.0 }, // 3
	{ +1.0, -1.0, -1.0 }, // 4
	{ +1.0, -1.0, +1.0 }, // 5
	{ +1.0, +1.0, -1.0 }, // 6
	{ +1.0, +1.0, +1.0 }, // 7

	{ -1.0, -1.0, -1.0 }, // 0 +8
	{ -1.0, -1.0, +1.0 }, // 1 +8
	{ -1.0, +1.0, -1.0 }, // 2 +8
	{ -1.0, +1.0, +1.0 }, // 3 +8
	{ +1.0, -1.0, -1.0 }, // 4 +8
	{ +1.0, -1.0, +1.0 }, // 5 +8
	{ +1.0, +1.0, -1.0 }, // 6 +8
	{ +1.0, +1.0, +1.0 }, // 7 +8

	{ -1.0, -1.0, -1.0 }, // 0 +16
	{ -1.0, -1.0, +1.0 }, // 1 +16
	{ -1.0, +1.0, -1.0 }, // 2 +16
	{ -1.0, +1.0, +1.0 }, // 3 +16
	{ +1.0, -1.0, -1.0 }, // 4 +16
	{ +1.0, -1.0, +1.0 }, // 5 +16
	{ +1.0, +1.0, -1.0 }, // 6 +16
	{ +1.0, +1.0, +1.0 }, // 7 +16
      } ;


   triangulos =
     {
       {0,1,3}, {0,3,2}, // X-                 //
       {4,7,5}, {4,6,7}, // X+ (+4)            //
       {8,13,9}, {8,12,13}, // Y-              //
       {10,11,15}, {10,15,14}, // Y+ (+2)      //
       {16,22,20}, {16,18,22}, // Z-           //
       {17,21,23}, {17,23,19}  // Z+ (+1)      //
      } ;

   cc_tt_ver=
     {
       { 0, 1}, // 0
       { 1, 1}, // 1
       { 0, 0}, // 2
       { 1, 0}, // 3
       { 1, 1}, // 4
       { 0, 1}, // 5
       { 1, 0}, // 6
       { 0, 0}, // 7

       { 0, 0}, // 0 +8
       { 1, 0}, // 1 +8
       { 1, 0}, // 2 +8
       { 0, 0}, // 3 +8
       { 0, 1}, // 4 +8
       { 1, 1}, // 5 +8
       { 1, 1}, // 6 +8
       { 0, 1}, // 7 +8

       { 1, 1}, // 0 +16
       { 0, 1}, // 1 +16
       { 1, 0}, // 2 +16
       { 0, 0}, // 3 +16
       { 0, 1}, // 4 +16
       { 1, 1}, // 5 +16
       { 0, 0}, // 6 +16
       { 1, 0}, // 7 +16
     };

   calcularNormales();

}

//-------------------------------------------------------------------------------

//Clase Diamante

Diamante::Diamante( Tupla3f nuevo_color)
:  MallaInd( "Diamante" )
{

  float c = cos(M_PI/3);
  float s = sin(M_PI/3);
  
   vertices =
     {// Rojo X, Verde Y, Azul Z
         { 0.0, -1.0, 0.0 }, // 0
         { c, 0.0, s }, // 1
         { -c, 0.0, s }, // 2
         { -1.0, 0.0, 0.0 }, // 3
	 { -c, 0.0, -s}, //4
	 { c, 0.0, -s }, // 5
	 { 1.0, 0.0, 0.0}, //6
	 { 0.6f*c, 0.5, 0.6f*s }, // 7
         { -0.6f*c, 0.5, 0.6f*s }, // 8
         { -0.6, 0.5, 0.0 }, // 9
	 { -0.6f*c, 0.5, -0.6f*s}, //10
	 { 0.6f*c, 0.5, -0.6f*s }, // 11
	 { 0.6, 0.5, 0.0}, //12
	 { 0.0, 0.5, 0.0}, //13
      } ;

   triangulos =
     {  {0,1,2}, {0,2,3}, //Unir al vertice inferior
         {0,3,4}, {0,4,5},
	 {0,5,6}, {0,6,1},
	 
	{1,2,7}, {7,8,2}, //Corona diamante
	 {2,3,8}, {8,9,3}, 
         {3,4,9}, {9,10,4},
	 {4,5,10}, {10,11,5},
	 {5,6,11}, {11,12,6}, 
         {6,1,12}, {12,7,1},

	{13,7,8}, {13,8,9}, //Base superior diamante
         {13,9,10}, {13,10,11},
	 {13,11,12}, {13,12,7},
      } ;

   ponerColor( nuevo_color );

   calcularNormales();

}

Diamante::Diamante():  MallaInd( "Diamante" )
{

  float c = cos(M_PI/3);
  float s = sin(M_PI/3);
  
   vertices =
     {// Rojo X, Verde Y, Azul Z
         { 0.0, -1.0, 0.0 }, // 0
         { c, 0.0, s }, // 1
         { -c, 0.0, s }, // 2
         { -1.0, 0.0, 0.0 }, // 3
	 { -c, 0.0, -s}, //4
	 { c, 0.0, -s }, // 5
	 { 1.0, 0.0, 0.0}, //6
	 { 0.6f*c, 0.5, 0.6f*s }, // 7
         { -0.6f*c, 0.5, 0.6f*s }, // 8
         { -0.6, 0.5, 0.0 }, // 9
	 { -0.6f*c, 0.5, -0.6f*s}, //10
	 { 0.6f*c, 0.5, -0.6f*s }, // 11
	 { 0.6, 0.5, 0.0}, //12
	 { 0.0, 0.5, 0.0}, //13
      } ;

   triangulos =
     {  {0,1,2}, {0,2,3}, //Unir al vertice inferior
         {0,3,4}, {0,4,5},
	 {0,5,6}, {0,6,1},
	 
	{1,2,7}, {7,8,2}, //Corona diamante
	 {2,3,8}, {8,9,3}, 
         {3,4,9}, {9,10,4},
	 {4,5,10}, {10,11,5},
	 {5,6,11}, {11,12,6}, 
         {6,1,12}, {12,7,1},

	{13,7,8}, {13,8,9}, //Base superior diamante
         {13,9,10}, {13,10,11},
	 {13,11,12}, {13,12,7},
      } ;

   col_ver =
     {   {0, 0.6, 0.6}, // 0
         {0, 1, 1}, // 1
         {0, 1, 1}, // 2
         {0, 1, 1}, // 3
         {0, 1, 1}, // 4
         {0, 1, 1}, // 5
         {0, 1, 1}, // 6
         {0.5, 1, 1}, // 7
	 {0.5, 1, 1}, // 8
         {0.5, 1, 1}, // 9
         {0.5, 1, 1}, // 10
         {0.5, 1, 1}, // 11
         {0.5, 1, 1}, // 12
         {1, 1, 1}, // 13

     } ;

   calcularNormales();
}
