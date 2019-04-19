#include "queue.h"

bool Queue::Push(Ficha *A)
{
   Node *P= Node::MontaNo(A);
   if(!P)
      return P;

   P->next=0;
   if(!Head) // FILA VAZIA.
      Head= P;
   else
       Tail->next= P;

   Tail= P;
   return true;
}

bool Queue::Pop(Ficha *A)
{
    if(!Head)//FILA VAZIA.
        return false;

    Node *aux= Head;
    Head= Head->next;
    if(!Head)
        Tail=0;

    Node::DesmontaNo(aux,A);
    return true;
}

int Queue::size()
{
    Node *aux= Head;

    int c=0;
    while(aux)
    {
        c++;
        aux= aux->next;
    }
    return c;
}

bool Queue::IsEmpty()
{
   return Head;
}
