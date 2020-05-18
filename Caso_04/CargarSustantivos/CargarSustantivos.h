//
// Created by Personal on 6/5/2020.
//

#ifndef CASO_04_CARGARSUSTANTIVOS_H
#define CASO_04_CARGARSUSTANTIVOS_H
#include "../Json/jsoncpp-master/dist/json/json.h"
#include "fstream"
class CargarSustantivos{
private:
    std::string filename = "../HtmlManager/sustantivos.json";
    Json::Value data;
    Grafo * grafo;

public:
    CargarSustantivos(Grafo*);
    Grafo * getGrafo();
    void cargarJson();
    void cargarGrafo();
    void OrdenarGrafo();
    void OrdenarAristas(Vertice * vertice);

};

CargarSustantivos::CargarSustantivos(Grafo * _grafo) {
    grafo = _grafo;
}

Grafo* CargarSustantivos::getGrafo() {
    return this->grafo;
}

void CargarSustantivos::cargarJson() {
    std::ifstream config_doc(this->filename, std::ifstream::binary);
    config_doc >> this->data;
}

void CargarSustantivos::cargarGrafo() {
    if(this->data.empty()) {
        std::cout << "Datos no han sido cargados" << std::endl;
        return;
    }

    //Recorre los parrafos
    bool primerRecorridoParrafo;
    Json::Value::iterator parrafoIt = this->data.begin();
    for(parrafoIt; parrafoIt != this->data.end(); ++parrafoIt){
    //for(parrafoIt; std::stoi(parrafoIt.key().asString()) < 2; ++parrafoIt){
        primerRecorridoParrafo = true;
        //Recorre las palabras
        Json::Value::iterator palabraIt = parrafoIt->begin();
        for(palabraIt; palabraIt != parrafoIt->end(); ++palabraIt){

            if(!grafo->existeVertice(palabraIt->asString()))  grafo->agregarVertice(palabraIt->asString());

            //Recorre las palabras a relacionar
            Json::Value::iterator relacionIt = parrafoIt->begin();
            for(relacionIt; relacionIt != parrafoIt->end(); ++relacionIt){
                //Evita que se relacione a si misma
                if(palabraIt.key() == relacionIt.key()) continue;

                //Si es el primer recorrido del parrafo agrega los vertices
                if(primerRecorridoParrafo && !grafo->existeVertice(relacionIt->asString()))
                    grafo->agregarVertice(relacionIt->asString());

                //Se agregan las aristas
                grafo->agregarArista(palabraIt->asString(), relacionIt->asString(), std::stoi(parrafoIt.key().asString()));
            }
            primerRecorridoParrafo = false;
        }
    }
}

//  vec -> first == key,  vec -> second == vertice
void CargarSustantivos::OrdenarGrafo() {

    std::unordered_map<std::string, Vertice*> * verticesMap = this->grafo->getIndiceVertices();
    std::vector<std::pair<std::string, Vertice*>> vec;
    //Copia hashmap [key,*vertice] en un vector [key,*vertice]
    std::copy(verticesMap->begin(), verticesMap->end(), std::back_inserter< std::vector<std::pair<std::string, Vertice*>>>(vec));
    //Ordena el vector con las parametros dentro del metodo (desc poder)
    std::sort(vec.begin(), vec.end(), [](const std::pair<std::string, Vertice*>& left, const std::pair<std::string, Vertice*>& right) {
        if (left.second->getPoder() != right.second->getPoder())
            return left.second->getPoder() > right.second->getPoder(); //Ordena con respecto al poder

        return left.first > right.first; //Ordena alfabeticamente
    });

    grafo->setPrimerVertice(vec.begin()->second);
    grafo->setUltimoVertice(vec.back().second);
    Vertice * anterior;
    // Recorre el vector con elemento actual
    // Apuntar a siguiente vector (desc poder)
    for (auto const &pair: vec) { // Es el gusano del espacio tiempo
        OrdenarAristas(pair.second);

        if(pair.first != vec.begin()->first)
            anterior->setSiguiente(pair.second); // Intercambio de los dos tiempos
        anterior = pair.second;

    }
}

void CargarSustantivos::OrdenarAristas(Vertice * vertice) {

    std::vector<std::pair<std::string, Arista*>> vec;
    std::unordered_map<std::string, Arista*> * aristasMap = vertice->getAristas();
    //Copia hashmap [key,*arista] en un vector [key,*arista]
    std::copy(aristasMap->begin(), aristasMap->end(), std::back_inserter< std::vector<std::pair<std::string, Arista*>>>(vec));
    //Ordena el vector con las parametros dentro del metodo (desc poder)
    std::sort(vec.begin(), vec.end(),
              [](const std::pair<std::string, Arista*>& left, const std::pair<std::string, Arista*>& right) {
                  if (left.second->getPoder()->getPoder() != right.second->getPoder()->getPoder())
                      return left.second->getPoder()->getPoder() > right.second->getPoder()->getPoder();
                  return left.first < right.first;
              });


    vertice->primerArista = vec.begin()->second;
    vertice->setMejorArista(vertice->primerArista);
    vertice->ultimaArista = vec.back().second;
    Arista * anterior;

    // Recorre el vector con elemento actual
    // Apuntar a siguiente arista (desc poder)
    for (auto const &pair: vec) {
        if(pair.first != vec.begin()->first)
            anterior->setSiguiente(pair.second);
        anterior = pair.second;
    }
}

#endif //CASO_04_CARGARSUSTANTIVOS_H
