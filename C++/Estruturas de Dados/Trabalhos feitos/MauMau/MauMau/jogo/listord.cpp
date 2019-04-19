#include "listord.h"

ListOrd::ListOrd()
{
    head=0;
    qtd=0;
}

bool ListOrd::Push(Carta *A)
{
    Node *p= Node::MontaNo(A);
    if(!p)
        throw string("Memoria cheia.(List Ord)");
    if(!head)
    {
        p->next=0;
        head=p;
        qtd++;
        return true;
    }

    Node **x=&head;
    while((*x) && ((*x)->A) >= A){
        x=&((*x)->next);
    }

    if(!(*x))
    {
        p->next=0;
        (*x)= p;
        qtd++;
        return true;
    }

    p->next= (*x);
    (*x)= p;
    qtd++;
    return true;
}

bool ListOrd::Pop(Carta *B, char v, char n)
{
    if(!head)
        throw string("Lista vazia.(List Ord)");

    Node **x=&head;
    while((*x) && ((*x)->A).getValor()!=v && ((*x)->A).getNaipe()!=n){
        x= &((*x)->next);
    }

    if(!(*x))
        return false;
    Node *aux= (*x);
    if(!((*x)->next))
        (*x)=0;
    else
        (*x)= (*x)->next;

    Node::DesmontaNo(aux,B);
    qtd--;
    return true;
}

bool ListOrd::PopFront(Carta *C)
{
    if(!head)
       throw string("Lista vazia.(List Ord)");
    Node *aux=head;
    head=head->next;
    Node::DesmontaNo(aux,C);
    qtd--;
    return true;
}

int ListOrd::size()
{
    return qtd;
}

void ListOrd::esvazia()
{
   if(head)
   {
      Node *aux;
      while(head){
         aux=head;
         head=head->next;
         delete aux;
      }
      qtd=0;
   }

}

int ListOrd::qtdDePts()
{
    int pts=0;

    if(head)
    {
        Node *p=head;
        while(p)
        {
           switch((p->A).getValor())
           {
              case 'A': pts+=1;
                        break;
              case 'B': pts+= 2;
                        break;
              case 'C': pts+= 3;
                        break;
              case 'D': pts+= 4;
                        break;
              case 'E': pts+= 5;
                        break;
              case 'F': pts+= 6;
                        break;
              case 'G': pts+= 7;
                        break;
              case 'H': pts+= 8;
                        break;
              case 'I': pts+= 9;
                        break;
              case 'J': pts+= 10;
                        break;
              case 'K': pts+= 11;
                        break;
              case 'L': pts+= 12;
                        break;
              case 'M': pts+= 13;
                        break;
           }
            p=p->next;
       }
    }

    return pts;
}










