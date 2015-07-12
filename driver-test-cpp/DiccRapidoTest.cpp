//#include "aed2/TiposBasicos.h"
#include <stdlib.h>
#include <iostream>
#include "DiccRapido.h"
#include "mini_test.h"

using namespace std;
using namespace aed2;


template<typename T>
string to_s(const T& m) {
 	ostringstream os;
	os << m;
	return os.str();
 }


 /*
 * Crea un diccionario vacio y no agrega elementos.
 */
void check_crear_dicc_vacio() {
    DiccRapido<int, int> dicc;

    ASSERT_EQ(dicc.Vacio(), true);

}

/*
* Define 6 elementos y verifica que estén agregados bien.
*/
void check_definir() {
	DiccRapido<int, int> dicc;

	ASSERT_EQ(dicc.Vacio(), true);

	dicc.Definir(5, 10);
	dicc.Definir(3, 6);
	dicc.Definir(10, 20);
	dicc.Definir(7, 14);
	dicc.Definir(12, 24);
	dicc.Definir(8, 16);
	
	ASSERT_EQ(dicc.Vacio(), false);
	ASSERT_EQ(dicc.Def(5), true);
	ASSERT_EQ(dicc.Def(3), true);
	ASSERT_EQ(dicc.Def(10), true);
	ASSERT_EQ(dicc.Def(7), true);
	ASSERT_EQ(dicc.Def(12), true);
	ASSERT_EQ(dicc.Def(8), true);

	ASSERT_EQ(dicc.Raiz(), 7);
	ASSERT_EQ(dicc.HijoIzq(7), 5);
	ASSERT_EQ(dicc.Padre(5), 7);
	ASSERT_EQ(dicc.HijoIzq(5), 3);
	ASSERT_EQ(dicc.Padre(3), 5);
	ASSERT_EQ(dicc.HijoDer(7), 10);
	ASSERT_EQ(dicc.Padre(10), 7);
	ASSERT_EQ(dicc.HijoIzq(10), 8);
	ASSERT_EQ(dicc.Padre(8), 10);
	ASSERT_EQ(dicc.HijoDer(10), 12);
	ASSERT_EQ(dicc.Padre(12), 10);

	ASSERT_EQ(dicc.ClaveMax(), 12);
	ASSERT_EQ(dicc.ClaveMin(), 3);

	ASSERT_EQ(dicc.Obtener(5), 10);
	ASSERT_EQ(dicc.Obtener(7), 14);
	ASSERT_EQ(dicc.Obtener(3), 6);
	ASSERT_EQ(dicc.Obtener(8), 16);
	ASSERT_EQ(dicc.Obtener(10), 20);
	ASSERT_EQ(dicc.Obtener(12), 24);

	//DEFINO EN OTRO ORDEN
	dicc.Definir(3, 6);
	dicc.Definir(5, 10);
	dicc.Definir(10, 20);
	dicc.Definir(7, 14);
	dicc.Definir(12, 24);
	dicc.Definir(8, 16);
	
	ASSERT_EQ(dicc.Vacio(), false);
	ASSERT_EQ(dicc.Def(5), true);
	ASSERT_EQ(dicc.Def(3), true);
	ASSERT_EQ(dicc.Def(10), true);
	ASSERT_EQ(dicc.Def(7), true);
	ASSERT_EQ(dicc.Def(12), true);
	ASSERT_EQ(dicc.Def(8), true);

	ASSERT_EQ(dicc.Raiz(), 7);
	ASSERT_EQ(dicc.HijoIzq(7), 5);
	ASSERT_EQ(dicc.Padre(5), 7);
	ASSERT_EQ(dicc.HijoIzq(5), 3);
	ASSERT_EQ(dicc.Padre(3), 5);
	ASSERT_EQ(dicc.HijoDer(7), 10);
	ASSERT_EQ(dicc.Padre(10), 7);
	ASSERT_EQ(dicc.HijoIzq(10), 8);
	ASSERT_EQ(dicc.Padre(8), 10);
	ASSERT_EQ(dicc.HijoDer(10), 12);
	ASSERT_EQ(dicc.Padre(12), 10);

	ASSERT_EQ(dicc.ClaveMax(), 12);
	ASSERT_EQ(dicc.ClaveMin(), 3);

	ASSERT_EQ(dicc.Obtener(5), 10);
	ASSERT_EQ(dicc.Obtener(7), 14);
	ASSERT_EQ(dicc.Obtener(3), 6);
	ASSERT_EQ(dicc.Obtener(8), 16);
	ASSERT_EQ(dicc.Obtener(10), 20);
	ASSERT_EQ(dicc.Obtener(12), 24);

	//DEFINO EN OTRO ORDEN
	dicc.Definir(10, 20);
	dicc.Definir(3, 6);
	dicc.Definir(5, 10);
	dicc.Definir(7, 14);
	dicc.Definir(12, 24);
	dicc.Definir(8, 16);
	
	ASSERT_EQ(dicc.Vacio(), false);
	ASSERT_EQ(dicc.Def(5), true);
	ASSERT_EQ(dicc.Def(3), true);
	ASSERT_EQ(dicc.Def(10), true);
	ASSERT_EQ(dicc.Def(7), true);
	ASSERT_EQ(dicc.Def(12), true);
	ASSERT_EQ(dicc.Def(8), true);

	ASSERT_EQ(dicc.Raiz(), 7);
	ASSERT_EQ(dicc.HijoIzq(7), 5);
	ASSERT_EQ(dicc.Padre(5), 7);
	ASSERT_EQ(dicc.HijoIzq(5), 3);
	ASSERT_EQ(dicc.Padre(3), 5);
	ASSERT_EQ(dicc.HijoDer(7), 10);
	ASSERT_EQ(dicc.Padre(10), 7);
	ASSERT_EQ(dicc.HijoIzq(10), 8);
	ASSERT_EQ(dicc.Padre(8), 10);
	ASSERT_EQ(dicc.HijoDer(10), 12);
	ASSERT_EQ(dicc.Padre(12), 10);

	ASSERT_EQ(dicc.ClaveMax(), 12);
	ASSERT_EQ(dicc.ClaveMin(), 3);

	ASSERT_EQ(dicc.Obtener(5), 10);
	ASSERT_EQ(dicc.Obtener(7), 14);
	ASSERT_EQ(dicc.Obtener(3), 6);
	ASSERT_EQ(dicc.Obtener(8), 16);
	ASSERT_EQ(dicc.Obtener(10), 20);
	ASSERT_EQ(dicc.Obtener(12), 24);

	//DEFINO EN OTRO ORDEN
	dicc.Definir(8, 16);
	dicc.Definir(10, 20);
	dicc.Definir(3, 6);
	dicc.Definir(5, 10);
	dicc.Definir(7, 14);
	dicc.Definir(12, 24);
	
	ASSERT_EQ(dicc.Vacio(), false);
	ASSERT_EQ(dicc.Def(5), true);
	ASSERT_EQ(dicc.Def(3), true);
	ASSERT_EQ(dicc.Def(10), true);
	ASSERT_EQ(dicc.Def(7), true);
	ASSERT_EQ(dicc.Def(12), true);
	ASSERT_EQ(dicc.Def(8), true);

	ASSERT_EQ(dicc.Raiz(), 7);
	ASSERT_EQ(dicc.HijoIzq(7), 5);
	ASSERT_EQ(dicc.Padre(5), 7);
	ASSERT_EQ(dicc.HijoIzq(5), 3);
	ASSERT_EQ(dicc.Padre(3), 5);
	ASSERT_EQ(dicc.HijoDer(7), 10);
	ASSERT_EQ(dicc.Padre(10), 7);
	ASSERT_EQ(dicc.HijoIzq(10), 8);
	ASSERT_EQ(dicc.Padre(8), 10);
	ASSERT_EQ(dicc.HijoDer(10), 12);
	ASSERT_EQ(dicc.Padre(12), 10);

	ASSERT_EQ(dicc.ClaveMax(), 12);
	ASSERT_EQ(dicc.ClaveMin(), 3);

	ASSERT_EQ(dicc.Obtener(5), 10);
	ASSERT_EQ(dicc.Obtener(7), 14);
	ASSERT_EQ(dicc.Obtener(3), 6);
	ASSERT_EQ(dicc.Obtener(8), 16);
	ASSERT_EQ(dicc.Obtener(10), 20);
	ASSERT_EQ(dicc.Obtener(12), 24);

	//DEFINO EN OTRO ORDEN
	dicc.Definir(12, 24);
	dicc.Definir(8, 16);
	dicc.Definir(10, 20);
	dicc.Definir(3, 6);
	dicc.Definir(5, 10);
	dicc.Definir(7, 14);
	
	ASSERT_EQ(dicc.Vacio(), false);
	ASSERT_EQ(dicc.Def(5), true);
	ASSERT_EQ(dicc.Def(3), true);
	ASSERT_EQ(dicc.Def(10), true);
	ASSERT_EQ(dicc.Def(7), true);
	ASSERT_EQ(dicc.Def(12), true);
	ASSERT_EQ(dicc.Def(8), true);

	ASSERT_EQ(dicc.Raiz(), 7);
	ASSERT_EQ(dicc.HijoIzq(7), 5);
	ASSERT_EQ(dicc.Padre(5), 7);
	ASSERT_EQ(dicc.HijoIzq(5), 3);
	ASSERT_EQ(dicc.Padre(3), 5);
	ASSERT_EQ(dicc.HijoDer(7), 10);
	ASSERT_EQ(dicc.Padre(10), 7);
	ASSERT_EQ(dicc.HijoIzq(10), 8);
	ASSERT_EQ(dicc.Padre(8), 10);
	ASSERT_EQ(dicc.HijoDer(10), 12);
	ASSERT_EQ(dicc.Padre(12), 10);

	ASSERT_EQ(dicc.ClaveMax(), 12);
	ASSERT_EQ(dicc.ClaveMin(), 3);

	ASSERT_EQ(dicc.Obtener(5), 10);
	ASSERT_EQ(dicc.Obtener(7), 14);
	ASSERT_EQ(dicc.Obtener(3), 6);
	ASSERT_EQ(dicc.Obtener(8), 16);
	ASSERT_EQ(dicc.Obtener(10), 20);
	ASSERT_EQ(dicc.Obtener(12), 24);

	//DEFINO EN OTRO ORDEN
	dicc.Definir(12, 24);
	dicc.Definir(8, 16);
	dicc.Definir(5, 10);
	dicc.Definir(10, 20);
	dicc.Definir(3, 6);
	dicc.Definir(7, 14);
	
	ASSERT_EQ(dicc.Vacio(), false);
	ASSERT_EQ(dicc.Def(5), true);
	ASSERT_EQ(dicc.Def(3), true);
	ASSERT_EQ(dicc.Def(10), true);
	ASSERT_EQ(dicc.Def(7), true);
	ASSERT_EQ(dicc.Def(12), true);
	ASSERT_EQ(dicc.Def(8), true);

	ASSERT_EQ(dicc.Raiz(), 7);
	ASSERT_EQ(dicc.HijoIzq(7), 5);
	ASSERT_EQ(dicc.Padre(5), 7);
	ASSERT_EQ(dicc.HijoIzq(5), 3);
	ASSERT_EQ(dicc.Padre(3), 5);
	ASSERT_EQ(dicc.HijoDer(7), 10);
	ASSERT_EQ(dicc.Padre(10), 7);
	ASSERT_EQ(dicc.HijoIzq(10), 8);
	ASSERT_EQ(dicc.Padre(8), 10);
	ASSERT_EQ(dicc.HijoDer(10), 12);
	ASSERT_EQ(dicc.Padre(12), 10);

	ASSERT_EQ(dicc.ClaveMax(), 12);
	ASSERT_EQ(dicc.ClaveMin(), 3);

	ASSERT_EQ(dicc.Obtener(5), 10);
	ASSERT_EQ(dicc.Obtener(7), 14);
	ASSERT_EQ(dicc.Obtener(3), 6);
	ASSERT_EQ(dicc.Obtener(8), 16);
	ASSERT_EQ(dicc.Obtener(10), 20);
	ASSERT_EQ(dicc.Obtener(12), 24);

	//DEFINO EN OTRO ORDEN
	dicc.Definir(12, 24);
	dicc.Definir(8, 16);
	dicc.Definir(5, 10);
	dicc.Definir(3, 6);
	dicc.Definir(7, 14);
	dicc.Definir(10, 20);
	
	ASSERT_EQ(dicc.Vacio(), false);
	ASSERT_EQ(dicc.Def(5), true);
	ASSERT_EQ(dicc.Def(3), true);
	ASSERT_EQ(dicc.Def(10), true);
	ASSERT_EQ(dicc.Def(7), true);
	ASSERT_EQ(dicc.Def(12), true);
	ASSERT_EQ(dicc.Def(8), true);

	ASSERT_EQ(dicc.Raiz(), 7);
	ASSERT_EQ(dicc.HijoIzq(7), 5);
	ASSERT_EQ(dicc.Padre(5), 7);
	ASSERT_EQ(dicc.HijoIzq(5), 3);
	ASSERT_EQ(dicc.Padre(3), 5);
	ASSERT_EQ(dicc.HijoDer(7), 10);
	ASSERT_EQ(dicc.Padre(10), 7);
	ASSERT_EQ(dicc.HijoIzq(10), 8);
	ASSERT_EQ(dicc.Padre(8), 10);
	ASSERT_EQ(dicc.HijoDer(10), 12);
	ASSERT_EQ(dicc.Padre(12), 10);

	ASSERT_EQ(dicc.ClaveMax(), 12);
	ASSERT_EQ(dicc.ClaveMin(), 3);

	ASSERT_EQ(dicc.Obtener(5), 10);
	ASSERT_EQ(dicc.Obtener(7), 14);
	ASSERT_EQ(dicc.Obtener(3), 6);
	ASSERT_EQ(dicc.Obtener(8), 16);
	ASSERT_EQ(dicc.Obtener(10), 20);
	ASSERT_EQ(dicc.Obtener(12), 24);
}

void check_redefinir() {
DiccRapido<int, int> dicc;

	ASSERT_EQ(dicc.Vacio(), true);

	dicc.Definir(5, 10);
	dicc.Definir(3, 6);
	dicc.Definir(10, 20);
	dicc.Definir(7, 14);
	dicc.Definir(12, 24);
	dicc.Definir(8, 16);
	
	ASSERT_EQ(dicc.Vacio(), false);
	ASSERT_EQ(dicc.Def(5), true);
	ASSERT_EQ(dicc.Def(3), true);
	ASSERT_EQ(dicc.Def(10), true);
	ASSERT_EQ(dicc.Def(7), true);
	ASSERT_EQ(dicc.Def(12), true);
	ASSERT_EQ(dicc.Def(8), true);

	ASSERT_EQ(dicc.Raiz(), 7);
	ASSERT_EQ(dicc.HijoIzq(7), 5);
	ASSERT_EQ(dicc.Padre(5), 7);
	ASSERT_EQ(dicc.HijoIzq(5), 3);
	ASSERT_EQ(dicc.Padre(3), 5);
	ASSERT_EQ(dicc.HijoDer(7), 10);
	ASSERT_EQ(dicc.Padre(10), 7);
	ASSERT_EQ(dicc.HijoIzq(10), 8);
	ASSERT_EQ(dicc.Padre(8), 10);
	ASSERT_EQ(dicc.HijoDer(10), 12);
	ASSERT_EQ(dicc.Padre(12), 10);

	ASSERT_EQ(dicc.ClaveMax(), 12);
	ASSERT_EQ(dicc.ClaveMin(), 3);

	ASSERT_EQ(dicc.Obtener(5), 10);
	ASSERT_EQ(dicc.Obtener(7), 14);
	ASSERT_EQ(dicc.Obtener(3), 6);
	ASSERT_EQ(dicc.Obtener(8), 16);
	ASSERT_EQ(dicc.Obtener(10), 20);
	ASSERT_EQ(dicc.Obtener(12), 24);

	//REDEFINO (5, 20)
	dicc.Definir(5, 20);

	ASSERT_EQ(dicc.Vacio(), false);
	ASSERT_EQ(dicc.Def(5), true);
	ASSERT_EQ(dicc.Def(3), true);
	ASSERT_EQ(dicc.Def(10), true);
	ASSERT_EQ(dicc.Def(7), true);
	ASSERT_EQ(dicc.Def(12), true);
	ASSERT_EQ(dicc.Def(8), true);

	ASSERT_EQ(dicc.Raiz(), 7);
	ASSERT_EQ(dicc.HijoIzq(7), 5);
	ASSERT_EQ(dicc.Padre(5), 7);
	ASSERT_EQ(dicc.HijoIzq(5), 3);
	ASSERT_EQ(dicc.Padre(3), 5);
	ASSERT_EQ(dicc.HijoDer(7), 10);
	ASSERT_EQ(dicc.Padre(10), 7);
	ASSERT_EQ(dicc.HijoIzq(10), 8);
	ASSERT_EQ(dicc.Padre(8), 10);
	ASSERT_EQ(dicc.HijoDer(10), 12);
	ASSERT_EQ(dicc.Padre(12), 10);

	ASSERT_EQ(dicc.ClaveMax(), 12);
	ASSERT_EQ(dicc.ClaveMin(), 3);

	ASSERT_EQ(dicc.Obtener(5), 20);
	ASSERT_EQ(dicc.Obtener(7), 14);
	ASSERT_EQ(dicc.Obtener(3), 6);
	ASSERT_EQ(dicc.Obtener(8), 16);
	ASSERT_EQ(dicc.Obtener(10), 20);
	ASSERT_EQ(dicc.Obtener(12), 24);

	//REDEFINO (3, 9)
	dicc.Definir(3, 9);

	ASSERT_EQ(dicc.Vacio(), false);
	ASSERT_EQ(dicc.Def(5), true);
	ASSERT_EQ(dicc.Def(3), true);
	ASSERT_EQ(dicc.Def(10), true);
	ASSERT_EQ(dicc.Def(7), true);
	ASSERT_EQ(dicc.Def(12), true);
	ASSERT_EQ(dicc.Def(8), true);

	ASSERT_EQ(dicc.Raiz(), 7);
	ASSERT_EQ(dicc.HijoIzq(7), 5);
	ASSERT_EQ(dicc.Padre(5), 7);
	ASSERT_EQ(dicc.HijoIzq(5), 3);
	ASSERT_EQ(dicc.Padre(3), 5);
	ASSERT_EQ(dicc.HijoDer(7), 10);
	ASSERT_EQ(dicc.Padre(10), 7);
	ASSERT_EQ(dicc.HijoIzq(10), 8);
	ASSERT_EQ(dicc.Padre(8), 10);
	ASSERT_EQ(dicc.HijoDer(10), 12);
	ASSERT_EQ(dicc.Padre(12), 10);

	ASSERT_EQ(dicc.ClaveMax(), 12);
	ASSERT_EQ(dicc.ClaveMin(), 3);

	ASSERT_EQ(dicc.Obtener(5), 20);
	ASSERT_EQ(dicc.Obtener(7), 14);
	ASSERT_EQ(dicc.Obtener(3), 9);
	ASSERT_EQ(dicc.Obtener(8), 16);
	ASSERT_EQ(dicc.Obtener(10), 20);
	ASSERT_EQ(dicc.Obtener(12), 24);

	//REDEFINO (7, 21)
	dicc.Definir(7, 21);

	ASSERT_EQ(dicc.Vacio(), false);
	ASSERT_EQ(dicc.Def(5), true);
	ASSERT_EQ(dicc.Def(3), true);
	ASSERT_EQ(dicc.Def(10), true);
	ASSERT_EQ(dicc.Def(7), true);
	ASSERT_EQ(dicc.Def(12), true);
	ASSERT_EQ(dicc.Def(8), true);

	ASSERT_EQ(dicc.Raiz(), 7);
	ASSERT_EQ(dicc.HijoIzq(7), 5);
	ASSERT_EQ(dicc.Padre(5), 7);
	ASSERT_EQ(dicc.HijoIzq(5), 3);
	ASSERT_EQ(dicc.Padre(3), 5);
	ASSERT_EQ(dicc.HijoDer(7), 10);
	ASSERT_EQ(dicc.Padre(10), 7);
	ASSERT_EQ(dicc.HijoIzq(10), 8);
	ASSERT_EQ(dicc.Padre(8), 10);
	ASSERT_EQ(dicc.HijoDer(10), 12);
	ASSERT_EQ(dicc.Padre(12), 10);

	ASSERT_EQ(dicc.ClaveMax(), 12);
	ASSERT_EQ(dicc.ClaveMin(), 3);

	ASSERT_EQ(dicc.Obtener(5), 20);
	ASSERT_EQ(dicc.Obtener(7), 21);
	ASSERT_EQ(dicc.Obtener(3), 9);
	ASSERT_EQ(dicc.Obtener(8), 16);
	ASSERT_EQ(dicc.Obtener(10), 20);
	ASSERT_EQ(dicc.Obtener(12), 24);

	//REDEFINO (7, 21)
	dicc.Definir(8, 24);

	ASSERT_EQ(dicc.Vacio(), false);
	ASSERT_EQ(dicc.Def(5), true);
	ASSERT_EQ(dicc.Def(3), true);
	ASSERT_EQ(dicc.Def(10), true);
	ASSERT_EQ(dicc.Def(7), true);
	ASSERT_EQ(dicc.Def(12), true);
	ASSERT_EQ(dicc.Def(8), true);

	ASSERT_EQ(dicc.Raiz(), 7);
	ASSERT_EQ(dicc.HijoIzq(7), 5);
	ASSERT_EQ(dicc.Padre(5), 7);
	ASSERT_EQ(dicc.HijoIzq(5), 3);
	ASSERT_EQ(dicc.Padre(3), 5);
	ASSERT_EQ(dicc.HijoDer(7), 10);
	ASSERT_EQ(dicc.Padre(10), 7);
	ASSERT_EQ(dicc.HijoIzq(10), 8);
	ASSERT_EQ(dicc.Padre(8), 10);
	ASSERT_EQ(dicc.HijoDer(10), 12);
	ASSERT_EQ(dicc.Padre(12), 10);

	ASSERT_EQ(dicc.ClaveMax(), 12);
	ASSERT_EQ(dicc.ClaveMin(), 3);

	ASSERT_EQ(dicc.Obtener(5), 20);
	ASSERT_EQ(dicc.Obtener(7), 21);
	ASSERT_EQ(dicc.Obtener(3), 9);
	ASSERT_EQ(dicc.Obtener(8), 24);
	ASSERT_EQ(dicc.Obtener(10), 20);
	ASSERT_EQ(dicc.Obtener(12), 24);

	//REDEFINO (10, 30)
	dicc.Definir(10, 30);

	ASSERT_EQ(dicc.Vacio(), false);
	ASSERT_EQ(dicc.Def(5), true);
	ASSERT_EQ(dicc.Def(3), true);
	ASSERT_EQ(dicc.Def(10), true);
	ASSERT_EQ(dicc.Def(7), true);
	ASSERT_EQ(dicc.Def(12), true);
	ASSERT_EQ(dicc.Def(8), true);

	ASSERT_EQ(dicc.Raiz(), 7);
	ASSERT_EQ(dicc.HijoIzq(7), 5);
	ASSERT_EQ(dicc.Padre(5), 7);
	ASSERT_EQ(dicc.HijoIzq(5), 3);
	ASSERT_EQ(dicc.Padre(3), 5);
	ASSERT_EQ(dicc.HijoDer(7), 10);
	ASSERT_EQ(dicc.Padre(10), 7);
	ASSERT_EQ(dicc.HijoIzq(10), 8);
	ASSERT_EQ(dicc.Padre(8), 10);
	ASSERT_EQ(dicc.HijoDer(10), 12);
	ASSERT_EQ(dicc.Padre(12), 10);

	ASSERT_EQ(dicc.ClaveMax(), 12);
	ASSERT_EQ(dicc.ClaveMin(), 3);

	ASSERT_EQ(dicc.Obtener(5), 20);
	ASSERT_EQ(dicc.Obtener(7), 21);
	ASSERT_EQ(dicc.Obtener(3), 9);
	ASSERT_EQ(dicc.Obtener(8), 24);
	ASSERT_EQ(dicc.Obtener(10), 30);
	ASSERT_EQ(dicc.Obtener(12), 24);

	//REDEFINO (12, 36)
	dicc.Definir(12, 36);

	ASSERT_EQ(dicc.Vacio(), false);
	ASSERT_EQ(dicc.Def(5), true);
	ASSERT_EQ(dicc.Def(3), true);
	ASSERT_EQ(dicc.Def(10), true);
	ASSERT_EQ(dicc.Def(7), true);
	ASSERT_EQ(dicc.Def(12), true);
	ASSERT_EQ(dicc.Def(8), true);

	ASSERT_EQ(dicc.Raiz(), 7);
	ASSERT_EQ(dicc.HijoIzq(7), 5);
	ASSERT_EQ(dicc.Padre(5), 7);
	ASSERT_EQ(dicc.HijoIzq(5), 3);
	ASSERT_EQ(dicc.Padre(3), 5);
	ASSERT_EQ(dicc.HijoDer(7), 10);
	ASSERT_EQ(dicc.Padre(10), 7);
	ASSERT_EQ(dicc.HijoIzq(10), 8);
	ASSERT_EQ(dicc.Padre(8), 10);
	ASSERT_EQ(dicc.HijoDer(10), 12);
	ASSERT_EQ(dicc.Padre(12), 10);

	ASSERT_EQ(dicc.ClaveMax(), 12);
	ASSERT_EQ(dicc.ClaveMin(), 3);

	ASSERT_EQ(dicc.Obtener(5), 20);
	ASSERT_EQ(dicc.Obtener(7), 21);
	ASSERT_EQ(dicc.Obtener(3), 9);
	ASSERT_EQ(dicc.Obtener(8), 24);
	ASSERT_EQ(dicc.Obtener(10), 30);
	ASSERT_EQ(dicc.Obtener(12), 36);
}

void check_borrar() {
DiccRapido<int, int> dicc;

	ASSERT_EQ(dicc.Vacio(), true);

	dicc.Definir(5, 10);
	dicc.Definir(3, 6);
	dicc.Definir(10, 20);
	dicc.Definir(7, 14);
	dicc.Definir(12, 24);
	dicc.Definir(8, 16);
	
	ASSERT_EQ(dicc.Vacio(), false);
	ASSERT_EQ(dicc.Def(5), true);
	ASSERT_EQ(dicc.Def(3), true);
	ASSERT_EQ(dicc.Def(10), true);
	ASSERT_EQ(dicc.Def(7), true);
	ASSERT_EQ(dicc.Def(12), true);
	ASSERT_EQ(dicc.Def(8), true);

	ASSERT_EQ(dicc.Raiz(), 7);
	ASSERT_EQ(dicc.HijoIzq(7), 5);
	ASSERT_EQ(dicc.Padre(5), 7);
	ASSERT_EQ(dicc.HijoIzq(5), 3);
	ASSERT_EQ(dicc.Padre(3), 5);
	ASSERT_EQ(dicc.HijoDer(7), 10);
	ASSERT_EQ(dicc.Padre(10), 7);
	ASSERT_EQ(dicc.HijoIzq(10), 8);
	ASSERT_EQ(dicc.Padre(8), 10);
	ASSERT_EQ(dicc.HijoDer(10), 12);
	ASSERT_EQ(dicc.Padre(12), 10);

	ASSERT_EQ(dicc.ClaveMax(), 12);
	ASSERT_EQ(dicc.ClaveMin(), 3);

	ASSERT_EQ(dicc.Obtener(5), 10);
	ASSERT_EQ(dicc.Obtener(7), 14);
	ASSERT_EQ(dicc.Obtener(3), 6);
	ASSERT_EQ(dicc.Obtener(8), 16);
	ASSERT_EQ(dicc.Obtener(10), 20);
	ASSERT_EQ(dicc.Obtener(12), 24);

	//BORRO RAIZ CON DOS HIJOS
	dicc.Borrar(7);

	ASSERT_EQ(dicc.Vacio(), false);

	ASSERT_EQ(dicc.Def(5), true);
	ASSERT_EQ(dicc.Def(3), true);
	ASSERT_EQ(dicc.Def(10), true);
	ASSERT_EQ(dicc.Def(7), false);
	ASSERT_EQ(dicc.Def(12), true);
	ASSERT_EQ(dicc.Def(8), true);

	ASSERT_EQ(dicc.Raiz(), 8);
	ASSERT_EQ(dicc.HijoIzq(8), 5);
	ASSERT_EQ(dicc.Padre(5), 8);
	ASSERT_EQ(dicc.HijoIzq(5), 3);
	ASSERT_EQ(dicc.Padre(3), 5);
	ASSERT_EQ(dicc.HijoDer(8), 10);
	ASSERT_EQ(dicc.Padre(10), 8);
	ASSERT_EQ(dicc.HijoDer(10), 12);
	ASSERT_EQ(dicc.Padre(12), 10);

	ASSERT_EQ(dicc.ClaveMax(), 12);
	ASSERT_EQ(dicc.ClaveMin(), 3);

	ASSERT_EQ(dicc.Obtener(5), 10);
	ASSERT_EQ(dicc.Obtener(3), 6);
	ASSERT_EQ(dicc.Obtener(8), 16);
	ASSERT_EQ(dicc.Obtener(10), 20);
	ASSERT_EQ(dicc.Obtener(12), 24);

	//VUELVO A DEFINIR LA CLAVE 7
	dicc.Definir(7, 1);

	ASSERT_EQ(dicc.Vacio(), false);

	ASSERT_EQ(dicc.Def(5), true);
	ASSERT_EQ(dicc.Def(3), true);
	ASSERT_EQ(dicc.Def(10), true);
	ASSERT_EQ(dicc.Def(7), true);
	ASSERT_EQ(dicc.Def(12), true);
	ASSERT_EQ(dicc.Def(8), true);

	ASSERT_EQ(dicc.Raiz(), 8);
	ASSERT_EQ(dicc.HijoIzq(8), 5);
	ASSERT_EQ(dicc.Padre(5), 8);
	ASSERT_EQ(dicc.HijoIzq(5), 3);
	ASSERT_EQ(dicc.Padre(3), 5);
	ASSERT_EQ(dicc.HijoDer(5), 7);
	ASSERT_EQ(dicc.Padre(7), 5);
	ASSERT_EQ(dicc.HijoDer(8), 10);
	ASSERT_EQ(dicc.Padre(10), 8);
	ASSERT_EQ(dicc.HijoDer(10), 12);
	ASSERT_EQ(dicc.Padre(12), 10);

	ASSERT_EQ(dicc.ClaveMax(), 12);
	ASSERT_EQ(dicc.ClaveMin(), 3);

	ASSERT_EQ(dicc.Obtener(5), 10);
	ASSERT_EQ(dicc.Obtener(7), 1);
	ASSERT_EQ(dicc.Obtener(3), 6);
	ASSERT_EQ(dicc.Obtener(8), 16);
	ASSERT_EQ(dicc.Obtener(10), 20);
	ASSERT_EQ(dicc.Obtener(12), 24);	

	//BORRO NODO NO RAIZ CON DOS HIJOS
	dicc.Borrar(5);

	ASSERT_EQ(dicc.Vacio(), false);

	ASSERT_EQ(dicc.Def(5), false);
	ASSERT_EQ(dicc.Def(3), true);
	ASSERT_EQ(dicc.Def(10), true);
	ASSERT_EQ(dicc.Def(7), true);
	ASSERT_EQ(dicc.Def(12), true);
	ASSERT_EQ(dicc.Def(8), true);

	ASSERT_EQ(dicc.Raiz(), 8);
	ASSERT_EQ(dicc.HijoIzq(8), 7);
	ASSERT_EQ(dicc.Padre(7), 8);
	ASSERT_EQ(dicc.HijoIzq(7), 3);
	ASSERT_EQ(dicc.Padre(3), 7);
	ASSERT_EQ(dicc.HijoDer(8), 10);
	ASSERT_EQ(dicc.Padre(10), 8);
	ASSERT_EQ(dicc.HijoDer(10), 12);
	ASSERT_EQ(dicc.Padre(12), 10);

	ASSERT_EQ(dicc.ClaveMax(), 12);
	ASSERT_EQ(dicc.ClaveMin(), 3);

	ASSERT_EQ(dicc.Obtener(7), 1);
	ASSERT_EQ(dicc.Obtener(3), 6);
	ASSERT_EQ(dicc.Obtener(8), 16);
	ASSERT_EQ(dicc.Obtener(10), 20);
	ASSERT_EQ(dicc.Obtener(12), 24);

	//BORRO NODO NO RAIZ CON UN HIJO IZQ
	dicc.Borrar(7);

	ASSERT_EQ(dicc.Vacio(), false);

	ASSERT_EQ(dicc.Def(5), false);
	ASSERT_EQ(dicc.Def(3), true);
	ASSERT_EQ(dicc.Def(10), true);
	ASSERT_EQ(dicc.Def(7), false);
	ASSERT_EQ(dicc.Def(12), true);
	ASSERT_EQ(dicc.Def(8), true);

	ASSERT_EQ(dicc.Raiz(), 8);
	ASSERT_EQ(dicc.HijoIzq(8), 3);
	ASSERT_EQ(dicc.Padre(3), 8);
	ASSERT_EQ(dicc.HijoDer(8), 10);
	ASSERT_EQ(dicc.Padre(10), 8);
	ASSERT_EQ(dicc.HijoDer(10), 12);
	ASSERT_EQ(dicc.Padre(12), 10);

	ASSERT_EQ(dicc.ClaveMax(), 12);
	ASSERT_EQ(dicc.ClaveMin(), 3);

	ASSERT_EQ(dicc.Obtener(3), 6);
	ASSERT_EQ(dicc.Obtener(8), 16);
	ASSERT_EQ(dicc.Obtener(10), 20);
	ASSERT_EQ(dicc.Obtener(12), 24);

	//BORRO NODO NO RAIZ CON UN HIJO DER
	dicc.Borrar(10);

	ASSERT_EQ(dicc.Vacio(), false);

	ASSERT_EQ(dicc.Def(5), false);
	ASSERT_EQ(dicc.Def(3), true);
	ASSERT_EQ(dicc.Def(10), false);
	ASSERT_EQ(dicc.Def(7), false);
	ASSERT_EQ(dicc.Def(12), true);
	ASSERT_EQ(dicc.Def(8), true);

	ASSERT_EQ(dicc.Raiz(), 8);
	ASSERT_EQ(dicc.HijoIzq(8), 3);
	ASSERT_EQ(dicc.Padre(3), 8);
	ASSERT_EQ(dicc.HijoDer(8), 12);
	ASSERT_EQ(dicc.Padre(12), 8);

	ASSERT_EQ(dicc.ClaveMax(), 12);
	ASSERT_EQ(dicc.ClaveMin(), 3);

	ASSERT_EQ(dicc.Obtener(3), 6);
	ASSERT_EQ(dicc.Obtener(8), 16);
	ASSERT_EQ(dicc.Obtener(12), 24);

	//BORRO NODO NO RAIZ HOJA
	dicc.Borrar(3);

	ASSERT_EQ(dicc.Vacio(), false);

	ASSERT_EQ(dicc.Def(5), false);
	ASSERT_EQ(dicc.Def(3), false);
	ASSERT_EQ(dicc.Def(10), false);
	ASSERT_EQ(dicc.Def(7), false);
	ASSERT_EQ(dicc.Def(12), true);
	ASSERT_EQ(dicc.Def(8), true);

	ASSERT_EQ(dicc.Raiz(), 8);
	ASSERT_EQ(dicc.HijoDer(8), 12);
	ASSERT_EQ(dicc.Padre(12), 8);

	ASSERT_EQ(dicc.ClaveMax(), 12);
	ASSERT_EQ(dicc.ClaveMin(), 8);

	ASSERT_EQ(dicc.Obtener(8), 16);
	ASSERT_EQ(dicc.Obtener(12), 24);

	//BORRO NODO NO RAIZ HOJA
	dicc.Borrar(12);

	ASSERT_EQ(dicc.Vacio(), false);

	ASSERT_EQ(dicc.Def(5), false);
	ASSERT_EQ(dicc.Def(3), false);
	ASSERT_EQ(dicc.Def(10), false);
	ASSERT_EQ(dicc.Def(7), false);
	ASSERT_EQ(dicc.Def(12), false);
	ASSERT_EQ(dicc.Def(8), true);

	ASSERT_EQ(dicc.Raiz(), 8);

	ASSERT_EQ(dicc.ClaveMax(), 8);
	ASSERT_EQ(dicc.ClaveMin(), 8);

	ASSERT_EQ(dicc.Obtener(8), 16);

	//BORRO RAIZ Y EL ARBOL QUEDA VACIO
	dicc.Borrar(8);

	ASSERT_EQ(dicc.Vacio(), true);

	ASSERT_EQ(dicc.Def(5), false);
	ASSERT_EQ(dicc.Def(3), false);
	ASSERT_EQ(dicc.Def(10), false);
	ASSERT_EQ(dicc.Def(7), false);
	ASSERT_EQ(dicc.Def(12), false);
	ASSERT_EQ(dicc.Def(8), false);
}
/*
void check_crearIT() {
    DiccRapido<int, int> dicc;
    dicc.
    
}
*/



int main() {
    RUN_TEST(check_crear_dicc_vacio);
    RUN_TEST(check_definir);
    RUN_TEST(check_redefinir);
    RUN_TEST(check_borrar);
    return 0;
}










/*
int main(){
	DiccRapido<int, int> dicc;

	//1
	std::cout << "Vacio?: " << dicc.Vacio();
	std::cout << "\n";


	std::cout << "Def?(5): " << dicc.Def(5);
	std::cout << "\n";

	std::cout << "\n";
	std::cout << "Defino(5, 1)\n";
	dicc.Definir(5, 1);
	

	std::cout << "Raiz: " << dicc.Raiz();
	std::cout << "\n";
	

	std::cout << "Def?(5): " << dicc.Def(5);
	std::cout << "\n";
	

	std::cout << "Vacio?: " << dicc.Vacio();
	std::cout << "\n";


	std::cout << "Obtener(5): " << dicc.Obtener(5);
	std::cout << "\n";
	

	//3
	std::cout << "ClaveMax: " << dicc.ClaveMax();
	std::cout << "\n";

////////////////defino 3
		std::cout << "\n";
	std::cout << "Defino(3, 1)\n";
	dicc.Definir(3, 1);
	

	std::cout << "Raiz: " << dicc.Raiz();
	std::cout << "\n";
	
	std::cout << "Izq(5): " << dicc.HijoIzq(5);
	std::cout << "\n";

	std::cout << "Padre(3): " << dicc.Padre(3);
	std::cout << "\n";

	//3
	std::cout << "ClaveMax: " << dicc.ClaveMax();
	std::cout << "\n";

////////////defino 10

	std::cout << "\n";
	std::cout << "Defino(10, 1)\n";
	dicc.Definir(10, 1);

	std::cout << "Raiz: " << dicc.Raiz();
	std::cout << "\n";


	std::cout << "Izq(5): " << dicc.HijoIzq(5);
	std::cout << "\n";

	std::cout << "Padre(3): " << dicc.Padre(3);
	std::cout << "\n";

	std::cout << "Der(5): " << dicc.HijoDer(5);
	std::cout << "\n";

	std::cout << "Padre(10): " << dicc.Padre(10);
	std::cout << "\n";

	std::cout << "ClaveMax: " << dicc.ClaveMax();
	std::cout << "\n";

///////////////defino 7
	
	std::cout << "\n";
	std::cout << "Defino(7, 1)\n";
	dicc.Definir(7, 1);

	std::cout << "Raiz: " << dicc.Raiz();
	std::cout << "\n";

	std::cout << "Izq(5): " << dicc.HijoIzq(5);
	std::cout << "\n";

	std::cout << "Padre(3): " << dicc.Padre(3);
	std::cout << "\n";

	std::cout << "Der(5): " << dicc.HijoDer(5);
	std::cout << "\n";

	std::cout << "Padre(10): " << dicc.Padre(10);
	std::cout << "\n";

	std::cout << "Izq(10): " << dicc.HijoIzq(10);
	std::cout << "\n";

	std::cout << "Padre(7): " << dicc.Padre(7);
	std::cout << "\n";

	std::cout << "ClaveMax: " << dicc.ClaveMax();
	std::cout << "\n";

	/////defino 12
	std::cout << "\n";
	std::cout << "Defino(12, 1)\n";
	dicc.Definir(12, 1);

	std::cout << "Raiz: " << dicc.Raiz();
	std::cout << "\n";

	std::cout << "Izq(5): " << dicc.HijoIzq(5);
	std::cout << "\n";

	std::cout << "Padre(3): " << dicc.Padre(3);
	std::cout << "\n";

	std::cout << "Der(5): " << dicc.HijoDer(5);
	std::cout << "\n";

	std::cout << "Padre(10): " << dicc.Padre(10);
	std::cout << "\n";

	std::cout << "Izq(10): " << dicc.HijoIzq(10);
	std::cout << "\n";

	std::cout << "Padre(7): " << dicc.Padre(7);
	std::cout << "\n";

	std::cout << "Der(10): " << dicc.HijoDer(10);
	std::cout << "\n";

	std::cout << "Padre(12): " << dicc.Padre(12);
	std::cout << "\n";

	std::cout << "ClaveMax: " << dicc.ClaveMax();
	std::cout << "\n";

	/////////defino 8

	std::cout << "\n";
	std::cout << "Defino(8, 1)\n";
	dicc.Definir(8, 1);

	std::cout << "Raiz: " << dicc.Raiz();
	std::cout << "\n";

	std::cout << "Izq(7): " << dicc.HijoIzq(7);
	std::cout << "\n";

	std::cout << "Padre(5): " << dicc.Padre(5);
	std::cout << "\n";

	std::cout << "Izq(5): " << dicc.HijoIzq(5);
	std::cout << "\n";

	std::cout << "Padre(3): " << dicc.Padre(3);
	std::cout << "\n";

	std::cout << "Der(7): " << dicc.HijoDer(7);
	std::cout << "\n";

	std::cout << "Padre(10): " << dicc.Padre(10);
	std::cout << "\n";

	std::cout << "Der(10): " << dicc.HijoDer(10);
	std::cout << "\n";

	std::cout << "Padre(12): " << dicc.Padre(12);
	std::cout << "\n";

	std::cout << "Izq(10): " << dicc.HijoIzq(10);
	std::cout << "\n";

	std::cout << "Padre(8): " << dicc.Padre(8);
	std::cout << "\n";

	std::cout << "ClaveMax: " << dicc.ClaveMax();
	std::cout << "\n";

//TESTEO DE REDEFINIR

	std::cout << "\n";
	std::cout << "Redefino(7, 7)\n";
	dicc.Definir(7, 7);

	std::cout << "Redefino(5, 5)\n";
	dicc.Definir(5, 5);

	std::cout << "Redefino(10, 10)\n";
	dicc.Definir(10, 10);

	std::cout << "Redefino(8, 8)\n";
	dicc.Definir(8, 8);

	std::cout << "Redefino(12, 12)\n";
	dicc.Definir(12, 12);

	std::cout << "Redefino(3, 3)\n";
	dicc.Definir(3, 3);

	std::cout << "Obtener(7): " << dicc.Obtener(7);
	std::cout << "\n";

	std::cout << "Obtener(10): " << dicc.Obtener(10);
	std::cout << "\n";

	std::cout << "Obtener(5): " << dicc.Obtener(5);
	std::cout << "\n";

	std::cout << "Obtener(8): " << dicc.Obtener(8);
	std::cout << "\n";

	std::cout << "Obtener(12): " << dicc.Obtener(12);
	std::cout << "\n";

	std::cout << "Obtener(3): " << dicc.Obtener(3);
	std::cout << "\n";

	std::cout << "Raiz: " << dicc.Raiz();
	std::cout << "\n";

	std::cout << "Izq(7): " << dicc.HijoIzq(7);
	std::cout << "\n";

	std::cout << "Padre(5): " << dicc.Padre(5);
	std::cout << "\n";

	std::cout << "Izq(5): " << dicc.HijoIzq(5);
	std::cout << "\n";

	std::cout << "Padre(3): " << dicc.Padre(3);
	std::cout << "\n";

	std::cout << "Der(7): " << dicc.HijoDer(7);
	std::cout << "\n";

	std::cout << "Padre(10): " << dicc.Padre(10);
	std::cout << "\n";

	std::cout << "Der(10): " << dicc.HijoDer(10);
	std::cout << "\n";

	std::cout << "Padre(12): " << dicc.Padre(12);
	std::cout << "\n";

	std::cout << "Izq(10): " << dicc.HijoIzq(10);
	std::cout << "\n";

	std::cout << "Padre(8): " << dicc.Padre(8);
	std::cout << "\n";

	std::cout << "ClaveMax: " << dicc.ClaveMax();
	std::cout << "\n";



//TESTEO DE BORRADO
/*
	std::cout << "\n";
	std::cout << "Borro(7)\n";
	dicc.Borrar(7);

	std::cout << "Def?(7): " << dicc.Def(7);
	std::cout << "\n";

	std::cout << "Raiz: " << dicc.Raiz();
	std::cout << "\n";

	std::cout << "Izq(8): " << dicc.HijoIzq(8);
	std::cout << "\n";

	std::cout << "Padre(5): " << dicc.Padre(5);
	std::cout << "\n";

	std::cout << "Izq(5): " << dicc.HijoIzq(5);
	std::cout << "\n";

	std::cout << "Padre(3): " << dicc.Padre(3);
	std::cout << "\n";

	std::cout << "Der(8): " << dicc.HijoDer(8);
	std::cout << "\n";

	std::cout << "Padre(10): " << dicc.Padre(10);
	std::cout << "\n";

	std::cout << "Der(10): " << dicc.HijoDer(10);
	std::cout << "\n";

	std::cout << "Padre(12): " << dicc.Padre(12);
	std::cout << "\n";

	std::cout << "Izq(10): " << dicc.HijoIzq(10);
	std::cout << "\n";

	std::cout << "Padre(8): " << dicc.Padre(8);
	std::cout << "\n";

	std::cout << "ClaveMax: " << dicc.ClaveMax();
	std::cout << "\n";


//TESTEO DE CREAR IT
	std::cout << "\n";
	std::cout << "Creo Iterador \n";
	DiccRapido<int, int>::ITClave iterador = dicc.Claves();

	std::cout << "Pido Clave: " << iterador.ClaveActual();
	std::cout << "\n";

	std::cout << "HayMas?: " << iterador.HayMas();
	std::cout << "\n";

	std::cout << "Avanzo Iterador \n";
	iterador.Avanzar();

	std::cout << "Pido Clave: " << iterador.ClaveActual();
	std::cout << "\n";

	std::cout << "HayMas?: " << iterador.HayMas();
	std::cout << "\n";

	std::cout << "Avanzo Iterador \n";
	iterador.Avanzar();

	std::cout << "Pido Clave: " << iterador.ClaveActual();
	std::cout << "\n";

	std::cout << "HayMas?: " << iterador.HayMas();
	std::cout << "\n";

	std::cout << "Avanzo Iterador \n";
	iterador.Avanzar();

	std::cout << "Pido Clave: " << iterador.ClaveActual();
	std::cout << "\n";

	std::cout << "HayMas?: " << iterador.HayMas();
	std::cout << "\n";

	std::cout << "Avanzo Iterador \n";
	iterador.Avanzar();

	std::cout << "Pido Clave: " << iterador.ClaveActual();
	std::cout << "\n";

	std::cout << "HayMas?: " << iterador.HayMas();
	std::cout << "\n";

	std::cout << "Avanzo Iterador \n";
	iterador.Avanzar();

	std::cout << "Pido Clave: " << iterador.ClaveActual();
	std::cout << "\n";

	std::cout << "HayMas?: " << iterador.HayMas();
	std::cout << "\n";

//CHEQUEO SI TENGO EL MISMO ARBOL DESPUES DE HABER ITERADO TODO

	std::cout << "\n";
	std::cout << "Chequeo del Arbol despues de haber iterado todo \n";

	std::cout << "Raiz: " << dicc.Raiz();
	std::cout << "\n";

	std::cout << "Izq(7): " << dicc.HijoIzq(7);
	std::cout << "\n";

	std::cout << "Padre(5): " << dicc.Padre(5);
	std::cout << "\n";

	std::cout << "Izq(5): " << dicc.HijoIzq(5);
	std::cout << "\n";

	std::cout << "Padre(3): " << dicc.Padre(3);
	std::cout << "\n";

	std::cout << "Der(7): " << dicc.HijoDer(7);
	std::cout << "\n";

	std::cout << "Padre(10): " << dicc.Padre(10);
	std::cout << "\n";

	std::cout << "Der(10): " << dicc.HijoDer(10);
	std::cout << "\n";

	std::cout << "Padre(12): " << dicc.Padre(12);
	std::cout << "\n";

	std::cout << "Izq(10): " << dicc.HijoIzq(10);
	std::cout << "\n";

	std::cout << "Padre(8): " << dicc.Padre(8);
	std::cout << "\n";


	std::cout << "ClaveMax: " << dicc.ClaveMax();
	std::cout << "\n";



/*
	std::cout << "\n";
	std::cout << "Borro(10)\n";
	dicc.Borrar(10);

	std::cout << "Def?(10): " << dicc.Def(10);
	std::cout << "\n";

	std::cout << "Raiz: " << dicc.Raiz();
	std::cout << "\n";

	std::cout << "Izq(7): " << dicc.HijoIzq(7);
	std::cout << "\n";

	std::cout << "Padre(5): " << dicc.Padre(5);
	std::cout << "\n";

	std::cout << "Izq(5): " << dicc.HijoIzq(5);
	std::cout << "\n";

	std::cout << "Padre(3): " << dicc.Padre(3);
	std::cout << "\n";

	std::cout << "Der(7): " << dicc.HijoDer(7);
	std::cout << "\n";

	std::cout << "Padre(12): " << dicc.Padre(12);
	std::cout << "\n";

	std::cout << "Der(10): " << dicc.HijoDer(10);
	std::cout << "\n";

	std::cout << "Padre(12): " << dicc.Padre(12);
	std::cout << "\n";

	std::cout << "Izq(10): " << dicc.HijoIzq(10);
	std::cout << "\n";

	std::cout << "Padre(8): " << dicc.Padre(8);
	std::cout << "\n";

	std::cout << "ClaveMax: " << dicc.ClaveMax();
	std::cout << "\n";

	std::cout << "\n";
	std::cout << "Borro(5)\n";
	dicc.Borrar(5);

	std::cout << "Def?(5): " << dicc.Def(5);
	std::cout << "\n";

	std::cout << "Raiz: " << dicc.Raiz();
	std::cout << "\n";

	std::cout << "Izq(7): " << dicc.HijoIzq(7);
	std::cout << "\n";

	std::cout << "Padre(3): " << dicc.Padre(3);
	std::cout << "\n";

	std::cout << "Izq(5): " << dicc.HijoIzq(5);
	std::cout << "\n";

	std::cout << "Padre(3): " << dicc.Padre(3);
	std::cout << "\n";

	std::cout << "Der(7): " << dicc.HijoDer(7);
	std::cout << "\n";

	std::cout << "Padre(12): " << dicc.Padre(12);
	std::cout << "\n";

	std::cout << "Der(10): " << dicc.HijoDer(10);
	std::cout << "\n";

	std::cout << "Padre(12): " << dicc.Padre(12);
	std::cout << "\n";

	std::cout << "Izq(10): " << dicc.HijoIzq(10);
	std::cout << "\n";

	std::cout << "Padre(8): " << dicc.Padre(8);
	std::cout << "\n";

	std::cout << "ClaveMax: " << dicc.ClaveMax();
	std::cout << "\n";
*/

/*
	std::cout << "\n";
	std::cout << "Defino(1, 1)\n";
	dicc.Definir(1, 1);

	std::cout << "Raiz: " << dicc.Raiz();
	std::cout << "\n";

	std::cout << "Izq(9): " << dicc.HijoIzq(9);
	std::cout << "\n";

	std::cout << "Padre(5): " << dicc.Padre(5);
	std::cout << "\n";	

	std::cout << "Der(5): " << dicc.HijoDer(5);
	std::cout << "\n";

	std::cout << "Padre(7): " << dicc.Padre(7);
	std::cout << "\n";

	std::cout << "Izq(5): " << dicc.HijoIzq(5);
	std::cout << "\n";

	std::cout << "Padre(1): " << dicc.Padre(1);
	std::cout << "\n";

	std::cout << "Der(9): " << dicc.HijoDer(9);
	std::cout << "\n";

	std::cout << "Padre(10): " << dicc.Padre(10);
	std::cout << "\n";

	std::cout << "ClaveMax: " << dicc.ClaveMax();
	std::cout << "\n";

	////////////defino 8

	std::cout << "\n";
	std::cout << "Defino(8, 1)\n";
	dicc.Definir(8, 1);

	std::cout << "Raiz: " << dicc.Raiz();
	std::cout << "\n";

	std::cout << "Izq(7): " << dicc.HijoIzq(7);
	std::cout << "\n";

	std::cout << "Padre(5): " << dicc.Padre(5);
	std::cout << "\n";	

	std::cout << "Izq(5): " << dicc.HijoIzq(5);
	std::cout << "\n";

	std::cout << "Padre(1): " << dicc.Padre(1);
	std::cout << "\n";

	std::cout << "Der(7): " << dicc.HijoDer(7);
	std::cout << "\n";

	std::cout << "Padre(9): " << dicc.Padre(9);
	std::cout << "\n";

	std::cout << "Der(9): " << dicc.HijoDer(9);
	std::cout << "\n";

	std::cout << "Padre(10): " << dicc.Padre(10);
	std::cout << "\n";

	std::cout << "Izq(9): " << dicc.HijoIzq(9);
	std::cout << "\n";

	std::cout << "Padre(8): " << dicc.Padre(8);
	std::cout << "\n";

	std::cout << "ClaveMax: " << dicc.ClaveMax();
	std::cout << "\n";

*/

/*
	std::cout << "Der(4): " << dicc.HijoDer(4);
	std::cout << "\n";
	std::cout << "\n";

	std::cout << "Der(5): " << dicc.HijoDer(5);
	std::cout << "\n";
	std::cout << "\n";
*/
	//6
	//std::cout << dicc.Obtener(8);
	//std::cout << "\n";

	//dicc.RotarSimpleIzq(dicc.raiz);

	//0
	/*
	std::cout << "Vacio?\n";
	std::cout << dicc.Vacio();
	std::cout << "\n";
	std::cout << "\n";

	//dicc.Borrar(3);

	//0
	std::cout << "Vacio?\n";
	std::cout << dicc.Vacio();
	std::cout << "\n";
	std::cout << "\n";
	

//RESULT [1		0	1	0	5	6	0	0]


 return 0;
}


*/