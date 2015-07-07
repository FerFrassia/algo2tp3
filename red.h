//
// Created by Sebastián on 28/06/2015.
//

#ifndef TP3___IMPLEMENTACION_RED_H
#define TP3___IMPLEMENTACION_RED_H

#include "dicc_trie.h"
#include "TiposSimples.h"
#include "aed2/TiposBasicos.h"
#include "aed2/Conj.h"
#include "aed2/Arreglo.h"
#include "aed2/Vector.h"
#include "aed2/Lista.h"


using namespace aed2;

class Red {

public:

    class TuplaDirectas;

    class TuplaDirectas {

    public:
        TuplaDirectas();
        TuplaDirectas(const TuplaDirectas &orig);
        ~TuplaDirectas();
        DiccString<Interfaz>* Directas();
        Conj<Compu>* CompusDirectas();

    private:
        DiccString<Interfaz>* directas;
        Conj<Compu>* compusDirectas;
    };

    Red();

    Red(const Red &orig);

    ~Red();

    Conj<Compu>::Iterador Computadoras();

    bool Conectadas(const Compu c1, const Compu c2);

    Interfaz InterfazUsada(const Compu c1, const Compu c2);

    void AgregarComputadora(const Compu c);

    void Conectar(const Compu c1, const Interfaz i1, const Compu c2, const Interfaz i2);

    Conj<Compu>::Iterador Vecinos(const Compu c);

    bool UsaInterfaz(const Compu c, const Interfaz i);

    Conj<Conj<Lista<Compu> > >::Iterador CaminosMinimos(const Compu c1, const Compu c2);

    bool HayCamino(const Compu c1, const Compu c2);

private:
    // Funciones Privadas
    Conj<Lista<Compu> > CalcularCaminosMinimos(const Compu c1, const Compu c2);

    Conj<Lista<Compu> > CaminosImportantes(const Compu c1, const Compu c2, const Lista<Compu> parcial);

    DiccString<TuplaDirectas>* directasEInterfaces;
    DiccString<DiccString<Conj<Lista<Compu> > > >* deOrigenADestino;
    Conj<Compu>* computadoras;

};

#endif //TP3___IMPLEMENTACION_RED_H
