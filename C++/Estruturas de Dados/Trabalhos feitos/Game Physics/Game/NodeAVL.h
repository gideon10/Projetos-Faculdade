#ifndef NODEAVL_H
#define NODEAVL_H

#include <ObjetosDoJogo.h>
#include <iostream>

using namespace std;

class NodeAVL
{
public:
    ObjetosDoJogo D;
    NodeAVL *Left,*Right;
    int fb;

    NodeAVL();
    static NodeAVL *MontaNo(ObjetosDoJogo *A);
    static void DesmontaNo(NodeAVL *N,ObjetosDoJogo *Obj);

    static void ImprimeNo(ObjetosDoJogo *S, NodeAVL *N);
};

#endif // NODEAVL_H
