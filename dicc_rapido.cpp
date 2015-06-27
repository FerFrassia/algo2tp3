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
				
			}
		}
	}
}



