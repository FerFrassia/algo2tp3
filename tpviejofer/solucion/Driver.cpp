#include "Driver.h"
#include "ArbolSintactico.h"

namespace aed2 {

bool Verifica(const ArbolSintactico* a, const Conj<Caracteristica>& cs) {
    if (!a->izq && !a->der)
        return cs.Pertenece(a->raiz);
    if (a->raiz=="!")
        return !Verifica(a->izq,cs);
    if (a->raiz=="&")
        return Verifica(a->izq,cs) && Verifica(a->der,cs);
    if (a->raiz=="|")
        return Verifica(a->izq,cs) || Verifica(a->der,cs);

    assert(false);
}

Driver::Driver(const Conj<Estacion> &estacionesIniciales): estaciones(estacionesIniciales) {
	for(typename Conj<Estacion>::const_Iterador it = estaciones.CrearIt(); it.HaySiguiente(); it.Avanzar()) {
    	robotsEnEstaciones.Definir(it.Siguiente(), Conj<RUR>());
    }
}

Driver::~Driver() {
    for(typename Conj<Senda>::Iterador it = sendas.CrearIt(); it.HaySiguiente(); it.Avanzar()) {
        if(it.Siguiente().expr != NULL)
            delete it.Siguiente().expr;
    }
}

Nat Driver::CantidadEstaciones() const
{
 	return estaciones.Cardinal();
}

Nat Driver::CantidadDeSendasParaEstacion(const Estacion &e) const
{
 	Nat cant = 0;
 	for(typename Conj<Senda>::const_Iterador it = sendas.CrearIt(); it.HaySiguiente(); it.Avanzar()) {
 		if(it.Siguiente().e1 == e || it.Siguiente().e2 == e) {
 			cant++;
 		}
 	}

 	return cant;
}

Estacion Driver::IesimaEstacionDeSenda(const Estacion &e, Nat i) const
{
 // TODO
}

Restriccion Driver::IesimaRestriccionDeSenda(const Estacion &e1, Nat i) const
{
 // TODO
}

void Driver::AgregarSenda(const Estacion &e1, const Estacion &e2, Restriccion r)
{
    ArbolSintactico* expr = ArbolSintactico::LeerDeString(r);
    sendas.AgregarRapido(Senda(e1, e2, expr)); 
}

Nat Driver::CantidadRobotsActivos() const
{
 	Nat cant = 0;
 	for(typename Vector<Robot>::const_Iterador it = robots.CrearIt(); it.HaySiguiente(); it.Avanzar()) {
 		if(it.Siguiente().activo) {
 			cant++;
 		}
 	}

 	return cant;
}

RUR Driver::IesimoRobotActivo(Nat i) const
{
 	return _IesimoRobotActivo(i).rur;
}

Estacion Driver::EstacionActualIesimoRobotActivo(Nat i) const
{
 	return _IesimoRobotActivo(i).estacionActual;
}

Conj<Caracteristica> Driver::CaracteristicasIesimoRobotActivo(Nat i) const
{
 	return _IesimoRobotActivo(i).caracteristicas;
}

Nat Driver::CantInfraccionesIesimoRobotActivo(Nat i) const
{
 	return _IesimoRobotActivo(i).infracciones;
}

RUR Driver::ElMasInfractor() const
{
	int infraccionesMax = -1;
	RUR masInfractor = -1;

 	for(Nat i = 0; i < CantidadRobotsActivos(); i++) {
 		int infraccionesActual = (int) CantInfraccionesIesimoRobotActivo(i);

 		if(infraccionesActual > infraccionesMax) {
 			infraccionesMax = infraccionesActual;
 			masInfractor = _IesimoRobotActivo(i).rur; 
 		}
 	}

 	return masInfractor;
}

void Driver::Entrar(const Conj<Caracteristica> &cs, const Estacion &estacionInicial)
{
	RUR rur = robots.Longitud();
	Conj<RUR>& conjEstacion = robotsEnEstaciones.Significado(estacionInicial);
	typename Conj<RUR>::Iterador it = conjEstacion.AgregarRapido(rur);	

	Robot robot(rur, estacionInicial, cs, it);

	Dicc<Estacion, Dicc<Estacion, bool> > sendasInfractoras;

	for(typename Conj<Senda>::const_Iterador it = sendas.CrearIt(); it.HaySiguiente(); it.Avanzar()) {
 		Estacion e1 = it.Siguiente().e1;
 		Estacion e2 = it.Siguiente().e2;
        bool infringe = !Verifica(it.Siguiente().expr,cs);

 		if(!sendasInfractoras.Definido(e1)) {
 			sendasInfractoras.Definir(e1, Dicc<Estacion, bool>());
 		}
 		sendasInfractoras.Significado(e1).Definir(e2, infringe);

 		if(!sendasInfractoras.Definido(e2)) {
 			sendasInfractoras.Definir(e2, Dicc<Estacion, bool>());
 		}
 		sendasInfractoras.Significado(e2).Definir(e1, infringe);
 	}

 	robot.sendasInfractoras = sendasInfractoras;
	robots.AgregarAtras(robot);
}

void Driver::Mover(RUR robot, const Estacion &destino)
{
	Estacion actual = robots[robot].estacionActual;

 	bool infringe = robots[robot].sendasInfractoras.Significado(actual).Significado(destino);
 	if(infringe) {
 		robots[robot].infracciones++;
 	}
 	robots[robot].estacionActual = destino;
 	// Lo elimino de la cola de la estacion anterior
 	robots[robot].itColaActual.EliminarSiguiente();
 	// Lo agrego a la cola de la nueva estacion
 	robots[robot].itColaActual = robotsEnEstaciones.Significado(destino).AgregarRapido(robot);
}

void Driver::Inspeccion(const Estacion &e)
{
	RUR rur = -1;
	Nat maxInfracciones = 0;
	bool eliminar = false; 
    const Conj<RUR>& robotsEnEstacion = robotsEnEstaciones.Significado(e);
    for(typename Conj<RUR>::const_Iterador it = robotsEnEstacion.CrearIt(); it.HaySiguiente(); it.Avanzar()) {
		if(robots[it.Siguiente()].infracciones > maxInfracciones) {
			eliminar = true;
			maxInfracciones = robots[it.Siguiente()].infracciones;
			rur = it.Siguiente(); 
		}
    }

    if(eliminar) {
    	robots[rur].activo = false;
    	// Lo saco de la estacion
    	robots[rur].itColaActual.EliminarSiguiente();
    }
}

} // namespace aed2
