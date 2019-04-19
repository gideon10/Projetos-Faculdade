#ifndef LISTDC_H
#define LISTDC_H
#include "noded.h"

#include <iostream>
using namespace std;

class ListDC
{
 private:
   NodeD *head;
   NodeD *iterator;
   int qtd;

 public:
    ListDC();
 bool Push(int num);
 bool Pop(int n);
 void operator ++(){iterator= iterator->next;}
 void operator ++(int){iterator= iterator->next;}
 void operator --(){iterator= iterator->prev;}
 void operator --(int){iterator= iterator->prev;}
 void operator +=(int i);
 void operator -=(int i);
 void inicializa_Iterator(){iterator=head;}
 void inicializa_Head(){head=0;}
 int size(){return qtd;}
 int getN(){return (iterator->n);}
 int getVencedor(){return (head->n);}

};

#endif // LISTDC_H
