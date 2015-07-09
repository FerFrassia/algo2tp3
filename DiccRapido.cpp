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
	std::cout << "\n";

	//0
	std::cout << "Def?(3): " << dicc.Def(3);
	std::cout << "\n";
	std::cout << "\n";

	std::cout << "Defino(3, 5)\n";
	dicc.Definir(3, 5);
	std::cout << "\n";

	std::cout << "Def?(3): " << dicc.Def(3);
	std::cout << "\n";
	std::cout << "\n";

	std::cout << "Vacio?: " << dicc.Vacio();
	std::cout << "\n";
	std::cout << "\n";

	std::cout << "Obtener(3): " << dicc.Obtener(3);
	std::cout << "\n";
	std::cout << "\n";

	//3
	int clave = dicc.ClaveMax();
	std::cout << "ClaveMax: " << clave;
	std::cout << "\n";
	std::cout << "\n";

	std::cout << "Defino(4, 6)\n";
	dicc.Definir(4, 6);
	std::cout << "\n";

	std::cout << "Defino(5, 6)\n";
	dicc.Definir(5, 6);
	std::cout << "\n";

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