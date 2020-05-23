//
// Created by alega on 3/31/2020.
//

#ifndef CASO03_02_BOLA_H
#define CASO03_02_BOLA_H
#include <iostream>
#include "Centro.h"
using namespace std;

class Bola {

public :
    // Si es centro, centro = nullptr
    Centro * centro;
    int offset_X;
    int offset_Y;

    Bola(Centro * centro, int desplazamientoX, int desplazamientoY) ;
    void printPos();
};

Bola::Bola(Centro *centro, int desplazamientoX, int desplazamientoY) {
    this->centro = centro;
    this->offset_X = desplazamientoX;
    this->offset_Y = desplazamientoY;
}

void Bola::printPos() {
    cout << "" << this->centro->pointX + this->offset_X<< "," << this->centro->pointY  + this->offset_Y<< "" << endl;
}

#endif //CASO03_02_BOLA_H