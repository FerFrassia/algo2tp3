#include "Driver.h"
#include "DiccString.h"
#include "ColaPrioritaria.h"
#include "CiudadFuturista.h"
#include "mini_test.h"
#include "aed2/Lista.h"
#include "aed2/Conj.h"
#include "aed2/Dicc.h"
#include "Rest.h"
#include "Mapa.h"

#include <string>
#include <iostream>

using namespace aed2;

/** 
 * Imprime un elemento a un string, en vez de a una pantalla, 
 * a través del operador << 
 */
template <typename T>
std::string to_str(const T& t)
{
	std::stringstream ss;
	ss << t;

	return ss.str();
}

/**
 * Esta función se puede utilizar para comparar dos colecciones
 * iterables que representen conjuntos, es decir, que no tengan 
 * elementos repetidos.
 */
template<typename T, typename S>
bool Comparar(const T& t, const S& s)
{
  typename T::const_Iterador it1 = t.CrearIt();
  typename S::const_Iterador it2 = s.CrearIt();

	// me fijo si tienen el mismo tamanho

	Nat len1 = 0;
	while( it1.HaySiguiente() ) {
		len1++;
		it1.Avanzar();
	}

	Nat len2 = 0;
	while( it2.HaySiguiente() ) {
		len2++;
		it2.Avanzar();
	}

	if ( len1 != len2 )
		return false;

	it1 = t.CrearIt();
	it2 = s.CrearIt();

	// me fijo que tengan los mismos elementos

	while( it1.HaySiguiente() )
	{
		bool esta = false;
		it2 = s.CrearIt();

		while( it2.HaySiguiente() ) {
		  if ( it1.Siguiente() == it2.Siguiente() ) {
			esta = true;
			break;
		  }
		  it2.Avanzar();
		}

		if ( !esta ) {
			return false;
		}
			
		it1.Avanzar();
	}
  
  return true;
}


// ---------------------------------------------------------------------

/**
 * Ejemplo de caso de test, con llamadas a las rutinas de aserción 
 * definidas en mini_test.h
 */
void test_ciudad_simple()
{
    Conj<Estacion> estaciones;
    estaciones.Agregar("Belgrano");
    estaciones.Agregar("Retiro");
    estaciones.Agregar("Martinez");

    Driver caba(estaciones);

    caba.AgregarSenda("Belgrano", "Retiro", "(trenDePasajeros | trenDeCarga) & !trenDeLaAlegria");
    caba.AgregarSenda("Martinez", "Retiro", "trenDeLaAlegria");
    caba.AgregarSenda("Martinez", "Belgrano", "trenDePasajeros");

    Conj<Caracteristica> r1, r2, r3;
    r1.Agregar("trenDePasajeros");
    r2.Agregar("trenDeCarga");
    r3.Agregar("trenDeLaAlegria");

    caba.Entrar(r1,"Belgrano"); // RUR 0
    caba.Entrar(r2,"Retiro");   // RUR 1
    caba.Entrar(r3,"Martinez"); // RUR 2

    ASSERT_EQ(caba.CantidadEstaciones(), 3);
    ASSERT_EQ(caba.CantidadRobotsActivos(), 3);
    ASSERT_EQ(caba.CantidadDeSendasParaEstacion("Belgrano"), 2);

    caba.Mover(0,"Retiro");    // RUR 0: 0 infracciones
    caba.Mover(0,"Martinez");  // RUR 0: 1 infracciones

    caba.Mover(1,"Belgrano");  // RUR 1: 0 infracciones
    caba.Mover(1,"Martinez");  // RUR 1: 1 infracciones

    caba.Mover(2,"Belgrano");  // RUR 2: 1 infracciones
    caba.Mover(2,"Retiro");    // RUR 2: 2 infracciones

    Dicc<RUR,Nat> infraccionesRobots;

    // Chequeo infracciones iterando los robots
    for (Nat i = 0;  i< caba.CantidadRobotsActivos(); ++i)
        infraccionesRobots.Definir(caba.IesimoRobotActivo(i),caba.CantInfraccionesIesimoRobotActivo(i));

    ASSERT_EQ(infraccionesRobots.Significado(0), 1);
    ASSERT_EQ(infraccionesRobots.Significado(1), 1);
    ASSERT_EQ(infraccionesRobots.Significado(2), 2);

    ASSERT_EQ(caba.ElMasInfractor(),2);

    // Vuela un robot
    caba.Inspeccion("Retiro");
    ASSERT_EQ(caba.CantidadRobotsActivos(),2);

}

void agregar_diccionario() {
    DiccString<Nat> dic;
    dic.Definir("a", 4);
    
    DiccString<Nat> dic2(dic);
    
    dic.Definir("coso", 6);

    ASSERT(dic.Definido("a"));
    ASSERT_EQ(dic.Significado("a"), 4);
    ASSERT(dic.Definido("coso"));
    ASSERT_EQ(dic.Significado("coso"), 6);    
    
    ASSERT(dic2.Definido("a"));
    ASSERT_EQ(dic2.Significado("a"), 4);
    ASSERT(!dic2.Definido("coso"));
    
    DiccString<DiccString<Nat> > ddic;
    ddic.Definir("Test", dic);
    
    ASSERT(ddic.Definido("Test"));
}

void test_tupla() {
    tuplaAB hola(1, 2);
    tuplaAB holis(1, 3);
    tuplaAB wow(hola);
    
    ASSERT(wow.pri == hola.pri);
    ASSERT(wow.seg == hola.seg);
    ASSERT(hola < holis);
}

void test_AVL() {
    ColaP AVL;
    
    AVL.Agregar(3,3);
    AVL.Agregar(2,2);
    AVL.Agregar(1,1);
    AVL.Agregar(4,4);
    AVL.Agregar(5,5);
    AVL.Agregar(6,6);
    AVL.Agregar(7,7);
    
    AVL.Eliminar(6,6);
    AVL.Eliminar(5,5);
    AVL.Eliminar(7,7);
    AVL.Eliminar(1,1);
    
    ASSERT_EQ(AVL.Tamanio(), 3);
    
    AVL.Agregar(1,1);
    AVL.Agregar(5,5);
    AVL.Agregar(7,7);
    AVL.Agregar(6,6);
    
    ColaP AVL2(AVL);

    tuplaAB test = AVL.Desencolar();
    ASSERT_EQ(test.pri, 7);
    ASSERT_EQ(test.seg, 7);
    test = AVL.Desencolar();
    ASSERT_EQ(test.pri, 6);
    ASSERT_EQ(test.seg, 6);
    test = AVL.Desencolar();
    ASSERT_EQ(test.pri, 5);
    ASSERT_EQ(test.seg, 5);
    test = AVL.Desencolar();
    ASSERT_EQ(test.pri, 4);
    ASSERT_EQ(test.seg, 4);
    test = AVL.Desencolar();
    ASSERT_EQ(test.pri, 3);
    ASSERT_EQ(test.seg, 3);
    test = AVL.Desencolar();
    ASSERT_EQ(test.pri, 2);
    ASSERT_EQ(test.seg, 2);
    test = AVL.Desencolar();
    ASSERT_EQ(test.pri, 1);
    ASSERT_EQ(test.seg, 1);
            
    ASSERT_EQ(AVL.Tamanio(), 0);
    ASSERT_EQ(AVL2.Tamanio(), 7)
}

void test_restriccion() {
    Rest rojo("rojo");
    Rest amarillo("Amarillo");
    Rest verde("VERDE");
    
    Rest res1((rojo.OR(amarillo)).AND(verde.NOT()));
    
    
//    Rest res1("(rojo | Amarillo) & !VERDE");
    Conj<Caracteristica> carac;
    carac.Agregar("Amarillo");
    
//    ASSERT(res1 -> Verifica(carac));
    ASSERT(res1.Verifica(carac));
    
    Rest coso("Coso");
    Rest noCoso(coso.NOT());
    Rest res2 = res1.AND(noCoso);
    
    carac.Agregar("Coso");
    ASSERT(res1.Verifica(carac));
    ASSERT(!res2.Verifica(carac));
    
    Conj<Caracteristica> carac2;
    carac2.Agregar("Coso");
    Rest siCoso = noCoso.NOT();
    ASSERT(siCoso.Verifica(carac2));
}

void test_mapa() {
    Mapa mapa1;
    
    mapa1.Agregar("Hola");
    mapa1.Agregar("Coso");
    mapa1.Agregar("Cafe");
    
    Rest res1("(rojo | Amarillo) & !VERDE");
    Rest res2("Amarillo");
    mapa1.Conectar("Hola", "Coso", res1);
    mapa1.Conectar("Hola", "Cafe", res2);
    
    ASSERT(mapa1.Conectadas("Hola", "Coso"));
    ASSERT(mapa1.Conectadas("Hola", "Cafe"));
    ASSERT(!mapa1.Conectadas("Coso", "Cafe"));

    ASSERT_EQ(mapa1.NroConexion("Hola", "Coso"), 0);
    ASSERT_EQ(mapa1.NroConexion("Coso", "Hola"), 0);
    ASSERT_EQ(mapa1.NroConexion("Hola", "Cafe"), 1);
    ASSERT_EQ(mapa1.NroConexion("Cafe", "Hola"), 1);
    
    Conj<Caracteristica> carac;
    carac.Agregar("Amarillo");
    carac.Agregar("VERDE");
    
    Arreglo<bool> sendas = mapa1.EvaluarSendas(carac);
    ASSERT(!sendas[0]);
    ASSERT(sendas[1]);
    
    Mapa mapa2(mapa1);
    
    mapa2.Conectar("Coso","Cafe", res1);
    
    ASSERT_EQ(mapa2.NroConexion("Coso", "Cafe"), 2);
    ASSERT_EQ(mapa2.NroConexion("Cafe", "Coso"), 2);
    ASSERT(mapa2.Conectadas("Coso", "Cafe"));
    ASSERT(!mapa1.Conectadas("Coso", "Cafe"));
}

int main(int argc, char **argv)
{
    RUN_TEST(agregar_diccionario);
    RUN_TEST(test_tupla);
    RUN_TEST(test_AVL);
    RUN_TEST(test_restriccion);
    RUN_TEST(test_mapa);
    RUN_TEST(test_ciudad_simple);
	
	/******************************************************************
	 * TODO: escribir casos de test exhaustivos para todas            *
	 * las funcionalidades del módulo.                                *
     * La interacción con el TAD Ciudad se debe hacer exclusivamente  *
	 * a través de la interfaz del driver.                            *
	 ******************************************************************/

	return 0;
}
