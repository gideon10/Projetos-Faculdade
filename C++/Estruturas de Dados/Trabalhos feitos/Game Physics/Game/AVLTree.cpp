#include "AVLTree.h"

AVLTree::AVLTree()
{
    root=0;
}

void AVLTree::InsereAVL(ObjetosDoJogo *A)
{
    AVLTree::InsereAVL(A,&root);
}

bool AVLTree::InsereAVL(ObjetosDoJogo *A, NodeAVL **R)
{
    if(!(*R))
    {
        NodeAVL *P= NodeAVL::MontaNo(A);
        if(!P) throw std::string("Memória insuficiente!!");

        P->fb=0;
        *R= P;
        return true;
    }

    if((*A) < &((*R)->D))
    {  // VAI PARA ESQUERDA.
       if(!AVLTree::InsereAVL(A,&((*R)->Left)))
       { // SUBÁRVORE DA ESQUERDA NÃO CRESCEU.
           return false;
       }	
       if(!((*R)->fb))
       {
           (*R)->fb=-1;
           return true;
       }
       if((*R)->fb==1)
       {
           (*R)->fb=0;
           return false;
       }
       // fb=-1  iria p/-2 ----->>>> ROTACÃO!
       if(((*R)->Left)->fb==-1)
       {
            AVLTree::RSD(R); // ROTAÇÃO SIMPLES À DIREITA!
            return false;
       }
       AVLTree::RDD(R);   // ROTAÇÃO DUPLA À DIREITA!
       return false;
    }

    // VAI PARA DIREITA.
    if(!AVLTree::InsereAVL(A,&((*R)->Right)))
    { // SUBÁRVORE DA DIREITA NÃO CRESCEU.
       return false;
    }
    if(!((*R)->fb))
    {
       (*R)->fb=1;
       return true;
    }
    if((*R)->fb==-1)
    {
       (*R)->fb=0;
       return false;
    }
    // fb=1  iria p/2   ---->>>> ROTAÇÃO!
    if(((*R)->Right)->fb==1)
    {
        AVLTree::RSE(R);  // ROTAÇÃO SIMPLES À ESQUERDA!
        return false;
    }
    AVLTree::RDE(R); // ROTAÇÃO DUPLA À ESQUERDA!
    return false;
}

void AVLTree::DeleteAVL(PosicaoDoObjeto *B, ObjetosDoJogo *Obj, bool *E)
{
     AVLTree::DeleteAVL(B,&root,Obj,E);
}

bool AVLTree::DeleteAVL(PosicaoDoObjeto *B, NodeAVL **R, ObjetosDoJogo *Obj, bool *E)
{
    if(!(*R))
    {  // ELEMENTO NÃO EXISTE.
       *E=false;
       return false;
    }

    if((*B) < &((*R)->D))
    {// VAI PARA ESQUERDA.
        if(AVLTree::DeleteAVL(B,&((*R)->Left),Obj,E))
        {   // REDUZIU A SUBÁRVORE DA ESQUERDA.
            if((*R)->fb==-1)
            {
                (*R)->fb=0;
                return true;
            }
            if((*R)->fb==0)
            {
                (*R)->fb=1;
                return false;
            }
            // fb= 1  iria p/2  --->>> ROTAÇÃO!
            if(((*R)->Right)->fb!=-1)
            {
                AVLTree::RSE(R);     // ROTAÇÃO SIMPLES À ESQUERDA!
                return (!((*R)->fb));
            }
            AVLTree::RDE(R);     // ROTAÇÃO DUPLA À ESQUERDA!
            return true;
        }
        // VEIO DA ESQUERDA E NÃO HOUVE ALTERAÇÃO.
        return false;
    }

    if((*B) > &((*R)->D))
    {   // VAI PARA DIREITA.
        if(AVLTree::DeleteAVL(B,&((*R)->Right),Obj,E))
        {  // REDUZIU A SUBÁRVORE DA DIREITA.
            if((*R)->fb==1)
            {
               (*R)->fb=0;
               return true;
            }
            if((*R)->fb==0)
            {
               (*R)->fb=-1;
               return false;
            }
            // fb= -1 iria p/-2 ---->>> FAZER ROTAÇÃO!
                                                                 //// if de antes --> if(((*R)->Left)->fb!=0 && ((*R)->Left)->fb!=1)
            if(((*R)->Left)->fb!=1)
            {
                AVLTree::RSD(R);         // ROTAÇÃO SIMPLES À DIREITA!
                return (!((*R)->fb));
            }
            AVLTree::RDD(R);       // ROTAÇÃO DUPLA À DIREITA!
            return true;
        }
        // VEIO DA DIREITA E NÃO HOUVE ALTERAÇÃO.
        return false;
    }

    // ACHOU !!
    if(!((*R)->Left))
    {// NÃO TEM FILHO À ESQUERDA.
        NodeAVL *X= (*R)->Right;
        NodeAVL::DesmontaNo((*R),Obj);
        *R= X;
        *E=true;
        return true;
    }
    if(!((*R)->Right))
    {// SÓ TEM FILHO DA ESQUERDA.
        NodeAVL *X= (*R)->Left;
        NodeAVL::DesmontaNo((*R),Obj);
        *R= X;
        *E=true;
        return true;
    }

    // ACHOU E TEM 2 FILHOS!!
    NodeAVL *Max= AVLTree::Maximo((*R)->Left);
    ObjetosDoJogo Aux= Max->D;
    Max->D= (*R)->D;
    (*R)->D= Aux;

    if(AVLTree::DeleteAVL(B,&((*R)->Left),Obj,E))
    { // REDUZIU A SUBÁRVORE DA ESQUERDA.
        if((*R)->fb==-1)
        {
           (*R)->fb=0;
           return true;
        }
        if((*R)->fb==0)
        {
           (*R)->fb=1;
           return false;
        }
        // fb= 1  iria p/2  --->>> FAZER ROTAÇÃO!
        if(((*R)->Right)->fb!=-1)
        {
            AVLTree::RSE(R);     // ROTAÇÃO SIMPLES À ESQUERDA!
            return (!((*R)->fb));
        }
        AVLTree::RDE(R);     // ROTAÇÃO DUPLA À ESQUERDA!
        return true;
    }
    // VEIO DA ESQUERDA E NÃO HOUVE ALTERAÇÃO.
    return false;
}

void AVLTree::In_Order()
{
    AVLTree::In_Order(root);
}

void AVLTree::In_Order(NodeAVL *R)
{
    if(R)
    {
        In_Order(R->Left);
        NodeAVL::ImprimeNo(&(R->D),R);
        In_Order(R->Right);
    }
}

bool AVLTree::Search(PosicaoDoObjeto *C, ObjetosDoJogo *Obj)
{
    return (AVLTree::Search(C,Obj,root));
}

bool AVLTree::Search(PosicaoDoObjeto *C, ObjetosDoJogo *Obj, NodeAVL *R)
{
    if(!R)
        return false;

    if((*C) == &(R->D))
    {
        *Obj= R->D;
        return true;
    }

    if((*C) < &(R->D))  // VAI PARA ESQUERDA.
       return (AVLTree::Search(C,Obj,R->Left));

    // VAI PARA DIREITA.
    return (AVLTree::Search(C,Obj,R->Right));
}

bool AVLTree::AlterarPtsDeAcao(PosicaoDoObjeto *D, int **pt)
{
    return AVLTree::AlterarPtsDeAcao(D,pt,root);
}

bool AVLTree::AlterarPtsDeAcao(PosicaoDoObjeto *D, int **pt, NodeAVL *R)
{
    if(!R)
        return false;
    if((*D) == &(R->D))
    {
        *pt= &((R->D).ptsDeAcao);
        return true;
    }

    if((*D) < &(R->D)) // VAI PARA ESQUERDA.
        return AVLTree::AlterarPtsDeAcao(D,pt,R->Left);
    // VAI PARA DIREITA.
    return AVLTree::AlterarPtsDeAcao(D,pt,R->Right);
}

bool AVLTree::AlterarHP(PosicaoDoObjeto *D, int **p)
{
    return AVLTree::AlterarHP(D,p,root);
}

void AVLTree::Esvazia()
{
    AVLTree::Esvazia(&root);
}

bool AVLTree::AlterarHP(PosicaoDoObjeto *D, int **p, NodeAVL *R)
{
    if(!R)
        return false;

    if((*D) == &(R->D))
    {
        *p= &((R->D).HP);
        return true;
    }

    if((*D) < &(R->D))
        return AVLTree::AlterarHP(D,p,R->Left);

    return AVLTree::AlterarHP(D,p,R->Right);
}

void AVLTree::RSD(NodeAVL **R) // ROTAÇÃO SIMPLES À DIREITA.
{
    NodeAVL *a= *R;
    NodeAVL *b= a->Left;

   *R= b;
    a->Left= b->Right;
    b->Right= a;
    if(!b->fb)
    {  // b->fb= 0.
        b->fb= 1;
    }
    else // b->fb= -1;
        a->fb=b->fb=0;
}

void AVLTree::RDD(NodeAVL **R) // ROTAÇÃO DUPLA À DIREITA.
{
    NodeAVL *a= *R;
    NodeAVL *b= a->Left;
    NodeAVL *c= b->Right;

    *R= c;
     b->Right= c->Left;
     a->Left= c->Right;
     c->Left= b;
     c->Right= a;
     if(c->fb==-1)
     {
        a->fb=1;
        b->fb=0;
        c->fb=0;
     }
     else
     {
        if(c->fb==0)
            a->fb=b->fb=0;
        else
        {// c->fb= 1.
            a->fb=0;
            b->fb= -1;
            c->fb=0;
        }
     }
}

void AVLTree::RSE(NodeAVL **R) // ROTAÇÃO SIMPLES À ESQUERDA.
{
    NodeAVL *a= *R;
    NodeAVL *b= a->Right;

    *R= b;
    a->Right= b->Left;
    b->Left= a;
    if(!b->fb)
    { // b->fb=0.
       b->fb= -1;
    }
    else // b->fb= 1;
       a->fb=b->fb=0;
}

void AVLTree::RDE(NodeAVL **R) // ROTAÇÃO DUPLA À ESQUERDA.
{
    NodeAVL *a= *R;
    NodeAVL *b= a->Right;
    NodeAVL *c= b->Left;

    *R= c;
    a->Right= c->Left;
    b->Left= c->Right;
    c->Left= a;
    c->Right= b;
    if(c->fb==-1)
    {
       a->fb=0;
       b->fb=1;
       c->fb=0;
    }
    else
    {
       if(c->fb==0)
           a->fb=b->fb=0;
       else
       {// c->fb= 1.
          a->fb=-1;
          b->fb=0;
          c->fb=0;
       }
    }
}

NodeAVL *AVLTree::Maximo(NodeAVL *R)
{
   if(!R)
       return NULL;
   if(!(R->Right))
        return R;
   return AVLTree::Maximo(R->Right);
}

void AVLTree::Esvazia(NodeAVL **R)
{
    if((*R))
    {
        AVLTree::Esvazia(&((*R)->Left));
        AVLTree::Esvazia(&((*R)->Right));

        if(!((*R)->Left) && !((*R)->Right))
        {
            NodeAVL *X= *R;
            *R=0;
            delete X;
        }
    }

}



