#ifndef DCNET_H
#define DCNET_H

#include "aed2.h"
#include "red.h"

class DCNet{
public:

	DCNet(Red&);

	~DCNet();

	Red& Red();

	Lista<Compu> CaminoRecorrido(const Paquete);

	Nat CantidadEnviados(Compu);

	DiccRapido<Paquete>::ITClave EnEspera(Compu);

	void CrearPaquete(Paquete);

	void AvanzarSegundo();

	bool PaqueteEnTransito(Paquete);

	Compu LaQueMasEnvio();

private:

	Red red;
	<Compu enviados> masEnviante;
	DiccString<hostname> compYPaq;

struct InfoCompu {

	DiccRapido<T> masPriori;
	DiccRapido<T> paqYCam;
	Nat enviados;

		InfoCompu(): masPriori(Vacio()), compYPaq(Vacio()),enviados(0){} 
};


}


}
#endif 