#ifndef DCNET_H
#define DCNET_H

#include "aed2.h"
#include "red.h"
#include "dicc_trie.h"
#include "DiccRapido.h"
#include "TiposSimples.h"

using namespace std;



class DCNet{
public:

	DCNet(Red&);

	~DCNet();

	Red DameRed();

	Lista<Compu> CaminoRecorrido(Paquete);

	Nat CantidadEnviados(Compu);

	DiccRapido<Paquete,Lista <Compu> >::ITClave EnEspera(Compu);

	void CrearPaquete(Paquete);

	void AvanzarSegundo();

	bool PaqueteEnTransito(Paquete);

	Compu LaQueMasEnvio();

private:

		struct masEnvio{
		
			Compu comp;
			Nat enviados;

			masEnvio(Compu c, Nat n) : comp(c), enviados(n) {};
		};

	Red* red;
	masEnvio* masEnviante;
	DiccString<Hostname>* compYPaq;

	
	

	struct InfoCompu{
		DiccRapido<Nat,Conj<Paquete> >* masPriori;
		DiccRapido<Paquete,Lista<Compu> >* paqYCam;
		Nat enviados;
		InfoCompu() : masPriori(new DiccRapido<Nat,Conj<Paquete> >()), paqYCam(new DiccRapido<Paquete,Lista<Compu> >()), enviados(0) {}; 
	};

};

#endif 