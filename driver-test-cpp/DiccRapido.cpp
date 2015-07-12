#include "aed2/TiposBasicos.h"
#include <stdlib.h>
#include <iostream>
#include "DiccRapido.h"


using namespace aed2;

int main(){
	DiccRapido<int, int> dicc;

	//1
	std::cout << "Vacio?: " << dicc.Vacio();
	std::cout << "\n";

	//0
	std::cout << "Def?(5): " << dicc.Def(5);
	std::cout << "\n";
////////////////////////defino 5
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

*/
//TESTEO DE CREAR IT
	std::cout << "Creo Iterador \n";
	DiccRapido<int, int>::ITClave iterador = dicc.Claves();

	std::cout << "Pido Clave: " << iterador.ClaveActual();
	std::cout << "\n";

	std::cout << "Avanzo Iterador \n";
	iterador.Avanzar();

	std::cout << "Pido Clave: " << iterador.ClaveActual();
	std::cout << "\n";

	std::cout << "Avanzo Iterador \n";
	iterador.Avanzar();

	std::cout << "Pido Clave: " << iterador.ClaveActual();
	std::cout << "\n";

	std::cout << "Avanzo Iterador \n";
	iterador.Avanzar();

	std::cout << "Pido Clave: " << iterador.ClaveActual();
	std::cout << "\n";

	std::cout << "Avanzo Iterador \n";
	iterador.Avanzar();

	std::cout << "Pido Clave: " << iterador.ClaveActual();
	std::cout << "\n";

	std::cout << "Avanzo Iterador \n";
	iterador.Avanzar();

	std::cout << "Pido Clave: " << iterador.ClaveActual();
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
	*/

//RESULT [1		0	1	0	5	6	0	0]

 return 0;
}