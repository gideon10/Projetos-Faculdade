#ifndef NODELIST_H
#define NODELIST_H

#include <PosicaoDoObjeto.h>

class NodeList
{
public:
    PosicaoDoObjeto A;
    NodeList *next;

    NodeList();
    static NodeList *MontaNo(PosicaoDoObjeto *B);
    static void DesmontaNo(NodeList *N,PosicaoDoObjeto *Obj);
};

#endif // NODELIST_H
