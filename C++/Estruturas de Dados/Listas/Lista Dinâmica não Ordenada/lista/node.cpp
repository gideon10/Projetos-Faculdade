#include "node.h"

Node *Node::MontaNo(Aluno *B)
{
    Node *N= new Node;
    if(!N)
        return N;
    N->A= *B;
    return N;
}

void Node::DesmontaNo(Node *P, Aluno *B)
{
    *B= P->A;
    delete P;
}
