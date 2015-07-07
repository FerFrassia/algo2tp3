#include "ArbolSintactico.h"
#include "Tipos.h"
#include "aed2/TiposBasicos.h"
#include "aed2/Conj.h"
#include "Rest.h"

Rest::Rest() {
    astring = "";
    raiz = "";
    izq = NULL;
    der = NULL;
}

Rest::Rest(Restriccion rest) {
    astring = rest;
    raiz = rest;
    izq = NULL;
    der = NULL;
}

//Rest::Rest(Restriccion rest) {
//    ArbolSintactico* arbol = ArbolSintactico::LeerDeString(rest);
//    raiz = arbol -> raiz;
//    astring = arbol -> aString();
//    if(arbol -> izq != NULL) {
//        izq = new Rest(*(arbol -> izq));
//        izq -> astring = (arbol -> izq) -> aString();
//    }
//    else { izq = NULL; }
//    if(arbol -> der != NULL) {
//        der = new Rest(*(arbol -> der));
//        der -> astring = (arbol -> der) -> aString();
//    }
//    else { der = NULL; }
//    delete arbol;
//}
//
//Rest::Rest(ArbolSintactico& arbol) {
//    raiz = arbol.raiz;
//    astring = arbol.aString();
//    if(arbol.izq != NULL) {
//        izq = new Rest(*(arbol.izq));
//        izq -> astring = (*(arbol.izq)).aString();
//    }
//    else { izq = NULL; }
//    if(arbol.der != NULL) {
//        der = new Rest(*(arbol.der));
//        der -> astring = (*(arbol.der)).aString();
//    }
//    else { der = NULL; }
//}

Rest::Rest(const Rest& orig) : izq(NULL), der(NULL) {
    raiz = orig.raiz;
    astring = orig.astring;
    if(orig.izq != NULL) {
        izq = new Rest(*(orig.izq));
        izq -> astring = (*(orig.izq)).astring;
    }
    if(orig.der != NULL) {
        der = new Rest(*(orig.der));
        der -> astring = (*(orig.der)).astring;
    }
}

Rest::~Rest() {
    if(izq != NULL) { delete izq; }
    if(der != NULL) { delete der; }
}

bool Rest::Verifica(const Conj<Caracteristica>& carac) {
    if(raiz == "&") {
        return izq -> Verifica(carac) && der -> Verifica(carac);
    } else if(raiz == "|") {
        return izq -> Verifica(carac) || der -> Verifica(carac);
    } else if(raiz == "!") {
        return !(izq -> Verifica(carac));
    } else {
        return carac.Pertenece(raiz);
    }
}
    
Rest Rest::AND(const Rest& rest) {
    Rest res = Rest();
    res.raiz = "&";
    res.astring = "(" + (*this).astring + " & " + rest.astring + ")";
    res.der = new Rest(*this);
    res.izq = new Rest(rest);
    return res;
}
    
Rest Rest::OR(const Rest& rest) {
    Rest res = Rest();
    res.raiz = "|";
    res.astring = "(" + (*this).astring + " | " + rest.astring + ")";
    res.der = new Rest(*this);
    res.izq = new Rest(rest);
    return res;
}
    
Rest Rest::NOT() {
    if(raiz == "!") {
        return Rest(*izq);
    } else {
        Rest res = Rest();
        res.raiz = "!";
        res.astring = "!(" + astring + ")";
        res.izq = new Rest(*this);
        return res;
    }
}

String Rest::aString() const {
    return astring;
}