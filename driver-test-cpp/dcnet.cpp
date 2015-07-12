#include "dcnet.h"
#include "red.h"
#include "dicc_trie.h"
#include "DiccRapido.h"
#include "aed2/TiposBasicos.h"
#include "TiposSimples.h"
#include "aed2/Conj.h"
#include "aed2/Arreglo.h"
#include "aed2/Vector.h"
#include "aed2/Lista.h"

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

	Conj<Compu>::Iterador it = red->Computadoras();

    masEnviante = new e_masEnvio(it.Siguiente(), 0);

	compYPaq = new DiccString<e_InfoCompu>();

	while (it.HaySiguiente()) {
		DCNet::e_InfoCompu* nuevainfo = new e_InfoCompu();

		compYPaq->definir(((it.Siguiente()).hostname), *nuevainfo);

		it.Avanzar();
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
    vector<string> vr = (compYPaq->claves());
    int i=0;
	bool esta = false;
	Lista<Compu> res;
	while (vr.size() < i && !esta) {
        if ((compYPaq->obtener(vr[i])->paqYCam)->Def(p)) {
			esta = true;
			res = ((compYPaq->obtener(vr[i]))->paqYCam)->Obtener(p);
		}

		i++;
	}
	return res;
}

Nat DCNet::CantidadEnviados(Compu c) {
    return compYPaq->obtener(c.hostname)->enviados;
}

DiccRapido<_Paquete, Lista<Compu> >::ITClave DCNet::EnEspera(Compu c) {
    DiccRapido<_Paquete, Lista<Compu> >* dicc = compYPaq->obtener(c.hostname)->paqYCam;
    DiccRapido<_Paquete, Lista<Compu> >::ITClave It = dicc->Claves();
    return It;
}

void DCNet::CrearPaquete(_Paquete p) {
	DiccRapido<Nat, Conj<_Paquete> >* diccprio = compYPaq->obtener((p.origen).hostname)->masPriori;
	DiccRapido<_Paquete, Lista<Compu> >* dicccam = compYPaq->obtener((p.origen).hostname)->paqYCam;

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
		DiccRapido<Nat, Conj<_Paquete> >* diccprio = compYPaq->obtener((it.Siguiente()).hostname)->masPriori;
		DiccRapido<_Paquete, Lista<Compu> >* dicccam = compYPaq->obtener((it.Siguiente()).hostname)->paqYCam;

		if (!diccprio->Vacio()) {

            _Paquete paq = (diccprio->Obtener(diccprio->ClaveMax())).DameUno();


            l.AgregarAdelante(InfoPaquete(paq, it.Siguiente(), dicccam->Obtener(paq)));

            diccprio->Obtener(diccprio->ClaveMax()).Eliminar(paq);
            if ((diccprio->Obtener(diccprio->ClaveMax())).EsVacio()) {
                diccprio->Borrar(diccprio->ClaveMax());
            }
            dicccam->Borrar(paq);
            (compYPaq->obtener((it.Siguiente()).hostname))->enviados++;
            if ((compYPaq->obtener((it.Siguiente()).hostname))->enviados > masEnviante->enviados) {
                masEnviante = new e_masEnvio(it.Siguiente(), compYPaq->obtener((it.Siguiente()).hostname)->enviados);
            }
        }
		it.Avanzar();
	}
	Lista<InfoPaquete>::Iterador itaux = l.CrearIt();

	while (itaux.HaySiguiente()) {
        Compu proxpc = red->CaminosMinimos(itaux.Siguiente().compuAnt, itaux.Siguiente().paque.destino).Siguiente().Primero();

		DiccRapido<Nat, Conj<_Paquete> >* diccprio = (compYPaq->obtener(proxpc.hostname))->masPriori;
		DiccRapido<_Paquete, Lista<Compu> >* dicccam = (compYPaq->obtener(proxpc.hostname))->paqYCam;

		if (proxpc != ((itaux.Siguiente()).paque).destino) {
			if (diccprio->Def(((itaux.Siguiente()).paque).prioridad)) {
                diccprio->Obtener(itaux.Siguiente().paque.prioridad).Agregar(itaux.Siguiente().paque);
                Conj<_Paquete> mismaPrio = diccprio->Obtener(itaux.Siguiente().paque.prioridad);
				diccprio->Definir(((itaux.Siguiente()).paque).prioridad, mismaPrio);
			} else {
				Conj<_Paquete> conjvacio;
                conjvacio.Agregar(itaux.Siguiente().paque);
                diccprio->Definir(itaux.Siguiente().paque.prioridad, conjvacio);
			}
		} else {
            itaux.Siguiente().camReco.AgregarAtras(proxpc);
			dicccam->Definir((itaux.Siguiente()).paque, itaux.Siguiente().camReco);
		}
		itaux.Avanzar();
	}
}

bool DCNet::PaqueteEnTransito(_Paquete p) {
	Conj<Compu>::Iterador it = red->Computadoras();
	bool esta = false;
	while (it.HaySiguiente() && !esta) {
        esta = compYPaq->obtener(it.Siguiente().hostname)->paqYCam->Def(p);
		it.Avanzar();
	}
	return esta;
}

Compu DCNet::LaQueMasEnvio() {
	return masEnviante->comp;
}


_Paquete DCNet::DamePaquete(Nat n){
	vector<string> vr = (compYPaq->claves());
    int i=0;
	bool esta = false;
	_Paquete p;
	while (vr.size() < i && !esta) {
    	DiccRapido<_Paquete, Lista<Compu> >::ITClave it = (compYPaq->obtener(vr[i])->paqYCam)->Claves();
    	while(it.HayMas()){

    		if((it.ClaveActual()).id == n){
    			p.id = (it.ClaveActual()).id;
				p.prioridad = (it.ClaveActual()).prioridad;
				p.origen = (it.ClaveActual()).origen;
				p.destino = (it.ClaveActual()).destino;

				return p;
				}
    		it.Avanzar();
    	}
		
		i++;
	}
}


