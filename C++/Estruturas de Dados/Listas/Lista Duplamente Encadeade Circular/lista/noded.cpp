#include "noded.h"

NodeD::NodeD()
{
    next=prev=0;
}

NodeD *NodeD::MontaNo(Aluno *obj)
{
    NodeD *p= new NodeD;
    if(!p)
        return p;
    p->A= *obj;
    return p;
}

void NodeD::DesmontaNo(NodeD *N, Aluno *B)
{
    *B= N->A;
    delete N;
}
