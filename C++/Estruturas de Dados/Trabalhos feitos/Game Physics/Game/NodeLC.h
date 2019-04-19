#ifndef NODELC_H
#define NODELC_H

#include "PosicaoDoObjeto.h"

class NodeLC
{
public:
    PosicaoDoObjeto A;
    NodeLC *next;

    NodeLC(){next=0;}
    static NodeLC *MontaNo(PosicaoDoObjeto *B);
    static void DesmontaNo(NodeLC *N,PosicaoDoObjeto *obj);

};

#endif // NODELC_H
