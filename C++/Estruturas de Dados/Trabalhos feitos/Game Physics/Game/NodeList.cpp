#include "NodeList.h"

NodeList::NodeList()
{
    next=0;
}

NodeList *NodeList::MontaNo(PosicaoDoObjeto *B)
{
    NodeList *p= new NodeList();
    if(!p)
        return p;

    p->A= *B;
    return p;
}

void NodeList::DesmontaNo(NodeList *N, PosicaoDoObjeto *Obj)
{
    *Obj= N->A;
    delete N;
}
