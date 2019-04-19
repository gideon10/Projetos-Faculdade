#include "noded.h"

NodeD *NodeD::MontaNo(Aluno *A)
{
    NodeD *p= new NodeD;
    if(!p)
        return p;
    p->A= *A;
    return p;
}

void NodeD::DesmontaNo(NodeD *N, Aluno *Obj)
{
    *Obj= N->A;
    delete N;
}
