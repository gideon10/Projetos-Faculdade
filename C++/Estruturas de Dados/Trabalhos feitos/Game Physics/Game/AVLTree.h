#ifndef AVLTREE_H
#define AVLTREE_H

#include <NodeAVL.h>
#include <PosicaoDoObjeto.h>
#include <iostream>

class AVLTree
{
private:
    NodeAVL *root;

    static bool InsereAVL(ObjetosDoJogo *A,NodeAVL **R);
    static bool DeleteAVL(PosicaoDoObjeto *B,NodeAVL **R,ObjetosDoJogo *Obj,bool *E);
    static void In_Order(NodeAVL *R);
    static bool Search(PosicaoDoObjeto *C, ObjetosDoJogo *Obj, NodeAVL *R);
    static bool AlterarPtsDeAcao(PosicaoDoObjeto *D,int **pt,NodeAVL *R);
    static bool AlterarHP(PosicaoDoObjeto *D, int **p,NodeAVL *R);
    static void RSD(NodeAVL **R); // ROTAÇÃO SIMPLES À DIREITA.
    static void RDD(NodeAVL **R); // ROTAÇÃO DUPLA À DIREITA.
    static void RSE(NodeAVL **R); // ROTAÇÃO SIMPLES À ESQUERDA.
    static void RDE(NodeAVL **R); // ROTAÇÃO DUPLA À ESQUERDA.
    static NodeAVL *Maximo(NodeAVL *R);
    static void Esvazia(NodeAVL **R);

public:
    AVLTree();
    void InsereAVL(ObjetosDoJogo *A);
    void DeleteAVL(PosicaoDoObjeto *B, ObjetosDoJogo *Obj, bool *E);
    void In_Order();
    bool Search(PosicaoDoObjeto *C, ObjetosDoJogo *Obj);
    bool AlterarPtsDeAcao(PosicaoDoObjeto *D, int **pt);
    bool AlterarHP(PosicaoDoObjeto *D,int **p);
    void Esvazia();
    bool isEmpty(){return !root;}

};

#endif // AVLTREE_H
