//
// Created by Sebastián on 28/06/2015.
//

#ifndef TP3___IMPLEMENTACION_TIPOSSIMPLES_H
#define TP3___IMPLEMENTACION_TIPOSSIMPLES_H

#include "aed2/TiposBasicos.h"
#include "aed2/Conj.h"

namespace aed2 {

    typedef String Hostname;
    typedef Nat Interfaz;

    struct Compu {
        Hostname hostname;
        Conj<Interfaz> interfaces;

        Compu() : hostname(), interfaces() {};
        Compu(Hostname h , Conj<Interfaz> ci ) : hostname(h), interfaces(ci) {}

        const bool operator==(const Compu &otra) const {
            return (hostname == otra.hostname) && (interfaces == otra.interfaces);
        }

        const bool operator!=(const Compu &otra) const {
            return !((hostname == otra.hostname) && (interfaces == otra.interfaces));

            
        }

    };

    struct _Paquete {
        Nat id;
        Nat prioridad;
        Compu origen;
        Compu destino;

        _Paquete() : id(), prioridad(),origen(),destino() {};

        _Paquete(Nat& i, Nat& p, Compu& o,Compu& d ) : id(i) , prioridad(p), origen(o), destino(d) {};

        const bool operator==(const _Paquete &otra) const {
            return (id == otra.id);
        }

        const bool operator!=(const _Paquete &otra) const {
            return (id != otra.id);
        }

        const bool operator<(const _Paquete &otra) const {
            return (id < otra.id);
        }

        const bool operator>(const _Paquete &otra) const {
            return (id > otra.id);
        }
    };


} // namespace aed2


#endif //TP3___IMPLEMENTACION_TIPOSSIMPLES_H
