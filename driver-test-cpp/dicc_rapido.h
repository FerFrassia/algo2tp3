#ifndef DICCRAPIDO_H_
#define DICCRAPIDO_H_

#include "aed2/Lista.h"
#include "aed2/Conj.h"
#include "aed2/TiposBasicos.h"
#include <stdlib.h>

using namespace aed2;

template<class Tc, class Ts>
class DiccRapido {
	public:

		class ITClave;

		DiccRapido();

		~DiccRapido();

		DiccRapido(const DiccRapido& otro);

		const bool Def(const Tc& c) const;

		Ts& Obtener(const Tc& c);

		void Definir(const Tc& c, const Ts& s);

		void Borrar(const Tc& c);

		const bool Vacio() const;

		Tc& ClaveMax() const;

		ITClave Claves() const;

		//iterador de clave
		class ITClave {
			public:

				ITClave();

				~ITClave();

				ITClave(const ITClave& otro);	

				const bool HayMas() const;

				Tc& ClaveActual() const;

				void Avanzar();

			private:

				struct e_estr {

					Nat nivelActual;
					Nat nodosRecorridos;
					Nat tam;
					typename DiccRapido<Tc, Ts>::nodo* nodoActual;
					typename DiccRapido<Tc, Ts>::nodo* raiz;

					e_estr();
				};

				const Lista<Tc> Siguientes() const;
		};


	private:

		struct nodo {
			Tc& clave;
			Ts& significado;
			nodo* padre;
			nodo* izq;
			nodo* der;
			Nat alt;

		nodo(const Tc& clv, const Ts& sig);

		~nodo();

		nodo(const nodo& otro);

		const bool operator < (const nodo& otro) const;

		const bool operator > (const nodo& otro) const;

		const bool operator == (const nodo& otro) const;

		};

		struct e_estr {
			nodo* raiz;
			Nat tam;

			e_estr();
		};

	Conj<nodo> DameNodos(const nodo* p, Nat actual, const Nat destino) const;

	void Rotar(nodo* p);

	void RotarSimpleIzq(nodo* p);

	void RotarSimpleDer(nodo* p);

	void RotarDobleIzq(nodo* p);

	void RotarDobleDer(nodo* p);

	Nat Altura(const nodo* p) const;

	Nat FactorDesbalance(const nodo* p) const; 

};


//ALGORITMOS


//metodos nodo

template<class Tc, class Ts>
DiccRapido<Tc, Ts>::nodo::nodo(const Tc& c, const Ts& s) {
	clave = c;
	significado = s;
	padre = NULL;
	izq = NULL;
	der = NULL;
	alt = 1;
}

template<class Tc, class Ts>
DiccRapido<Tc, Ts>::nodo::nodo(const nodo& otro) : clave(otro.clave), significado(otro.significado), padre(otro.padre), izq(NULL), der(NULL) {
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

template<class Tc, class Ts>
DiccRapido<Tc, Ts>::nodo::~nodo() {
	if (izq != NULL) {
		delete izq;
	}
	if (der != NULL) {
		delete der;
	}
}

//metodos e_estr (DiccRapido)
template<class Tc, class Ts>
DiccRapido<Tc, Ts>::e_estr::e_estr() {
	raiz = NULL;
	tam = 0;
}

//metodos publicos DiccRapido
template<class Tc, class Ts>
DiccRapido<Tc, Ts>::DiccRapido() {
}

template<class Tc, class Ts>
DiccRapido<Tc, Ts>::~DiccRapido() {
	delete this->raiz;
}

template<class Tc, class Ts>
DiccRapido<Tc, Ts>::DiccRapido(const DiccRapido<Tc, Ts>& otro) {
	if(otro.raiz != NULL) {
		this->raiz = new nodo(*otro.raiz);
		this->tam = otro.tam;
	}
}

template<class Tc, class Ts>
const bool DiccRapido<Tc, Ts>::Def(const Tc& c) const {
	nodo* pNodo = this->raiz;
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

template<class Tc, class Ts>
Ts& DiccRapido<Tc, Ts>::Obtener(const Tc& c) {
	nodo* pNodo = this->raiz;
	while (*(pNodo).clave != c) {
		if (c > *(pNodo).clave) {
			pNodo = *(pNodo).der;
		} else {
			pNodo = *(pNodo).izq;
		}
	}
	return *(pNodo).significado;
}

template<class Tc, class Ts>
void DiccRapido<Tc, Ts>::Definir(const Tc& c, const Ts& s) {
	if (this->raiz = NULL) {
		this->raiz = new nodo(c, s);
		this->tam = 1;
	} else {
		if (this.Def(c)) {
			nodo* pNodo = this->raiz;
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
			nodo* pNodo = this->raiz;
			while (seguir == true) {
				if (c > *(pNodo).clave && *(pNodo).der == NULL) {
					*(pNodo).der = &tupla(c, s, pNodo, NULL, NULL, 1);
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
			this->tam = this->tam + 1;
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

template<class Tc, class Ts>
void DiccRapido<Tc, Ts>::Borrar(const Tc& c) {
	nodo* pNodo = this->raiz;
	nodo* nuevoPNodo = NULL;
	while (c != *(pNodo).clave) {
		if (c > *(pNodo).clave) {
			pNodo = *(pNodo).der;
		} else {
			pNodo = *(pNodo).izq;
		}
	}
	if(*(pNodo).izq == NULL && *(pNodo).der == NULL) {
		if (*(pNodo).padre == NULL) {
			this->raiz = NULL;
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
				this->raiz = *(pNodo).der;
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
					this->raiz = *(pNodo).izq;
				} else {
					if (pNodo == *(*(pNodo).padre).izq) {
						*(*(pNodo).padre).izq = *(pNodo).izq;
					} else {
						*(*(pNodo).padre).der = *(pNodo).izq;
					}
					*(*(pNodo).izq).padre = *(pNodo).padre;
				}
			} else {
				nuevoPNodo = *(pNodo).der;
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
	this->tam = this->tam - 1;
	if (nuevoPNodo != NULL) {
		pNodo = *(nuevoPNodo).padre;
	}
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

template<class Tc, class Ts>
const bool DiccRapido<Tc, Ts>::Vacio() const {
	if (this->raiz == NULL) {
		return true;
	} else {
		return false;
	}
}

template<class Tc, class Ts>
Tc& DiccRapido<Tc, Ts>::ClaveMax() const {
	nodo* pNodo = this->raiz;
	while (*(pNodo).der != NULL) {
		pNodo = *(pNodo).der;
	}
	return *(pNodo).clave;
}

template<class Tc, class Ts>
typename DiccRapido<Tc, Ts>::ITClave DiccRapido<Tc, Ts>::Claves() const {
	return ITClave();
}

//metodos privados de DiccRapido
template<class Tc, class Ts>
Conj DiccRapido<Tc, Ts>::DameNodos(const nodo* p, Nat actual, const Nat destino) const {
	Conj<nodo> res = Conj();
	if (p != NULL) {
		if (actual == destino) {
			res.Agregar(p);
		} else {
			Union(DameNodos(*(p).izq, actual + 1, destino), DameNodos(*(p).der, actual + 1, destino));
		}
	}
	return res;
}

template<class Tc, class Ts>
void DiccRapido<Tc, Ts>::Rotar(nodo* p) {
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

template<class Tc, class Ts>
void DiccRapido<Tc, Ts>::RotarSimpleIzq(nodo* p) {
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

template<class Tc, class Ts>
void DiccRapido<Tc, Ts>::RotarSimpleDer(nodo* p) {
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

template<class Tc, class Ts>
void DiccRapido<Tc, Ts>::RotarDobleIzq(nodo* p) {
	RotarSimpleDer(*(p).der);
	RotarSimpleIzq(p);
}

template<class Tc, class Ts>
void DiccRapido<Tc, Ts>::RotarDobleDer(nodo* p) {
	RotarSimpleIzq(*(p).izq);
	RotarSimpleDer(p);
}

template<class Tc, class Ts>
Nat DiccRapido<Tc, Ts>::Altura(const nodo* p) const {
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

template<class Tc, class Ts>
Nat DiccRapido<Tc, Ts>::FactorDesbalance(const nodo* p) const {
	if (*(p).izq == NULL && *(p).der == NULL) {
		return 0;
	} else {
		if (*(p).izq != NULL && *(p).der == NULL) {
			return *(*(p).izq).alt;
		} else {
			if (*(p).izq == NULL && *(p).der != NULL) {
				return -*(*(p).der).alt;
			} else {
				return *(*(p).izq).alt - *(*(p).der).alt;
			}
		}
	}
}

//metodos e_estr (ITClave)
template<class Tc, class Ts>
DiccRapido<Tc, Ts>::ITClave::e_estr::e_estr() {
	nivelActual = 1;
	nodosRecorridos = 0;
	tam = 0;
	nodoActual = NULL;
	nodoActual = NULL;
}

//metodos publicos de ITClave
template<class Tc, class Ts>
ITClave::ITClave() : it() {
}

template<class Tc, class Ts>
ITClave::~ITClave() {
	delete it.nodoActual;
}

template<class Tc, class Ts>
ITClave::ITClave(const ITClave& otro) {
//	if(otro.dicc.raiz != NULL) dicc.raiz = new Nodo(*otro.dicc.raiz);
//	dicc.tam = otro.dicc.tam;
}

template<class Tc, class Ts>
const bool ITClave::HayMas() const {
	if (it.nodosRecorridos < it.tam - 1) {
		return true;
	} else {
		return false;
	}
}

template<class Tc, class Ts>
T& c ITClave::ClaveActual() const {
	return *(it.nodoActual).clave;
}

template<class Tc, class Ts>
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
template<class Tc, class Ts>
const Lista ITClave::Siguientes() const {
	ITClave itVar = it;
	Lista siguientes = Lista();
	while (HayMas(itVar)) {
		siguientes.AgregarAtras(ClaveActual(itVar));
		Avanzar(it);
	}
	return siguientes;
}

#endif


