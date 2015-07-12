//
// Created by Sebasti�n on 28/06/2015.
//

#ifndef TP3___IMPLEMENTACION_RED_H
#define TP3___IMPLEMENTACION_RED_H

#include "dicc_trie.h"
#include "aed2/TiposBasicos.h"
#include "TiposSimples.h"
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

    //*** Borrar
    Conj<Compu> Computadoras2();
    //***

    //*** Borrar
    void DefinirDummy();
    //***

    bool Conectadas(const Compu c1, const Compu c2); // Chequeado

    Interfaz& InterfazUsada(const Compu c1, const Compu c2); // Chequeado

    void AgregarComputadora(const Compu c); // Chequeado

    void Conectar(Compu c1, Interfaz i1, Compu c2, Interfaz i2); // Chequeado

    Conj<Compu> Vecinos(const Compu c); // Chequeado

    bool UsaInterfaz(const Compu c, const Interfaz i); // Chequeado

    Conj<Lista<Compu> >::Iterador CaminosMinimos(const Compu c1, const Compu c2);

    //*** Borrar
    Conj<Lista<Compu> > CaminosMinimos2(const Compu c1, const Compu c2);
    //***

    bool HayCamino(const Compu c1, const Compu c2); // Chequeado

    Compu DameCompu(Hostname);

private:
    // Funciones Privadas
    Conj<Lista<Compu> > CalcularCaminosMinimos(const Compu c1, const Compu c2);

    Conj<Lista<Compu> > CaminosImportantes(const Compu c1, const Compu c2, Lista<Compu> parcial);

    DiccString<TuplaDirectas>* directasEInterfaces;
    DiccString<DiccString<Conj<Lista<Compu> > > >* deOrigenADestino;
    Conj<Compu>* computadoras;

};

#endif //TP3___IMPLEMENTACION_RED_H
