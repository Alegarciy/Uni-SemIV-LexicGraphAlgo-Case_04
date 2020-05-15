#ifndef CASO_04_PODERARISTA_H
#define CASO_04_PODERARISTA_H

#include <algorithm>

//PoderArista almacena la cantidad de veces que una relacion se repite entre dos palabras (vertices)
//Guarda los distintos parrafos donde la relacion aparece

class PoderArista{
private:
    //Numero de parrafo(s) al que la arista pertenece
    std::vector<int> * parrafos;
    //Cuantas veces se encuentra la relacion origen (vertice) -> destino (vertice)
    int poder;
public:
    PoderArista(int parrafo);
    int getPoder();
    void aumentarPoder(int parrafo);
    std::vector<int> * getParrafos();
};

PoderArista::PoderArista(int parrafo) {
    parrafos = new std::vector<int>();
    parrafos->push_back(parrafo);
    poder = 1;
}

int PoderArista::getPoder() {
    return poder;
}

void PoderArista::aumentarPoder(int parrafo) {
    if(std::find(parrafos->begin(), parrafos->end(), parrafo) == parrafos->end()) // Si parrafo no esta agregue nuevo a parrafos
        parrafos->push_back(parrafo);
    poder++;
}

std::vector<int> *PoderArista::getParrafos() {
    return parrafos;
}


#endif //CASO_04_PODERARISTA_H
