#ifndef DCNET_H
#define DCNET_H

#include "TiposSimples.h"
#include "aed2/TiposBasicos.h"
#include "aed2/Conj.h"
#include "aed2/Arreglo.h"
#include "aed2/Vector.h"
#include "aed2/Lista.h"
#include "dicc_trie.h"
#include "DiccRapido.h"
#include "red.h"


using namespace aed2;



class DCNet {
public:

	DCNet(const Red &);

	~DCNet();

	Red DameRed();

	Lista<Compu> CaminoRecorrido(_Paquete);

	Nat CantidadEnviados(Compu);

	DiccRapido<_Paquete, Lista<Compu> >::ITClave EnEspera(Compu);

	DiccRapido<_Paquete, Lista<Compu> >* EnEsperaAux(Compu);

	void CrearPaquete(_Paquete);

	void AvanzarSegundo();

	bool PaqueteEnTransito(_Paquete);

	Compu& LaQueMasEnvio();



	_Paquete DamePaquete(Nat);
	

private:

	struct e_InfoCompu {
		DiccRapido<Nat, Conj<_Paquete> >* masPriori;
		DiccRapido<_Paquete, Lista<Compu> >* paqYCam;
		Nat enviados;

		e_InfoCompu() : masPriori(new DiccRapido<Nat, Conj<_Paquete> >()),
					  paqYCam(new DiccRapido<_Paquete, Lista<Compu> >()), enviados(0) { };
	};

	struct e_masEnvio {
		Compu comp;
		Nat enviados;
		e_masEnvio(Compu c, Nat n) : comp(c), enviados(n) { };
	};

	Red* red;
	e_masEnvio* masEnviante;
	DiccString<e_InfoCompu>* compYPaq;

};

#endif 