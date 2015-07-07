/* 
 * File:   DiccString.h
 * Author: Federico
 *
 * Created on November 20, 2014, 9:34 PM
 */

#ifndef DICCSTRING_H
#define	DICCSTRING_H

#include "aed2/TiposBasicos.h"
#include "aed2/Arreglo.h"


using namespace aed2;

template<typename T>
class DiccString {
public:
    DiccString();
    
    DiccString(const DiccString<T>& orig);
    
    ~DiccString();
    
    void Definir(const String& clv, const T& def);
    
    bool Definido(const String& clv) const;
    
    // PRE: La clave tiene que estar definida.
    T& Significado(const String& clv);
    
private:
    struct e_nodo {
        T* definicion;
        Arreglo<e_nodo*> hijos;
        
        e_nodo() : definicion(NULL), hijos(256) {
            for(Nat i = 0; i <= 255; i++) {
                hijos.Definir(i, NULL);
            }
        }
        
        e_nodo(const e_nodo& otro) : definicion(NULL), hijos(256) {
            for(Nat i = 0; i <= 255; i++) {
                hijos.Definir(i, NULL);
            }
            if (otro.definicion != NULL) definicion = new T(*otro.definicion);
            for (Nat i = 0; i <= 255; i++) {
                if (otro.hijos[i] != NULL) {
//                    e_nodo* copiaNodo = new e_nodo(*otro.hijos[i]);
//                    hijos[i] = new e_nodo(*otro.hijos[i]);
                    hijos.Definir(i, new e_nodo(*otro.hijos[i]));
                }
            }
        }

        ~e_nodo() {

            if (definicion != NULL) {
                delete definicion;
            }

            for (Nat i = 0; i <= 255; i++) {
                if (hijos[i] != NULL) {
                    delete hijos[i];
                }
            }
        }
    };
    
    e_nodo* raiz;
};

template<typename T>
DiccString<T>::DiccString() : raiz(new e_nodo()) {
}

template<typename T>
DiccString<T>::DiccString(const DiccString<T>& orig) : raiz(new e_nodo(*(orig.raiz))) {
}

template<typename T>
DiccString<T>::~DiccString() {
    delete raiz;
}

template<typename T>
void DiccString<T>::Definir(const String& clv, const T& def) {
    e_nodo* actual = raiz;
    for(int i = 0; i < clv.length(); i++) {
        if(actual -> hijos[clv[i]] == NULL) {
            actual -> hijos.Definir(clv[i], new e_nodo());
        }
        actual = actual -> hijos[clv[i]];
    }
    actual -> definicion = new T(def);
}

template<typename T>
bool DiccString<T>::Definido(const String& clv) const {
    const e_nodo* actual = raiz;
    for(int i = 0; i < clv.length(); i++) {
        if(actual -> hijos[clv[i]] != NULL) {
            actual = actual -> hijos[clv[i]];
        } else {
            return false;
        }
    }
    return actual -> definicion != NULL;
}

template<typename T>
T& DiccString<T>::Significado(const String& clv) {
    e_nodo* actual =  raiz;
    for(int i = 0; i < clv.length(); i++) {
        actual = actual -> hijos[clv[i]];
    }
    return *(actual -> definicion);
}

#endif	/* DICCSTRING_H */