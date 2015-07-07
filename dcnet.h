#ifndef DCNET_H
#define DCNET_H

#include "aed2.h"
#include "red.h"
#include "dicc_trie.h"




class DCNet{
public:

	DCNet(Red);

	~DCNet();

	Red DameRed();

	Lista<Compu> CaminoRecorrido(Paquete);

	Nat CantidadEnviados(Compu);

	DiccRapido<Paquete>::ITClave EnEspera(Compu);

	void CrearPaquete(Paquete);

	void AvanzarSegundo();

	bool PaqueteEnTransito(Paquete);

	Compu LaQueMasEnvio();

private:

	Red red;
	pair<Compu, Nat> masEnviante;
	DiccString<Hostname> compYPaq;

	struct InfoCompu{
		DiccRapido<prioridad> masPriori;
		DiccRapido<Paquete> paqYCam;
		Nat enviados;



	};

};

#endif 