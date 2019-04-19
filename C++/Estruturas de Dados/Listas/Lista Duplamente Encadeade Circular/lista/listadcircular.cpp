#include "listadcircular.h"
#include <iostream>
using namespace std;

bool ListaDcircular::Push(Aluno *A)
{
    NodeD *p= NodeD::MontaNo(A);
    if(!p)
        return false;
    if(!head)
    {//lista vazia.
        head=p->prev=p->next= p;
        qtd++;
        return true;
    }
    if(head->next==head)
    {// so tem 1 elemento na lista.
        p->next= p->prev =head;
        head->prev= head->next= p;
        head=p;
        qtd++;
        return true;
    }

    p->next= head;
    (head->prev)->next= p;
    p->prev= head->prev;
    head->prev= p;
    head= p;
    qtd++;
    return true;
}

bool ListaDcircular::Pop(long long mat, Aluno *Obj)
{
    NodeD *p=head;
    if(!p)
        return false;

    bool test=true;
    while((p!=head || test) && (p->A).getMat()!=mat)
    {
        test=false;
        p=p->next;
    }
    if((p->A).getMat()!=mat)
        return false;
    if(p==p->next)// único elemento.
        head=0;
    else
    {
        if(p==head)// é o 1º elemento(ñ único).
            head=p->next;

        (p->prev)->next= p->next;
        (p->next)->prev= p->prev;
    }
    NodeD::DesmontaNo(p,Obj);
    qtd--;
    return true;
}

void ListaDcircular::lista()
{
    if(size())
    {
        NodeD *aux= head;
        bool ok=true;

        while(aux!=head || ok)
        {
            ok=false;
            cout<<"\nNome: "<<aux->A.getNome()<<'\n';
            cout<<"Matricula: "<<aux->A.getMat()<<'\n';
            aux= aux->next;
        }
    }
    else
        cout<<"\nLISTA VAZIA.\n";
}
