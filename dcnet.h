#ifndef DCNET_H
#define DCNET_H

#include "red.h"
#include "dicc_trie.h"
#include "DiccRapido.h"
#include "aed2/TiposBasicos.h"
#include "TiposSimples.h"
#include "Red.h"
#include "aed2/Conj.h"
#include "aed2/Arreglo.h"
#include "aed2/Vector.h"
#include "aed2/Lista.h"

using namespace std;



class DCNet {
public:

	DCNet(const Red &);

	~DCNet();

	Red DameRed();

	Lista<Compu> CaminoRecorrido(Paquete);

	Nat CantidadEnviados(Compu);

	DiccRapido<Paquete, Lista<Compu> >::ITClave EnEspera(Compu);

	void CrearPaquete(Paquete);

	void AvanzarSegundo();

	bool PaqueteEnTransito(Paquete);

	Compu LaQueMasEnvio();

private:

	struct e_InfoCompu {
		DiccRapido<Nat, Conj<Paquete> >* masPriori;
		DiccRapido<Paquete, Lista<Compu> >* paqYCam;
		Nat enviados;

		e_InfoCompu() : masPriori(new DiccRapido<Nat, Conj<Paquete> >()),
					  paqYCam(new DiccRapido<Paquete, Lista<Compu> >()), enviados(0) { };
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