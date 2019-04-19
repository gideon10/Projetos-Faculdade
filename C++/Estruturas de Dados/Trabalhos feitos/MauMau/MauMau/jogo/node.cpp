#include "node.h"

Node::Node()
{
    next=0;
}

Node *Node::MontaNo(Carta *A)
{
    Node *p= new Node;
    if(!p)
        return p;
    p->A= *A;
    return p;
}

void Node::DesmontaNo(Node *N, Carta *B)
{
    *B= N->A;
    delete N;
}
