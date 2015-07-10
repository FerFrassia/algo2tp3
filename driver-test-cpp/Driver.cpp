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
    ::Compu 
}
        
void Driver::Conectar(const Computadora& c1, const Interfaz& i1, const Computadora& c2, const Interfaz& i2) {
    // TODO
}
    
    
Nat Driver::CantidadNodosRecorridosPor(const Paquete& p) const {
    // TODO
    return 0;
}

const Computadora& Driver::IesimoNodoRecorridoPor(const Paquete& p) const {
    // TODO
}

Nat Driver::CantidadEnviadosPor(const Computadora& c) const {
    // TODO
    return 0;
}
    
Nat Driver::CantidadEnEsperaEn(const Computadora& c) const {
    // TODO
    return 0;
}

const Paquete& Driver::IesimoEnEsperaEn(const Computadora& c) const {
    // TODO
    return 0;
}

void Driver::CrearPaquete(const Computadora& origen, const Computadora& destino, Nat prioridad) {
    // TODO
}
        
void Driver::AvanzarSegundo() {
    // TODO
}
        
const Computadora& Driver::laQueMasEnvio() const {
    // TODO 
    return 0;
}

const Computadora& Driver::origen(const Paquete& p) const {
    // TODO 
    return 0;
} 

const Computadora& Driver::destino(const Paquete& p) const { 
    // TODO 
    return 0;
}

Nat Driver::prioridad(const Paquete& p) const { 
    // TODO 
    return 0;
}
        


} // namespace aed2

