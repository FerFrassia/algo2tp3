//
// Created by Sebasti�n on 28/06/2015.
//

#include "dicc_trie.h"
#include "aed2/TiposBasicos.h"
#include "TiposSimples.h"
#include "Red.h"
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
    TuplaDirectas tup = TuplaDirectas();
    directasEInterfaces->definir(c.hostname, tup);

    Conj<Compu>::Iterador itComputadoras = computadoras->CrearIt();

    while (itComputadoras.HaySiguiente()){
        Conj<Lista<Compu> > cConj = Conj<Lista<Compu> >();
        (deOrigenADestino->obtener((itComputadoras.Siguiente()).hostname))->definir(c.hostname, cConj);
        itComputadoras.Avanzar();
    }

    DiccString<Conj<Lista<Compu > > >* diccNuevaCompu = new DiccString<Conj<Lista<Compu> > >;

    while (itComputadoras.HayAnterior()) {
        Conj<Lista<Compu> >* cConj = new Conj<Lista<Compu> >;
        diccNuevaCompu->definir((itComputadoras.Anterior()).hostname, *cConj);
        itComputadoras.Retroceder();
    }

    deOrigenADestino->definir(c.hostname, *diccNuevaCompu);
    computadoras->Agregar(c);
}

void Red::Conectar(Compu c1, Interfaz i1, Compu c2, Interfaz i2) {
    TuplaDirectas* tupSig1 = directasEInterfaces->obtener(c1.hostname);
    tupSig1->Directas()->definir(c2.hostname, i1);
    tupSig1->CompusDirectas()->Agregar(c2);

    TuplaDirectas* tupSig2 = directasEInterfaces->obtener(c2.hostname);
    tupSig2->Directas()->definir(c1.hostname, i2);
    tupSig2->CompusDirectas()->Agregar(c1);

    Conj<Compu>::Iterador itOrigenes = computadoras->CrearIt();
    while (itOrigenes.HaySiguiente()) {
        DiccString<Conj<Lista<Compu> > >* dicCompu = deOrigenADestino->obtener((itOrigenes.Siguiente()).hostname);

        Conj<Compu>::Iterador itDestinos = computadoras->CrearIt();
        while (itDestinos.HaySiguiente()) {
            if (itOrigenes.Siguiente() != itDestinos.Siguiente()) {
                Conj<Lista<Compu> > prueba = CalcularCaminosMinimos(itOrigenes.Siguiente(), itDestinos.Siguiente());
                dicCompu->definir((itDestinos.Siguiente()).hostname, prueba);
            }
            itDestinos.Avanzar();
        }
        itOrigenes.Avanzar();
    }
}

Conj<Compu> Red::Vecinos(const Compu c) {
    return *(directasEInterfaces->obtener(c.hostname))->CompusDirectas();
}

bool Red::UsaInterfaz(const Compu c, const Interfaz i) {
    TuplaDirectas* tupVecinos = directasEInterfaces->obtener(c.hostname);
    Conj<Compu>::Iterador itCompusDirectas = tupVecinos->CompusDirectas()->CrearIt();
    bool res = false;

    while (itCompusDirectas.HaySiguiente()) {
        if (*tupVecinos->Directas()->obtener((itCompusDirectas.Siguiente()).hostname) == i)
            res = true;
        itCompusDirectas.Avanzar();
    }
    return res;
}

Conj<Lista<Compu> >::Iterador Red::CaminosMinimos(const Compu c1, const Compu c2) {
    return deOrigenADestino->obtener(c1.hostname)->obtener(c2.hostname)->CrearIt();
}

bool Red::HayCamino(const Compu c1, const Compu c2) {
    Conj<Lista<Compu> >::Iterador itConjLinealCaminosMinimos = CaminosMinimos(c1, c2);
    return itConjLinealCaminosMinimos.HaySiguiente();
}

Conj<Lista<Compu> > Red::CalcularCaminosMinimos(const Compu c1, const Compu c2) {
    Conj<Lista<Compu> >* res = new Conj<Lista<Compu> >;
    Conj<Lista<Compu> > conjLinealCaminosImportantes = Conj<Lista<Compu> >();

    Lista<Compu>* parcial = new Lista<Compu>;
    parcial->AgregarAtras(c1);

    conjLinealCaminosImportantes = CaminosImportantes(c1, c2, *parcial);

    Conj<Lista<Compu> >::Iterador itCaminosImportantes = conjLinealCaminosImportantes.CrearIt();
    while (itCaminosImportantes.HaySiguiente()) {
        if (res->EsVacio() || res->CrearIt().Siguiente().Longitud() == itCaminosImportantes.Siguiente().Longitud()) {
            res->Agregar(itCaminosImportantes.Siguiente());
        }else if (res->CrearIt().Siguiente().Longitud() < itCaminosImportantes.Siguiente().Longitud()){
            res = new Conj<Lista<Compu> >;
            res->Agregar(itCaminosImportantes.Siguiente());
        }
    }
}

Conj<Lista<Compu> > Red::CaminosImportantes(const Compu c1, const Compu c2, Lista<Compu> parcial) {
    Conj<Lista<Compu> >* res = new Conj<Lista<Compu> >;

    if (Vecinos(c1).Pertenece(c2)) {
        parcial.AgregarAtras(c2);
        res->Agregar(parcial);
    }else{
        Conj<Compu>::Iterador itVecinos = Vecinos(c1).CrearIt();
        while (itVecinos.HaySiguiente()) {
            if (parcial.Esta(itVecinos.Siguiente())) {
                Lista<Compu> auxParcial = Lista<Compu>(parcial);
                auxParcial.AgregarAtras(itVecinos.Siguiente());
                res->Union(CaminosImportantes(itVecinos.Siguiente(), c2, auxParcial));
            }
            itVecinos.Avanzar();
        }
    }
}