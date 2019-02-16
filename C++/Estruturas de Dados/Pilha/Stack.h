#ifndef STACK_H
#define STACK_H

#include <Node.h>

namespace Gideon{

template <class tipo>
class Stack
{
private:
    Node<tipo> *Top;
    int qtd;

public:
    Stack(){Top=0,qtd=0;}
    void Push(tipo *A);
    void Pop(tipo *Obj);
    bool empty(){ return !Top;}
    int size(){return qtd;}
    void esvazia();
    void Listar();   // Metodo de Teste.

};

template <class tipo>
void Stack<tipo>::Push(tipo *A)
{
    if(!Top) // pilha vazia.
        Top= Node<tipo>::MontaNo(A);
    else
    {
        Node<tipo> *aux= Node<tipo>::MontaNo(A);
        aux->next= Top;
        Top= aux;
    }

    qtd++;
}

template <class tipo>
void Stack<tipo>::Pop(tipo *Obj)
{
    if(!Top) throw string("Pilha vazia !");

    Node<tipo> *aux= Top;
    Top= Top->next;
    Node<tipo>::Desmontano(aux,Obj);
    qtd--;
}

template <class tipo>
void Stack<tipo>::esvazia()
{
    if(!Top) throw string("A pilha já está vazia !");

    Node<tipo> *aux= Top;
    while(Top){
        Top=Top->next;
        delete aux;
        aux= Top;
    }
    qtd=0;
}

template <class tipo>
void Stack<tipo>::Listar()
{
    if(!Top) throw string("Pilha vazia !");

    Node<tipo> *aux= Top;
    while(aux){
        cout<<"\nNome: "<<(aux->Dado).getNome()<<"\n";
        cout<<"Matricula: "<<(aux->Dado).getMatricula()<<'\n';
        aux= aux->next;
    }
}


}
#endif // STACK_H
