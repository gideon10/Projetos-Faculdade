#include "list.h"

bool List::Push(Aluno *A)
{
    Node *p= Node::MontaNo(A);
    if(!p)
        return false;
    p->next= head;
    head= p;
    qtd++;
    return true;
}

bool List::Pop(long long mat, Aluno *C)
{
    Node **p= &head;
    while((*p) && ((*p)->A).getMat()!=mat)
    {// não achou e não chegou ao fim.
        p= &((*p)->next);
    }
    if(!(*p))
       return false; //não achou.
    Node *pn= *p;
    *p= pn->next;
    Node::DesmontaNo(pn,C);
    qtd--;
    return true;
}

int List::getQtd()
{
    return qtd;
}
