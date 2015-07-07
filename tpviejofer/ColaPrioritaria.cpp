#include "aed2/TiposBasicos.h"
#include <stdlib.h>
#include "ColaPrioritaria.h"

using namespace aed2;

// METODOS tuplaAB

tuplaAB::tuplaAB(const tuplaAB& otra) {
    pri = otra.pri;
    seg = otra.seg;
}

tuplaAB::tuplaAB(const Nat a, const Nat b) {
    pri = a;
    seg = b;
}

const bool tuplaAB::operator<(const tuplaAB& otra) const {
    if (pri < otra.pri) {
        return true;
    } else if (pri == otra.pri) {
        return seg < otra.seg;
    } else {
        return false;
    }
}

const bool tuplaAB::operator>(const tuplaAB& otra) const {
    if (pri > otra.pri) {
        return true;
    } else if (pri == otra.pri) {
        return seg > otra.seg;
    } else {
        return false;
    }
}

const bool tuplaAB::operator==(const tuplaAB& otra) const {
    return (pri == otra.pri) && (seg == otra.seg);
}

// METODOS nodo

ColaP::nodo::nodo(const tuplaAB& clv) : clave(clv) {
    padre = NULL;
    izq = NULL;
    der = NULL;
    alt = 1;
}

ColaP::nodo::nodo(const Nat a, const Nat b) : clave(a, b) {
    padre = NULL;
    izq = NULL;
    der = NULL;
    alt = 1;
}

ColaP::nodo::nodo(const nodo& otro) : clave(otro.clave), padre(NULL), izq(NULL), der(NULL) {
    if (otro.izq != NULL) {
        izq = new nodo(*otro.izq);
        izq -> padre = this;
    }
    if (otro.der != NULL) {
        der = new nodo(*otro.der);
        der -> padre = this;
    }
    alt = otro.alt;
}

ColaP::nodo::~nodo() {
    if (izq != NULL) {
        delete izq;
    }
    if (der != NULL) {
        delete der;
    }
}

// METODOS e_cola

        ColaP::e_cola::e_cola() {
            raiz = NULL;
            tam = 0;
        }

// METODOS PRIVADOS CLASE ColaP        

Nat ColaP::SetAltura(const nodo* a) {
    if (a -> izq == NULL) {
        if (a -> der == NULL) {
            return 1;
        } else {
            return 1 + a -> der -> alt;
        }
    } else {
        if (a -> der == NULL) {
            return 1 + a -> izq -> alt;
        } else {
            if (a -> izq -> alt > a -> der -> alt) {
                return 1 + a -> izq -> alt;
            } else {
                return 1 + a -> der -> alt;
            }
        }
    }
}

Nat ColaP::FactorDesbalance(const nodo* a) {
    if (a -> izq == NULL) {
        if (a -> der == NULL) {
            return 0;
        } else {
            return -(a -> der -> alt);
        }
    } else {
        if (a -> der == NULL) {
            return a -> izq -> alt;
        } else {
            return a -> izq -> alt - a-> der -> alt;
        }
    }
}

ColaP::nodo* ColaP::MaximoEnSubarbol(nodo* a) {
    nodo* nodoActual = a;
    while ((nodoActual -> der) != NULL) {
        nodoActual = nodoActual -> der;
    }
    return nodoActual;
}

ColaP::nodo* ColaP::HijoMasAlto(const nodo* a) {
    if (a -> izq == NULL) {
        return a -> der;
    } else if (a -> der == NULL) {
        return a -> izq;
    } else if ((a -> izq -> alt) >= (a -> der -> alt)) {
        return a -> izq;
    } else {
        return a -> der;
    }
}

ColaP::nodo* ColaP::Rotar(nodo* p1, nodo* p2, nodo* p3) {
    nodo* temp1 = NULL;
    nodo* temp2 = NULL;
    nodo* temp3 = NULL;
    if ((p3 -> clave < p1 -> clave) && (p1 -> clave < p2 -> clave)) {
        temp1 = p3;
        temp2 = p1;
        temp3 = p2;
    }
    if ((p3 -> clave > p1 -> clave) && (p1 -> clave > p2 -> clave)) {
        temp1 = p2;
        temp2 = p1;
        temp3 = p3;
    }
    if ((p3 -> clave < p2 -> clave) && (p2 -> clave < p1 -> clave)) {
        temp1 = p3;
        temp2 = p2;
        temp3 = p1;
    }
    if ((p3 -> clave > p2 -> clave) && (p2 -> clave > p1 -> clave)) {
        temp1 = p1;
        temp2 = p2;
        temp3 = p3;
    }
    if (cola.raiz == p3) {
        cola.raiz = temp2;
        temp2 -> padre = NULL;
    } else {
        if (p3 -> padre -> izq == p3) {
            CIzq(p3 -> padre, temp2);
        } else {
            CDer(p3 -> padre, temp2);
        }
    }
    if ((temp2 -> izq != p1) && (temp2 -> izq != p2) && (temp2 -> izq != p3)) {
        CDer(temp1, temp2 -> izq);
    }
    if ((temp2 -> der != p1) && (temp2 -> der != p2) && (temp2 -> der != p3)) {
        CIzq(temp3, temp2 -> der);
    }
    CIzq(temp2, temp1);
    CDer(temp2, temp3);
    return temp2;
}

void ColaP::CIzq(nodo* a, nodo* b) {
    a -> izq = b;
    if (b != NULL) b -> padre = a;
}

void ColaP::CDer(nodo* a, nodo* b) {
    a -> der = b;
    if (b != NULL) b -> padre = a;
}

// METODOS PUBLICOS CLASE ColaP

ColaP::ColaP() : cola() {
}

ColaP::~ColaP() {
    delete cola.raiz;
}

ColaP::ColaP(const ColaP& otra) {
    if(otra.cola.raiz != NULL) cola.raiz = new nodo(*otra.cola.raiz);
    cola.tam = otra.cola.tam;
}

void ColaP::Agregar(const Nat a, const Nat b) {
    if (cola.raiz == NULL) {
        cola.raiz = new nodo(a, b);
        cola.tam = 1;
    } else {
        tuplaAB nClave = tuplaAB(a, b);
        nodo* nodoActual = cola.raiz;
        while (true) {
            if (nClave > nodoActual -> clave) {
                if (nodoActual -> der != NULL) {
                    nodoActual = nodoActual -> der;
                } else {
                    nodo* nuevoNodo = new nodo(nClave);
                    nuevoNodo -> padre = nodoActual;
                    nodoActual -> der = nuevoNodo;
                    nodoActual = nuevoNodo;
                    break;
                }
            } else {
                if (nodoActual -> izq != NULL) {
                    nodoActual = nodoActual -> izq;
                } else {
                    nodo* nuevoNodo = new nodo(nClave);
                    nuevoNodo -> padre = nodoActual;
                    nodoActual -> izq = nuevoNodo;
                    nodoActual = nuevoNodo;
                    break;
                }
            }
        }
        cola.tam++;
        while (nodoActual != NULL) {
            nodoActual -> alt = SetAltura(nodoActual);
            if (abs(FactorDesbalance(nodoActual)) > 1) {
                nodoActual = Rotar(HijoMasAlto(HijoMasAlto(nodoActual)), HijoMasAlto(nodoActual), nodoActual);
                nodoActual -> izq -> alt = SetAltura(nodoActual -> izq);
                nodoActual -> der -> alt = SetAltura(nodoActual -> der);
                nodoActual -> alt = SetAltura(nodoActual);
                break;
            }
            nodoActual = nodoActual -> padre;
        }
    }
}

void ColaP::Eliminar(Nat a, Nat b) {
    tuplaAB eClave = tuplaAB(a, b);
    nodo* nodoActual = cola.raiz;
    while (nodoActual != NULL) {
        if (eClave == nodoActual -> clave) {
            break;
        } else {
            if (eClave > nodoActual -> clave) {
                nodoActual = nodoActual -> der;
            } else {
                nodoActual = nodoActual -> izq;
            }
        }
    }
    if (nodoActual != NULL) {
        nodo* nodosAntecesores = nodoActual -> padre;
        if ((nodoActual -> izq == NULL) && (nodoActual -> der == NULL)) {
            if (nodoActual == cola.raiz) {
                cola.raiz = NULL;
            } else {
                if (nodoActual -> padre -> izq == nodoActual) {
                    nodoActual -> padre -> izq = NULL;
                } else {
                    nodoActual -> padre -> der = NULL;
                }
            }
            nodoActual -> izq = NULL;
            nodoActual -> der = NULL;
            nodoActual -> padre = NULL;
            delete nodoActual;
        } else if ((nodoActual -> izq != NULL) && (nodoActual -> der == NULL)) {
            if (nodoActual == cola.raiz) {
                cola.raiz = nodoActual -> izq;
                nodoActual -> izq -> padre = NULL;
            } else {
                if (nodoActual -> padre -> izq == nodoActual) {
                    nodoActual -> izq -> padre = nodoActual -> padre;
                    nodoActual -> padre -> izq = nodoActual -> izq;
                } else {
                    nodoActual -> izq -> padre = nodoActual -> padre;
                    nodoActual -> padre -> der = nodoActual -> izq;
                }
            }
            nodoActual -> izq = NULL;
            nodoActual -> der = NULL;
            nodoActual -> padre = NULL;
            delete nodoActual;
        } else if ((nodoActual -> izq == NULL) && (nodoActual -> der != NULL)) {
            if (nodoActual == cola.raiz) {
                cola.raiz = nodoActual -> der;
                nodoActual -> der -> padre = NULL;
            } else {
                if (nodoActual -> padre -> izq == nodoActual) {
                    nodoActual -> der -> padre = nodoActual -> padre;
                    nodoActual -> padre -> izq = nodoActual -> der;
                } else {
                    nodoActual -> der -> padre = nodoActual -> padre;
                    nodoActual -> padre -> der = nodoActual -> der;
                }
            }
            nodoActual -> izq = NULL;
            nodoActual -> der = NULL;
            nodoActual -> padre = NULL;
            delete nodoActual;
        } else if ((nodoActual -> izq != NULL) && (nodoActual -> der != NULL)) {
            nodo* nodoMax = MaximoEnSubarbol(nodoActual -> izq);
            tuplaAB sClave = tuplaAB(nodoMax -> clave);
            this->Eliminar(nodoMax -> clave.pri, nodoMax -> clave.seg);
            nodoActual -> clave = sClave;
            cola.tam++;
        }
        cola.tam--;
        while (nodosAntecesores != NULL) {
            nodosAntecesores -> alt = SetAltura(nodosAntecesores);
            if (abs(FactorDesbalance(nodosAntecesores)) > 1) {
                nodosAntecesores = Rotar(HijoMasAlto(HijoMasAlto(nodosAntecesores)), HijoMasAlto(nodosAntecesores), nodosAntecesores);
                nodosAntecesores -> izq -> alt = SetAltura(nodosAntecesores -> izq);
                nodosAntecesores -> der -> alt = SetAltura(nodosAntecesores -> der);
                nodosAntecesores -> alt = SetAltura(nodosAntecesores);
            }
            nodosAntecesores = nodosAntecesores -> padre;
        }
    }
}

tuplaAB ColaP::Desencolar() {
    tuplaAB maximo = (MaximoEnSubarbol(cola.raiz) -> clave);
    this->Eliminar(maximo.pri, maximo.seg);
    return maximo;
}

const Nat ColaP::Tamanio() const {
    return cola.tam;
}

const bool ColaP::Vacia() const {
    return cola.raiz != NULL;
}