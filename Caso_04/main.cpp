#include <iostream>
#include<vector>
#include <string>
#include <map>

#include "Estructura/Grafo.h"
#include "CargarSustantivos/CargarSustantivos.h"
#include "Algoritmos/Algoritmos.h"

int main() {
    Algoritmos * algoritmos = new Algoritmos();
    //algoritmos->Agrupar2(100,"curanderos");
    algoritmos->PalabrasMasPoderosas(100000);
    //algoritmos->grafo->imprimir();
    algoritmos->PalabrasRelacionadas("curanderos");
    return 0;
}
