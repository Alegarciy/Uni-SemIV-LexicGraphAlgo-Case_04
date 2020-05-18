#ifndef CASO_04_GRAFO_H
#define CASO_04_GRAFO_H

#include <unordered_map>
#include "Vertice.h"
#include "../Json/jsoncpp-master/dist/json/json.h"

class Grafo{
private:
    std::unordered_map<std::string, Vertice*> * indiceVertices;
    Vertice * primerVertice;
    Vertice * ultimoVertice;
public:
    Grafo();
    std::unordered_map<std::string, Vertice*>* getIndiceVertices();
    //No se ocupa setIndiceVertices
    void setIndiceVertices(std::unordered_map<std::string, Vertice*>* map);
    void setUltimoVertice(Vertice * vertice);
    void setPrimerVertice(Vertice * vertice);
    Vertice * getUltimoVertice();
    Vertice * getPrimerVertice();
    void agregarVertice(std::string palabra);
    void agregarArista(std::string origen, std::string destino, int parrafo);
    void imprimir();
    bool existeVertice(std::string palabra);

};

Grafo::Grafo() {
    indiceVertices = new std::unordered_map<std::string, Vertice*>;
}

std::unordered_map<std::string, Vertice *>* Grafo::getIndiceVertices() {
    return indiceVertices;
}

void Grafo::agregarVertice(std::string palabra) {
    indiceVertices->insert(std::pair<std::string, Vertice*>(palabra, new Vertice(palabra)));
}

//Accesa los contenidos del vertice "v" con la llave origen
//Agrega a "v" una arista "a"
//"a" contiene [puntero a otro vertice, numero de parrafo]
void Grafo::agregarArista(std::string origen, std::string destino, int parrafo) {
    indiceVertices->at(origen)->agregarArista(indiceVertices->at(destino), parrafo);
    indiceVertices->at(origen)->aumentarPoder();
}

//No lo imprime en orden porque es un hashmap
void Grafo::imprimir() {
    std::cout << "* Imprimiendo Grafo *" << std::endl;
    Vertice * verticeActual = this->getPrimerVertice();

    bool ultimaAristaFlag = false;
    bool ultimoVerticeFlag = false;

    while(!ultimoVerticeFlag){
        std::cout <<"-"<<verticeActual->palabra << " Aristas (" << verticeActual->getPoder() <<")"<< std::endl;
        Arista* aristaActual = verticeActual->getPrimerArista();
        ultimaAristaFlag = false;
        while(!ultimaAristaFlag){
            std::cout << "   *" << aristaActual->getVerticeDestino()->palabra;
            std::cout << "  Poder (" <<aristaActual->getPoder()->getPoder() << ")";
            std::vector<int>::iterator itParrafos = aristaActual->getPoder()->getParrafos()->begin();
            std::cout << " Parrafos [";
            for (itParrafos; itParrafos != aristaActual->getPoder()->getParrafos()->end(); ++itParrafos) {
                std::cout << *itParrafos.base() << " ";
            }
            std::cout << "]" << std::endl;
            if(aristaActual == verticeActual->ultimaArista) ultimaAristaFlag = true;
            aristaActual = aristaActual->getSiguiente();
        }

        if(verticeActual == ultimoVertice) ultimoVerticeFlag = true;
        verticeActual = verticeActual->getSiguiente();
    }
}


bool Grafo::existeVertice(std::string palabra) {
    return indiceVertices->count(palabra) == 1;
}

void Grafo::setIndiceVertices(std::unordered_map<std::string, Vertice *> *map) {
    indiceVertices = map;
}

Vertice* Grafo::getPrimerVertice() {
    return primerVertice;
}

Vertice* Grafo::getUltimoVertice() {
    return ultimoVertice;
}

void Grafo::setPrimerVertice(Vertice *vertice) {
    primerVertice = vertice;
}

void Grafo::setUltimoVertice(Vertice *vertice) {
    ultimoVertice = vertice;
}

#endif //CASO_04_GRAFO_H
