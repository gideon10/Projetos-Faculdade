#ifndef LISTACIRCULAR_H
#define LISTACIRCULAR_H

#include <NodeLC.h>
#include <iostream>

using namespace std;

class ListaCircular
{
private:
    NodeLC *head,*tail;
    NodeLC *iterator;
    int qtd;

public:
    ListaCircular();
    void Push_Back(PosicaoDoObjeto *B);
    bool Pop(int numJog,PosicaoDoObjeto *obj);
    void operator ++(int){iterator=iterator->next;}
    void IteratorRecebeHead(){iterator=head;}
    PosicaoDoObjeto *getDado()const{return (&(iterator->A));}
    int size()const{return qtd;}
    bool isEmpty()const{return !head;}
    void Esvazia();

    void Listar(); // teste

};

#endif // LISTACIRCULAR_H
