#ifndef LISTORD_H
#define LISTORD_H
#include "node.h"

class ListOrd
{
 private:
    Node *head;
    int qtd;

 public:
    ListOrd(){qtd=0,head=0;}
 bool Push(Aluno *A);
 bool Pop(long long matricula,Aluno *C);
 int getQtd();
 void lista(); /// metodo para teste.

};

#endif // LISTORD_H
