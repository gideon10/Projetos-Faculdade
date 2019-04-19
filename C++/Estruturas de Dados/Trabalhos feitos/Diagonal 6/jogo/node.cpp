#include "node.h"

Node::Node()
{
    next=0;
}

Node *Node::MontaNo(Ficha *B)
{
    Node *D= new Node;
    if(!D)
        return D;

    D->A= *B;
    return D;
}

void Node::DesmontaNo(Node *N, Ficha *C)
{
    *C= N->A;
    delete N;
}
