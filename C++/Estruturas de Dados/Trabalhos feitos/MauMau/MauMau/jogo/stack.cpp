#include "stack.h"

Stack::Stack()
{
    Top=0;
    qtd=0;
}

bool Stack::Push(Carta *A)
{
    Node *a= Node::MontaNo(A);
    if(!a)
        throw string("Memoria cheia.(Stack)");
    a->next= Top;
    Top= a;
    qtd++;
    return true;
}

bool Stack::Pop(Carta *B)
{
    if(!Top)
        return false;
    Node *aux= Top;
    Top= Top->next;
    Node::DesmontaNo(aux,B);
    qtd--;
    return true;
}

int Stack::size()
{
    return qtd;
}

void Stack::esvazia()
{
    if(Top)
    {
        Node *x;
        while(Top){
            x=Top;
            Top=Top->next;
            delete x;
        }
        qtd=0;
    }
}














