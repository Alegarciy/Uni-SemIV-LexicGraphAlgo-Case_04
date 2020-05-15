//
// Created by alega on 5/13/2020.
//

#ifndef CASO_04_ALGORITMOS_H
#define CASO_04_ALGORITMOS_H

#include "../Estructura/Grafo.h"
#include "../CargarSustantivos/CargarSustantivos.h"

class Algoritmos {
private:
    Grafo * grafo;
public:
    Algoritmos();
    std::unordered_map<std::string, int>* Agrupar(int cantidadDeGrupos, std::string palabra);
    void AgruparRecursivo(std::string palabra, int grupoActual, int cantidadDePalabras, std::unordered_map<std::string, int> *map);
};

Algoritmos::Algoritmos() {
    grafo = new Grafo();
    //Ordenar grafo
    CargarSustantivos * cargar = new CargarSustantivos(grafo);
    cargar->cargarJson();
    cargar->cargarGrafo();
    cargar->OrdenarGrafo();
    cargar->getGrafo()->imprimir();
}

std::unordered_map<std::string , int> *Algoritmos::Agrupar(int cantidadDeGrupos, std::string palabra) {
    auto * resultado = new std::unordered_map<std::string , int>();
    int cantidadDePalabras = grafo->getIndiceVertices()->size()/cantidadDeGrupos;
    //std::cout << "Cantidad de palabras por grupo: " << cantidadDePalabras << std::endl;
    //Vertice no tiene ruta porque no se puede usar para agrupar
    grafo->getIndiceVertices()->at(palabra)->setRuta(false);

//    for(int i = 0; i < cantidadDeGrupos; i++)
//        AgruparRecursivo(palabra, i, cantidadDePalabras, resultado);

    std::cout << "(Agrupar) Resultado: " << resultado->at(palabra) << std::endl;
    return resultado;
}

//Nota: no se pueden usar la palabra de inicio 2 veces, esta solo se llama en el for
void Algoritmos::AgruparRecursivo(std::string palabra,int grupoActual ,int cantidadDePalabras, std::unordered_map<std::string , int> * resultado) {

    Arista * aristaActual = grafo->getIndiceVertices()->at(palabra)->mejorArista;
    Arista * ultimaArista =  grafo->getIndiceVertices()->at(palabra)->ultimaArista;

    grafo->getIndiceVertices()->at(palabra)->mejorArista->getVerticeDestino();
    //While: Arista actual a una arista que noHayRuta sea falso, luego
    while(!aristaActual->getVerticeDestino()->HayRuta() && aristaActual != ultimaArista)
    {
        aristaActual = aristaActual->getSiguiente();
        grafo->getIndiceVertices()->at(palabra)->mejorArista = aristaActual;
    }

    //Si es la ultima arista el vertice ua no tiene rutas
    if(aristaActual == ultimaArista)
        aristaActual->getVerticeDestino()->setRuta(true);
    //Condicion de parada, else hay ruta
    if(cantidadDePalabras == 0 || (aristaActual == ultimaArista && !aristaActual->getSiguiente()->getVerticeDestino()->HayRuta()) )
        return;
    //Agregar palabra del vertice actual a resultado; sino se quiere repetir la palabra entonces haces un if aqui
    resultado->insert(std::pair<std::string , int>(aristaActual->getVerticeDestino()->palabra, grupoActual));
    //Recursion: Seguir agrupando pero ahora necesito una palabra menos y ya no uso es ruta papu
    cantidadDePalabras--;
    std::cout << "(Agrupar Recursivo) Resultado: " << resultado->at(palabra) << std::endl;
    //AgruparRecursivo(aristaActual->getSiguiente()->getVerticeDestino()->palabra,grupoActual ,cantidadDePalabras, resultado);



}

#endif //CASO_04_ALGORITMOS_H
