#include "DiccString.h"
#include "Rest.h"
#include "Tipos.h"
#include "aed2/TiposBasicos.h"
#include "aed2/Conj.h"
#include "aed2/Arreglo.h"
#include "aed2/Vector.h"
#include "Mapa.h"

Mapa::Mapa() {
    uniones = new DiccString<DiccString<Nat> >();
    
    estaciones = new Conj<Estacion>();
    
    sendas = new Vector<Rest>();
    
    cantSendas = 0;
}

Mapa::Mapa(const Mapa& orig) {
    uniones = new DiccString<DiccString<Nat> >(*orig.uniones);
    
    estaciones = new Conj<Estacion>(*orig.estaciones);
    
    sendas = new Vector<Rest>(*orig.sendas);
    
    cantSendas = orig.cantSendas;
}

Mapa::~Mapa() {
    delete uniones;
    delete estaciones;
    delete sendas;
}

Conj<Estacion>::Iterador Mapa::Estaciones() {
    return estaciones -> CrearIt();
}
    
bool Mapa::Conectadas(const Estacion est1, const Estacion est2) {
    return (uniones -> Significado(est1)).Definido(est2);
}
    
Rest Mapa::Restriccion(const Estacion est1, const Estacion est2) {
    return (*sendas)[((uniones -> Significado(est1)).Significado(est2))];
}
    
void Mapa::Agregar(const Estacion est) {
    estaciones -> Agregar(est);
    uniones -> Definir(est, DiccString<Nat>());
}
    
void Mapa::Conectar(const Estacion est1, const Estacion est2, const Rest& rest) {
    (uniones -> Significado(est1)).Definir(est2, cantSendas);
    (uniones -> Significado(est2)).Definir(est1, cantSendas);
    sendas -> Agregar(cantSendas, rest);
    cantSendas++;
}
    
Nat Mapa::NroConexion(const Estacion est1, const Estacion est2) {
    return (uniones -> Significado(est1)).Significado(est2);
}
    
Arreglo<bool> Mapa::EvaluarSendas(const Conj<Caracteristica>& carac) {
    Arreglo<bool> res = Arreglo<bool>(cantSendas);
    Nat i = 0;
    while(i < cantSendas) {
        Rest rest = (*sendas)[i];
        res.Definir(i, rest.Verifica(carac));
        i++;
    }
    return res;
}
    
Arreglo<Rest> Mapa::Restricciones() {
    Arreglo<Rest> res = Arreglo<Rest>(cantSendas);
    Nat i = 0;
    while(i < cantSendas) {
        res.Definir(i, (*sendas)[i]);
        i++;
    }
    return res;
}