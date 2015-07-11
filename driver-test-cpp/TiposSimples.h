//
// Created by Sebasti�n on 28/06/2015.
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
        //Compu(const Hostname& h) : interfaces(new Conj<Interfaz>) {}
        //     const bool operator==(const Compu& otra) const;
        //    const bool operator!=(const Compu& otra) const;

        const bool operator==(const Compu &otra) const {
            return (hostname == otra.hostname) && (interfaces == otra.interfaces);
        }

        const bool operator!=(const Compu &otra) const {
            return !((hostname == otra.hostname) && (interfaces == otra.interfaces));
        }

    };


    struct Paquete {
        Nat id;
        Nat prioridad;
        Compu origen;
        Compu destino;
        //Paquete(const String& h) : interfaces(NULL) {}
        //         const bool operator==(const Paquete& otra) const;
        //        const bool operator!=(const Paquete& otra) const;
        //       const bool operator<(const Paquete& otra) const;
        //      const bool operator>(const Paquete& otra) const;

        const bool operator==(const Paquete &otra) const {
            return (id == otra.id);
        }

        const bool operator!=(const Paquete &otra) const {
            return (id != otra.id);
        }

        const bool operator<(const Paquete &otra) const {
            return (id < otra.id);
        }

        const bool operator>(const Paquete &otra) const {
            return (id > otra.id);
        }
    };


} // namespace aed2


#endif //TP3___IMPLEMENTACION_TIPOSSIMPLES_H
