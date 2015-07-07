#ifndef dicc_rapido_algo2
#define dicc_rapido_algo2

#include "aed2/TiposBasicos.h"
#include <stdlib.h>

using namespace aed2;


class DiccRapido {
public:

	DiccRapido();

	~DiccRapido();

	DiccRapido(const DiccRapido& otro);

	const bool Def(const Nat c) const;

	Nat s Obtener(const Nat c);

	void Definir(const Nat c, const Nat s);

	void Borrar(const Nat c);

	const bool Vacio() const;

	Nat c ClaveMax() const;

	ITClave Claves() const;

private:

	struct nodo {
		Nat clave;
		Nat significado;
		nodo* padre;
		nodo* izq;
		nodo* der;
		Nat alt;

		nodo(const Nat& c, const Nat& s);

		nodo(const Nat c, const Nat s);

		nodo(const nodo& otro);

		~nodo();

		const bool operator < (const nodo& otro) const;

		const bool operator > (const nodo& otro) const;

		const bool operator == (const nodo& otro) const;

	};

	struct e_estr {
		nodo* raiz;
		Nat tam;

		e_estr();
	};

	Conj DameNodos(const nodo* p, Nat actual, const Nat destino) const;

	void Rotar(nodo* p);

	void RotarSimpleIzq(nodo* p);

	void RotarSimpleDer(nodo* p);

	void RotarDobleIzq(nodo* p);

	void RotarDobleDer(nodo* p);

	Nat Altura(const nodo* p) const;

	Nat FactorDesbalance(const nodo* p) const; 

};

class ITClave {
public:

	ITClave();

	~ITClave();

	ITClave(const ITClave& otro);	

	const bool HayMas() const;

	Nat c ClaveActual() const;

	void Avanzar();

private:

	struct nodo {
		Nat clave;
		Nat significado;
		nodo* padre;
		nodo* izq;
		nodo* der;
		Nat alt;

		nodo(const Nat& c, const Nat& s);

		nodo(const Nat c, const Nat s);

		nodo(const nodo& otro);

		~nodo();

		const bool operator < (const nodo& otro) const;

		const bool operator > (const nodo& otro) const;

		const bool operator == (const nodo& otro) const;

	};

	struct e_estr {

		Nat nivelActual;
		Nat nodosRecorridos;
		Nat tam;
		nodo* nodoActual;
		nodo* raiz;

		e_estr();
	};

	const ListaEnlazada(Nat c) Siguientes() const;
};
