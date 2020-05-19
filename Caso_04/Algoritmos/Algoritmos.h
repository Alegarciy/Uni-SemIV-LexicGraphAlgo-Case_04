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
    std::unordered_map<std::string, std::string>* Agrupar(int cantidadDeGrupos, std::string palabra);
    void AgruparRecursivo(std::string palabra, int grupoActual, int cantidadDePalabras, std::unordered_map<std::string, std::string> *map);
    void AgruparRecursivo2(std::string palabra,std::string palabraInicial, int grupoActual, int cantidadDePalabras, std::unordered_map<std::string, int> *map);

    void Agrupar2(int cantidadGrupos, std::string palabraInicial);
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

std::unordered_map<std::string , std::string> *Algoritmos::Agrupar(int cantidadDeGrupos, std::string palabra) {

    //Agrupar Recursivo
    auto * resultado = new std::unordered_map<std::string , std::string>();
    //Agrupar Recursivo 2.0

    int cantidadDePalabras = grafo->getIndiceVertices()->size()/cantidadDeGrupos;
    std::cout << "Cantidad de palabras por grupo: " << cantidadDePalabras << std::endl;

    //Vertice no tiene ruta porque no se puede usar para agrupar
    grafo->getIndiceVertices()->at(palabra)->setRuta(false);
    grafo->getIndiceVertices()->at(palabra)->leido = true;

    //complejo -> desde -> hasta
    for(int i = 0; i < cantidadDeGrupos ; i++) {
        if(grafo->getIndiceVertices()->at(palabra)->mejorArista != grafo->getIndiceVertices()->at(palabra)->ultimaArista)
        {
            std::cout << "MAPA NUMERO :" << i << std::endl;
            AgruparRecursivo(palabra, i, cantidadDePalabras, resultado);
        }


        auto resultadoIt = resultado->begin();
        for (resultadoIt; resultadoIt != resultado->end(); ++resultadoIt)
            std::cout << "(Agrupar Recursivo) Palabra: " << resultadoIt->first << " Grupo: " << resultadoIt->second
                      << std::endl;
    }

    return resultado;
}

//Nota: no se pueden usar la palabra de inicio 2 veces, esta solo se llama en el for
//Duracion : O(n^2)
void Algoritmos::AgruparRecursivo(std::string palabra,int grupoActual ,int cantidadDePalabras, std::unordered_map<std::string , std::string> * resultado) {
    std::cout << "Curanderos apunta a :"<< grafo->getIndiceVertices()->at("curanderos")->mejorArista->getVerticeDestino()->palabra <<std::endl;
    Arista * aristaActual = grafo->getIndiceVertices()->at(palabra)->mejorArista;
    Arista * ultimaArista =  grafo->getIndiceVertices()->at(palabra)->ultimaArista;

    //Si no se ha leido marquela como leida y reduzca la cantidad de palabras
    if(grafo->getIndiceVertices()->at(palabra)->leido == false) {
        cantidadDePalabras--;
        grafo->getIndiceVertices()->at(palabra)->leido = true;
    }

    // Condicion de parada : Si es la ultima arista del vertice termine
    if(cantidadDePalabras == 0 || aristaActual == ultimaArista)
    {
        resultado->insert(std::pair<std::string , std::string>(aristaActual->getVerticeDestino()->palabra, std::to_string(grupoActual)));
        std::cout << "ERROR" << std::endl;
        return;
    }


    if(!aristaActual->getSiguiente()->getVerticeDestino()->ruta && aristaActual->getSiguiente() != ultimaArista) //aristaActual ("x") -> aristaSiguiente ("curanderos") && aristaActual("x") != es su ultima arista
    {
        aristaActual = aristaActual->getSiguiente(); // aristaActual("curanderos")
    }
    else if(!aristaActual->getSiguiente()->getVerticeDestino()->ruta && aristaActual->getSiguiente() == ultimaArista)
    {
        return;
    }

   //Agregar palabra del vertice actual a resultado;
    resultado->insert(std::pair<std::string , std::string>(aristaActual->getVerticeDestino()->palabra, std::to_string(grupoActual) ));
    //Mejor arista apunta a la siguiente arista
    //Recursion: Seguir agrupando pero ahora necesito una palabra menos y ya no uso es ruta papu
    aristaActual = aristaActual->getSiguiente();
    grafo->getIndiceVertices()->at(palabra)->mejorArista = aristaActual;

    AgruparRecursivo(aristaActual->getVerticeDestino()->palabra,grupoActual ,cantidadDePalabras, resultado);
}

void Algoritmos::Agrupar2(int cantidadGrupos, std::string palabraInicial)
{

    // cantidad de grupos cada grupo es un hashmap [palabra, #numero de grupo]
    std::unordered_map<std::string , int> * arrayResultados [cantidadGrupos];
    //cantidad de palabras por grupo, no se cumple necesariamente
    int cantidadDePalabras = grafo->getIndiceVertices()->size()/cantidadGrupos;
    std::cout << "Cantidad de palabras por grupo: " << cantidadDePalabras << std::endl;

    for(int i = 0; i < cantidadGrupos ; i++)
        arrayResultados[i] = new std::unordered_map<std::string , int>();

    for(int i = 0; i < cantidadGrupos ; i++)
    {
        //get la siguiente palabra
        std::string palabra = grafo->getIndiceVertices()->at(palabraInicial)->primerArista->getVerticeDestino()->palabra;
        AgruparRecursivo2(palabra, palabraInicial, i, cantidadDePalabras, arrayResultados[i]);
        grafo->getIndiceVertices()->at(palabraInicial)->mejorArista = grafo->getIndiceVertices()->at(palabraInicial)->mejorArista->getSiguiente();
    }

    for(int j = 0; j < cantidadGrupos; j++)
    {
        auto resultadoIt = arrayResultados[j]->begin();
        for (resultadoIt; resultadoIt != arrayResultados[j]->end(); ++resultadoIt)
        {
            std::cout << "(Agrupar Recursivo) Palabra: " << resultadoIt->first << " Grupo: " << resultadoIt->second << std::endl;
        }
    }

}

//Nota: se permiten repeticiones
//Duracion : O(n)
void Algoritmos::AgruparRecursivo2(std::string palabra,std::string palabraInicial, int grupoActual, int cantidadDePalabras, std::unordered_map<std::string, int> *map)
{
    //Vertice apunta a la aristaActual
    Arista * aristaActual = grafo->getIndiceVertices()->at(palabra)->mejorArista;
    Arista * ultimaArista =  grafo->getIndiceVertices()->at(palabra)->ultimaArista;

    //Condicion de parada
    //#1 : se agruparon las palabras deseadas
    //#2 : ruta del vertice agotada (no tiene mas relaciones distintas)
    //#3 : la palabra que actual es la palabra inicial
    if(cantidadDePalabras == 1 || aristaActual == ultimaArista || palabra == palabraInicial)
    {
        //cantidadDePalabras - 1 = 0, termina
        map->insert(std::pair<std::string , int>(aristaActual->getVerticeDestino()->palabra, grupoActual));
        return;
    }

    //Sino es la condicion de parada entonces agregue la palabra al hash actual
    map->insert(std::pair<std::string , int>(aristaActual->getVerticeDestino()->palabra, grupoActual));

    //Vertice va a apuntar a su arista siguiente
    aristaActual = aristaActual->getSiguiente();
    grafo->getIndiceVertices()->at(palabra)->mejorArista = aristaActual;
    //No importa que relacion sea ya este o no, siempre acerquese a la condicion de parada
    cantidadDePalabras--;

    //Get la palabra de donde la arista actual apunta para continua en depth
    AgruparRecursivo2(aristaActual->getVerticeDestino()->palabra,palabraInicial,grupoActual ,cantidadDePalabras, map);
}

#endif //CASO_04_ALGORITMOS_H
