#include "queue.h"


bool Queue::Push(Carta *A)
{
   Node *aux= Node::MontaNo(A);
   if(!aux)
       return false;

   aux->next=0;
   if(!head)
   {  // Fila Vazia.
      head= aux;
   }
   else // Fila não está vazia.
      tail->next= aux;

   tail= aux;
   return true;
}

bool Queue::empty()
{
    if(!head)
        return true;
    return false;
}

Carta Queue::getFront() // RETORNA O PRIMEIRO ELEMENTO DA FILA.
{
    return head->A;
}

int Queue::size() // RETORNA O TAMANHO DA FILA.
{
    if(!head)
        return 0;

    int i=1;
    Node *aux= head;

    while(aux->next)
    {
       aux= aux->next;
       i++;
    }
    return i;
}

bool Queue::Pop_Front()
{
    if(!head)
        return false; //Fila vazia.

    Node *aux;
    aux= head->next;
    Node::DesmontaNo(head);
    head= aux;
    return true;
}
