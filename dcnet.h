#ifndef DCNET_H
#define DCNET_H

#include "aed2.h"

class DCNet{
public:

	DCNet IniciarDCNet(red);

	~DCNet();

	red Red();

	Lista CaminoRecorrido(Paquete);

	Nat CantidadEnviados(Compu);

	It EnEspera(Compu);

	void CrearPaquete(Paquete);

	void AvanzarSegundo();

	bool PaqueteEnTransito?(Paquete);

	Compu LaQueMasEnvio();

private:

	Red red;
	<Compu enviados> masEnviante;
	DiccString<>

















}