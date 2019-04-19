#ifndef TREE_H
#define TREE_H

#include "Node.h"

namespace Gideon { // Início

template <typename Type>
class Tree
{
private:
    Node<Type> *Root;
    int qtd;

    bool Insert(const Type &A, Node<Type> **R);   
    bool Delete(Node<Type> **R, const Type &key, Type *A, bool *Achou);
    bool Search(Node<Type> *R, const Type &key, Type **B);
    void Esvazia(Node<Type> **R);
    void Pre_Order(Node<Type> *R);
    void In_Order(Node<Type> *R);
    void Pos_Order(Node<Type> *R);
    void RSD(Node<Type> **R);
    void RDD(Node<Type> **R);
    void RSE(Node<Type> **R);
    void RDE(Node<Type> **R);
    Node<Type> *Maximum(Node<Type> *R);

public:    
    Tree();
    ~Tree();
    void Insert(const Type &A);
    void Delete(const Type &key, Type *A, bool *Achou);
    bool Search(const Type &key, Type **B);
    void Esvazia();
    void Pre_Order();
    void In_Order();
    void Pos_Order();
    int size()const{return qtd;}

};

template <typename Type>
Tree<Type>::Tree()
{
    Root=0;
    qtd=0;
}

template <typename Type>
Tree<Type>::~Tree()
{
    Esvazia(&Root);
    qtd=0;
}

template <typename Type>
void Tree<Type>::Insert(const Type &A)
{
    Insert(A,&Root);
}

template <typename Type>
bool Tree<Type>::Insert(const Type &A, Node<Type> **R)
{
    if(!(*R))
    {
        *R= Node<Type>::MontaNO(A);
        qtd++;
        return true;
    }

    if(A < (*R)->Dado)
    { // Vai para a esquerda!

        if(!Insert(A, &((*R)->Left)) )
            return false;         // Subárvore da esquerda não cresceu.

        if((*R)->fb == 0)
        {
            (*R)->fb= -1;
            return true;
        }

        if((*R)->fb == 1)
        {
            (*R)->fb= 0;
            return false;
        }

        //fb = -1 iria para -2 -->> ROTAÇÃO!
        if(((*R)->Left)->fb == -1)
        {
            RSD(R);             // Rotação simples à direita.
            return false;
        }

        RDD(R);                 // Rotação dupla à direita.
        return false;
    }

    // Vai para a direita!
    if(!Insert(A, &((*R)->Right)) )
        return false;           // Subárvore da direita não cresceu.

    if((*R)->fb == 0)
    {
        (*R)->fb= 1;
        return true;
    }

    if((*R)->fb == -1)
    {
        (*R)->fb= 0;
        return false;
    }

    // fb= 1 iria para 2    -->> ROTAÇÃO!
    if(((*R)->Right)->fb == 1)
    {
        RSE(R);             // Rotação simples à esquerda.
        return false;
    }

    RDE(R);                // Rotação dupla à esquerda.
    return false;
}

template <typename Type>
void Tree<Type>::Delete(const Type &key, Type *A, bool *Achou)
{
    Delete(&Root,key,A,Achou);
}

template <typename Type>
bool Tree<Type>::Delete(Node<Type> **R, const Type &key, Type *A, bool *Achou)
{
    if(!(*R))
    {  // Elemento não existe.
        *Achou= false;
        return false;
    }

    if(key < (*R)->Dado)
    {  // Vai para a esquerda.
        if(Delete(&((*R)->Left), key, A, Achou))
        { // Reduziu a subárvore da esquerda.
            if((*R)->fb == -1)
            {
                (*R)->fb= 0;
                return true;
            }

            if((*R)->fb == 0)
            {
                (*R)->fb= 1;
                return false;
            }

            // fb= 1 iria para 2    -->> ROTAÇÃO!
            if(((*R)->Right)->fb != -1)
            {
                RSE(R);               // Rotação simples à esquerda.
                return ( !((*R)->fb) );
            }

            RDE(R);                   // Rotação dupla à esquerda.
            return true;
        }
        // Veio da esquerda e não houve alteração.
        return false;
    }

    if(key > (*R)->Dado)
    {   // Vai para a direita.
        if(Delete(&((*R)->Right), key, A, Achou))
        { // Reduziu a subárvore da direita.
            if((*R)->fb == 1)
            {
                (*R)->fb= 0;
                return true;
            }

            if((*R)->fb == 0)
            {
                (*R)->fb= -1;
                return false;
            }

            // fb= -1 iria para -2   -->> ROTAÇÃO!
            if(((*R)->Left)->fb != 1)
            {
                RSD(R);                 // Rotação simples à direita.
                return ( !((*R)->fb) );
            }

            RDD(R);                     // Rotação dupla à direita.
            return true;
        }
        // Veio da direita e não houve alteração.
        return false;
    }

    // Achou !!!

    if( !((*R)->Left) )
    { // Não tem filho à esquerda.
        Node<Type> *X= (*R)->Right;
        Node<Type>::DesmontaNO(*R, A);
        *R= X;
        *Achou= true;
        qtd--;
        return true;
    }

    if( !((*R)->Right) )
    { // Só tem filho da esquerda.
        Node<Type> *X= (*R)->Left;
        Node<Type>::DesmontaNO((*R), A);
        *R= X;
        *Achou= true;
        qtd--;
        return true;
    }

    // Achou e tem 2 filhos !!!

    Node<Type> *Max= Tree::Maximum((*R)->Left);
    Type Aux= Max->Dado;
    Max->Dado= (*R)->Dado;
    (*R)->Dado= Aux;

    if(Delete(&((*R)->Left),key,A,Achou))
    { // Reduziu a subárvore da esquerda.
        if((*R)->fb == -1)
        {
            (*R)->fb= 0;
            return true;
        }

        if((*R)->fb == 0)
        {
            (*R)->fb= 1;
            return false;
        }

        // fb= 1 iria para 2  -->> ROTAÇÃO!
        if( ((*R)->Right)->fb != -1 )
        {
            RSE(R);                 // Rotação simples à esquerda.
            return ( !((*R)->fb) );
        }

        RDE(R);                     // Rotação dupla à esquerda.
        return true;
    }

    // Veio da esquerda e não houve alteração.
    return false;
}

template <typename Type>
bool Tree<Type>::Search(const Type &key, Type **B)
{
    return ( Search(Root, key, B) );
}

template <typename Type>
bool Tree<Type>::Search(Node<Type> *R,const Type &key, Type **B)
{
    if(!R)
        return false;

    if(key == R->Dado)
    {
        *B= &(R->Dado);
        return true;
    }

    if(key < R->Dado)
        return ( Search(R->Left, key, B) );

    return ( Search(R->Right, key, B) );
}

template <typename Type>
void Tree<Type>::Esvazia()
{
    Esvazia(&Root);
    qtd=0;
}

template <typename Type>
void Tree<Type>::Esvazia(Node<Type> **R)
{
    if((*R))
    {
        Esvazia(&((*R)->Left));
        Esvazia(&((*R)->Right));

        delete (*R);
        *R=0;
    }
}

template <typename Type>
void Tree<Type>::Pre_Order()
{
    Pre_Order(Root);
}

template <typename Type>
void Tree<Type>::Pre_Order(Node<Type> *R)    // Imprime raiz, esquerda e direita.
{
    if(R)
    {
        Node<Type>::Print_Dado(R->Dado);
        Pre_Order(R->Left);
        Pre_Order(R->Right);
    }
}

template <typename Type>
void Tree<Type>::In_Order()
{
    In_Order(Root);
}

template <typename Type>
void Tree<Type>::In_Order(Node<Type> *R)    // Imprime esquerda, raiz e direita.
{
    if(R)
    {
        In_Order(R->Left);
        Node<Type>::Print_Dado(R->Dado);
        In_Order(R->Right);
    }
}

template <typename Type>
void Tree<Type>::Pos_Order()
{
    Pos_Order(Root);
}

template <typename Type>
void Tree<Type>::Pos_Order(Node<Type> *R)   // Imprime esquerda, direita e raiz.
{
    if(R)
    {
       Pos_Order(R->Left);
       Pos_Order(R->Right);
       Node<Type>::Print_Dado(R->Dado);
    }
}

template <typename Type>
void Tree<Type>::RSD(Node<Type> **R)      // Rotação simples à direita.
{
    Node<Type> *a= *R;
    Node<Type> *b= a->Left;

    *R= b;
    a->Left= b->Right;
    b->Right= a;
    if(b->fb == 0)
        b->fb= 1;
    else    // b->fb = -1
        a->fb= b->fb = 0;
}

template <typename Type>
void Tree<Type>::RDD(Node<Type> **R)      // Rotação dupla à direita.
{
    Node<Type> *a= *R;
    Node<Type> *b= a->Left;
    Node<Type> *c= b->Right;

    *R= c;
     b->Right= c->Left;
     a->Left= c->Right;
     c->Left= b;
     c->Right= a;
     if(c->fb == -1)
     {
        a->fb=1;
        b->fb=0;
        c->fb=0;
     }
     else
     {
        if(c->fb == 0)
            a->fb=b->fb=0;
        else
        {  // c->fb= 1.
            a->fb=0;
            b->fb= -1;
            c->fb=0;
        }
     }
}

template <typename Type>
void Tree<Type>::RSE(Node<Type> **R)     // Rotação simples à esquerda.
{
    Node<Type> *a= *R;
    Node<Type> *b= a->Right;

    *R= b;
    a->Right= b->Left;
    b->Left= a;
    if(b->fb == 0)
        b->fb= -1;
    else  // b->fb= 1
        a->fb= b->fb= 0;
}

template <typename Type>
void Tree<Type>::RDE(Node<Type> **R)     // Rotação dupla à esquerda.
{
    Node<Type> *a= *R;
    Node<Type> *b= a->Right;
    Node<Type> *c= b->Left;

    *R= c;
    a->Right= c->Left;
    b->Left= c->Right;
    c->Left= a;
    c->Right= b;
    if(c->fb == -1)
    {
        a->fb= c->fb= 0;
        b->fb= 1;
    }
    else
    {
        if(c->fb == 0)
            a->fb= b->fb= 0;
        else
        { // c->fb = 1
            a->fb= -1;
            b->fb= c->fb =0;
        }
    }
}

template <typename Type>
Node<Type> * Tree<Type>::Maximum(Node<Type> *R)
{
    if(!R)
        return NULL;
    if( !(R->Right) )
        return R;

    return Maximum(R->Right);
}



} // Fim

#endif // TREE_H
