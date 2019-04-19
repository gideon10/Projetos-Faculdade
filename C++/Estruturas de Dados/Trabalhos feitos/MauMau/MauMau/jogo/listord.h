#ifndef LISTORD_H
#define LISTORD_H
#include "node.h"

#include <iostream>
using namespace std;

class ListOrd
{
 private:
    Node *head;
    int qtd;

 public:
    ListOrd();
 bool Push(Carta *A);
 bool Pop(Carta *B,char v,char n);
 bool PopFront(Carta *C);
 int size();
 void esvazia();
 int qtdDePts();


};

#endif // LISTORD_H
