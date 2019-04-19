#include "listdc.h"

ListDC::ListDC()
{
    head=0;
    qtd=0;
    iterator=0;
}

bool ListDC::Push(int num) // insercao no final.
{
    NodeD *p= NodeD::MontaNo(num);
    if(!p)
        throw string("Memoria cheia.(ListDC)");

    if(!head)
    {
        p->prev= p->next= p;
        head= p;
        iterator= head;
        qtd++;
        return true;
    }

    NodeD *x= head;
    bool test=true;
    while(x->next!=head || test){
        test=false;
        x= x->next;
    }

    x->next= p;
    p->prev= head->prev;
    p->next= head;
    head->prev= p;

    iterator= head;
    qtd++;
    return true;
}

bool ListDC::Pop(int n)
{
    if(!head)
        throw string("Lista vazia(ListDC).");

    NodeD *p=head;
    while(p->n!=n){
        p=p->next;
    }

    if(size()==1)
    {
        head=0;
        qtd--;
        return true;
    }


    if(p==head)
    {
        head= p->next;
        head->prev= p->prev;
        (head->prev)->next= head;
    }
    else
    {
        (p->prev)->next= p->next;
        (p->next)->prev= p->prev;
    }

    iterator=head;
    qtd--;
    NodeD::DesmontaNo(p);
    return true;
}

void ListDC::operator +=(int i)
{
    for(int j=0;j<i;j++)
        iterator= iterator->next;
}

void ListDC::operator -=(int i)
{
    for(int j=0;j<i;j++)
        iterator= iterator->prev;
}






