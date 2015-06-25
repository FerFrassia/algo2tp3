#include "ArbolSintactico.h"
#include "CiudadFuturista.h"
#include "Tipos.h"
#include "aed2/TiposBasicos.h"
#include "Driver.h"

using namespace aed2;

namespace aed2 {

Driver::Driver(const Conj<Estacion> &estacionesIniciales) {
    Mapa mapaInicial;
    
    Conj<Estacion>::const_Iterador it = estacionesIniciales.CrearIt();
    while(it.HaySiguiente()) {
        mapaInicial.Agregar(it.Siguiente());
        it.Avanzar();
    }
    
    ciudad = new CiudadFuturista(mapaInicial);
}

Driver::~Driver() {
    if(ciudad != NULL) { delete ciudad; }
}

Nat Driver::CantidadEstaciones() const
{
    Nat cantEstaciones = 0;
//    Conj<Estacion>::Iterador it = mapa -> Estaciones();
    Conj<Estacion>::Iterador it = (ciudad -> GetMapa()).Estaciones();
    while(it.HaySiguiente()) {
        cantEstaciones++;
        it.Avanzar();
    }
    return cantEstaciones;
}

Nat Driver::CantidadDeSendasParaEstacion(const Estacion &e) const
{
    Nat sendas = 0;
    Conj<Estacion>::Iterador it = (ciudad -> GetMapa()).Estaciones();
    while(it.HaySiguiente()) {
        if((ciudad -> GetMapa()).Conectadas(e, it.Siguiente())) { sendas++; }
        it.Avanzar();
    }
    return sendas;
}

Estacion Driver::IesimaEstacionDeSenda(const Estacion &e, Nat i) const
{
    Conj<Estacion>::Iterador it = (ciudad -> GetMapa()).Estaciones();
    while(it.HaySiguiente()) {
        if((ciudad -> GetMapa()).Conectadas(e, it.Siguiente())) { i--; }
        if(i == 0) { return it.Siguiente(); }
        it.Avanzar();
    }
    return NULL;
}

Restriccion Driver::IesimaRestriccionDeSenda(const Estacion &e1, Nat i) const
{
    Conj<Estacion>::Iterador it = (ciudad -> GetMapa()).Estaciones();
    while(it.HaySiguiente()) {
        if((ciudad -> GetMapa()).Conectadas(e1, it.Siguiente())) { i--; }
        if(i == 0) { return ((ciudad -> GetMapa()).Restriccion(e1, it.Siguiente())).aString(); }
        it.Avanzar();
    }
    return NULL;
}

void Driver::AgregarSenda(const Estacion &e1, const Estacion &e2, Restriccion r)
{
    ArbolSintactico* expr = ArbolSintactico::LeerDeString(r);

    Rest* rest = new Rest(restriccionAux(*expr));
    (ciudad -> GetMapa()).Conectar(e1, e2, *rest);
    
    delete expr;
    delete rest;
}

Nat Driver::CantidadRobotsActivos() const
{
    Nat robots = 0;
    CiudadFuturista::Iterador it = ciudad -> Robots();
        while (it.HayMas()) {
            robots++;
            it.Avanzar();
        }
    return robots;
}

RUR Driver::IesimoRobotActivo(Nat i) const
{
    Nat j = -1;
    CiudadFuturista::Iterador it = ciudad -> Robots();
    while(it.HayMas()) {
        j++;
        if(i == j) { return it.Actual().id; }
        it.Avanzar();
    }
    return 0;
}

Estacion Driver::EstacionActualIesimoRobotActivo(Nat i) const
{
    Nat j = -1;
    CiudadFuturista::Iterador it = ciudad -> Robots();
    while(it.HayMas()) {
        j++;
        if(i == j) { return it.Actual().est; }
        it.Avanzar();
    }
    return NULL;
}

Conj<Caracteristica> Driver::CaracteristicasIesimoRobotActivo(Nat i) const
{
    Nat j = -1;
    CiudadFuturista::Iterador it = ciudad -> Robots();
    while(it.HayMas()) {
        j++;
        if(i == j) { return it.Actual().carac; }
        it.Avanzar();
    }
    return it.Actual().carac;
}

Nat Driver::CantInfraccionesIesimoRobotActivo(Nat i) const
{
    Nat j = -1;
    CiudadFuturista::Iterador it = ciudad -> Robots();
    while(it.HayMas()) {
        j++;
        if(i == j) { return it.Actual().inf; }
        it.Avanzar();
    }
    return 0;
}

RUR Driver::ElMasInfractor() const
{
    Nat robotMax;
    Nat valorMax = 0;
    CiudadFuturista::Iterador it = ciudad -> Robots();
    while(it.HayMas()) {
        if((it.Actual().inf > valorMax)) {
            robotMax = it.Actual().id;
            valorMax = it.Actual().inf;
        }
        it.Avanzar();
    }
    return robotMax;
}

void Driver::Entrar(const Conj<Caracteristica> &cs, const Estacion &estacionInicial)
{
    ciudad -> Entrar(cs, estacionInicial);
}

void Driver::Mover(RUR robot, const Estacion &destino)
{
    ciudad -> Mover(robot, destino);
}

void Driver::Inspeccion(const Estacion &e)
{
    ciudad -> Inspeccion(e);
}

Rest Driver::restriccionAux(const ArbolSintactico& arbol) {
    if(arbol.raiz == "&") {
        Rest rIzq(restriccionAux(*arbol.izq));
        Rest rDer(restriccionAux(*arbol.der));
        return rIzq.AND(rDer);
    } else if(arbol.raiz == "|") {
        Rest rIzq(restriccionAux(*arbol.izq));
        Rest rDer(restriccionAux(*arbol.der));
        return rIzq.OR(rDer);
    } else if(arbol.raiz == "!") {
        Rest rNot(restriccionAux(*arbol.izq));
        return rNot.NOT();
    } else {
        return Rest(arbol.raiz);
    }
}

} // namespace aed2

