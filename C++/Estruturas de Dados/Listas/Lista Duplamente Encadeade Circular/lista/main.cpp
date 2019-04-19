#include <iostream>
#include "listadcircular.h"

using namespace std;

int main()
{
    Aluno A;
    ListaDcircular lista;
    char nome[50];
    long long mat;
    int op=0;

    cout<<"\n**********LISTA DUPLAMENTE ENCADEADA CIRCULAR Ñ ORDENADA (inserção na frente).*****************\n\n\n\n\n";

    while(op!=5)
    {
        cout<<"\nDigite a opcao desejada.\n";
        cout<<"\n1- Inserir elemento(aluno) na lista.\n2- Retirar elemento(aluno) da lista.\n3- Qtd de elementos na lista.\n4- Elementos da lista.\n5- Sair.\n";
        cin>>op;

        switch (op)
        {
             case 1: cout<<"\nNome: ";
                     cin.ignore();
                     cin.getline(nome,50);
                     cout<<"Matricula: ";
                     cin>>mat;
                     A.setNome(nome);
                     A.setMat(mat);
                     if(!lista.Push(&A))
                         cout<<"\nFALHA: Memoria cheia ou já tem uma matricula igual a essa na lista.\n";
                     else
                         cout<<"\nSucesso.\n";
                     break;

              case 2: cout<<"\nMatricula (chave de busca): ";
                      cin>>mat;
                      if(!lista.Pop(mat,&A))
                          cout<<"\nFALHA: Lista vazia ou elemento não foi encontrado.\n";
                      else
                      {
                          cout<<"\nELEMENTO RETIRADO.\n";
                          cout<<"\nNome: "<<A.getNome()<<'\n';
                          cout<<"Matricula: "<<A.getMat()<<'\n';
                      }
                      break;

             case 3: cout<<"\nQtd de elementos na lista: "<<lista.size()<<'\n';
                     break;

             case 4: lista.lista();
                     break;

             default: op=5;
                      break;

       }
    }

    return 0;
}
