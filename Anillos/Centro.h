//
// Created by alega on 3/31/2020.
//

#ifndef CASO03_02_CENTRO_H
#define CASO03_02_CENTRO_H
class Centro {
public :
    int pointX, pointY;
    Centro(int pointX, int pointY);
};

Centro::Centro(int pointX, int pointY) {
    this->pointX = pointX;
    this->pointY = pointY;
}
#endif //CASO03_02_CENTRO_H
