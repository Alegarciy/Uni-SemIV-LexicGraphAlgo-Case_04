//
// Created by alega on 3/31/2020.
//

#ifndef CASO03_02_LISTASIMPLE_H
#define CASO03_02_LISTASIMPLE_H
#include "Nodo.h"
template <typename T>
class LinkedList{
private:
public:
    Node<T> *first;
    Node<T> *last;
    LinkedList();
    void insert(T);
    //void Delete();
    void print();
};

template<typename T>
LinkedList<T>::LinkedList() {
    this->first = this->last = nullptr;
}

template<typename T>
void LinkedList<T>::insert(T value) {
    if(this->first == nullptr)
    {
        this->first = new Node<T>(value);
        this->last = first;
    } else {
        this->last->next = new Node<T>(value);
        this->last = this->last->next;
    }
}
#endif //CASO03_02_LISTASIMPLE_H