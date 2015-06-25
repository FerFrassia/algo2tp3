#include "ArbolSintactico.h"
#include "ColaPrioritaria.h"
#include "Mapa.h"
#include "Rest.h"
#include "Tipos.h"
#include "aed2/TiposBasicos.h"
#include "aed2/Conj.h"
#include "aed2/Arreglo.h"
#include "CiudadFuturista.h"

CiudadFuturista::CiudadFuturista(Mapa& otroMapa) {
    mapa = new Mapa(otroMapa);
//    mapa = &otroMapa;
    
    RUREnEst = new DiccString<ColaP>();
    Conj<Estacion>::Iterador it(otroMapa.Estaciones());
    while(it.HaySiguiente()) {
        RUREnEst -> Definir(it.Siguiente(), ColaP());
        it.Avanzar();
    }
        
    RURs = new Vector<Robot>();
    
    cantRURHistoricos = 0;
}

CiudadFuturista::CiudadFuturista(CiudadFuturista& orig) {
    mapa = new Mapa(*(orig.mapa));
    
    RUREnEst = new DiccString<ColaP>(*(orig.RUREnEst));
    
    RURs = new Vector<Robot>(*(orig.RURs));
    
    cantRURHistoricos = orig.cantRURHistoricos;
}

CiudadFuturista::~CiudadFuturista() { 
    if(mapa != NULL) { delete mapa; } 
    if(RUREnEst != NULL) { delete RUREnEst; } 
    if(RURs != NULL) { delete RURs; }
}

RUR CiudadFuturista::ProximoRUR() {
    return cantRURHistoricos;
}
    
Mapa& CiudadFuturista::GetMapa() {
    return *mapa;
}
    
CiudadFuturista::Iterador CiudadFuturista::Robots() {
    return CrearIt();
}
    
Estacion CiudadFuturista::GetEstacion(const RUR rur) {
    return (*RURs)[rur].est;
}
    
Conj<Caracteristica> CiudadFuturista::Tags(const RUR rur) {
    return (*RURs)[rur].carac;
}
    
Nat CiudadFuturista::CantInfracciones(const RUR rur) {
    return (*RURs)[rur].inf;
}
    
void CiudadFuturista::Entrar(const Conj<Caracteristica> carac, const Estacion est) {
    (RUREnEst -> Significado(est)).Agregar(0, cantRURHistoricos);
    Robot robot;
    robot.id = cantRURHistoricos;
    robot.esta = true;
    robot.est = est;
    robot.inf = 0;
    robot.carac = carac;
    robot.sendEv = mapa -> EvaluarSendas(carac);
    RURs -> Agregar(cantRURHistoricos, robot);
    cantRURHistoricos++;
}
    
void CiudadFuturista::Mover(const RUR rur, const Estacion est) {
    (RUREnEst -> Significado((*RURs)[rur].est)).Eliminar((*RURs)[rur].inf, rur);
    if(!((*RURs)[rur].sendEv[mapa -> NroConexion((*RURs)[rur].est, est)])) {
        (*RURs)[rur].inf++;
    }
    (RUREnEst -> Significado(est)).Agregar((*RURs)[rur].inf, rur);
    (*RURs)[rur].est = est;
}
    
void CiudadFuturista::Inspeccion(const Estacion est) {
    RUR rur = (RUREnEst -> Significado(est)).Desencolar().seg;
    if((*RURs)[rur].inf != 0) {
        (*RURs)[rur].esta = false;
    } else {
        (RUREnEst -> Significado(est)).Agregar((*RURs)[rur].inf, (*RURs)[rur].id);
    }
}
    
CiudadFuturista::Iterador::Iterador(Vector<Robot>& robots) : actual(0), robots(&robots) {

}

//CiudadFuturista::Iterador::~Iterador() {
//    
//}

CiudadFuturista::Iterador CiudadFuturista::CrearIt() {
    Vector<Robot>* robots = new Vector<Robot>();
    
    for(Nat i = 0; i < (RURs -> Longitud()); i++) {
        if((*RURs)[i].esta) { robots -> AgregarAtras((*RURs)[i]); }
    }
    
    return Iterador((*robots));
}

CiudadFuturista::Iterador& CiudadFuturista::Iterador::Iterador::operator = (CiudadFuturista::Iterador& otro) {
    return otro;
}

bool CiudadFuturista::Iterador::HayMas() {
    return actual < (robots -> Longitud());
}

CiudadFuturista::Robot CiudadFuturista::Iterador::Actual() {
    return (*robots)[actual];
}

void CiudadFuturista::Iterador::Avanzar() {
    actual++;
}
