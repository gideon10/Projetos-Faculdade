#ifndef STACK_H
#define STACK_H
#include "node.h"

class Stack
{
 private:
    Node *Top;

 public:
    Stack(){Top=0;}
 bool Push(Ficha *A);
 bool Pop(Ficha *A);
 int size();

};

#endif // STACK_H
