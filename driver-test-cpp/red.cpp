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

//*** Borrar
void Red::DefinirDummy() {
    DiccString<Conj<Lista<Compu> > > diccDummy;
    deOrigenADestino->definir("dummy", diccDummy);
}
//***

bool Red::Conectadas(const Compu c1, const Compu c2) {
    return directasEInterfaces->obtener(c1.hostname)->Directas()->definido(c2.hostname);
}

Interfaz& Red::InterfazUsada(const Compu c1, const Compu c2) {
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

    //std::cout << "*** Conectando " << c1.hostname << " con ";
    //std::cout << "" << c2.hostname << "... \n";

    TuplaDirectas* tupSig1 = directasEInterfaces->obtener(c1.hostname);
    tupSig1->Directas()->definir(c2.hostname, i1);
    tupSig1->CompusDirectas()->Agregar(c2);

    TuplaDirectas* tupSig2 = directasEInterfaces->obtener(c2.hostname);
    tupSig2->Directas()->definir(c1.hostname, i2);
    tupSig2->CompusDirectas()->Agregar(c1);

    Conj<Compu>::Iterador itOrigenes = computadoras->CrearIt();

    while (itOrigenes.HaySiguiente()) {
        //std::cout << "\n";
        DiccString<Conj<Lista<Compu> > >* dicCompu = deOrigenADestino->obtener((itOrigenes.Siguiente()).hostname);

        Conj<Compu>::Iterador itDestinos = computadoras->CrearIt();
        while (itDestinos.HaySiguiente()) {
            //std::cout << "* Definiendo Origen: " << itOrigenes.Siguiente().hostname << " - ";
            //std::cout << "Destino: " << itDestinos.Siguiente().hostname << "\n";
            if (itOrigenes.Siguiente() != itDestinos.Siguiente()) {
                Conj<Lista<Compu> > cCaminosMinimos = CalcularCaminosMinimos(itOrigenes.Siguiente(), itDestinos.Siguiente());
                //std::cout << "Cantidad de caminos mínimos encontrados: " << cCaminosMinimos.Cardinal() << "\n\n";
                dicCompu->definir((itDestinos.Siguiente()).hostname, cCaminosMinimos);
            }else{
                //std::cout << "IGUALES - SALTEAR" << "\n\n";
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

//*** Borrar
Conj<Lista<Compu> > Red::CaminosMinimos2(const Compu c1, const Compu c2) {
    return *deOrigenADestino->obtener(c1.hostname)->obtener(c2.hostname);
}
//***

bool Red::HayCamino(const Compu c1, const Compu c2) {
    Conj<Lista<Compu> >::Iterador itConjLinealCaminosMinimos = CaminosMinimos(c1, c2);
    return itConjLinealCaminosMinimos.HaySiguiente();
}

Conj<Lista<Compu> > Red::CalcularCaminosMinimos(const Compu c1, const Compu c2) {
    //std::cout << "Calculando caminos mínimos entre " << c1.hostname << " y " << c2.hostname << "\n";
    Conj<Lista<Compu> > res;
    //Conj<Lista<Compu> > conjLinealCaminosImportantes = Conj<Lista<Compu> >();
    Conj<Lista<Compu> > conjLinealCaminosImportantes;

    Lista<Compu> parcial;
    parcial.AgregarAtras(c1);
    conjLinealCaminosImportantes = CaminosImportantes(c1, c2, parcial);
    //std::cout << "Caminos importantes detectados: " << conjLinealCaminosImportantes.Cardinal() << "\n";

    Conj<Lista<Compu> >::Iterador itCaminosImportantes = conjLinealCaminosImportantes.CrearIt();
    while (itCaminosImportantes.HaySiguiente()) {
        if (res.EsVacio() || res.CrearIt().Siguiente().Longitud() == itCaminosImportantes.Siguiente().Longitud()) {
            res.Agregar(itCaminosImportantes.Siguiente());
        }else if (res.CrearIt().Siguiente().Longitud() > itCaminosImportantes.Siguiente().Longitud()){
            Conj<Lista<Compu> >::Iterador resit = res.CrearIt();
            while (resit.HaySiguiente())
                resit.EliminarSiguiente();

            res.Agregar(itCaminosImportantes.Siguiente());
        }
        itCaminosImportantes.Avanzar();
    }

    return res;
}

Conj<Lista<Compu> > Red::CaminosImportantes(const Compu c1, const Compu c2, Lista<Compu> parcial) {
    //std::cout << "Calculando caminos importantes: " << "\n";
//    Conj<Lista<Compu> >* res = new Conj<Lista<Compu> >;
    Conj<Lista<Compu> > res;

    Conj<Compu> cVecinos = Vecinos(c1);

    if (cVecinos.Pertenece(c2)) {
        parcial.AgregarAtras(c2);
        res.Agregar(parcial);
    }else{
        Conj<Compu>::Iterador itVecinos = cVecinos.CrearIt();

        while (itVecinos.HaySiguiente()) {
            if (!(parcial.Esta(itVecinos.Siguiente()))) {
                Lista<Compu> auxParcial = Lista<Compu>(parcial);
                auxParcial.AgregarAtras(itVecinos.Siguiente());
                res.Union(CaminosImportantes(itVecinos.Siguiente(), c2, auxParcial));
            }
            itVecinos.Avanzar();
        }
    }
    return res;
}

Compu Red::DameCompu(Hostname h) {
    Conj<Compu>::Iterador it = Computadoras();
    Compu pc;

    while (it.HaySiguiente()) {
        if ((it.Siguiente()).hostname == h) {
            pc.hostname = h;
            pc.interfaces = (it.Siguiente()).interfaces;
            return pc;
        }
        it.Avanzar();
    }
}

//int main() {
//    DiccString<int> dicc;
//    string str = "jose";
//    int num1 = 3;
//    int num2 = 4;
//    int num3 = 5;
//
//    dicc.definir(str, num1);
//    dicc.definir(str, num2);
//    dicc.definir(str, num3);
//
//
//}

//int main(){
//
//    Red red;
//
//    Compu c1;
//    Compu c2;
//    Compu c3;
//    Compu c4;
//    Compu c5;
//    Compu c6;
//
//    c1.hostname = "c1";
//    c2.hostname = "c2";
//    c3.hostname = "c3";
//    c4.hostname = "c4";
//    c5.hostname = "c5";
//    c6.hostname = "c6";
//
//    red.AgregarComputadora(c1);
//    red.AgregarComputadora(c2);
//    red.AgregarComputadora(c5);
//    red.AgregarComputadora(c3);
//    red.AgregarComputadora(c4);
//    red.AgregarComputadora(c6);
//
//    Interfaz i1 = 1;
//    Interfaz i2 = 2;
//    Interfaz i3 = 3;
//    Interfaz i5 = 5;
//
//    red.Conectar(c1, i1, c2, i2);
//    red.Conectar(c1, i3, c3, i1);
//    red.Conectar(c3, i2, c5, i1);
//    red.Conectar(c2, i1, c4, i1);
//    red.Conectar(c4, i2, c5, i2);
//    red.Conectar(c6, i1, c1, i2);
//    red.Conectar(c6, i2, c2, i3);
//    red.Conectar(c6, i3, c5, i3);
//
//
//    //Conj<Lista<Compu> > camc3c4 = red.CaminosMinimos(c3, c4);
//    Conj<Lista<Compu> >::Iterador camc3c4it = red.CaminosMinimos(c3, c4);
//    while (camc3c4it.HaySiguiente()) {
//        Lista<Compu> liscompu = camc3c4it.Siguiente();
//        Lista<Compu>::Iterador liscompuit = liscompu.CrearIt();
//
//        while (liscompuit.HaySiguiente()) {
//            std::cout << liscompuit.Siguiente().hostname << "-";
//            liscompuit.Avanzar();
//        }
//
//        camc3c4it.Avanzar();
//        std::cout << "\n";
//    }

//
//    Lista<Compu> li;
//    li.AgregarAtras(c3);
//    //Conj<Lista<Compu> >::Iterador camc3c4 = red.CaminosMinimos(c3, c4);
//    Conj<Lista<Compu> > camimpc3c4 = red.CaminosImportantes(c3, c4, li);
//    Conj<Lista<Compu> >::Iterador camimpc3c4it = camimpc3c4.CrearIt();
//
//    while (camimpc3c4it.HaySiguiente()) {
//        Lista<Compu> liscompu = camimpc3c4it.Siguiente();
//        Lista<Compu>::Iterador liscompuit = liscompu.CrearIt();
//
//        while (liscompuit.HaySiguiente()) {
//            std::cout << liscompuit.Siguiente().hostname << "-";
//            liscompuit.Avanzar();
//        }
//
//        camimpc3c4it.Avanzar();
//        std::cout << "\n";
//    }


//}

/*
int main(){
    Red red;

//    red.DefinirDummy();
//    red.DefinirDummy();
//    red.DefinirDummy();
//    red.DefinirDummy();
//    red.DefinirDummy();
//    red.DefinirDummy();
//
    std::cout << "Creo c1, c2 y c3 (Computadoras). \n\n";
    Compu c1;
    Compu c2;
    Compu c3;
    Compu c4;

    std::cout << "Asigno hostname de c1 = 'computadora_1'. \n\n";
    c1.hostname = "c1";

    std::cout << "Asigno hostname de c2 = 'computadora_2'. \n\n";
    c2.hostname = "c2";

    std::cout << "Asigno hostname de c3 = 'computadora_3'. \n\n";
    c3.hostname = "c3";

    std::cout << "Asigno hostname de c4 = 'computadora_4'. \n\n";
    c4.hostname = "c4";

    std::cout << "Agrego computadora 1 a la red. \n\n";
    red.AgregarComputadora(c1);

    std::cout << "Agrego computadora 2 a la red. \n\n";
    red.AgregarComputadora(c2);

    std::cout << "Agrego computadora 3 a la red. \n\n";
    red.AgregarComputadora(c3);

    std::cout << "Cardinal de computadoras. \n";
    std::cout << "Conectadas(c1, c2): " << red.Computadoras2().Cardinal() << "\n\n";
    assert(red.Computadoras2().Cardinal() == 3);

    std::cout << "Creo interfaz i1(1), interfaz i2(2) y interfaz i3(3). \n\n";
    Interfaz i1 = 1;
    Interfaz i2 = 2;
    Interfaz i3 = 3;

    std::cout << "Conecto c1 con c2 usando i1 y i2. \n\n";
    red.Conectar(c1, i1, c2, i2);

    std::cout << "Chequeo si están conectadas: \n";
    std::cout << "Conectadas(c1, c2): " << red.Conectadas(c1, c2) << "\n\n";
    assert(red.Conectadas(c1, c2) == true);

    assert(red.InterfazUsada(c2, c1) == 2);
    std::cout << "Chequeo si están conectadas: \n";
    std::cout << "Conectadas(c1, c3): " << red.Conectadas(c1, c3) << "\n\n";
    assert(red.Conectadas(c1, c3) == false);

    std::cout << "Chequeo que la interfaz usada sea la correcta: \n";
    std::cout << "InterfazUsada(c1, c2): " << red.InterfazUsada(c1, c2) << "\n\n";
    assert(red.InterfazUsada(c1, c2) == 1);

    std::cout << "Chequeo que la interfaz usada sea la correcta: \n";
    std::cout << "InterfazUsada(c2, c1): " << red.InterfazUsada(c2, c1) << "\n\n";

    std::cout << "Chequeo si usa una interfaz dada: \n";
    std::cout << "UsaInterfaz(c1, i1): " << red.UsaInterfaz(c1, i1) << "\n\n";
    assert(red.UsaInterfaz(c1, i1) == true);

    std::cout << "Chequeo si usa una interfaz dada: \n";
    std::cout << "UsaInterfaz(c1, i2): " << red.UsaInterfaz(c1, i2) << "\n\n";
    assert(red.UsaInterfaz(c1, i2) == false);

    std::cout << "Chequeo si usa una interfaz dada: \n";
    std::cout << "UsaInterfaz(c2, i1): " << red.UsaInterfaz(c2, i1) << "\n\n";
    assert(red.UsaInterfaz(c2, i1) == false);

    std::cout << "Chequeo si usa una interfaz dada: \n";
    std::cout << "UsaInterfaz(c2, i2): " << red.UsaInterfaz(c2, i2) << "\n\n";
    assert(red.UsaInterfaz(c2, i2) == true);

    std::cout << "Chequeo si hay camino: \n";
    std::cout << "HayCamino(c1, c2): " << red.HayCamino(c1, c2) << "\n\n";
    assert(red.HayCamino(c1, c2) == true);

    std::cout << "Chequeo si hay camino: \n";
    std::cout << "HayCamino(c2, c1): " << red.HayCamino(c2, c1) << "\n\n";
    assert(red.HayCamino(c2, c1) == true);

    std::cout << "Chequeo si hay camino: \n";
    std::cout << "HayCamino(c1, c3): " << red.HayCamino(c1, c3) << "\n\n";
    assert(red.HayCamino(c1, c3) == false);

    std::cout << "Chequeo vecinos: \n";
    std::cout << "Vecinos(c1).Cardinal(): " << red.Vecinos(c1).Cardinal() << "\n\n";
    assert(red.Vecinos(c1).Cardinal() == 1);

    std::cout << "Conecto c1 con c3 usando i3 y i1. \n\n";
    red.Conectar(c1, i3, c3, i1);

    std::cout << "Chequeo si están conectadas: \n";
    std::cout << "Conectadas(c1, c3): " << red.Conectadas(c1, c3) << "\n\n";
    assert(red.Conectadas(c1, c3) == true);

    std::cout << "Chequeo si hay camino: \n";
    std::cout << "HayCamino(c1, c3): " << red.HayCamino(c1, c3) << "\n\n";
    assert(red.HayCamino(c1, c3) == true);

    std::cout << "Chequeo vecinos c1: \n";
    std::cout << "Vecinos(c1).Cardinal(): " << red.Vecinos(c1).Cardinal() << "\n\n";
    assert(red.Vecinos(c1).Cardinal() == 2);

    std::cout << "Chequeo vecinos c2: \n";
    std::cout << "Vecinos(c2).Cardinal(): " << red.Vecinos(c2).Cardinal() << "\n\n";
    assert(red.Vecinos(c2).Cardinal() == 1);

    std::cout << "Chequeo vecinos c3: \n";
    std::cout << "Vecinos(c3).Cardinal(): " << red.Vecinos(c3).Cardinal() << "\n\n";
    assert(red.Vecinos(c3).Cardinal() == 1);

    std::cout << "Chequeo si c2 y c3 están conectadas: \n";
    std::cout << "Conectadas(c2, c3): " << red.Conectadas(c2, c3) << "\n\n";
    assert(red.Conectadas(c2, c3) == false);

    std::cout << "Agrego computadora 4 a la red. \n\n";
    red.AgregarComputadora(c4);

    std::cout << "Chequeo si c1 y c4 están conectadas: \n";
    std::cout << "Conectadas(c1, c4): " << red.Conectadas(c1, c4) << "\n\n";
    assert(red.Conectadas(c1, c4) == false);

    std::cout << "Chequeo si c2 y c4 están conectadas: \n";
    std::cout << "Conectadas(c2, c4): " << red.Conectadas(c2, c4) << "\n\n";
    assert(red.Conectadas(c2, c4) == false);

    std::cout << "Chequeo si c3 y c4 están conectadas: \n";
    std::cout << "Conectadas(c3, c4): " << red.Conectadas(c3, c4) << "\n\n";
    assert(red.Conectadas(c3, c4) == false);

    std::cout << "Chequeo si c4 y c1 están conectadas: \n";
    std::cout << "Conectadas(c4, c1): " << red.Conectadas(c4, c1) << "\n\n";
    assert(red.Conectadas(c4, c1) == false);

    std::cout << "Chequeo vecinos c4: \n";
    std::cout << "Vecinos(c4).Cardinal(): " << red.Vecinos(c4).Cardinal() << "\n\n";
    assert(red.Vecinos(c4).Cardinal() == 0);

    std::cout << "Chequeo si hay camino: \n";
    std::cout << "HayCamino(c1, c4): " << red.HayCamino(c1, c4) << "\n\n";
    assert(red.HayCamino(c1, c4) == false);

    std::cout << "Chequeo si hay camino: \n";
    std::cout << "HayCamino(c2, c4): " << red.HayCamino(c2, c4) << "\n\n";
    assert(red.HayCamino(c2, c4) == false);

    std::cout << "Chequeo si hay camino: \n";
    std::cout << "HayCamino(c3, c4): " << red.HayCamino(c3, c4) << "\n\n";
    assert(red.HayCamino(c3, c4) == false);

    std::cout << "Chequeo si hay camino: \n";
    std::cout << "HayCamino(c4, c1): " << red.HayCamino(c4, c1) << "\n\n";
    assert(red.HayCamino(c4, c1) == false);

    std::cout << "Caminos minimos entre c1 y c2: \n";
    std::cout << "CaminosMinimos(c1, c2).Cardinal(): " << red.CaminosMinimos2(c1, c2).Cardinal() << "\n\n";
    assert(red.CaminosMinimos2(c1, c2).Cardinal() == 1);

    // Chequeo caminos minimos con una red mas compleja.

    Red red2;

    Compu c5;
    c5.hostname = "c5";

    Interfaz i5;
    i5 = 5;

    red2.AgregarComputadora(c1);
    red2.AgregarComputadora(c2);
    red2.AgregarComputadora(c3);
    red2.AgregarComputadora(c4);
    red2.AgregarComputadora(c5);

    red2.Conectar(c1, i1, c3, i1);
    red2.Conectar(c3, i2, c5, i1);
    red2.Conectar(c2, i1, c4, i1);

    assert(red2.HayCamino(c1, c3) == true);
    assert(red2.HayCamino(c1, c5) == true);
    assert(red2.HayCamino(c3, c1) == true);
    assert(red2.HayCamino(c3, c5) == true);
    assert(red2.HayCamino(c5, c1) == true);
    assert(red2.HayCamino(c5, c3) == true);

    assert(red2.HayCamino(c2, c4) == true);
    assert(red2.HayCamino(c4, c2) == true);

    assert(red2.HayCamino(c2, c1) == false);
    assert(red2.HayCamino(c2, c3) == false);
    assert(red2.HayCamino(c2, c5) == false);
    assert(red2.HayCamino(c4, c1) == false);
    assert(red2.HayCamino(c4, c3) == false);
    assert(red2.HayCamino(c4, c5) == false);

    assert(red2.HayCamino(c1, c2) == false);
    assert(red2.HayCamino(c1, c4) == false);
    assert(red2.HayCamino(c3, c2) == false);
    assert(red2.HayCamino(c3, c4) == false);
    assert(red2.HayCamino(c5, c2) == false);
    assert(red2.HayCamino(c5, c4) == false);

    assert(red2.Conectadas(c1, c3) == true);
    assert(red2.Conectadas(c1, c5) == false);
    assert(red2.Conectadas(c3, c1) == true);
    assert(red2.Conectadas(c3, c5) == true);
    assert(red2.Conectadas(c5, c1) == false);
    assert(red2.Conectadas(c5, c3) == true);

    assert(red2.Conectadas(c2, c4) == true);
    assert(red2.Conectadas(c4, c2) == true);

    assert(red2.Conectadas(c2, c1) == false);
    assert(red2.Conectadas(c2, c3) == false);
    assert(red2.Conectadas(c2, c5) == false);
    assert(red2.Conectadas(c4, c1) == false);
    assert(red2.Conectadas(c4, c3) == false);
    assert(red2.Conectadas(c4, c5) == false);

    assert(red2.Conectadas(c1, c2) == false);
    assert(red2.Conectadas(c1, c4) == false);
    assert(red2.Conectadas(c3, c2) == false);
    assert(red2.Conectadas(c3, c4) == false);
    assert(red2.Conectadas(c5, c2) == false);
    assert(red2.Conectadas(c5, c4) == false);

    assert(red2.Vecinos(c1).Cardinal() == 1);
    assert(red2.Vecinos(c2).Cardinal() == 1);
    assert(red2.Vecinos(c3).Cardinal() == 2);
    assert(red2.Vecinos(c4).Cardinal() == 1);
    assert(red2.Vecinos(c5).Cardinal() == 1);

    assert(red2.CaminosMinimos2(c1, c3).Cardinal() == 1);
    assert(red2.CaminosMinimos2(c1, c5).Cardinal() == 1);
    assert(red2.CaminosMinimos2(c3, c1).Cardinal() == 1);
    assert(red2.CaminosMinimos2(c3, c5).Cardinal() == 1);
    assert(red2.CaminosMinimos2(c5, c1).Cardinal() == 1);
    assert(red2.CaminosMinimos2(c5, c3).Cardinal() == 1);

    assert(red2.CaminosMinimos2(c2, c4).Cardinal() == 1);
    assert(red2.CaminosMinimos2(c4, c2).Cardinal() == 1);

    assert(red2.CaminosMinimos2(c2, c1).Cardinal() == 0);
    assert(red2.CaminosMinimos2(c2, c3).Cardinal() == 0);
    assert(red2.CaminosMinimos2(c2, c5).Cardinal() == 0);
    assert(red2.CaminosMinimos2(c4, c1).Cardinal() == 0);
    assert(red2.CaminosMinimos2(c4, c3).Cardinal() == 0);
    assert(red2.CaminosMinimos2(c4, c5).Cardinal() == 0);

    assert(red2.CaminosMinimos2(c1, c2).Cardinal() == 0);
    assert(red2.CaminosMinimos2(c1, c4).Cardinal() == 0);
    assert(red2.CaminosMinimos2(c3, c2).Cardinal() == 0);
    assert(red2.CaminosMinimos2(c3, c4).Cardinal() == 0);
    assert(red2.CaminosMinimos2(c5, c2).Cardinal() == 0);
    assert(red2.CaminosMinimos2(c5, c4).Cardinal() == 0);

    red2.Conectar(c4, i2, c5, i2);

    assert(red2.CaminosMinimos2(c1, c3).Cardinal() == 1);
    assert(red2.CaminosMinimos2(c1, c5).Cardinal() == 1);
    assert(red2.CaminosMinimos2(c3, c1).Cardinal() == 1);
    assert(red2.CaminosMinimos2(c3, c5).Cardinal() == 1);
    assert(red2.CaminosMinimos2(c5, c1).Cardinal() == 1);
    assert(red2.CaminosMinimos2(c5, c3).Cardinal() == 1);

    assert(red2.CaminosMinimos2(c2, c4).Cardinal() == 1);
    assert(red2.CaminosMinimos2(c4, c2).Cardinal() == 1);

    assert(red2.CaminosMinimos2(c2, c1).Cardinal() == 1);
    assert(red2.CaminosMinimos2(c2, c3).Cardinal() == 1);
    assert(red2.CaminosMinimos2(c2, c5).Cardinal() == 1);
    assert(red2.CaminosMinimos2(c4, c1).Cardinal() == 1);
    assert(red2.CaminosMinimos2(c4, c3).Cardinal() == 1);
    assert(red2.CaminosMinimos2(c4, c5).Cardinal() == 1);

    assert(red2.CaminosMinimos2(c1, c2).Cardinal() == 1);
    assert(red2.CaminosMinimos2(c1, c4).Cardinal() == 1);
    assert(red2.CaminosMinimos2(c3, c2).Cardinal() == 1);
    assert(red2.CaminosMinimos2(c3, c4).Cardinal() == 1);
    assert(red2.CaminosMinimos2(c5, c2).Cardinal() == 1);
    assert(red2.CaminosMinimos2(c5, c4).Cardinal() == 1);

    Compu c6;
    c6.hostname = "c6";

    red2.AgregarComputadora(c6);

    red2.Conectar(c6, i1, c1, i2);
    red2.Conectar(c6, i2, c2, i2);

    assert(red2.CaminosMinimos2(c1, c5).Cardinal() == 1);
    assert(red2.CaminosMinimos2(c6, c5).Cardinal() == 2);
    assert(red2.CaminosMinimos2(c5, c6).Cardinal() == 2);

    red2.Conectar(c6, i3, c5, i3);

    assert(red2.CaminosMinimos2(c1, c5).Cardinal() == 2);
    assert(red2.CaminosMinimos2(c6, c5).Cardinal() == 1);
    assert(red2.CaminosMinimos2(c5, c6).Cardinal() == 1);

    assert(red2.HayCamino(c1, c4) == true);

     std::cout << "haycamino(c1, c4) " << (red2.CaminosMinimos(c1, c4)).Cardinal() << "\n\n";
}*/
     /* // Como es que funciona esto :X
     int main (){
        Red red;



    Compu c1;
    Compu c2;
    Compu c3;
    Compu c4;
    Compu c5;
    Compu c6;

   
    c1.hostname = "c1";

   
    c2.hostname = "c2";


    c3.hostname = "c3";

  
    c4.hostname = "c4";

    c5.hostname = "c5";

    c6.hostname = "c6";

   
    red.AgregarComputadora(c1);

    
    red.AgregarComputadora(c2);

    red.AgregarComputadora(c5);

   
    red.AgregarComputadora(c3);

    red.AgregarComputadora(c4);

    red.AgregarComputadora(c6);

    Interfaz i1 = 1;
    Interfaz i2 = 2;
    Interfaz i3 = 3;

    Interfaz i5 = 5;


    red.Conectar(c1, i1, c2, i2);

 
    red.Conectar(c1, i3, c3, i1);

    red.Conectar(c3, i2, c5, i1);

    red.Conectar(c2, i1, c4, i1);

    red.Conectar(c4, i2, c5, i2);

    red.Conectar(c6, i1, c1, i2);

    red.Conectar(c6, i2, c2, i3);

    red.Conectar(c6, i3, c5, i3);

    std::cout << "la cantidad de caminos minimos: " << ((red.CaminosMinimos(c1, c4)).Siguiente()).Longitud() << "\n";
    
    Lista<Compu>::const_Iterador it = ((red.CaminosMinimos(c1, c4)).Siguiente()).CrearIt();
    while(it.HaySiguiente()){
            std::cout << (it.Siguiente()).hostname << "\n";
       it.Avanzar();
    }
     }*/
