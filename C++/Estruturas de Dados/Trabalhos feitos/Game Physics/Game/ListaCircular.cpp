#include "ListaCircular.h"

ListaCircular::ListaCircular()
{
    head=tail=iterator=0;
    qtd=0;
}

void ListaCircular::Push_Back(PosicaoDoObjeto *B)
{
    NodeLC *p= NodeLC::MontaNo(B);
    if(!p) throw string("ERRO: Memória insuficiente!!");

    if(!head)
    {
        head=tail=p;
        tail->next=head;
    }
    else
    {
        tail->next=p;
        tail=p;
        tail->next=head;
    }
    qtd++;
    iterator=head;
}

bool ListaCircular::Pop(int numJog, PosicaoDoObjeto *obj)
{
    if(!head)
        return false;

    bool test=true;
    NodeLC **ptr=&head;

    while(((*ptr)!=head || test) && ((*ptr)->A).getNumeroDoJogador()!=numJog){
        test=false;
        ptr= &((*ptr)->next);
    }

    if(((*ptr)->A).getNumeroDoJogador()!=numJog)
        return false;

    NodeLC *aux;
    if((*ptr)==head)
    {
        aux= head;
        if((*ptr)->next==head) // Primeiro e único.
            head=tail=iterator=0;
        else               // Primeiro ñ único.
        {
            head=head->next;
            tail->next=head;
        }
    }
    else
    {
        aux= *ptr;
        if((*ptr)==tail) // É o último.
        {
            NodeLC **a=&head;
            while((*a)->next!=tail){
                a= &((*a)->next);
            }
            tail= *a;
            tail->next=head;
        }
        else
            *ptr= (*ptr)->next;
    }

    NodeLC::DesmontaNo(aux,obj);
    qtd--;
    return true;
}

void ListaCircular::Esvazia()
{
    if(head)
    {
        NodeLC *p=head;
        NodeLC *aux;
        bool test=true;
        while(p!=head || test)
        {
            test=false;
            aux=p;
            p=p->next;
            delete aux;
        }

        head=tail=iterator=0;
        qtd=0;
    }
}

void ListaCircular::Listar()
{
    if(head)
    {
        NodeLC *aux=head;
        bool test=true;
        while(aux!=head || test)
        {
            test=false;
            cout<<(aux->A).getNumeroDoJogador()<<"\n";
            aux= aux->next;
        }
    }

}
