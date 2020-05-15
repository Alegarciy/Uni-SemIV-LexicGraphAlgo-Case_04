
#ifndef CASO_04_ARISTA_H
#define CASO_04_ARISTA_H

#include "PoderArista.h"

class Vertice;

class Arista{
private:
    Vertice * destino;
    PoderArista * poder;
    //Un puntero que indique a el siguiente arista (relacio de poder)
    Arista * siguiente;

public:
    Arista(Vertice * destino, int parrafo);
    Vertice* getVerticeDestino();
    Arista* getSiguiente();
    void setSiguiente(Arista* arista);
    PoderArista* getPoder();

};


Arista::Arista(Vertice * destino, int parrafo) {
    destino = destino;
    poder = new PoderArista(parrafo);
}

Vertice *Arista::getVerticeDestino() {
    return destino;
}

Arista* Arista::getSiguiente() {
    return siguiente;
}

void Arista::setSiguiente(Arista *arista) {
    siguiente = arista;
}

PoderArista *Arista::getPoder() {
    return poder;
}

#endif //CASO_04_ARISTA_H
