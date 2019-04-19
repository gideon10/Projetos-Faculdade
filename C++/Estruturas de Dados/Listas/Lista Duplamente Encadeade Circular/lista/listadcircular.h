#ifndef LISTADCIRCULAR_H
#define LISTADCIRCULAR_H
#include "noded.h"

class ListaDcircular
{
 private:
    NodeD *head;
    int qtd;

 public:
    ListaDcircular(){head=0,qtd=0;}
 bool Push(Aluno *A);
 bool Pop(long long mat,Aluno *Obj);
 int size(){return qtd;}
 void lista();

};

#endif // LISTADCIRCULAR_H
