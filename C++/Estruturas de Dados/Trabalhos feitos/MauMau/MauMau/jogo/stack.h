#ifndef STACK_H
#define STACK_H
#include "node.h"

#include <iostream>
using namespace std;

class Stack
{
 private:
    Node *Top;
    int qtd;

 public:
    Stack();
 bool Push(Carta *A);
 bool Pop(Carta *B);
 int size();
 void esvazia();
 bool isEmpty(){return !Top;}
 Carta getTop(){return (Top->A);}

};

#endif // STACK_H
