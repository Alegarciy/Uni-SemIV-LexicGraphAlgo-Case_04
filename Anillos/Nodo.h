//
// Created by alega on 3/31/2020.
//

#ifndef CASO03_02_NODO_H
#define CASO03_02_NODO_H
#include <iostream>

template <typename T>
class Node{
public:
    Node();
    Node(T);

    Node *next;
    T value;
};

template <typename T>
Node<T>::Node()
{
    this->value = 0;
    this->next = 0;
}

template <typename T>
Node<T>::Node(T value)
{
    this->value = value;
    this->next = nullptr;
}
#endif //CASO03_02_NODO_H
