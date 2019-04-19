#include <iostream>
#include "queue.h"

using namespace std;

int main()
{
    Queue Fila;
    Carta A;
    int num;
    char naipe;
    int op=0;


    while(op!=6)
    {
        cout<<"\nEscolha o opcao desejada.\n";
        cout<<"\nDigite (1) - PARA INSERIR UM ELEMENTO NA FILA.\n";
        cout<<"Digite (2) - PARA REMOVER UM ELEMENTO DA FILA.\n";
        cout<<"Digite (3) - PARA VERIFICAR SE A FILA ESTÁ VAZIA.\n";
        cout<<"Digite (4) - PARA MOSTRAR O PRIMEIRO ELEMENTO.\n";
        cout<<"Digite (5) - PARA MOSTRAR O TAMANHO DA FILA.\n";
        cout<<"Digite (6) - PARA FECHAR O PROGRAMA.\n";
        cin>>op;

        switch(op)
        {
            case 1: cout<<"\nNumero da carta (>=1 e <=13): ";
                    cin>>num;
                    while(!A.setNum(num))
                    {
                        cout<<"Numero invalido, tente novamente.\n";
                        cout<<"\nNumero da carta (>=1 e <=13): ";
                        cin>>num;
                    }
                    cout<<"Naipe da carta ('E'-ESPADAS, 'O'-OUROS, 'C'-COPAS, 'P'-PAUS): ";
                    cin>>naipe;
                    while(!A.setNaipe(naipe))
                    {
                        cout<<"\nNaipe invalido, tente novamente.\n";
                        cout<<"Naipe da carta ('E'-ESPADAS, 'O'-OUROS, 'C'-COPAS, 'P'-PAUS): ";
                        cin>>naipe;
                    }
                    if(!Fila.Push(&A))
                    {
                        cout<<"\nERRO: Sem espaço na memória.\n";
                        break;
                    }
                    cout<<"\nCarta inserida.\n";
                    break;

             case 2: if(!Fila.Pop_Front())
                     {
                        cout<<"\nFila vazia.\n";
                        break;
                     }
                     cout<<"\nCarta retirada.\n";
                     break;

             case 3: if(Fila.empty())
                     {
                        cout<<"\nFila vazia.\n";
                        break;
                     }
                     cout<<"\nFila não vazia.\n";
                     break;

             case 4: if(Fila.empty())
                     {
                        cout<<"\nFila vazia.\n";
                        break;
                     }
                     //Carta B= Fila.getFront();

                     cout<<"\nPRIMEIRA CARTA DA FILA:\n";
                     switch(Fila.getFront().getNum())
                     {
                        case 1: cout<<"\n ÁS DE ";
                                 break;

                        case 11: cout<<"\n VALETE DE ";
                                 break;

                        case 12: cout<<"\n DAMA DE ";
                                 break;

                        case 13: cout<<"\n REI DE ";
                                 break;

                        default: cout<<"\n "<<Fila.getFront().getNum()<<" DE ";
                                 break;
                     }
                     switch(Fila.getFront().getNaipe())
                     {
                        case 'O': cout<<"OUROS.\n";
                                  break;

                        case 'P': cout<<"PAUS.\n";
                                  break;

                        case 'E': cout<<"ESPADAS.\n";
                                  break;

                        case 'C': cout<<"COPAS.\n";
                                  break;
                     }
                      break;

              case 5: cout<<"\nTamanho: "<<Fila.size()<<'\n';
                      break;

              default: op=6;
                       break;

        }

    }

    return 0;
}
