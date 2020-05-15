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
    std::unordered_map<std::string, Vertice*>::iterator it = this->getIndiceVertices()->begin();
    for (it; it != this->getIndiceVertices()->end(); ++it) { //Recorre vertices en el grafo
        std::cout <<"-"<<it->first << " Aristas (" << it->second->getPoder() <<")"<< std::endl;
        std::unordered_map<std::string, Arista*>::iterator itArista = it->second->getAristas()->begin();
        for (itArista; itArista != it->second->getAristas()->end(); ++itArista){ //Recorre las aristas en un vertice
            std::cout << "   *"<< itArista->first << "  Poder (" <<itArista->second->getPoder()->getPoder() << ")";
            std::vector<int>::iterator itParrafos = itArista->second->getPoder()->getParrafos()->begin();
            std::cout << " Parrafos [";
            for(itParrafos; itParrafos != itArista->second->getPoder()->getParrafos()->end(); ++itParrafos){ //Recorre los parrafos en una arista
                std::cout <<  *itParrafos.base() << " ";
            }
            std::cout << "]" <<std::endl;
        }
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
