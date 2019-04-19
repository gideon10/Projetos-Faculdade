#include "listad.h"
#include <iostream>
using namespace std;

ListaD::ListaD()
{
    head=0;
    qtd=0;
}

bool ListaD::Push(Aluno *B)
{
    NodeD *p= NodeD::MontaNo(B);
    if(!p)
        return p;

    if(!head)
    {// lista vazia.
        p->next= head;
        p->prev= 0;
        head= p;
        qtd++;
        return true;
    }
    p->next= head;
    p->prev= head->prev;
    head->prev= p;
    head= p;
    qtd++;
    return true;
}

bool ListaD::Pop(long long matricula, Aluno *Obj)
{
    NodeD *pn= head;

    while(pn && (pn->A).getMat()!=matricula)
    {
        pn= pn->next;
    }
    if(!pn)
        return false;

    if(pn->next)
        (pn->next)->prev= pn->prev;
    if(pn==head)
        head= pn->next;
    else
        (pn->prev)->next= pn->next;

    NodeD::DesmontaNo(pn,Obj);
    qtd--;
    return true;
}

int ListaD::size()
{
    return qtd;
}

void ListaD::lista()
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
