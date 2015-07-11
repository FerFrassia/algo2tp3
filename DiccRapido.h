#ifndef DICCRAPIDO_H_
#define DICCRAPIDO_H_

#include "aed2/Lista.h"
#include "aed2/Conj.h"
#include "aed2/TiposBasicos.h"
#include <stdlib.h>
#include <algorithm>

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

//BEGIN METODOS DE TESTING
		Tc& Raiz();

		Tc& HijoIzq(const Tc& c);

		Tc& HijoDer(const Tc& c);

		Tc& Padre(const Tc& c);
//FIN METODOS DE TESTING

		//iterador de clave
		class ITClave {
			public:

				ITClave(const DiccRapido<Tc, Ts>& dicc) ;

				~ITClave();

				ITClave(const ITClave& otro);	

				const bool HayMas() const;

				Tc& ClaveActual() const;

				void Avanzar();

			private:

				struct e_it {
					const DiccRapido<Tc, Ts>& diccIt;
					int nivelActual;
					int nodosRecorridos;
					int tam;
					typename DiccRapido<Tc, Ts>::Nodo* nodoActual;
					typename DiccRapido<Tc, Ts>::Nodo* raiz;
					e_it(const DiccRapido<Tc, Ts>& dicc): nivelActual(1), nodosRecorridos(0), tam(0), nodoActual(NULL), raiz(NULL), diccIt(dicc) {}
				};

				const Lista<Tc> Siguientes() const;

				e_it it;
		};


	private:

		struct Nodo {
			Tc clave;
			Ts significado;
			Nodo* padre;
			Nodo* izq;
			Nodo* der;
			int alt;

		Nodo(const Tc& c, const Ts& s);

		Nodo(const Nodo& otro);

		~Nodo();

		const bool operator < (const Nodo& otro) const {
			return (clave < otro.clave);
		}

		const bool operator > (const Nodo& otro) const {
			return (clave > otro.clave);
		}

		const bool operator == (const Nodo& otro) const {
			return (clave == otro.clave && significado == otro.significado && (*padre) == (*otro.padre) && (*izq) == (*otro.izq) && (*der) == (*otro.der) && alt == otro.alt);
		}

		const bool operator != (const Nodo& otro) const {
			return !(clave == otro.clave && significado == otro.significado && (*padre) == (*otro.padre) && (*izq) == (*otro.izq) && (*der) == (*otro.der) && alt == otro.alt);
		}

		};

		struct e_dicc {
			Nodo* raiz;
			int tam;

			e_dicc();
		};

		Conj<Tc> DameNodos(Nodo* p, int actual, const int destino) const;

		void Rotar(Nodo* p);

		void RotarSimpleIzq(Nodo* p);

		void RotarSimpleDer(Nodo* p);

		void RotarDobleIzq(Nodo* p);

		void RotarDobleDer(Nodo* p);

		int Altura(const Nodo* p) const;

		int FactorDesbalance(const Nodo* p) const;

		e_dicc dicc;

};


//ALGORITMOS


//metodos Nodo

template<class Tc, class Ts>
DiccRapido<Tc, Ts>::Nodo::Nodo(const Tc& c, const Ts& s) {
	clave = c;
	significado = s;
	padre = NULL;
	izq = NULL;
	der = NULL;
	alt = 1;
}

template<class Tc, class Ts>
DiccRapido<Tc, Ts>::Nodo::Nodo(const Nodo& otro) : clave(otro.clave), significado(otro.significado), padre(otro.padre), izq(NULL), der(NULL) {
	if (otro -> izq != NULL) {
		izq = new Nodo(otro -> izq);
		izq -> padre = dicc; 
	}
	if (otro -> der != NULL) {
		der = new Nodo(otro -> der);
		der -> padre = dicc;
	}
	alt = otro -> alt;
}

template<class Tc, class Ts>
DiccRapido<Tc, Ts>::Nodo::~Nodo() {
	if (izq != NULL) delete izq;
	if (der != NULL) delete der;
}

//metodos e_estr (DiccRapido)
template<class Tc, class Ts>
DiccRapido<Tc, Ts>::e_dicc::e_dicc() {
	raiz = NULL;
	tam = 0;
}

//metodos publicos DiccRapido
template<class Tc, class Ts>
DiccRapido<Tc, Ts>::DiccRapido() {
}

template<class Tc, class Ts>
DiccRapido<Tc, Ts>::~DiccRapido() {
	delete dicc.raiz;
}

template<class Tc, class Ts>
DiccRapido<Tc, Ts>::DiccRapido(const DiccRapido<Tc, Ts>& otro) {
	if(otro.raiz != NULL) {
		dicc.raiz = new Nodo(*otro.raiz);
		dicc.tam = otro.tam;
	}
}

template<class Tc, class Ts>
const bool DiccRapido<Tc, Ts>::Def(const Tc& c) const {
	Nodo* pNodo = dicc.raiz;
	while (pNodo != NULL) {
		if ((*pNodo).clave == c) {
			return true;
		} else {
		 	if (c > (*pNodo).clave) {
				pNodo = (*pNodo).der;
			} else {
				pNodo = (*pNodo).izq;
			}
		}
	}
	return false;
}

template<class Tc, class Ts>
Ts& DiccRapido<Tc, Ts>::Obtener(const Tc& c) {
	Nodo* pNodo = dicc.raiz;
	while ((*pNodo).clave != c) {
		if (c > (*pNodo).clave) {
			pNodo = (*pNodo).der;
		} else {
			pNodo = (*pNodo).izq;
		}
	}
	return (*pNodo).significado;
}

template<class Tc, class Ts>
void DiccRapido<Tc, Ts>::Definir(const Tc& c, const Ts& s) {
	if (dicc.raiz == NULL) {
		dicc.raiz = new Nodo(c, s);
		dicc.tam = 1;
	} else {
		if (Def(c)) {
			Nodo* pNodo = dicc.raiz;
			while ((*pNodo).clave != c) {
				if (c > (*pNodo).clave) {
					pNodo = (*pNodo).der;
				} else {
					pNodo = (*pNodo).izq;
				}
			}
		(*pNodo).significado = s;
		} else {
			bool seguir = true;
			Nodo* pNodo = dicc.raiz;
			while (seguir == true) {
				if (c > (*pNodo).clave && (*pNodo).der == NULL) {
					(*pNodo).der = new Nodo(c, s);
					(*(*pNodo).der).padre = pNodo;
					seguir = false;
				} else {
					if (c > (*pNodo).clave && (*pNodo).der != NULL) {
						pNodo = (*pNodo).der;
					} else {
						if (c < (*pNodo).clave && (*pNodo).izq == NULL) {
							(*pNodo).izq = new Nodo(c, s);
							(*(*pNodo).izq).padre = pNodo;
							seguir = false;
						} else {
							pNodo = (*pNodo).izq;
						}
					}
				}
			}
			dicc.tam = dicc.tam + 1;
			while (pNodo != NULL) {
				Nodo* padrePNodo = (*pNodo).padre;
				if (abs(FactorDesbalance(pNodo)) > 1) {
					Rotar(pNodo);
					//(*pNodo).alt = Altura(pNodo);
				} else {
					(*pNodo).alt = Altura(pNodo);
				}
				pNodo = padrePNodo;
			}
		}
	}
}

template<class Tc, class Ts>
void DiccRapido<Tc, Ts>::Borrar(const Tc& c) {
	Nodo* pNodo = dicc.raiz;
	Nodo* nuevoPNodo = NULL;
	Nodo* pNodo2 = NULL;
	while (c != (*pNodo).clave) {
		if (c > (*pNodo).clave) {
			pNodo = (*pNodo).der;
		} else {
			pNodo = (*pNodo).izq;
		}
	}
	if((*pNodo).izq == NULL && (*pNodo).der == NULL) {
		if ((*pNodo).padre == NULL) {
			dicc.raiz = NULL;
		} else {
			if (pNodo == (*((*pNodo).padre)).izq) {
				(*((*pNodo).padre)).izq = NULL;
			} else {
				(*((*pNodo).padre)).der = NULL;
			}
		}
	(*pNodo).padre = NULL;
	(*pNodo).izq = NULL;
	(*pNodo).der = NULL; 
	delete pNodo;
	} 
	 else {
		if ((*pNodo).izq == NULL && (*pNodo).der != NULL) {
			if ((*pNodo).padre == NULL) {
				(*((*pNodo).der)).padre = NULL;
				dicc.raiz = (*pNodo).der;
			} else {
				if (pNodo == (*((*pNodo).padre)).izq) {
					(*((*pNodo).padre)).izq = (*pNodo).der;
				} else {
					(*((*pNodo).padre)).der = (*pNodo).der;
				}
				(*(*pNodo).der).padre = (*pNodo).padre;
			}
		(*pNodo).padre = NULL;
		(*pNodo).izq = NULL;
		(*pNodo).der = NULL; 
		delete pNodo;
		} else {
			if ((*pNodo).izq != NULL && (*pNodo).der == NULL) {
				if ((*pNodo).padre == NULL) {
					(*(*pNodo).izq).padre = NULL;
					dicc.raiz = (*pNodo).izq;
				} else {
					if (pNodo == (*((*pNodo).padre)).izq) {
						(*((*pNodo).padre)).izq = (*pNodo).izq;
					} else {
						(*((*pNodo).padre)).der = (*pNodo).izq;
					}
					(*((*pNodo).izq)).padre = (*pNodo).padre;
				}
			(*pNodo).padre = NULL;
			(*pNodo).izq = NULL;
			(*pNodo).der = NULL; 
			delete pNodo;	
			} else {
				nuevoPNodo = (*pNodo).der;
				while ((*nuevoPNodo).izq != NULL) {
					nuevoPNodo = (*nuevoPNodo).izq;
				}
				(*pNodo).clave = (*nuevoPNodo).clave;
				(*pNodo).significado = (*nuevoPNodo).significado;
				if ((*nuevoPNodo).der != NULL) {
					if ((*((*nuevoPNodo).padre)).izq == nuevoPNodo) {
						(*((*nuevoPNodo).padre)).izq = (*nuevoPNodo).der; 
					} else {
						(*((*nuevoPNodo).padre)).der = (*nuevoPNodo).der;
					}
					(*((*nuevoPNodo).der)).padre = (*nuevoPNodo).padre;
				} else {
					if ((*((*nuevoPNodo).padre)).izq == nuevoPNodo) {
						(*((*nuevoPNodo).padre)).izq = NULL;
					} else {
						(*((*nuevoPNodo).padre)).der = NULL;
					}
				}
			pNodo2 = (*nuevoPNodo).padre;
			(*nuevoPNodo).padre = NULL;
			(*nuevoPNodo).izq = NULL;
			(*nuevoPNodo).der = NULL; 
			delete nuevoPNodo;
			}
		}
	}
	dicc.tam = dicc.tam - 1;
	while (pNodo2 != NULL) {
		Nodo* padrePNodo = (*pNodo2).padre;
		if (abs(FactorDesbalance(pNodo2)) > 1) {
			Rotar(pNodo2);
		} else {
			(*pNodo2).alt = Altura(pNodo2);
		}
		pNodo2 = padrePNodo;
	}	
}

template<class Tc, class Ts>
const bool DiccRapido<Tc, Ts>::Vacio() const {
	if (dicc.raiz == NULL) {
		return true;
	} else {
		return false;
	}
}

template<class Tc, class Ts>
Tc& DiccRapido<Tc, Ts>::ClaveMax() const {
	Nodo* pNodo = dicc.raiz;
	while ((*pNodo).der != NULL) {
		pNodo = (*pNodo).der;
	}
	return (*pNodo).clave;
}

//BEGIN METODOS DE TESTING
template<class Tc, class Ts>
Tc& DiccRapido<Tc, Ts>::Raiz() {
	return (*dicc.raiz).clave;
}

template<class Tc, class Ts>
Tc& DiccRapido<Tc, Ts>::HijoIzq(const Tc& c) {
	Nodo* pNodo = dicc.raiz;
	while ((*pNodo).clave != c) {
		if (c > (*pNodo).clave) {
			pNodo = (*pNodo).der;
		} else {
			pNodo = (*pNodo).izq;
		}
	}
	return (*(*pNodo).izq).clave;
}

template<class Tc, class Ts>
Tc& DiccRapido<Tc, Ts>::HijoDer(const Tc& c) {
		Nodo* pNodo = dicc.raiz;
	while ((*pNodo).clave != c) {
		if (c > (*pNodo).clave) {
			pNodo = (*pNodo).der;
		} else {
			pNodo = (*pNodo).izq;
		}
	}
	return (*(*pNodo).der).clave;
}

template<class Tc, class Ts>
Tc& DiccRapido<Tc, Ts>::Padre(const Tc& c) {
		Nodo* pNodo = dicc.raiz;
	while ((*pNodo).clave != c) {
		if (c > (*pNodo).clave) {
			pNodo = (*pNodo).der;
		} else {
			pNodo = (*pNodo).izq;
		}
	}
	return (*(*pNodo).padre).clave;
}
//FIN METODOS DE TESTING

template<class Tc, class Ts>
typename DiccRapido<Tc, Ts>::ITClave DiccRapido<Tc, Ts>::Claves() const {
	return ITClave(*this);
}

//metodos privados de DiccRapido
template<class Tc, class Ts>
Conj<Tc> DiccRapido<Tc, Ts>::DameNodos(Nodo* p, int actual, const int destino) const {
	Conj<Tc> res;
	//Conj<typename DiccRapido<Tc, Ts>::Nodo*> res = *(new  Conj<typename DiccRapido<Tc, Ts>::Nodo*>());
	if (p != NULL) {
		if (actual == destino) {
			res.Agregar(((*p).clave));
		} else {
			(DameNodos((*p).izq, actual + 1, destino)).Union(DameNodos((*p).der, actual + 1, destino));
		}
	}
	return res;
}

template<class Tc, class Ts>
void DiccRapido<Tc, Ts>::Rotar(Nodo* p) {
	if (FactorDesbalance(p) < -1) {
		if (FactorDesbalance((*p).der) > 0) {
			RotarDobleIzq(p);
		} else {
			RotarSimpleIzq(p);
		} 
	} else {
		if (FactorDesbalance((*p).izq) < 0) {
			RotarDobleDer(p);
		} else {
			RotarSimpleDer(p);
		}
	}
}

template<class Tc, class Ts>
void DiccRapido<Tc, Ts>::RotarSimpleIzq(Nodo* p) {
	Nodo* r = p;
	Nodo* r2 = (*r).der;
	Nodo* i = (*r).izq;
	Nodo* i2 = (*r2).izq;
	Nodo* d2 = (*r2).der;
	Nodo* padre = (*r).padre;
	if (padre != NULL) {
		if (r == (*padre).izq) {
			(*padre).izq = r2;
		} else {
			(*padre).der = r2;
		}
	} else {
		dicc.raiz = r2;
	}
	(*r2).padre = padre;
	(*r2).izq = r;
	(*r).padre = r2;
	(*r).der = i2;
	if (i2 != NULL) {
		(*i2).padre = r;
	}
	(*r).alt = Altura(r);
	(*r2).alt = Altura(r2);

}

template<class Tc, class Ts>
void DiccRapido<Tc, Ts>::RotarSimpleDer(Nodo* p) {
	Nodo* r = p;
	Nodo* r2 = (*r).izq;
	Nodo* d = (*r).der;
	Nodo* i2 = (*r2).izq;
	Nodo* d2 = (*r2).der;
	Nodo* padre = (*r).padre;
	if (padre != NULL) {
		if (r == (*padre).izq) {
			(*padre).izq = r2;
		} else {
			(*padre).der = r2;
		}
	} else {
		dicc.raiz = r2;
	}
	(*r2).padre = padre;
	(*r2).der = r;
	(*r).padre = r2;
	(*r).izq = d2;
	if (d2 != NULL) {
		(*d2).padre = r;
	}
	(*r).alt = Altura(r);
	(*r2).alt = Altura(r2);
}

template<class Tc, class Ts>
void DiccRapido<Tc, Ts>::RotarDobleIzq(Nodo* p) {
	RotarSimpleDer((*p).der);
	RotarSimpleIzq(p);
}

template<class Tc, class Ts>
void DiccRapido<Tc, Ts>::RotarDobleDer(Nodo* p) {
	RotarSimpleIzq((*p).izq);
	RotarSimpleDer(p);
}

template<class Tc, class Ts>
int DiccRapido<Tc, Ts>::Altura(const Nodo* p) const {
	if ((*p).izq == NULL && (*p).der == NULL) {
		return 1;
	} else {
		if ((*p).izq != NULL && (*p).der == NULL) {
			return (*((*p).izq)).alt + 1;
		} else {
			if ((*p).izq == NULL && (*p).der != NULL) {
				return (*((*p).der)).alt + 1;
			} else {
				return std::max((*((*p).izq)).alt, (*((*p).der)).alt) + 1;
			}
		}
	}
}

template<class Tc, class Ts>
int DiccRapido<Tc, Ts>::FactorDesbalance(const Nodo* p) const {
	if ((*p).izq == NULL && (*p).der == NULL) {
		return 0;
	} else {
		if ((*p).izq != NULL && (*p).der == NULL) {
			return (*((*p).izq)).alt;
		} else {
			if ((*p).izq == NULL && (*p).der != NULL) {
				return -((*((*p).der)).alt);
			} else {
				return (*((*p).izq)).alt - ((*((*p).der)).alt);
			}
		}
	}
}

//metodos publicos de ITClave
template<class Tc, class Ts>
DiccRapido<Tc, Ts>::ITClave::ITClave(const DiccRapido<Tc, Ts>& dicc) : it(dicc) {
	it.nivelActual = 1;
	it.nodosRecorridos = 0;
	it.tam = 0;
	it.nodoActual = dicc.dicc.raiz;
	it.raiz = dicc.dicc.raiz;
}

template<class Tc, class Ts>
DiccRapido<Tc, Ts>::ITClave::~ITClave() {
	delete it.nodoActual;
	delete it.raiz;
}

template<class Tc, class Ts>
DiccRapido<Tc, Ts>::ITClave::ITClave(const ITClave& otro) : it(otro.it.diccIt) {
	it.nivelActual = otro.it.nivelActual;
	it.nodosRecorridos = otro.it.nodosRecorridos;
	it.tam = otro.it.tam;
	it.nodoActual = otro.it.nodoActual;
	it.raiz = otro.it.raiz;
}

template<class Tc, class Ts>
const bool DiccRapido<Tc, Ts>::ITClave::HayMas() const {
	if (it.nodosRecorridos < it.tam - 1) {
		return true;
	} else {
		return false;
	}
}

template<class Tc, class Ts>
Tc& DiccRapido<Tc, Ts>::ITClave::ClaveActual() const {
	return (*(it.nodoActual)).clave;
}

template<class Tc, class Ts>
void DiccRapido<Tc, Ts>::ITClave::Avanzar() {
	it.nodosRecorridos = it.nodosRecorridos + 1;
	typename Conj<Tc>::Iterador itNodosNivelActual = it.diccIt.DameNodos(it.raiz, 1, it.nivelActual).CrearIt();
	while (itNodosNivelActual.Siguiente() != (*(it.nodoActual)).clave) {
		itNodosNivelActual.Avanzar();
	}
	if (itNodosNivelActual.HaySiguiente()) {

		Nodo* pNodo = it.raiz;
		while ((*pNodo).clave !=  itNodosNivelActual.Siguiente()) {
			if (itNodosNivelActual.Siguiente() > (*pNodo).clave) {
				pNodo = (*pNodo).der;
			} else {
				pNodo = (*pNodo).izq;
			}
		}		

		it.nodoActual = pNodo;
	} else {
		it.nivelActual = it.nivelActual + 1;

		Nodo* pNodo = it.raiz;
		Tc c = (it.diccIt.DameNodos(it.raiz, 1, it.nivelActual)).DameUno();

		while ((*pNodo).clave != c ) {
			if (c > (*pNodo).clave) {
				pNodo = (*pNodo).der;
			} else {
				pNodo = (*pNodo).izq;
			}
		}	

		it.nodoActual = pNodo;
	}	

}

//metodos privados de ITClave
template<class Tc, class Ts>
const Lista<Tc> DiccRapido<Tc, Ts>::ITClave::Siguientes() const {
	ITClave itVar = new ITClave(this);
	Lista<Tc> siguientes = Lista<Tc>();
	while (HayMas(itVar)) {
		siguientes.AgregarAtras(itVar.ClaveActual());
		itVar.Avanzar;
	}
	delete itVar;
	return siguientes;
}

#endif


