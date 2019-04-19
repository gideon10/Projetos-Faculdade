#ifndef LISTAD_H
#define LISTAD_H
#include "noded.h"

class ListaDOrd
{
 private:
    NodeD *head;
    int qtd;

 public:
    ListaDOrd();
 bool Push(Aluno *B);
 bool Pop(long long matricula, Aluno *Obj);
 int size();
 void lista(); /// metodo para teste.

};

#endif // LISTAD_H
