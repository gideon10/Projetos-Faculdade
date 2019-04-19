#include "NodeLC.h"

NodeLC *NodeLC::MontaNo(PosicaoDoObjeto *B)
{
    NodeLC *p= new NodeLC();
    if(!p)
        return p;

    p->A= *B;
    return p;
}

void NodeLC::DesmontaNo(NodeLC *N, PosicaoDoObjeto *obj)
{
    *obj= N->A;
    delete N;
}
