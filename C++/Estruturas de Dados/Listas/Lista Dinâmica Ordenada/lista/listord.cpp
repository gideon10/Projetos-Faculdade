#include "listord.h"
#include <iostream>
using namespace std;

bool ListOrd::Push(Aluno *A)
{
    Node *pn= Node::MontaNo(A);
    if(!pn)
        return false;
    Node **p= &head;
    long long k= A->getMat();
    while((*p) && ((*p)->A).getMat() < k)
    {
        p= &((*p)->next);
    }
    if(!(*p) || ((*p)->A).getMat() > k)
    {// É para inserir.
        pn->next= (*p);
        *p= pn;
        qtd++;
        return true;
    }
    return false;
}

bool ListOrd::Pop(long long matricula, Aluno *C)
{
    Node **p= &head;
    Node *pn;

    while((*p) && ((*p)->A).getMat() < matricula)
    {
        p= &((*p)->next);
    }
    if((*p) && ((*p)->A).getMat()==matricula)
    {// Achou!!
        pn= *p;
        *p= pn->next;
        Node::DesmontaNo(pn,C);
        qtd--;
        return true;
    }
    return false;
}

int ListOrd::getQtd()
{
    return qtd;
}

void ListOrd::lista()
{
    Node *aux= head;

    cout<<"\n\nELEMENTOS DA LISTA.\n\n";

    while(aux)
    {
       cout<<"\nNome: "<<aux->A.getNome()<<'\n';
       cout<<"Matricula: "<<aux->A.getMat()<<'\n';
       aux= aux->next;
    }
}




