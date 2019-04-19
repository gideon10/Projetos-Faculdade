#include <iostream>
#include "list.h"

using namespace std;

int main()
{
    char nome[50];
    long long mat=0;
    float n1=0,n2=0;
    Aluno A;
    List lista;
    int op=0;


    while(op!=4)
    {
        cout<<"\nDigite a opção desejada:\n";
        cout<<"\n 1- Inserir aluno na lista.\n 2- Retirar aluno da lista\n 3- Tamanho da lista.\n 4-Sair.\n";
        cin>>op;
        switch(op)
        {
            case 1: cout<<"\nNome: ";
                    cin.ignore();
                    cin.getline(nome,50);
                    cout<<"Matricula: ";
                    cin>>mat;
                    cout<<"N1 e N2: ";
                    cin>>n1>>n2;
                    A.setNome(nome);
                    A.setMat(mat);
                    A.setNota(n1,n2);
                    if(!lista.Push(&A))
                        cout<<"\nMemória cheia.\n";
                    else
                        cout<<"\nSucesso!!!\n";
                    break;

            case 2: cout<<"\nMatricula do aluno: ";
                    cin>>mat;
                    if(!lista.Pop(mat,&A))
                        cout<<"\nLista vazia ou aluno não encontrado.\n";
                    else
                    {
                        cout<<"\nINFORMAÇÕES DO ALUNO RETIRADO.\n";
                        cout<<"\nNome: "<<A.getNome()<<'\n';
                        cout<<"Matricula: "<<A.getMat()<<'\n';
                        cout<<"N1= "<<A.getN1()<<'\n';
                        cout<<"N2= "<<A.getN2()<<'\n';
                    }
                    break;

            case 3: cout<<"\nTamanho da lista: "<<lista.getQtd()<<'\n';
                    break;

            default: op=4;
                    break;
        }
    }


    return 0;
}
