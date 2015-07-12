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


using namespace aed2;



/*Este Struct solamente se utiliza en la funcion "Avanzar Segundo" y es requerido para poder guardar la informacion
  	de los paquetes a mover.*/

struct InfoPaquete {
	_Paquete paque;
	Compu compuAnt;
	Lista<Compu> camReco;

	InfoPaquete(_Paquete p, Compu c, Lista<Compu> cr) : paque(p), compuAnt(c), camReco(cr) { };
};

DCNet::DCNet(const Red &lared) {
	red = new Red(lared);
	//std::cout << "creo un puntero a una copia de la red \n";

	Conj<Compu>::Iterador it = red->Computadoras();
	//std::cout << "creo un iterador de las computadoras \n";

    masEnviante = new e_masEnvio(it.Siguiente(), 0);
    //std::cout << "la mas enviante va a ser la primera del iterador con 0 enviados \n";

	compYPaq = new DiccString<e_InfoCompu>();
	//std::cout << "creo un diccionario vacio \n";

	while (it.HaySiguiente()) {
		DCNet::e_InfoCompu* nuevainfo = new e_InfoCompu();

		compYPaq->definir(((it.Siguiente()).hostname), *nuevainfo);

	//	std::cout << "defino una computadora en el diccionario, con informacion vacia  \n";

		it.Avanzar();
	//	std::cout << "avanzo a la siguiente computadora \n";
	}
}

DCNet::~DCNet() {
	delete red;
	delete compYPaq;
	delete masEnviante;
}

Red DCNet::DameRed() {
	return *red;
}

Lista<Compu> DCNet::CaminoRecorrido(const _Paquete p) {
    Conj<Compu>::Iterador it = red->Computadoras();
//std::cout << "creo un iterador de las computadoras \n";
	bool esta = false;
	Lista<Compu> res;
	while (it.HaySiguiente() && !esta) {
        if (((compYPaq->obtener((it.Siguiente()).hostname))->paqYCam)->Def(p)) {
			esta = true;
			res = ((compYPaq->obtener((it.Siguiente()).hostname))->paqYCam)->Obtener(p);
		}

		it.Avanzar();
	}
	return res;
}

Nat DCNet::CantidadEnviados(Compu c) {
    return compYPaq->obtener(c.hostname)->enviados;
}

DiccRapido<_Paquete, Lista<Compu> >::ITClave DCNet::EnEspera(Compu c) {
    DiccRapido<_Paquete, Lista<Compu> >* dicc = (compYPaq->obtener(c.hostname))->paqYCam;
    DiccRapido<_Paquete, Lista<Compu> >::ITClave It = dicc->Claves();
    return It;
}

void DCNet::CrearPaquete(_Paquete p) {
	DiccRapido<Nat, Conj<_Paquete> >* diccprio = (compYPaq->obtener((p.origen).hostname))->masPriori;
	DiccRapido<_Paquete, Lista<Compu> >* dicccam = (compYPaq->obtener((p.origen).hostname))->paqYCam;

	if (!diccprio->Def(p.prioridad)) {
		Conj<_Paquete> cj;
		cj.AgregarRapido(p);
		diccprio->Definir(p.prioridad, cj);
	}
    else
    {
		Conj<_Paquete> cj(diccprio->Obtener(p.prioridad));
		cj.AgregarRapido(p);
		diccprio->Definir(p.prioridad, cj);
	}

	Lista<Compu> l;
	l.AgregarAtras(p.origen);
	dicccam->Definir(p, l);
}

void DCNet::AvanzarSegundo() {
	Conj<Compu>::Iterador it = red->Computadoras();

	Lista<InfoPaquete> l;

	while (it.HaySiguiente()) {
		DiccRapido<Nat, Conj<_Paquete> >* diccprio = (compYPaq->obtener((it.Siguiente()).hostname))->masPriori;
		DiccRapido<_Paquete, Lista<Compu> >* dicccam = (compYPaq->obtener((it.Siguiente()).hostname))->paqYCam;

		if (!diccprio->Vacio()) {

            _Paquete paq = (diccprio->Obtener(diccprio->ClaveMax())).DameUno();
            //std::cout << "Agarre el paq de mayor prioridad \n";


            l.AgregarAdelante(InfoPaquete(paq, it.Siguiente(), dicccam->Obtener(paq)));

            //std::cout << "lo agrego a la lista de paquetes para mover \n";
             dicccam->Borrar(paq);
           // std::cout << "borro el paquete de la lista de paquetes y su camino recorrido \n";
            (compYPaq->obtener((it.Siguiente()).hostname))->enviados++;
            // std::cout << "Actualizo los enviados \n";

            diccprio->Obtener(diccprio->ClaveMax()).Eliminar(paq);

          //  std::cout << "Elimino el paquete de la lista de paquetes con esa misma prioridad \n";

            if ((diccprio->Obtener(diccprio->ClaveMax())).EsVacio()) {
            	
                diccprio->Borrar(diccprio->ClaveMax());
        //        std::cout << "si no quedaban mas paquetes borro esa definicion de prioridad \n";
            }
           

            if ((compYPaq->obtener((it.Siguiente()).hostname))->enviados > masEnviante->enviados) {

            	delete masEnviante;
                masEnviante = new e_masEnvio(it.Siguiente(), compYPaq->obtener((it.Siguiente()).hostname)->enviados);
      //          std::cout << "si la compu que acaba de enviar,es la que mas envio, actualizo\n";
            }
           
        }
		it.Avanzar();
	//	std::cout << "paso a la siguiente compu\n";
	}
	//std::cout << "Ya recogi todos las paquetes que tienen que ser enviados\n";

	Lista<InfoPaquete>::Iterador itaux = l.CrearIt();

	//std::cout << "creo un iterador de los paquetes que tengo que transferir\n";

	while (itaux.HaySiguiente()) {

		
		Lista<Compu>::const_Iterador itCamino = ((red->CaminosMinimos(itaux.Siguiente().compuAnt, ((itaux.Siguiente()).paque).destino)).Siguiente()).CrearIt(); 
        //std::cout << "Agarro el recorrido minimo que tiene que hacer la computadora en la que estaba hasta su destino\n";
        itCamino.Avanzar();
        //std::cout << "agarro el segundo elemento de la lista, ya que el camino minimo de 1 a 3 es [1,2,3]\n";
        
        Compu proxpc = itCamino.Siguiente();
      //  std::cout << "busco a que compu tendria que ir el paquete\n";
		DiccRapido<Nat, Conj<_Paquete> >* diccprio = (compYPaq->obtener(proxpc.hostname))->masPriori;
		DiccRapido<_Paquete, Lista<Compu> >* dicccam = (compYPaq->obtener(proxpc.hostname))->paqYCam;

		if (proxpc != ((itaux.Siguiente()).paque).destino) {
			//std::cout << "si la compu a la que tendria que ir el paquete es distinto al destino sigo\n";
			if (diccprio->Def(((itaux.Siguiente()).paque).prioridad)) {
				//std::cout << "Si ya existe una conj de paquetes de esa prioridad\n";
	
                Conj<_Paquete> mismaPrio = diccprio->Obtener(itaux.Siguiente().paque.prioridad);
              // std::cout << "obtengo el conjunto de paquetes con esa prioridad\n";
				diccprio->Definir(((itaux.Siguiente()).paque).prioridad, mismaPrio);
			//	std::cout << "agrego el paquete a la lista de paquetes con esa misma prioridad\n";
			} else {
				Conj<_Paquete> conjvacio;
			//	std::cout << "Si no estaba definida esa prioridad creo una conj vacio de paquetes\n";
                conjvacio.Agregar(itaux.Siguiente().paque);
            //    std::cout << "Agrego el paquete a la lista vacia\n";
                diccprio->Definir(itaux.Siguiente().paque.prioridad, conjvacio);
          //      std::cout << "Defino esa prioridad con el conj solo con ese paquete\n";
			}

			((itaux.Siguiente()).camReco).AgregarAtras(proxpc);
		//	std::cout << "Agrego la proxima pc a la que se movio el paquete a su camino recorrido\n";
			dicccam->Definir((itaux.Siguiente()).paque, itaux.Siguiente().camReco);
		//	std::cout << "Defino el paquete con su camino recorrido\n";

		}
		//std::cout << "Si llego a su destino no hago nada\n";
 
		itaux.Avanzar();
		//std::cout << "Avanzo al siguiente paquete a enviar\n";

	}
}

bool DCNet::PaqueteEnTransito(_Paquete p) {
	Conj<Compu>::Iterador it = red->Computadoras();
	//std::cout << "voy a recorrer las computadoras\n";
	bool esta = false;
	//std::cout << "creo un flag para saber si ya la encontre\n";
	while (it.HaySiguiente() && !esta) {
		//std::cout << "sigo recorriendo porque todavia no la encontre\n";
        esta = compYPaq->obtener(it.Siguiente().hostname)->paqYCam->Def(p);
      //  std::cout << "devuelvo si el paquete esta definido en esta computadora\n";
		it.Avanzar();
	//	std::cout << "Avanzo ala siguiente compu\n";
	}
	return esta;
	//std::cout << "devuelvo si estaba o no\n";
}

Compu& DCNet::LaQueMasEnvio() {

	std::cout << "entro a la funcion la que mas envio \n";
	return 	masEnviante->comp;
	std::cout << "devuelvo la Compu mas enviante \n";
}


_Paquete DCNet::DamePaquete(Nat n){
	Conj<Compu>::Iterador it = red->Computadoras();
	std::cout << "Creo un iterador a las computadoras \n";
	_Paquete p;
	Compu orip;
	Compu desp;
	std::cout << "inicializo un paquete \n";
	while (it.HaySiguiente()) {
    	DiccRapido<_Paquete, Lista<Compu> >::ITClave itcl = ((compYPaq->obtener((it.Siguiente()).hostname))->paqYCam)->Claves();

    	std::cout << "creo un iterador a las claves del diccionario de paquetes y caminos \n";
    	while(itcl.HayMas()){

    		std::cout << "pregunto si todavia hay paquetes por revisar \n";

    		if((itcl.ClaveActual()).id == n){
    			std::cout << "si el paquete era el que buscaba le asigno los datos al paquete que habia creado \n";
    			
    			//Nat i = (itcl.ClaveActual()).id;
    			
				//Nat prio = (itcl.ClaveActual()).prioridad;
				
				orip.hostname = ((itcl.ClaveActual()).origen).hostname ; 
				orip.interfaces = ((itcl.ClaveActual()).origen).interfaces;

				desp.hostname = ((itcl.ClaveActual()).destino).hostname ; 
				desp.interfaces = ((itcl.ClaveActual()).destino).interfaces;

				p( ((itcl.ClaveActual()).id) ,((itcl.ClaveActual()).prioridad) ,orip, desp );
    			return p;
				
				
				}

    		itcl.Avanzar();
    		std::cout << "No era el paquete que buscaba asi que paso al siguiente \n";
    	}
		
		it.Avanzar();
		std::cout << "paso a buscar en la siguiente compu \n";
	}
}


