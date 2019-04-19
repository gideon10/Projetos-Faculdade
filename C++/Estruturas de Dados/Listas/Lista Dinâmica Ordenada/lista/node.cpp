#include "node.h"

Node::Node()
{
    next=0;
}

Node *Node::MontaNo(Aluno *B)
{
    Node *N= new Node;
    if(!N)
        return N;
    N->A= *B;
    N->next=0;
    return N;
}

void Node::DesmontaNo(Node *N, Aluno *C)
{
   *C= N->A;
    delete N;
}
