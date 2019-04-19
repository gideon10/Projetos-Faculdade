#include "noded.h"

NodeD::NodeD()
{
    next=0;
    prev=0;
    n=0;
}

NodeD *NodeD::MontaNo(int i)
{
    NodeD *p= new NodeD;
    if(!p)
        return p;
    p->n= i;
    return p;
}

void NodeD::DesmontaNo(NodeD *N)
{
    delete N;
}
