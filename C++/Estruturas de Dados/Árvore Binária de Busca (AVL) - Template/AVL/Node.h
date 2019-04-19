#ifndef NODE_H
#define NODE_H

#include <bits/stdc++.h>

template <typename Type>
class Node
{
public:
    Type Dado;
    Node<Type> *Left, *Right;
    int fb;     // Fator de balanceamento.

    Node();
    static Node<Type> *MontaNO(const Type &D);
    static void DesmontaNO(Node<Type> *N, Type *Obj);
    static void Print_Dado(const Type &d);
};

template <typename Type>
Node<Type>::Node()
{
    Left=Right=0;
    fb=0;
}

template <typename Type>
Node<Type> * Node<Type>::MontaNO(const Type &D)
{
    Node<Type> *p= new Node<Type>();
    if(!p) throw std::string("Memória cheia! - Função: MontaNo");

    p->Dado= D;
    return p;
}

template <typename Type>
void Node<Type>::DesmontaNO(Node<Type> *N, Type *Obj)
{
    *Obj= N->Dado;
    delete N;
}

template <typename Type>
void Node<Type>::Print_Dado(const Type &d)
{
    std::cout<<d<<"\n";
}

#endif // NODE_H
