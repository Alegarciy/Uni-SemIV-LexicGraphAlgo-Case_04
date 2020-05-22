#ifndef CASO_04_VERTICE_H
#define CASO_04_VERTICE_H

#include "Arista.h"

//Nota: el poder de la arista es equivalente a cada relacion con el parrafo donde se encuentre esa palabra
//Cada vertice va a contener su propio hashmap de aristas
//

class Vertice{
public:
    std::unordered_map<std::string, Arista*> * aristas;
    Arista * primerArista;
    Arista * ultimaArista;
    //Un puntero que indique ruta actual
    Arista * mejorArista = nullptr;
    //Key del hashmap del grafo
    std::string palabra;
    //Un puntero que indique a el siguiente vertice (relacio de poder)
    Vertice * siguiente;
    int poder;
    bool ruta;
    bool leido;

public:
    Vertice(std::string palabra);
    std::unordered_map<std::string, Arista*>* getAristas();
    std::string getPalabra();
    Vertice * getSiguiente();
    void setSiguiente(Vertice * vertice);
    Arista * getMejorArista();
    Arista * getPrimerArista();
    Arista * getUltimaArista();
    void setMejorArista(Arista * arista);
    int getPoder();
    void agregarArista(Vertice* destino, int parrafo);
    void aumentarPoder();
    bool HayRuta();
    void setRuta(bool);
};

Vertice::Vertice(std::string _palabra) {
    aristas = new std::unordered_map<std::string, Arista*>;
    palabra = _palabra;
    poder = 0;
    ruta = true;
    leido = false;
}

std::unordered_map<std::string, Arista *> * Vertice::getAristas() {
    return aristas;
}

Arista* Vertice::getMejorArista() {
    return mejorArista;
}

void Vertice::setMejorArista(Arista *arista) {
    mejorArista = arista;
}

void Vertice::aumentarPoder() {
    poder++;
}

int Vertice::getPoder() {
    return poder;
}

std::string Vertice::getPalabra() {
    return palabra;
}

//Si la arista ya existe se aumenta el  poder de la relacion origen -> destino
void Vertice::agregarArista(Vertice *destino, int parrafo) {
    if(aristas->count(destino->palabra) == 1) //Si ya hay una relacion existente aumente poder de la arista en un parrafo
        aristas->at(destino->palabra)->getPoder()->aumentarPoder(parrafo);
    else{ //Si no cree relacion con poder == 1
        aristas->insert(std::pair<std::string, Arista*>(destino->getPalabra(),new Arista(destino, parrafo)));
    }

}


Vertice* Vertice::getSiguiente() {
    return siguiente;
}

void Vertice::setSiguiente(Vertice *vertice) {
    siguiente = vertice;
}

bool Vertice::HayRuta() {
    return ruta;
}

void Vertice::setRuta(bool _ruta)
{
    ruta = _ruta;
}

Arista *Vertice::getPrimerArista() {
    return primerArista;
}

Arista* Vertice::getUltimaArista() {
    return ultimaArista;
}
#endif //CASO_04_VERTICE_H
