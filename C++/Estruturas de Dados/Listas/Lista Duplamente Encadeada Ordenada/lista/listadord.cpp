#include "listadord.h"
#include <iostream>
using namespace std;

ListaDOrd::ListaDOrd()
{
    head=0;
    qtd=0;
}

bool ListaDOrd::Push(Aluno *B)
{
   NodeD *pt= NodeD::MontaNo(B);
   if(!pt)
       return false;

   if(!head)
   {// lista vazia.
       head= pt;
       pt->next=0;
       pt->prev=0;
       qtd++;
       return true;
   }

   long long mat= B->getMat();
   NodeD *p= head;
   // lista ñ vazia.
   while(p && (p->A).getMat()<mat)
   {
       p= p->next;
   }
   if(!p)
   {// chegou ao fim.
       p=head;
       while(p->next)
       {
           p=p->next;
       }
       p->next= pt;
       pt->prev= p;
       pt->next=0;
       qtd++;
       return true;
   }
   if((p->A).getMat()==mat)
       return false;
   if(p==head)
   {
       pt->next=p;
       p->prev=pt;
       head= pt;
       pt->prev=0;
       qtd++;
       return true;
   }

   pt->next=p;
   pt->prev= p->prev;
   (p->prev)->next= pt;
   p->prev= pt;
   qtd++;
   return true;
}

bool ListaDOrd::Pop(long long matricula, Aluno *Obj)
{
    NodeD *p= head;

    while(p && (p->A).getMat()<matricula)
    {
        p= p->next;
    }
    if(!p)//chegou ao fim(ñ achou).
        return false;
    if((p->A).getMat()==matricula)
    {
        if(p==head)
        {// é o 1 elemento.
            head= p->next;
            NodeD::DesmontaNo(p,Obj);
            qtd--;
            return true;
        }
        if(p->next)// ñ é o último.
        {
            (p->prev)->next= p->next;
            (p->next)->prev= p->prev;
            NodeD::DesmontaNo(p,Obj);
            qtd--;
            return true;
        }
        // é o último.
        (p->prev)->next= p->next;
        NodeD::DesmontaNo(p,Obj);
        qtd--;
        return true;
    }
    return false;
}

int ListaDOrd::size()
{
    return qtd;
}

void ListaDOrd::lista()
{
    NodeD *aux= head;

    cout<<"\n\nELEMENTOS DA LISTA.\n\n";

    while(aux)
    {
        cout<<"\nNome: "<<aux->A.getNome()<<'\n';
        cout<<"Matricula: "<<aux->A.getMat()<<'\n';
        aux= aux->next;
    }
}
