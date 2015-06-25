/* 
 * File:   Mapa.h
 * Author: Juan
 *
 * Created on 18 de noviembre de 2014, 20:38
 */

#ifndef MAPA_H
#define	MAPA_H

#include "DiccString.h"
#include "Rest.h"
#include "Tipos.h"
#include "aed2/TiposBasicos.h"
#include "aed2/Conj.h"
#include "aed2/Arreglo.h"
#include "aed2/Vector.h"


using namespace aed2;

class Mapa {
public:
    Mapa();
    
    Mapa(const Mapa& orig);
    
    ~Mapa();
    
    Conj<Estacion>::Iterador Estaciones();
    
    bool Conectadas(const Estacion est1, const Estacion est2);
    
    Rest Restriccion(const Estacion est1, const Estacion est2);
    
    void Agregar(const Estacion est);
    
    void Conectar(const Estacion est1, const Estacion est2, const Rest& rest);
    
    Nat NroConexion(const Estacion est1, const Estacion est2);
    
    Arreglo<bool> EvaluarSendas(const Conj<Caracteristica>& carac);
    
    Arreglo<Rest> Restricciones();
private:
    DiccString< DiccString<Nat> >* uniones;
    
    Conj<Estacion>* estaciones;
    
    Vector<Rest>* sendas;
    
    Nat cantSendas;
};

#endif	/* MAPA_H */