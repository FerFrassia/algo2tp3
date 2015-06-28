#include "aed2/TiposBasicos.h"
#include <stdlib.h>
#include "dicc_rapido.h"

using namespace aed2;

//metodos nodo

DiccRapido::nodo::nodo(const Nat& clv, const Nat& sig) : clave(clv), significado(sig) {
	padre = NULL;
	izq = NULL;
	der = NULL;
	alt = 1;
}

DiccRapido::nodo::nodo(const nodo& otro) : clave(otro.clave), significado(otro.significado), padre(NULL), izq(NULL), der(NULL) {
	if (otro -> izq != NULL) {
		izq = new nodo(otro -> izq);
		izq -> padre = this; 
	}
	if (otro -> der != NULL) {
		der = new nodo(otro -> der);
		der -> padre = this;
	}
	alt = otro -> alt;
}

DiccRapido::nodo::~nodo() {
	if (izq != NULL) {
		delete izq;
	}
	if (der != NULL) {
		delete der;
	}
}

//metodos e_estr (DiccRapido)

DiccRapido::e_estr::e_estr() {
	raiz = NULL;
	tam = 0;
}
//metodos publicos DiccRapido

DiccRapido::DiccRapido() : dicc() {
}

DiccRapido::~DiccRapido() {
	delete dicc.raiz;
}

DiccRapido::DiccRapido(const DiccRapido& otro) {
	if(otro.dicc.raiz != NULL) dicc.raiz = new Nodo(*otro.dicc.raiz);
	dicc.tam = otro.dicc.tam;
}

const bool DiccRapido::Def(const Nat c) const {
	nodo* pNodo = dicc.raiz;
	while (pNodo != NULL) {
		if (*(pNodo).clave == c) {
			return true;
		} else {
		 	if (c > *(pNodo).clave) {
				pNodo = *(pNodo).der;
			} else {
				pNodo = *(pNodo).izq;
			}
		}
	}
	return false;
}

Nat s DiccRapido::Obtener(const Nat c) {
	nodo* pNodo = dicc.raiz;
	while (*(pNodo).clave != c) {
		if (c > *(pNodo).clave) {
			pNodo = *(pNodo).der;
		} else {
			pNodo = *(pNodo).izq;
		}
	}
	return *(pNodo).significado;
}

void DiccRapido::Definir(const Nat c, const Nat s) {
	if (dicc.raiz = NULL) {
		dicc.raiz = new nodo(c, s);
		dicc.tam = 1;
	} else {
		if (Def(c, d)) {
			nodo* pNodo = dicc.raiz;
			while (*(pNodo).clave != c) {
				if (c > *(pNodo).clave) {
					pNodo = *(pNodo).der;
				} else {
					pNodo = *(pNodo).izq;
				}
			}
		*(pNodo).significado = s;
		} else {
			bool seguir = true;
			nodo* pNodo = dicc.raiz;
			while (seguir == true) {
				if (c > *(pNodo).clave && *(pNodo).der == NULL) {
					*(pNodo).der = &tupla(c, s, pNodo, NULL, NULL, 1)
					seguir = false;
				} else {
					if (c > *(pNodo).clave && *(pNodo).der != NULL) {
						pNodo = *(pNodo).der;
					} else {
						if (c < *(pNodo).clave && *(pNodo).izq == NULL) {
							*(pNodo).izq = &tupla(c, s, pNodo, NULL, NULL, 1);
							seguir = false;
						} else {
							pNodo = *(pNodo).izq;
						}
					}
				}
			}
			dicc.tam = dicc.tam + 1;
			while (pNodo != NULL) {
				nodo* padrePNodo = *(pNodo).padre;
				if (abs(FactorDesbalance(pNodo)) > 1) {
					Rotar(pNodo);
				} else {
					*(pNodo).alt = Altura(pNodo);
				}
				pNodo = padrePNodo;
			}
		}
	}
}

void DiccRapido::Borrar(const Nat c) {
	nodo* pNodo = dicc.raiz;
	while (c != *(pNodo).clave) {
		if (c > *(pNodo).clave) {
			pNodo = *(pNodo).der;
		} else {
			pNodo = *(pNodo).izq;
		}
	}
	if(*(pNodo).izq == NULL && *(pNodo).der == NULL) {
		if (*(pNodo).padre == NULL) {
			dicc.raiz = NULL;
		} else {
			if (pNodo == *(*(pNodo).padre).izq) {
				*(*(pNodo).padre).izq = NULL;
			} else {
				*(*(pNodo).padre).der = NULL;
			}
		}
	} else {
		if (*(pNodo).izq == NULL && *(pNodo).der != NULL) {
			if (*(pNodo).padre == NULL) {
				*(*(pNodo).der).padre = NULL;
				dicc.raiz = *(pNodo).der;
			} else {
				if (pNodo == *(*(pNodo).padre).izq) {
					*(*(pNodo).padre).izq = *(pNodo).der;
				} else {
					*(*(pNodo).padre).der = *(pNodo).der;
				}
				*(*(pNodo).der).padre = *(pNodo).padre;
			}
		} else {
			if (*(pNodo).izq != NULL && *(pNodo).der == NULL) {
				if (*(pNodo).padre == NULL) {
					*(*(pNodo).izq).padre = NULL;
					dicc.raiz = *(pNodo).izq;
				} else {
					if (pNodo == *(*(pNodo).padre).izq) {
						*(*(pNodo).padre).izq = *(pNodo).izq;
					} else {
						*(*(pNodo).padre).der = *(pNodo).izq;
					}
					*(*(pNodo).izq).padre = *(pNodo).padre;
				}
			} else {
				*nodo nuevoPNodo = *(pNodo).der;
				while (*(nuevoPNodo).izq != NULL) {
					nuevoPNodo = *(nuevoPNodo).izq;
				}
				*(pNodo).clave = *(nuevoPNodo).clave;
				*(pNodo).significado = *(nuevoPNodo).significado;
				if (*(nuevoPNodo).der != NULL) {
					if (*(*(nuevoPNodo).padre).izq == nuevoPNodo) {
						*(*(nuevoPNodo).padre.izq) = *(nuevoPNodo).der; 
					} else {
						*(*(nuevoPNodo).padre).der = *(nuevoPNodo).der;
					}
					*(*(nuevoPNodo).der).padre = *(nuevoPNodo).padre;
				} else {
					if (*(*(nuevoPNodo).padre).izq == nuevoPNodo) {
						*(*(nuevoPNodo).padre).izq = NULL;
					} else {
						*(*(nuevoPNodo).padre).der = NULL;
					}
				}
			}
		}
	}
	dicc.tam = dicc.tam - 1;
	pNodo = *(nuevoPNodo).padre;
	while (pNodo != NULL) {
		nodo* padrePNodo = *(pNodo).padre;
		if (abs(FactorDesbalance(pNodo)) > 1) {
			Rotar(pNodo);
		} else {
			*(pNodo).alt = Altura(pNodo);
		}
		pNodo = padrePNodo;
	}
}

const bool DiccRapido::Vacio() const {
	if (dicc.raiz == NULL) {
		return true;
	} else {
		return false;
	}
}

Nat c DiccRapido::ClaveMax() const {
	nodo* pNodo = dicc.raiz;
	while (*(pNodo).der != NULL) {
		pNodo = *(pNodo).der;
	}
	return *(pNodo).clave;
}

ITClave DiccRapido::Claves() const {
	return CrearIT();
}

//metodos privados de DiccRapido

Conj DiccRapido::DameNodos(const nodo* p, Nat actual, const Nat destino) const {
	Conj res = Conj();
	if (p != NULL) {
		if (actual == destino) {
			res.Agregar(p);
		} else {
			Union(DameNodos(*(p).izq, actual + 1, destino), DameNodos(*(p).der, actual + 1, destino));
		}
	}
	return res;
}

void DiccRapido::Rotar(nodo* p) {
	if (FactorDesbalance(p) < -1) {
		if (FactorDesbalance(*(p).der) > 0) {
			return RotarDobleIzq(p);
		} else {
			return RotarSimpleIzq(p);
		} 
	} else {
		if (FactorDesbalance(*(p).izq) < 0) {
			return RotarDobleDer(p);
		} else {
			return RotarSimpleDer(p);
		}
	}
}

void DiccRapido::RotarSimpleIzq(nodo* p) {
	nodo* r = p;
	nodo* r2 = *(r).der;
	nodo* i = *(r).izq;
	nodo* i2 = *(r2).izq;
	nodo* d2 = *(r2).der;
	nodo* padre = *(r).padre;
	if (padre != NULL) {
		if (r == *(padre).izq) {
			*(padre).izq = r2;
		} else {
			*(padre).der = r2;
		}
	}
	*(r2).padre = padre;
	*(r2).izq = r;
	*(r).padre = r2;
	*(r).der = i2;
	if (i2 != NULL) {
		*(i2).padre = r;
	}
	*(r).alt = Altura(r);
	*(r2).alt = Altura(r2);
}

void DiccRapido::RotarSimpleDer(nodo* p) {
	nodo* r = p;
	nodo* r2 = *(r).izq;
	nodo* d = *(r).der;
	nodo* i2 = *(r2).izq;
	nodo* d2 = *(r2).der;
	nodo* padre = *(r).padre;
	if (padre != NULL) {
		if (r == *(padre).izq) {
			*(padre).izq = r2;
		} else {
			*(padre).der = r2;
		}
	}
	*(r2).padre = padre;
	*(r2).der = r;
	*(r).padre = r2;
	*(r).izq = d2;
	if (d2 != NULL) {
		*(d2).padre = r;
	}
	*(r).alt = Altura(r);
	*(r2).alt = Altura(r2);
}


void DiccRapido::RotarDobleIzq(nodo* p) {
	RotarSimpleDer(*(p).der);
	RotarSimpleIzq(p);
}

void DiccRapido::RotarDobleDer(nodo* p) {
	RotarSimpleIzq(*(p).izq);
	RotarSimpleDer(p);
}

Nat DiccRapido::Altura(const nodo* p) const {
	if (*(p).izq == NULL && *(p).der == NULL) {
		return 1;
	} else {
		if (*(p).izq != NULL *(p).der == NULL) {
			return *(*(p).izq).alt + 1;
		} else {
			if (*(p).izq == NULL && *(p).der != NULL) {
				return *(*(p).der).alt + 1;
			} else {
				return max(*(*(p).izq).alt, *(*(p).der).alt) + 1;
			}
		}
	}
}

Nat DiccRapido::FactorDesbalance(const nodo* p) const {
	if (*(p).izq == NULL && *(p).der == NULL) {
		return 0;
	} else {
		if (*(p).izq != NULL && *(p).der == NULL) {
			return *(*(p).izq).alt;
		} else {
			if (*(p).izq == NULL && *(p).der !== NULL) {
				return -*(*(p).der).alt;
			} else {
				return *(*(p).izq).alt - *(*(p).der).alt;
			}
		}
	}
}

//metodos e_estr (ITClave)

ITClave::e_estr::e_estr() {
	nivelActual = 1;
	nodosRecorridos = 0;
	tam = 0;
	nodoActual = NULL;
	nodoActual = NULL;
}

//metodos publicos de ITClave

ITClave::ITClave() : it() {
}

ITClave::~ITClave() {
	delete it.nodoActual;
}

ITClave::ITClave(const ITClave& otro) {
//	if(otro.dicc.raiz != NULL) dicc.raiz = new Nodo(*otro.dicc.raiz);
//	dicc.tam = otro.dicc.tam;
}

const bool ITClave::HayMas() const {
	if (it.nodosRecorridos < it.tam - 1) {
		return true;
	} else {
		return false;
	}
}

Nat c ITClave::ClaveActual() const {
	return *(it.nodoActual).clave;
}

void ITClaveAvanzar() {
	it.nodosRecorridos = it.nodosRecorridos + 1;
	itConj itNodosNivelActual = ITClave(DameNodos(it.raiz, 1, it.nivelActual));
	bool bAvanzar = true;
	while (bAvanzar) {
		Avanzar(itNodosNivelActual);
		if (Anterior(itNodosNivelActual) == Actual(it)) {
			bAvanzar = false;
		}
	}
	if (HaySiguiente(itNodosNivelActual)) {
		it.nodoActual = Siguiente(itNodosNivelActual);
	} else {
		it.nivelActual = it.nivelActual + 1;
		it.nodoActual = Siguiente(CrearIT(DameNodos(it.raiz, 1, it.nivelActual)));
	}
}

//metodos privados de ITClave

const Lista ITClave::Siguientes() const {
	ITClave itVar = it;
	Lista siguientes = Lista();
	while (HayMas(itVar)) {
		siguientes.AgregarAtras(ClaveActual(itVar));
		Avanzar(it);
	}
	return siguientes;
}



















	











