#ifndef LIST_H
#define LIST_H
#include "node.h"

class List
{
 private:
    Node *head;
    int qtd; //qtd de elementos na lista.

 public:
    List(){head=0,qtd=0;}
 bool Push(Aluno *A);
 bool Pop(long long mat, Aluno *C);
 int getQtd();

};

#endif // LIST_H
