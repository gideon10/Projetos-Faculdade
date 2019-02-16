#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;

namespace Gideon {

template <class tipo>
class Node
{
public:
    tipo Dado;
    Node *next;

    Node(){next=0;}
    static Node *MontaNo(tipo *A);
    static void Desmontano(Node *N,tipo *Obj);
};

template <class tipo>
Node<tipo> *Node<tipo>::MontaNo(tipo *A)
{
    Node<tipo> *p= new Node<tipo>();
    if(!p)
        throw string("Memória insuficiente !");

    p->Dado= *A;
    return p;
}

template <class tipo>
void Node<tipo>::Desmontano(Node *N, tipo *Obj)
{
    *Obj= N->Dado;
    delete N;
}

}
#endif // NODE_H
