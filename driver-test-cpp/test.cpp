#include "TiposSimples.h"
#include "TiposBasicos.h"
#include "aed2/Lista.h"
#include "aed2/Conj.h"
#include "aed2/Dicc.h"
#include "DiccRapido.h"
#include "red.h"
#include "dcnet.h"
#include "Driver.h"
#include "mini_test.h"


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
 
void test_dcnet_ejemplo() {
	Conj<Interfaz> conjIc1;
	Conj<Interfaz> conjIc2;
	Conj<Interfaz> conjIc3;
	
	conjIc1.Agregar(1);
	conjIc1.Agregar(2);
	conjIc1.Agregar(3);
	
    std::cout << "Agregar de conj funciona \n";
	conjIc2.Agregar(1);
	conjIc2.Agregar(2);
	conjIc2.Agregar(3);
	
	conjIc3.Agregar(1);
	conjIc3.Agregar(2);
	
	Computadora c1 = "dc.uba.ar";
	Computadora c2 = "uba.ar";
	Computadora c3 = "dm.uba.ar";
	
	Driver dcnet;

	

    std::cout << "Creo un dcnet \n";
	
	dcnet.AgregarComputadora(c1, conjIc1);

    std::cout << "Agrega 1 Computadora \n";
	dcnet.AgregarComputadora(c2, conjIc2);
	std::cout << "Agrega 2 Computadora \n";

	dcnet.AgregarComputadora(c3, conjIc3);
	std::cout << "Agrega 3 Computadora \n";
	
	// ejemplo - Indexado en 0 
	Interfaz i1 = dcnet.IesimaInterfazDe(c1, 0); 
	std::cout << "pide la interfaz de c1 << i1 << \n";
	Interfaz i2 = dcnet.IesimaInterfazDe(c2, 2);
	std::cout << "pide la interfaz de c2: <<i2<< \n";
	
	dcnet.Conectar(c1, i1, c2, i2);

	std::cout << "Hace conectar entre c1 y c2 \n";

	std::cout << "prioridad del paquete 0"<<dcnet.prioridad(0) <<"\n";


	dcnet.CrearPaquete(c1, c2, 3);

	std::cout << "Crea un paquete \n";
	
	dcnet.AvanzarSegundo();	

	std::cout << "Avanza un segundo \n";
	dcnet.CrearPaquete(c2, c1, 2);
	std::cout << "Crea otro paquete \n";
	dcnet.AvanzarSegundo();	

	std::cout << "Avanza un segundo \n";

	ASSERT_EQ(dcnet.laQueMasEnvio(), c1);

	std::cout << "Hace la que mas envio \n";
		
}
void dicc_vacio() {
	DiccRapido<int, int>();
}

void definir_dicc_vacio() {
	DiccRapido<int, int> dicc;

	dicc.Definir(5, 8);
}

int main(int argc, char **argv)
{
    RUN_TEST(test_dcnet_ejemplo);
	RUN_TEST(dicc_vacio);
	
	/******************************************************************
	 * TODO: escribir casos de test exhaustivos para todas            *
	 * las funcionalidades del módulo.                                *
     * La interacción con el TAD DcNet se debe hacer exclusivamente  *
	 * a través de la interfaz del driver.                            *
	 ******************************************************************/

	return 0;
}
