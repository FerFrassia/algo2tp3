//
// Created by Sebastián on 28/06/2015.
//

#include "dicc_rapido.h"
#include "TiposSimples.h"
#include "Red.h"
#include "aed2/TiposBasicos.h"
#include "aed2/Conj.h"
#include "aed2/Arreglo.h"
#include "aed2/Vector.h"
#include "aed2/Lista.h"


Red::Red() {
    directasEInterfaces = new DiccRapido<TuplaDirectas>();
    deOrigenADestino = new DiccRapido<DiccRapido<Conj<Lista<Compu>>>>();
    computadoras = new Conj<Compu>();
}

Red::Red(const Red& original) {
    directasEInterfaces = new DiccRapido<TuplaDirectas>(*original.directasEInterfaces);
    deOrigenADestino = new DiccRapido<DiccRapido<Conj<Lista<Compu>>>>(*original.deOrigenADestino);
    computadoras = new Conj<Compu>(*original.computadoras);
}

Red::~Red() {
    delete directasEInterfaces;
    delete deOrigenADestino;
    delete computadoras;
}

Conj<Compu>::Iterador Red::Computadoras() {
    return computadoras->CrearIt();
}

bool Red::Conectadas(const Compu c1, const Compu c2) {
    return (directasEInterfaces->Obtener(c1.hostname).directas).Definido(c2.hostname);

    //return (uniones -> Significado(est1)).Definido(est2);
}

Interfaz Red::InterfazUsada(const Compu c1, const Compu c2) {
    (directasEInterfaces->Obtener(c1.hostname).directas).Obtener(c2.hostname);
    //return (*sendas)[((uniones -> Significado(est1)).Significado(est2))];
}

// Iniciar red?

void Red::AgregarComputadora(const Compu c) {
    directasEInterfaces->Definir(c.hostname, <TuplaDirectas::directas->Vacio(), TuplaDirectas::compusDirectas->Conj())>;
    Conj<Compu>::Iterador itComputadoras = computadoras->CrearIt();

    while (itComputadoras.HaySiguiente()){
        (deOrigenADestino->Obtener((itComputadoras.Siguiente()).hostname)).Definir(c.hostname, DiccRapido::Vacio());
        itComputadoras.Avanzar();
    }

    DiccRapido diccNuevaCompu = DiccRapido::Vacio();
}

void Red::Conectar(const Compu c1, const Interfaz i1, const Compu c2, const Interfaz i2) { }

Conj<Compu>::Iterador Red::Vecinos(const Compu c) { }

bool Red::UsaInterfaz(const Compu c, const Interfaz i) { }

Conj<Conj<Lista<Compu>>>::Iterador Red::CaminosMinimos(const Compu c1, const Compu c2) { }

bool Red::HayCamino(const Compu c1, const Compu c2) { }

Conj<Lista<Compu>> Red::CalcularCaminosMinimos(const Compu c1, const Compu c2) { }

Conj<Lista<Compu>> Red::CaminosImportantes(const Compu c1, const Compu c2, const Lista parcial) { }

//void Mapa::Agregar(const Estacion est) {
//    estaciones -> Agregar(est);
//    uniones -> Definir(est, DiccString<Nat>());
//}
//
//void Mapa::Conectar(const Estacion est1, const Estacion est2, const Rest& rest) {
//    (uniones -> Significado(est1)).Definir(est2, cantSendas);
//    (uniones -> Significado(est2)).Definir(est1, cantSendas);
//    sendas -> Agregar(cantSendas, rest);
//    cantSendas++;
//}
//
//Nat Mapa::NroConexion(const Estacion est1, const Estacion est2) {
//    return (uniones -> Significado(est1)).Significado(est2);
//}
//
//Arreglo<bool> Mapa::EvaluarSendas(const Conj<Caracteristica>& carac) {
//    Arreglo<bool> res = Arreglo<bool>(cantSendas);
//    Nat i = 0;
//    while(i < cantSendas) {
//        Rest rest = (*sendas)[i];
//        res.Definir(i, rest.Verifica(carac));
//        i++;
//    }
//    return res;
//}
//
//Arreglo<Rest> Mapa::Restricciones() {
//    Arreglo<Rest> res = Arreglo<Rest>(cantSendas);
//    Nat i = 0;
//    while(i < cantSendas) {
//        res.Definir(i, (*sendas)[i]);
//        i++;
//    }
//    return res;
//}