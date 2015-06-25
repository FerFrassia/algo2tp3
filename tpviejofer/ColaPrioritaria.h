/* 
 * File:   ColaPrioritaria.h
 * Author: Federico
 *
 * Created on November 24, 2014, 12:24 AM
 */

#ifndef COLAPRIORITARIA_H
#define	COLAPRIORITARIA_H

#include "aed2/TiposBasicos.h"
#include <stdlib.h>

using namespace aed2;

struct tuplaAB {
    Nat pri;
    Nat seg;

    tuplaAB(const tuplaAB& otra);

    tuplaAB(const Nat a, const Nat b);

    const bool operator<(const tuplaAB& otra) const;

    const bool operator>(const tuplaAB& otra) const;

    const bool operator==(const tuplaAB& otra) const;

};

class ColaP {
public:
    
    ColaP();
    
    ~ColaP();
    
    ColaP(const ColaP& otra);
    
    void Agregar(const Nat a, const Nat b);
    
    const bool Vacia() const;
    
    tuplaAB Desencolar();
    
    const Nat Tamanio() const;
    
    void Eliminar(Nat a, Nat b);
    
private:
    
    struct nodo {
        tuplaAB clave;
        nodo* padre;
        nodo* izq;
        nodo* der;
        Nat alt;
        
        nodo(const tuplaAB& clv);
        
        nodo(const Nat a, const Nat b);

        nodo(const nodo& otro);
        
        ~nodo();
        
    };
    
    struct e_cola {
        nodo* raiz;
        Nat tam;
        
        e_cola();
        
    };
    
    Nat SetAltura(const nodo* a);

    Nat FactorDesbalance(const nodo* a);
    
    nodo* MaximoEnSubarbol(nodo* a);

    nodo* HijoMasAlto(const nodo* a);

    nodo* Rotar(nodo* p1, nodo* p2, nodo* p3);

    void CIzq(nodo* a, nodo* b);

    void CDer(nodo* a, nodo* b);
    
    e_cola cola;
};

#endif	/* COLAPRIORITARIA_H */

