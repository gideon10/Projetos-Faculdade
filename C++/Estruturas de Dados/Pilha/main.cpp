#include <iostream>
#include <Stack.h>
#include <Aluno.h>
#include <stdio.h>

using namespace std;

int main()
{

    cout<<"\n -------------------------- PILHA TEMPLATE -------------------------------------\n";


    Gideon::Stack<Aluno> stack;
    char nome[50];
    long int matricula=0;
    int op=0;
    Aluno A;

    while(op!=7)
    {
        try{
            cout<<"\nDigite :\n1 - Inserir na pilha.\n2 - Remover da pilha.\n3 - Tamanho da pilha.\n4 - Pilha vazia ?\n5 - Esvaziar pilha.\n6 - Listar elementos.\n7 - Sair.\n";
            cin>>op;

            switch(op)
            {
                case 1: cout<<"\nNome: ";
                        cin.ignore();
                        cin.getline(nome,50);
                        cout<<"Matricula: ";
                        cin>>matricula;
                        A.setNome(nome);
                        A.setMatricula(matricula);
                        stack.Push(&A);
                        break;

                case 2: stack.Pop(&A);
                        cout<<"\nElemento retirado.\n";
                        cout<<"Nome: "<<A.getNome()<<'\n';
                        cout<<"Matricula: "<<A.getMatricula()<<'\n';
                        break;

                case 3: cout<<"\nTamanho: "<<stack.size()<<'\n';
                        break;

                case 4: if(stack.empty()) cout<<"\nSim\n";
                        else cout<<"\nNão.\n";
                        break;

                case 5: stack.esvazia();
                        cout<<"\nPilha esvaziada!\n";
                        break;

                case 6: stack.Listar();
                        break;

                default: op=7;
                         break;
            }

        }
        catch(string &erro){
            cout<<"\n"<<erro<<"\n";
        }

    }

    return 0;
}
