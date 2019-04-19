#include "stack.h"

bool Stack::Push(Ficha *A)
{
   Node *aux;

   aux= Top;
   Top= Node::MontaNo(A);
   if(!Top)
        return false;

   Top->next= aux;
   return true;
}

bool Stack::Pop(Ficha *A)
{
    if(!Top)// PILHA VAZIA.
        return false;

    Node *aux;
    aux= Top;
    Top= Top->next;
    Node::DesmontaNo(aux,A);
    return true;
}

int Stack::size()
{
    int cont=0;
    Node *aux= Top;

    while(aux)
    {
        cont++;
        aux= aux->next;
    }
    return cont;
}
