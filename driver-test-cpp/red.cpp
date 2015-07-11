//
// Created by Sebasti�n on 28/06/2015.
//

#include "dicc_trie.h"
#include "aed2/TiposBasicos.h"
#include "TiposSimples.h"
#include "red.h"
#include "aed2/Conj.h"
#include "aed2/Arreglo.h"
#include "aed2/Vector.h"
#include "aed2/Lista.h"

Red::TuplaDirectas::TuplaDirectas() {
    directas = new DiccString<Interfaz>;
    compusDirectas = new Conj<Compu>;
}

Red::TuplaDirectas::TuplaDirectas(const TuplaDirectas &orig) {
    directas = new DiccString<Interfaz>(*orig.directas);
    compusDirectas = new Conj<Compu>(*orig.compusDirectas);
}

Red::TuplaDirectas::~TuplaDirectas() {
    delete directas;
    delete compusDirectas;
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

//*** Borrar
Conj<Compu> Red::Computadoras2() {
    return *computadoras;
}
//***

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
        Conj<Lista<Compu> >* cConj = new Conj<Lista<Compu> >;
        (deOrigenADestino->obtener((itComputadoras.Siguiente()).hostname))->definir(c.hostname, *cConj);
        itComputadoras.Avanzar();
        delete cConj;
    }

    DiccString<Conj<Lista<Compu > > >* diccNuevaCompu = new DiccString<Conj<Lista<Compu> > >;

    while (itComputadoras.HayAnterior()) {
        Conj<Lista<Compu> >* cConj = new Conj<Lista<Compu> >;
        diccNuevaCompu->definir((itComputadoras.Anterior()).hostname, *cConj);
        itComputadoras.Retroceder();
        delete cConj;
    }

    deOrigenADestino->definir(c.hostname, *diccNuevaCompu);
    computadoras->Agregar(c);

    delete diccNuevaCompu;
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
        std::cout << "While 1." << itOrigenes.Siguiente().hostname << "\n";
        DiccString<Conj<Lista<Compu> > >* dicCompu = deOrigenADestino->obtener((itOrigenes.Siguiente()).hostname);

        Conj<Compu>::Iterador itDestinos = computadoras->CrearIt();
        while (itDestinos.HaySiguiente()) {
            std::cout << "While 2." << itDestinos.Siguiente().hostname << "\n";
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
        itCaminosImportantes.Avanzar();
    }
    return *res;
}

Conj<Lista<Compu> > Red::CaminosImportantes(const Compu c1, const Compu c2, Lista<Compu> parcial) {
    Conj<Lista<Compu> >* res = new Conj<Lista<Compu> >;

    std::cout << "Llega." << "\n";
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
    std::cout << "Sale." << "\n";
    return *res;
}

int main(){
    Red red;

    std::cout << "Creo c1, c2 y c3 (Computadoras). \n";
    Compu c1;
    Compu c2;
    Compu c3;

    std::cout << "Asigno hostname de c1 = 'computadora_1'. \n";
    c1.hostname = "computadora_1";

    std::cout << "Asigno hostname de c2 = 'computadora_2'. \n";
    c2.hostname = "computadora_2";

    std::cout << "Asigno hostname de c3 = 'computadora_3'. \n";
    c3.hostname = "computadora_3";

    std::cout << "Agrego computadora 1 a la red. \n";
    red.AgregarComputadora(c1);

    std::cout << "Agrego computadora 2 a la red. \n";
    red.AgregarComputadora(c2);

    std::cout << "Agrego computadora 3 a la red. \n";
    red.AgregarComputadora(c3);

    std::cout << "Cardinal de computadoras. \n";
    std::cout << "Conectadas(c1, c2): " << red.Computadoras2().Cardinal() << "\n";
    assert(red.Computadoras2().Cardinal() == 3);

    std::cout << "Creo interfaz i1(2) y interfaz i2(3). \n";
    Interfaz i1 = 2;
    Interfaz i2 = 3;

    std::cout << "Conecto c1 con c2 usando i1 y i2. \n";
    red.Conectar(c1, i1, c2, i2);

    std::cout << "Chequeo si están conectadas: \n";
    std::cout << "Conectadas(c1, c2): " << red.Conectadas(c1, c2) << "\n";
    assert(red.Conectadas(c1, c2) == true);

    std::cout << "Chequeo si están conectadas: \n";
    std::cout << "Conectadas(c1, c3): " << red.Conectadas(c1, c3) << "\n";
    assert(red.Conectadas(c1, c3) == false);

    std::cout << "Chequeo que la interfaz usada sea la correcta: \n";
    std::cout << "InterfazUsada(c1, c2): " << red.InterfazUsada(c1, c2) << "\n";
    assert(red.InterfazUsada(c1, c2) == 2);

    std::cout << "Chequeo que la interfaz usada sea la correcta: \n";
    std::cout << "InterfazUsada(c2, c1): " << red.InterfazUsada(c2, c1) << "\n";
    assert(red.InterfazUsada(c2, c1) == 3);

    std::cout << "Chequeo si usa una interfaz dada: \n";
    std::cout << "UsaInterfaz(c1, i1): " << red.UsaInterfaz(c1, i1) << "\n";
    assert(red.UsaInterfaz(c1, i1) == true);

    std::cout << "Chequeo si usa una interfaz dada: \n";
    std::cout << "UsaInterfaz(c1, i2): " << red.UsaInterfaz(c1, i2) << "\n";
    assert(red.UsaInterfaz(c1, i2) == false);

    std::cout << "Chequeo si usa una interfaz dada: \n";
    std::cout << "UsaInterfaz(c2, i1): " << red.UsaInterfaz(c2, i1) << "\n";
    assert(red.UsaInterfaz(c2, i1) == false);

    std::cout << "Chequeo si usa una interfaz dada: \n";
    std::cout << "UsaInterfaz(c2, i2): " << red.UsaInterfaz(c2, i2) << "\n";
    assert(red.UsaInterfaz(c2, i2) == true);

    std::cout << "Chequeo si hay camino: \n";
    std::cout << "HayCamino(c1, c2): " << red.HayCamino(c1, c2) << "\n";
    assert(red.HayCamino(c1, c2) == true);

    std::cout << "Chequeo si hay camino: \n";
    std::cout << "HayCamino(c2, c1): " << red.HayCamino(c2, c1) << "\n";
    assert(red.HayCamino(c2, c1) == true);

    std::cout << "Chequeo si hay camino: \n";
    std::cout << "HayCamino(c1, c3): " << red.HayCamino(c1, c3) << "\n";
    assert(red.HayCamino(c1, c3) == false);
}