#include "Driver.h"
#include "TiposBasicos.h"

namespace aed2 {

Driver::Driver() {
    lared = new  Red();
    eldcnet = NULL;
    iddelproximopaquete = 0;
}

Driver::~Driver() {
    delete lared;
    delete eldcnet;
}

// TAD RED
Nat Driver::CantidadComputadoras() const {
    Conj<Compu>::Iterador it = lared->Computadoras();
    int res = 0;
        while(it.HaySiguiente()){
            res ++;
            it.Avanzar();
        }
     return res;

}

const Computadora& Driver::IesimaComputadora(const Nat i) const {
    Conj<Compu>::Iterador it = lared->Computadoras();
    int n = 0;
    Computadora res;
        while(it.HaySiguiente()){
            if(n == i){
                return res = (it.Siguiente()).hostname;
            }
            n ++;
            it.Avanzar();
}
}
 
        
Nat Driver::CantidadInterfacesDe(const Computadora& c) const{
    Conj<Compu>::Iterador it = lared->Computadoras();
        while((it.Siguiente()).hostname != c){
              
            it.Avanzar();
        }
    return ((it.Siguiente()).interfaces).Cardinal();
}

const Interfaz& Driver::IesimaInterfazDe(const Computadora& c, const Nat i) const{
    Conj<Compu>::Iterador it = lared->Computadoras();
    Conj<Interfaz> cji;
    
    
    while((it.Siguiente()).hostname != c){
        it.Avanzar();
    }
    cji = ((it.Siguiente()).interfaces);
    Conj<Interfaz>::Iterador itint = cji.CrearIt();
    int n = 0;
    

    while(itint.HaySiguiente()){
        if(n == i){
            return  itint.Siguiente();
        }
        n++;
        it.Avanzar();

    }
}


const Interfaz& Driver::IntefazUsada(const Computadora& c1, const Computadora& c2) const {
    

     
     return  lared->InterfazUsada(lared->DameCompu(c1), lared ->DameCompu(c2));
    
}

bool Driver::conectadas(const Computadora& c1, const Computadora& c2) const {
    
    return lared->Conectadas(lared->DameCompu(c1),lared->DameCompu(c2));
}

// TAD DCNET
void Driver::AgregarComputadora(const Computadora& ip, const Conj<Interfaz>& ci) {
    //ASSERT(eldcnet == NULL)
    Compu c;
    c.hostname = ip;
    c.interfaces = ci;

    lared->AgregarComputadora(c);
}
        
void Driver::Conectar(const Computadora& c1, const Interfaz& i1, const Computadora& c2, const Interfaz& i2) {
        //ASSERT(eldcnet == NULL)
        Conj<Compu>::Iterador it = lared->Computadoras();
        
        lared->Conectar(lared->DameCompu(c1),i1,lared->DameCompu(c2),i2);
}
    
    
Nat Driver::CantidadNodosRecorridosPor(const Paquete& p) const {
 
    return (eldcnet->CaminoRecorrido(eldcnet->DamePaquete(p))).Longitud();

}

const Computadora& Driver::IesimoNodoRecorridoPor(const Paquete& p, const Nat i) const {
    Lista<Compu>::Iterador it = (eldcnet->CaminoRecorrido(eldcnet->DamePaquete(p))).CrearIt();
    int n = 0;

     while(it.HaySiguiente()){
        if(n == i){
            return (it.Siguiente()).hostname;
        }
        n++;
        it.Avanzar();
    }
}

Nat Driver::CantidadEnviadosPor(const Computadora& c) const {
    return eldcnet->CantidadEnviados(lared->DameCompu(c));
    
}
    
Nat Driver::CantidadEnEsperaEn(const Computadora& c) const {
    DiccRapido<_Paquete, Lista<Compu> >::ITClave it = eldcnet->EnEspera(lared->DameCompu(c));
    Nat n = 0;
    while(it.HayMas()){
        n++;
        it.Avanzar();
    }
    return n;
}

const Paquete& Driver::IesimoEnEsperaEn(const Computadora& c, const Nat i) const {
    DiccRapido<_Paquete, Lista<Compu> >::ITClave it = eldcnet->EnEspera(lared->DameCompu(c));
    Nat n = 0;
    while(it.HayMas()){
        if(n==i){
            return (it.ClaveActual()).id;
        }
        n++;
        it.Avanzar();
    }
}


void Driver::CrearPaquete(const Computadora& origen, const Computadora& destino, Nat prioridad) {
    if(eldcnet==NULL){
        eldcnet = new DCNet(*lared);
    }


    ::_Paquete paq;
    paq.id = iddelproximopaquete;///?;
    iddelproximopaquete ++;
    paq.prioridad = prioridad;

    paq.destino = lared->DameCompu(destino);
    paq.origen = lared->DameCompu(origen);

    eldcnet -> CrearPaquete(paq);

}
        
void Driver::AvanzarSegundo() {
    if(eldcnet==NULL){
        eldcnet = new DCNet(*lared);
    }




    eldcnet->AvanzarSegundo();
}
        
const Computadora& Driver::laQueMasEnvio() const {
    return (eldcnet->LaQueMasEnvio()).hostname;
    
}

const Computadora& Driver::origen(const Paquete& p) const {
    return ((eldcnet->DamePaquete(p)).origen).hostname;

} 

const Computadora& Driver::destino(const Paquete& p) const { 
    return ((eldcnet->DamePaquete(p)).destino).hostname;
}

Nat Driver::prioridad(const Paquete& p) const { 
    return (eldcnet->DamePaquete(p)).prioridad;
    }
}

        


 // namespace aed2

