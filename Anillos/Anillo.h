//
// Created by alega on 3/31/2020.
//

#ifndef CASO03_02_ANILLO_H
#define CASO03_02_ANILLO_H
#include "Bola.h"
#include "ListaSimple.h"
#include <cmath>
class Anillo {

public:
    Centro * centro = new Centro(0,0);
    int radio = 40;
    // Maximo de circulos por anillo
    int maxCirculos = 10;
    int cantidadBolas;
    //Bola * arregloBola [];
    LinkedList<Bola*> listaBolas;

    void PrintPos();
    Anillo(int cantidadBolas);



};

Anillo::Anillo(int cantidadBolas) {
    this->cantidadBolas = cantidadBolas;

    // Bola central
    listaBolas.insert(new Bola(centro,0,0));
    cantidadBolas -= 1;

    // Cantidad de bolas por anillo, redondeo para arriba
    int Bolas_porAnillos = ceil(cantidadBolas / 10.0);
    int posAnillo = 1;

    // Crecimiento angular
    int particionesAngulo = ceil(cantidadBolas/Bolas_porAnillos) + 1;
    int crecimientoAngular = 0;

    //Llenado de bolas
    for(int i = 1; i <= cantidadBolas; i++) {

        if(posAnillo > Bolas_porAnillos) {
            posAnillo = 1;
            crecimientoAngular ++;
        }
        posAnillo++;
        int tempRes = cantidadBolas % Bolas_porAnillos;
        listaBolas.insert(new Bola(centro,(radio * posAnillo)*cos(2*3.14*crecimientoAngular/particionesAngulo),(radio * posAnillo)*sin(2*3.14*crecimientoAngular/particionesAngulo)));

    }


}

void Anillo::PrintPos() {
    Node<Bola*> * temp = this->listaBolas.first;
    while(temp != nullptr)
    {
        temp->value->printPos();
        temp = temp->next;
    }
}

#endif //CASO03_02_ANILLO_H