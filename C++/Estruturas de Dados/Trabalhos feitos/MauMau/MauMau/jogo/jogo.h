#ifndef JOGO_H
#define JOGO_H

#include <iostream>
#include "listdc.h"
#include "stack.h"
#include "listord.h"
#include <fstream>

using namespace std;

class Jogo
{
 public:

 void lerCartas_Distribui(ListDC *LC,ListOrd *v,Stack *M,int J);
 void Distribui_Cartas(ListDC *LC,ListOrd *v,Stack *M);
 void funcaoDaCarta(ListDC *LC,ListOrd *v,Stack *M,Stack *L,string *s,Carta A);
 void verificaMonte(Stack *M,Stack *L);

 void Jogar();


};

#endif // JOGO_H
