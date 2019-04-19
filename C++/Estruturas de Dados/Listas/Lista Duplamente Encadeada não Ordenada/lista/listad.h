#ifndef LISTAD_H
#define LISTAD_H
#include "noded.h"

class ListaD
{
 private:
    NodeD *head;
    int qtd;

 public:
    ListaD();
 bool Push(Aluno *B);
 bool Pop(long long matricula, Aluno *Obj);
 int size();
 void lista(); /// metodo para teste.

};

#endif // LISTAD_H
