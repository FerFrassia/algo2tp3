/* 
 * File:   Restriccion.h
 * Author: Juan
 *
 * Created on 18 de noviembre de 2014, 20:38
 */

#ifndef REST_H
#define	REST_H

#include "ArbolSintactico.h"
#include "Tipos.h"
#include "aed2/TiposBasicos.h"
#include "aed2/Conj.h"


using namespace aed2;

class Rest {
public:
    Rest();
    
    Rest(Restriccion rest);
    
    Rest(const ArbolSintactico& arbol);
    
    Rest(const Rest& orig);
    
    ~Rest();
    
    bool Verifica(const Conj<Caracteristica>& carac);
    
    Rest AND(const Rest& rest);
    
    Rest OR(const Rest& rest);
    
    Rest NOT();
    
    String aString() const;
private:
    String astring;
    
    String raiz;
    
    Rest* izq;
    
    Rest* der;
};

#endif	/* RESTRICCION_H */