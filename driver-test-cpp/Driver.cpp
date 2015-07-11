#include "Driver.h"
#include "TiposBasicos.h"

namespace aed2 {

Driver::Driver() {
    lared = new  Red();
    eldcnet = new DCNet(lared);
}

Driver::~Driver() {
    delete lared;
    delete eldcnet;
}

// TAD RED
Nat Driver::CantidadComputadoras() const {
    Conj<Compu>::Iterador it = (lared->Computadoras()).CrearIt();
    int res = 0;
        while(it.HaySiguiente()){
            res ++;
            it.Avanzar();
        }
     return res;

}

const Computadora& Driver::IesimaComputadora(const Nat i) const {
    Conj<Compu>::Iterador it = (lared->Computadoras()).CrearIt();
    int n = 0;
    Computadora res;
        while(it.HaySiguiente()){
            if(n == i){
                return res = it.Siguiente();
            }
            i ++;
            it.Avanzar();
}
        
Nat Driver::CantidadInterfacesDe(const Computadora& c) const {
    Conj<Compu>::Iterador it = (lared->Computadoras()).CrearIt();
        while((it.Siguiente()).hostname != c){
              
            it.Avanzar();
        }
    return ((it.Siguiente()).interfaces).Cardinal();
}

const Interfaz& Driver::IesimaInterfazDe(const Computadora& c, const Nat i) const{
    Conj<Compu>::Iterador it = (lared->Computadoras()).CrearIt();
    Conj<Interfaz> cji;
    
    while((it.Siguiente()).hostname != c){
        it.Avanzar();
    }
    cji = ((it.Siguiente()).interfaces);
    Conj<Interfaz>::Iterador itint = cji.CrearIt();
    int n = 0
    Interfaz res;

    while(itint.HaySiguiente()){
        if(n == i){
            return res = itint.Siguiente();
        }
        i++;
        it.Avanzar();

    }
}


const Interfaz& Driver::IntefazUsada(const Computadora& c1, const Computadora& c2) const {
    
     return lared.InterfazUsada(c1, c2);
    
}

bool Driver::conectadas(const Computadora& c1, const Computadora& c2) const {
    
    return lared.Conectadas(c1,c2);
}

// TAD DCNET
void Driver::AgregarComputadora(const Computadora& ip, const Conj<Interfaz>& ci) {
    Compu c;
    c.hostname = ip;
    c.interfaces = ci;

    lared.AgregarComputadora(c);
}
        
void Driver::Conectar(const Computadora& c1, const Interfaz& i1, const Computadora& c2, const Interfaz& i2) {
        Conj<Compu>::Iterador it = (lared->Computadoras()).CrearIt();
        Compu pc1;
        Compu pc2;
         while(it.HaySiguiente()){
            if((it.Siguiente()).hostname == c1){
                pc1.hostname = c1;
                pc1.interfaces = (it.Siguiente()).interfaces;
            }else{
                if((it.Siguiente()).hostname == c2){
                    pc2.hostname = c2;
                    pc2.interfaces = (it.Siguiente()).interfaces;
                }
            }  
              
            it.Avanzar();
            }
        
        lared->Conectar(pc1,i1,pc2,i2);
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
        i++;
        it.Avanzar();
    }
}

Nat Driver::CantidadEnviadosPor(const Computadora& c) const {
    return eldcnet->CantidadEnviados(eldcnet->DameCompu(c));
    
}
    
Nat Driver::CantidadEnEsperaEn(const Computadora& c) const {
    DiccRapido<Paquete, Lista<Compu> >::ITClave it = eldcnet->EnEspera(eldcnet->DameCompu(c));
    Nat n = 0;
    while(it.HayMas()){
        n++;
        it.Avanzar();
    }
    return n;
}

const Paquete& Driver::IesimoEnEsperaEn(const Computadora& c, const Nat i) const {
    DiccRapido<Paquete, Lista<Compu> >::ITClave it = eldcnet->EnEspera(eldcnet->DameCompu(c));
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
    ::Paquete paq;
    paq.id = 
}
        
void Driver::AvanzarSegundo() {
    eldcnet->AvanzarSegundo();
}
        
const Computadora& Driver::laQueMasEnvio() const {
    return (eldcnet->laQueMasEnvio()).hostname;
    
}

const Computadora& Driver::origen(const Paquete& p) const {
    return (eldcnet->DamePaquete(p)).origen;

} 

const Computadora& Driver::destino(const Paquete& p) const { 
    return (eldcnet->DamePaquete(p)).destino;
}

Nat Driver::prioridad(const Paquete& p) const { 
    return (eldcnet->DamePaquete(p)).prioridad;
}
        


} // namespace aed2

