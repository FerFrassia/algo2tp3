//
// Created by Sebastián on 28/06/2015.
//

#include "dicc_trie.h"
#include "TiposSimples.h"
#include "Red.h"
#include "aed2/TiposBasicos.h"
#include "aed2/Conj.h"
#include "aed2/Arreglo.h"
#include "aed2/Vector.h"
#include "aed2/Lista.h"

Red::TuplaDirectas::TuplaDirectas() {
    directas = new DiccString<Interfaz>;
    compusDirectas = new Conj<Compu>;
}

Red::TuplaDirectas::TuplaDirectas(const TuplaDirectas &orig) {
    directas = orig.directas;
    compusDirectas = orig.compusDirectas;
}

Red::TuplaDirectas::~TuplaDirectas() {
    delete directas;
    delete  compusDirectas;
}

DiccString<Interfaz>* Red::TuplaDirectas::Directas() {
    return directas;
}

Conj<Compu>* Red::TuplaDirectas::CompusDirectas() {
    return compusDirectas;
}



Red::Red() {
    directasEInterfaces = new DiccString<TuplaDirectas>;
    deOrigenADestino = new DiccString<DiccString<Conj<Lista<Compu> > > >;
    computadoras = new Conj<Compu>;
}

Red::Red(const Red &original) {
    directasEInterfaces = new DiccString<TuplaDirectas>(*original.directasEInterfaces);
    deOrigenADestino = new DiccString<DiccString<Conj<Lista<Compu> > > >(*original.deOrigenADestino);
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
    return directasEInterfaces->obtener(c1.hostname)->Directas()->definido(c2.hostname);
}

Interfaz Red::InterfazUsada(const Compu c1, const Compu c2) {
    return *directasEInterfaces->obtener(c1.hostname)->Directas()->obtener(c2.hostname);
}

// Iniciar red?

void Red::AgregarComputadora(const Compu c) {

}

void Red::Conectar(const Compu c1, const Interfaz i1, const Compu c2, const Interfaz i2) { }

Conj<Compu>::Iterador Red::Vecinos(const Compu c) { }

bool Red::UsaInterfaz(const Compu c, const Interfaz i) { }

Conj<Conj<Lista<Compu> > >::Iterador Red::CaminosMinimos(const Compu c1, const Compu c2) { }

bool Red::HayCamino(const Compu c1, const Compu c2) { }

Conj<Lista<Compu> > Red::CalcularCaminosMinimos(const Compu c1, const Compu c2) { }

Conj<Lista<Compu> > Red::CaminosImportantes(const Compu c1, const Compu c2, const Lista<Compu> parcial) { }

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