#include "mini_test.h"
#include "TiposSimples.h"
#include "aed2/TiposBasicos.h"
#include "aed2/Conj.h"
#include "aed2/Arreglo.h"
#include "aed2/Vector.h"
#include "aed2/Lista.h"
#include "dicc_trie.h"
#include "DiccRapido.h"
#include "red.h"
#include "dcnet.h"

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

    
void IniciarDCNET() {

	Red red;



    Compu c1;
    Compu c2;
    Compu c3;
    Compu c4;
    Compu c5;
    Compu c6;

   
    c1.hostname = "c1";

   
    c2.hostname = "c2";


    c3.hostname = "c3";

  
    c4.hostname = "c4";

    c5.hostname = "c5";

    c6.hostname = "c6";

   
    red.AgregarComputadora(c1);

    
    red.AgregarComputadora(c2);

    red.AgregarComputadora(c5);

   
    red.AgregarComputadora(c3);

    red.AgregarComputadora(c4);

    red.AgregarComputadora(c6);

    Interfaz i1 = 1;
    Interfaz i2 = 2;
    Interfaz i3 = 3;

    Interfaz i5 = 5;


    red.Conectar(c1, i1, c2, i2);

 
    red.Conectar(c1, i3, c3, i1);

    red.Conectar(c3, i2, c5, i1);

    red.Conectar(c2, i1, c4, i1);

    red.Conectar(c4, i2, c5, i2);

    red.Conectar(c6, i1, c1, i2);

    red.Conectar(c6, i2, c2, i3);

    red.Conectar(c6, i3, c5, i3);




	  /*
					         
				  C1/e0-----------C2/e0
				   /   \       /  | 
				  /	    \     /   |
				 /	     \   /    |
				/   	  \ /     |                    /eN con N la cantidad de enviados
	           C3/e0  	 C6/e0    |
				 \		/    	  |
 				  \	   /		  |
                   \  /  		  |
                    \/            |
				C5/e0------------C4/e0 
  */

	DCNet dcnet(red);

	std::cout << "cant enviados por c1 " << dcnet.CantidadEnviados(c1) << "\n";
	std::cout << "cant enviados por c2 " << dcnet.CantidadEnviados(c2) << "\n";
	std::cout << "cant enviados por c3 " << dcnet.CantidadEnviados(c3) << "\n";
	std::cout << "cant enviados por c4 " << dcnet.CantidadEnviados(c4) << "\n";
	std::cout << "cant enviados por c5 " << dcnet.CantidadEnviados(c5) << "\n";
	std::cout << "cant enviados por c6 " << dcnet.CantidadEnviados(c6) << "\n";
	std::cout << "la que mas envio " << (dcnet.LaQueMasEnvio()).hostname << "\n";
	assert((dcnet.LaQueMasEnvio()).hostname == c6.hostname);


	assert(dcnet.CantidadEnviados(c1) == 0);

	_Paquete paq1;
	paq1.id = 1;
	paq1.prioridad = 2;
	paq1.origen = c1 ;
	paq1.destino = c4 ;

	std::cout << "esta el paquete 1 en transito : " << (dcnet.PaqueteEnTransito(paq1)) << "\n";
	assert(dcnet.PaqueteEnTransito(paq1) == false);
	//Creo un paquete

	dcnet.CrearPaquete(paq1);
	std::cout << "Creo paquete 1 \n";

	  /*
					         
				  C1/e1-----------C2/e1
				   /   \       /  | 
				  /	    \     /   |
				 /	     \   /    |
				/   	  \ /     |
	           C3/e0  	 C6/e0    |            /eN con N la cantidad de enviados
				 \		/    	  |
 				  \	   /		  |
                   \  /  		  |
                    \/            |
				C5/e0------------C4/e0 paq1 destino, se va
  */	

	std::cout << "la longitud camino recorrido por el paquete1 es : " << (dcnet.CaminoRecorrido(paq1)).Longitud() << "\n";

	//Verifico si el paquete esta en transito
	std::cout << "esta el paquete 1 en transito : " << (dcnet.PaqueteEnTransito(paq1)) << "\n";
	assert(dcnet.PaqueteEnTransito(paq1) == true);
	std::cout << "origen de paq1 es  : " << ((dcnet.DamePaquete(1)).origen).hostname << "\n";
	std::cout << "des de paq1 es " << ((dcnet.DamePaquete(1)).destino).hostname << "\n";
	std::cout << "prioridad de paq1 es : " << (dcnet.DamePaquete(1)).prioridad << "\n";
	



	dcnet.AvanzarSegundo();
	std::cout << "Avanzo segundo \n";


	  /*
					         
				  C1/e1-----------C2/e1
				   /   \       /  | 
				  /	    \     /   |
				 /	     \   /    |
				/   	  \ /     |
	           C3/e0  	 C6/e0    |     /eN con N la cantidad de enviados
				 \		/    	  |
 				  \	   /		  |
                   \  /  		  |
                    \/            |
				C5/e0------------C4/e0 paq1 destino, se va
  */

	//habia un solo paquete el cual estaba en c1 y tiene que ir hasta c4 ,
	//tiene que pasar por dos computadoras para llegar y c1 tiene que se la que mas envio
	std::cout << "esta el paquete 1 en transito : " << (dcnet.PaqueteEnTransito(paq1)) << "\n";
	assert(dcnet.PaqueteEnTransito(paq1) == true);
	assert((dcnet.LaQueMasEnvio()).hostname == c1.hostname);

	dcnet.AvanzarSegundo();
	std::cout << "Avanzo segundo \n";

	  /*
					         
				  C1/e1-----------C2/e1
				   /   \       /  | 
				  /	    \     /   |
				 /	     \   /    |
				/   	  \ /     |
	           C3/e0  	 C6/e0    |        /eN con N la cantidad de enviados
				 \		/    	  |
 				  \	   /		  |
                   \  /  		  |
                    \/            |
				C5/e0------------C4/e0 paq1 destino, se va
  */

// Aca ya tiene que haber llegado a destino
	std::cout << "esta el paquete 1 en transito : " << (dcnet.PaqueteEnTransito(paq1)) << "\n";
	assert(dcnet.PaqueteEnTransito(paq1) == false);

	assert((dcnet.LaQueMasEnvio()).hostname == c1.hostname);

	//std::cout << "la longitud camino recorrido por el paquete1 es : " << (dcnet.CaminoRecorrido(paq1)).Longitud() << "\n";
	std::cout << "La que mas envio es  : " << (dcnet.LaQueMasEnvio()).hostname << "\n";
	assert((dcnet.LaQueMasEnvio()).hostname == c1.hostname);

	
	_Paquete paq3;
	paq3.id = 3;
	paq3.prioridad = 1;
	paq3.origen = c3 ;
	paq3.destino = c4 ;

	

	dcnet.CrearPaquete(paq3);
std::cout << "Creo paquete 3 \n";

	  /*
					         
				  C1/e1-----------C2/e1
				   /   \       /  | 
				  /	    \     /   |
				 /	     \   /    |
				/   	  \ /     |
	       paq3 C3/e0  	 C6/e0    |        /eN con N la cantidad de enviados
				 \		/    	  |
 				  \	   /		  |
                   \  /  		  |
                    \/            |
				C5/e0------------C4/e0 
  */
	_Paquete paq4;
	paq4.id = 4;
	paq4.prioridad = 1;
	paq4.origen = c1 ;
	paq4.destino = c2 ;

	dcnet.CrearPaquete(paq4);

	std::cout << "Creo paquete 4 \n";

	  /*
					         
			  C1/e2-----------C2/e1 paq4 llega a destino
				   /   \       /  | 
				  /	    \     /   |
				 /	     \   /    |
				/   	  \ /     |
	      paq3 C3/e1  	 C6/e0    |        /eN con N la cantidad de enviados
				 \		/    	  |
 				  \	   /		  |
                   \  /  		  |
                    \/            |
				C5/e0------------C4/e0
  */

	std::cout << "esta el paquete 4 en transito : " << (dcnet.PaqueteEnTransito(paq4)) << "\n";
	assert(dcnet.PaqueteEnTransito(paq4) == true);


	dcnet.AvanzarSegundo();
	std::cout << "Avanzo segundo \n";


	  /*
					         
			       C1/e2-----------C2/e1 paq4 se va llego a destino
				   /   \       /  | 
				  /	    \     /   |
				 /	     \   /    |
				/   	  \ /     |
	         C3/e1  	 C6/e0    |        /eN con N la cantidad de enviados
				 \		/    	  |
 				  \	   /		  |
                   \  /  		  |
                    \/            |
		    paq3   C5/e0---------C4/e0 
  */


	std::cout << "esta el paquete 4 en transito : " << (dcnet.PaqueteEnTransito(paq4)) << "\n";
	assert(dcnet.PaqueteEnTransito(paq4) == false);

	assert((dcnet.LaQueMasEnvio()).hostname == c1.hostname);
	
	_Paquete paq2;
	paq2.id = 2;
	paq2.prioridad = 2;
	paq2.origen = c2 ;
	paq2.destino = c3 ;


	dcnet.CrearPaquete(paq2);
	std::cout << "Creo paquete 2 \n";
		  /*
					         
			       C1/e2-----------C2/e1 paq2
				   /   \       /  | 
				  /	    \     /   |
				 /	     \   /    |
				/   	  \ /     |
	         C3/e1  	 C6/e0    |        /eN con N la cantidad de enviados
				 \		/    	  |
 				  \	   /		  |
                   \  /  		  |
                    \/            |
		    paq3   C5/e0---------C4/e0 
  */

		    std::cout << "La que mas envio es  : " << (dcnet.LaQueMasEnvio()).hostname << "\n";
	assert((dcnet.LaQueMasEnvio()).hostname == c1.hostname);



	std::cout << "esta el paquete 3 en transito : " << (dcnet.PaqueteEnTransito(paq3)) << "\n";
	assert(dcnet.PaqueteEnTransito(paq3) == true);
	std::cout << "esta el paquete 2 en transito : " << (dcnet.PaqueteEnTransito(paq2)) << "\n";
	assert(dcnet.PaqueteEnTransito(paq2) == true);

	dcnet.AvanzarSegundo();
	std::cout << "Avanzo segundo \n";



		  /*
					         
			  paq2 C1/e2-----------C2/e2 
				   /   \       /  | 
				  /	    \     /   |
				 /	     \   /    |
				/   	  \ /     |
	         C3/e1  	 C6/e0    |        /eN con N la cantidad de enviados
				 \		/    	  |
 				  \	   /		  |
                   \  /  		  |
                    \/            |
		         C5/e1---------C4/e0 paq3 llego a su destino


  */
std::cout << "esta el paquete 3 en transito : " << (dcnet.PaqueteEnTransito(paq3)) << "\n";

		    std::cout << "La que mas envio es  : " << (dcnet.LaQueMasEnvio()).hostname << "\n";
	assert((dcnet.LaQueMasEnvio()).hostname == c1.hostname);

	_Paquete paq5;
	paq5.id = 5;
	paq5.prioridad = 4;
	paq5.origen = c1 ;
	paq5.destino = c3 ;

	dcnet.CrearPaquete(paq5);

	std::cout << "Creo paquete 5 \n";

			  /*
					         
  paq5/p4,paq2/2 C1/e2-----------C2/e2 
				   /   \       /  | 
				  /	    \     /   |
				 /	     \   /    |
				/   	  \ /     |
	         C3/e1  	 C6/e0    |        /eN con N la cantidad de enviados
				 \		/    	  |
 				  \	   /		  |
                   \  /  		  |
                    \/            |
		         C5/e1---------C4/e0 
  */

	std::cout << "origen de paq2 es  : " << ((dcnet.DamePaquete(2)).origen).hostname << "\n";
	std::cout << "destino de paq2 es " << ((dcnet.DamePaquete(2)).destino).hostname << "\n";
	std::cout << "prioridad de paq2 es : " << (dcnet.DamePaquete(2)).prioridad << "\n";
	std::cout << "origen de paq5 es  : " << ((dcnet.DamePaquete(5)).origen).hostname << "\n";
	std::cout << "destino de paq5 es " << ((dcnet.DamePaquete(5)).destino).hostname << "\n";
	std::cout << "prioridad de paq5 es : " << (dcnet.DamePaquete(5)).prioridad << "\n";

	std::cout << "La primer compu que recorrio fue (c2) : " << (((dcnet.CaminoRecorrido(paq2))).Primero()).hostname << "\n";
	std::cout << "La ultima compu que recorrio fue (c1) : " << (((dcnet.CaminoRecorrido(paq2))).Ultimo()).hostname << "\n";

dcnet.AvanzarSegundo();
std::cout << "Avanzo segundo \n";

		  /*
					         
			  paq5 C1/e3-----------C2/e2 
				   /   \       /  | 
				  /	    \     /   |
				 /	     \   /    |
				/   	  \ /     |
paq2 llega    C3/e1  	 C6/e0    |        /eN con N la cantidad de enviados
a destino		 \		/    	  |
 				  \	   /		  |
                   \  /  		  |
                    \/            |
		         C5/e1---------C4/e0
  */

	std::cout << "esta el paquete 5 en transito : " << (dcnet.PaqueteEnTransito(paq5)) << "\n";
	assert(dcnet.PaqueteEnTransito(paq5) == true);
	std::cout << "esta el paquete 2 en transito : " << (dcnet.PaqueteEnTransito(paq2)) << "\n";
	assert(dcnet.PaqueteEnTransito(paq2) == false);

}



void test_copia(){
	Red red;
	Hostname c1 = "skynet";
	Hostname c2 = "terminator";
	Hostname c3 = "connor";
	Hostname c4 = "sky";
	Hostname c5 = "sarah";

	Interfaz i1 = 1;
	Interfaz i2 = 2;
	Interfaz i3 = 3;
	Interfaz i4 = 4;
	Interfaz i5 = 5;
	Interfaz i6 = 6;
	Interfaz i7 = 7;
	Interfaz i8 = 8;
	Interfaz i9 = 9;
	Interfaz i10 = 10;
	Interfaz i11 = 11;
	Interfaz i12 = 12;
	
	Conj<Interfaz> conjIc1;
	Conj<Interfaz> conjIc2;
	Conj<Interfaz> conjIc3;
	Conj<Interfaz> conjIc4;
	Conj<Interfaz> conjIc5;

	conjIc1.Agregar(i1);
	conjIc1.Agregar(i2);
	
	conjIc2.Agregar(i3);
	conjIc2.Agregar(i4);
	
	conjIc3.Agregar(i5);
	conjIc3.Agregar(i6);
	conjIc3.Agregar(i7);

	conjIc4.Agregar(i8);
	conjIc4.Agregar(i9);
	conjIc4.Agregar(i10);

	conjIc5.Agregar(i11);
	conjIc5.Agregar(i12);

	Compu pc1;
	pc1.hostname = c1;
	pc1.interfaces = conjIc1;

	Compu pc2;
	pc2.hostname = c2;
	pc2.interfaces = conjIc2;
	Compu pc3;
	pc3.hostname = c3;
	pc3.interfaces = conjIc3;
	Compu pc4;
	pc4.hostname = c4;
	pc4.interfaces = conjIc4;
	Compu pc5;
	pc5.hostname = c5;
	pc5.interfaces = conjIc5;



	
	red.AgregarComputadora(pc1);
	red.AgregarComputadora(pc2);
	red.AgregarComputadora(pc3);
	red.AgregarComputadora(pc4);
	red.AgregarComputadora(pc5);
	
	red.Conectar(pc1, i1,pc2, i3);	
	red.Conectar(pc1, i2,pc3, i5);

	red.Conectar(pc2, i4,pc4, i8);

	red.Conectar(pc3, i6,pc4, i9);
	red.Conectar(pc3, i7,pc5, i11);

	red.Conectar(pc4, i10,pc5, i12);

	DCNet dcnet(red);

	_Paquete paq0;
	paq0.id = 0;
	paq0.prioridad = 1;
	paq0.origen = pc1 ;
	paq0.destino = pc5 ;



	dcnet.CrearPaquete(paq0);
	
	Lista<Compu> lc = dcnet.CaminoRecorrido(paq0);
	Lista<Compu>::Iterador iterador = lc.CrearIt();

	std::cout << "este es el iterador de lista"<< (iterador.Siguiente()).hostname << "\n";

	ASSERT_EQ(((dcnet.CaminoRecorrido(paq0))).Longitud(),1);
	
	//while(n < ((dcnet.CaminoRecorrido(paq0))).Longitud()){
	//	std::cout << "Esta la pc"<< (iterador.Siguiente()).hostname << "\n";
	//	iterador.Avanzar();
	//	n++;
	//}
	
	
	dcnet.AvanzarSegundo();

	ASSERT_EQ(lc.Longitud(),2);



	ASSERT(lc.Primero().hostname == c1);
	ASSERT(lc.Ultimo().hostname == c2);



}













int main(int argc, char **argv)
{
    RUN_TEST(IniciarDCNET);
    RUN_TEST(test_copia);
	
	

	return 0;
}
