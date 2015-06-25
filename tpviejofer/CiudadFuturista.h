/* 
 * File:   CiudadFuturista.h
 * Author: Juan
 *
 * Created on 18 de noviembre de 2014, 20:39
 */

#ifndef CIUDADFUTURISTA_H
#define	CIUDADFUTURISTA_H

#include "Tipos.h"
#include "ArbolSintactico.h"
#include "Rest.h"
#include "Mapa.h"
#include "ColaPrioritaria.h"
#include "aed2/TiposBasicos.h"
#include "aed2/Conj.h"
#include "aed2/Arreglo.h"

using namespace aed2;

class CiudadFuturista {
public:
    struct Robot {
        Nat id;
        bool esta;
        String est;
        Nat inf;
        Conj<String> carac;
        Arreglo<bool> sendEv;
    };
    
    CiudadFuturista(Mapa& mapa);
    
    CiudadFuturista(CiudadFuturista& orig);
    
    ~CiudadFuturista();
    
    RUR ProximoRUR();
    
    Mapa& GetMapa();
    
    Estacion GetEstacion(const RUR rur);
    
    Conj<Caracteristica> Tags(const RUR rur);
    
    Nat CantInfracciones(const RUR rur);
    
    void Entrar(const Conj<Caracteristica> carac, const Estacion est);
    
    void Mover(const RUR rur, const Estacion est);
    
    void Inspeccion(const Estacion est);
    
    //Iterador    
    class Iterador {
        public:
            Iterador(Vector<Robot>& robots);
            
//            ~Iterador();

            Iterador& operator = (Iterador& otro);

            bool HayMas();

            Robot Actual();

            void Avanzar();
        private:
            RUR actual;
            
            Vector<Robot>* robots;
    };
    
    CiudadFuturista::Iterador Robots();
private:
    Mapa* mapa;
    
    DiccString<ColaP>* RUREnEst;
    
    Vector<Robot>* RURs;
    
    Nat cantRURHistoricos;
    
    Iterador CrearIt();
};

#endif	/* CIUDADFUTURISTA_H */