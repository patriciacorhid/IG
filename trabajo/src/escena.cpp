

#include "ig-aux.h"
#include "escena.h"

#include "objeto3d.h"
#include "malla-ind.h"
#include "malla-revol.h"
#include "practicas.h"
#include "camara.h"
#include "materiales-luces.h"
#include "seleccion.h"
#include "modelo-jer.h"
#include "malla-barrido.h"
#include "latapeones.h"


// -----------------------------------------------------------------------------------------------

Escena::Escena()
{
   // COMPLETAR: Práctica 4: inicializar 'col_fuentes' y 'material_ini'
   // ...
  col_fuentes = new Col2Fuentes();
  material_ini = new Material();

   // COMPLETAR: Práctica 5: hacer 'push_back' de varias camaras perspectiva u ortogonales,
   // (sustituir la cámara orbital simple ('CamaraOrbitalSimple') por varias cámaras de 3 modos ('Camara3Modos')
   camaras.push_back( new CamaraOrbitalSimple() );

}
// -----------------------------------------------------------------------------------------------
// visualiza la escena en la ventana actual, usando la configuración especificada en 'cv'

void Escena::visualizarGL( ContextoVis & cv )
{
   using namespace std ;

   // recuperar el cauce actual de 'cv' en 'cauce', activarlo
   Cauce * cauce = cv.cauce_act ; assert( cauce != nullptr );
   cauce->activar() ;

   // recuperar la cámara actual de esta escena y  fijar las matrices 'modelview'
   // y 'projection' en el cauce gráfico (es decir: activar la cámara actual)
   CamaraInteractiva * camara = camaras[ind_camara_actual] ; assert( camara != nullptr );
   const float ratio_vp = float(cv.ventana_tam_y)/float(cv.ventana_tam_x) ;
   camara->fijarRatioViewport( ratio_vp );
   camara->activar( *cauce ) ;


   // dibujar los ejes, si procede
   if ( cv.dibujar_ejes  )
      DibujarEjesSolido( *cauce ) ;

   // fijar el color por defecto en el cauce para dibujar los objetos
   glColor3f( 1.0, 1.0, 1.0 );
   
   // COMPLETAR: Práctica 1: Configurar el cauce en función de:
   //    cv.sombr_plano (true/false)              --> usar fijarModoSombrPlano (método del 'cauce')
   cauce->fijarModoSombrPlano(cv.sombr_plano);
   //    cv.modo_visu   (puntos,lineas o relleno) --> usar glPolygonMode
   GLenum modo_v; //Modo de visualización
   
   switch(cv.modo_visu){
   case ModosVisu::relleno:
     modo_v = GL_FILL;
     break;
   case ModosVisu::lineas:
     modo_v = GL_LINE;
     break;
   case ModosVisu::puntos:
     modo_v = GL_POINT;
     break;
   }
   
   glPolygonMode(GL_FRONT_AND_BACK, modo_v);


   if ( cv.iluminacion )
   {
      // COMPLETAR: Práctica 4: activar evaluación del MIL (y desactivar texturas)
      // * comprobar que existe la coleccion de fuentes (col_fuentes)
      // * comprobar que existe el material inicial (material_ini)
      // * activar la colección de fuentes y el material inicial
      // ....
          
     cauce->fijarEvalMIL( true );
     cauce->fijarEvalText( false );
     
     if(col_fuentes != nullptr){
       //std::cout<<"Activando colfuentes" << std::endl; 
       col_fuentes->activar(*cauce);
     }

     if(material_ini != nullptr){
       //std::cout<<"Activando material" << std::endl;
       cv.material_act = material_ini;
       cv.material_act->activar(*cauce);
     }

   }
   else // si la iluminación no está activada, deshabilitar MIL y texturas
   {  cauce->fijarEvalMIL( false );
      cauce->fijarEvalText( false );
   }

   // recuperar el objeto actual de esta escena
   Objeto3D * objeto = objetos[ind_objeto_actual] ; assert( objeto != nullptr );

   // COMPLETAR: Práctica 1: visualizar el objeto actual ('objeto')
   objeto->visualizarGL(cv);



   // si hay un FBO, dibujarlo:

}





// -----------------------------------------------------------------------------------------------
// pasa la cámara actual a la siguiente

void Escena::siguienteCamara()
{
   assert( ind_camara_actual < camaras.size() );
   ind_camara_actual = (ind_camara_actual+1 ) % camaras.size();
   using namespace std ;
   cout << "Cámara actual cambiada a: " << (ind_camara_actual+1) << " (de " << camaras.size() << ")" << endl ;
}

// -----------------------------------------------------------------------------------------------
// pasa el objeto actual al siguiente

void Escena::siguienteObjeto()
{
   if ( objetos.size() == 0 )
      return ;
   assert( ind_objeto_actual < objetos.size() );
   ind_objeto_actual = (ind_objeto_actual+1 ) % objetos.size();
   using namespace std ;
   cout << "Objeto actual cambiado a: " << objetoActual()->leerNombre()
        << " (" << (ind_objeto_actual+1) << "/" << objetos.size() << ")." << endl  ;
}

// -----------------------------------------------------------------------------------------------
// devuelve puntero al objeto actual

Objeto3D * Escena::objetoActual()
{
   assert( ind_objeto_actual < objetos.size() );
   assert( objetos[ind_objeto_actual] != nullptr );
   return objetos[ind_objeto_actual] ;
}
// -----------------------------------------------------------------------------------------------
// devuelve un puntero a la cámara actual

CamaraInteractiva * Escena::camaraActual()
{
   assert( ind_camara_actual < camaras.size() );
   assert( camaras[ind_camara_actual] != nullptr );
   return camaras[ind_camara_actual] ;
}
// -----------------------------------------------------------------------------------------------
// devuelve un puntero a la colección de fuentes actual

ColFuentesLuz * Escena::colFuentes()
{
   assert( col_fuentes != nullptr );
   return col_fuentes ;
}
// -----------------------------------------------------------------------------------------------

Escena1::Escena1()
{
   using namespace std ;
   cout << "Creando objetos de escena 1 .... " << flush ;

   // añadir el objeto 'Cubo' a la lista de objetos de esta escena:
   objetos.push_back( new Cubo() );
   // añadir el objeto 'Tetraedro' a la lista de objetos de esta escena:
   objetos.push_back( new Tetraedro({0.3, 0.85, 0.8}) );
   objetos.push_back( new Tetraedro() );
   objetos.push_back( new Tetraedro({0.8, 0.85, 0.3}) );
   objetos.push_back( new CuboColores() );
   
   // COMPLETAR: Práctica 1: creación del resto objetos de la práctica 1
   // Añadir objetos al vector 'objetos', con:
   //     objetos.push_back( new .... )
   // .........


   cout << "hecho." << endl << flush ;
}

// -------------------------------------------------------------------------
// COMPLETAR: Práctica 2
// Añadir la implementación del constructor de la clase Escena2 para construir
// los objetos que se indican en los guiones de las práctica 2
// .......

Escena2::Escena2()
{
   using namespace std ;
   cout << "Creando objetos de escena 2 .... " << flush ;

   // añadir el objetos '.ply' a la lista de objetos de esta escena:
   objetos.push_back( new MallaPLY("../recursos/plys/beethoven.ply") );
   objetos.push_back( new MallaRevolPLY("../recursos/plys/peon.ply", 20));
   objetos.push_back( new Cilindro(10, 20));
   objetos.push_back( new Cono(10, 20));
   objetos.push_back( new Esfera(20, 20));
   
   cout << "hecho." << endl << flush ;
}

// -------------------------------------------------------------------------
// COMPLETAR: Práctica 3
// Añadir la implementación del constructor de la clase Escena3 para construir
// los objetos que se indican en los guiones de las práctica 3
// .......

Escena3::Escena3()
{
   using namespace std ;
   cout << "Creando objetos de escena 3 .... " << flush ;

   objetos.push_back( new C());
   
   cout << "hecho." << endl << flush ;
}

// ----------------------------------------------------------------------
// COMPLETAR: Práctica 4
// Añadir la implementación del constructor de la clase Escena4 para construir
// los objetos que se indican en los guiones de las práctica 4
// .......

Escena4::Escena4()
{
   using namespace std ;
   cout << "Creando objetos de escena 4 .... " << flush ;

   objetos.push_back( new LataPeones());
   
   cout << "hecho." << endl << flush ;
}

// ----------------------------------------------------------------------
// COMPLETAR: Práctica 5
// Añadir la implementación del constructor de la clase Escena5 para construir
// los objetos que se indican en los guiones de las práctica 5
// .......

EscenaPrueba::EscenaPrueba()
{
   using namespace std ;
   cout << "Creando objetos de escena prueba .... " << flush ;

   objetos.push_back( new Diamante({0.5, 1, 1}));
   objetos.push_back( new Diamante());
   objetos.push_back( new Pesa(15));
   objetos.push_back( new Polea(20, 20));
   objetos.push_back( new Tunel(10, 20, 1, 5));
   objetos.push_back( new MallaBarridoPLY("../recursos/plys/peon.ply", 20, -1, 4));
   
   cout << "hecho." << endl << flush ;
}


