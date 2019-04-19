#include "jogo.h"

int pos=0;

void Jogo::lerCartas_Distribui(ListDC *LC, ListOrd *v, Stack *M,int J)
{
   ifstream file;

   file.open("cartas",ios::in);
   if(!file.is_open())
       throw string("ERRO: Arquivo nao aberto.");

   Carta A;
   string aux="",linha;
   int cont=0,i=0,k=0;

   while(!file.eof()){
       getline(file,linha);
       aux= aux + linha;
   }
   //DISTRIBUINDO CARTAS.
   //pos=0;
   for(i=0;i<J;i++)
   {
       for(k=0;k<5;k++,pos+=3,cont++)
       {
           A.setValor(aux[pos]);
           A.setNaipe(aux[pos+1]);
           v[i].Push(&A);
       }
       LC->Push(i+1);
   }

   // EMPILHANDO O RESTO DAS CARTAS NO MONTE.
   M->esvazia();
   while(cont<104){
       A.setValor(aux[pos]);
       A.setNaipe(aux[pos+1]);
       M->Push(&A);
       cont++;
       pos+=3;
   }

   file.close();
}

void Jogo::Distribui_Cartas(ListDC *LC, ListOrd *v, Stack *M)
{
    ifstream file;

    file.open("cartas",ios::in);
    if(!file.is_open())
        throw string("ERRO: Arquivo nao aberto.");

    Carta A;
    string aux="",linha;
    int cont=0,i=0,k=0;

    while(!file.eof()){
        getline(file,linha);
        aux= aux + linha;
    }
    // ESVAZIANDO MAO DO JOGADOR.
    for(i=0;i<10;i++)
        v[i].esvazia();

    //DISTRIBUINDO CARTAS.
    LC->inicializa_Iterator();
    for(i=0;i<LC->size();i++,LC->operator ++())
    {
        for(k=0;k<5;k++,pos+=3,cont++)
        {
            A.setValor(aux[pos]);
            A.setNaipe(aux[pos+1]);
            v[LC->getN()-1].Push(&A);
        }
    }

    // EMPILHANDO O RESTO DAS CARTAS NO MONTE.
    M->esvazia();
    while(cont<104){
        A.setValor(aux[pos]);
        A.setNaipe(aux[pos+1]);
        M->Push(&A);
        pos+=3;
        cont++;
    }
    LC->inicializa_Iterator();

    file.close();
}

void Jogo::funcaoDaCarta(ListDC *LC, ListOrd *v, Stack *M, Stack *L, string *s, Carta A)
{
    Carta B;
    switch (A.getValor())
    {
        case 'L': if(*s=="H")
                  {
                     *s="A-H";
                     //LC--;
                     LC->operator --();
                  }
                  else
                  {
                     *s="H";
                     //LC++;
                     LC->operator ++();
                  }
                  break;

        case 'A': if(*s=="H")
                     LC->operator +=(2);
                  else
                     LC->operator -=(2);
                  break;

        case 'G': if(*s=="H")
                  {
                     //LC++;
                     LC->operator ++();
                     for(int i=0;i<2;i++)
                     {
                        M->Pop(&B);
                        verificaMonte(M,L);
                        v[LC->getN()-1].Push(&B);
                     }
                  }
                  else
                  {
                     //LC--;
                     LC->operator --();
                     for(int i=0;i<2;i++)
                     {
                         M->Pop(&B);
                         verificaMonte(M,L);
                         v[LC->getN()-1].Push(&B);
                     }
                  }
                  break;

       case 'I': if(*s=="H")
                 {
                     //LC--;
                     LC->operator --();
                     for(int i=0;i<3;i++)
                     {
                         M->Pop(&B);
                         verificaMonte(M,L);
                         v[LC->getN()-1].Push(&B);
                     }
                     //LC+=2;
                     LC->operator +=(2);
                 }
                 else
                 {
                    //LC++;
                    LC->operator ++();
                    for(int i=0;i<3;i++)
                    {
                        M->Pop(&B);
                        verificaMonte(M,L);
                        v[LC->getN()-1].Push(&B);
                    }
                    //LC-=2;
                    LC->operator -=(2);
                 }
                 break;

       default : if(*s=="H")
                    LC->operator ++();
                 else
                    LC->operator --();
                 break;
    }

}

void Jogo::verificaMonte(Stack *M, Stack *L)
{
    if(M->isEmpty())
    {
        Carta C;
        Carta topL;

        L->Pop(&topL);
        while(L->Pop(&C)){
            M->Push(&C);
        }
        L->Push(&topL);
    }
}



void Jogo::Jogar()
{
    Stack Monte,Lixo;
    ListDC LC;
    ListOrd vet[10];
    int maior=0,n=0;
    string sentido;
    int N=0,J=0,part=0,NUM=0,i=0;
    Carta A;


    try
    {
        cout<<"\n\n               MAUMAU              \n";
        cout<<"\nQtd de partidas: ";
        cin>>N;

        while(part < N)
        {
            cout<<"\nQtd de jogadores: ";
            cin>>J;
            while(J<=1 || J>=11){
                cout<<"\nValor fora do intervalo,tente novamente.\n";
                cout<<"\nQtd de jogadores (>1 e <11): ";
                cin>>J;
            }

            LC.inicializa_Head();
            LC.inicializa_Iterator();
            lerCartas_Distribui(&LC,vet,&Monte,J);
            sentido="H";                      // H: horario , A-H : anti-horario.
            LC.inicializa_Iterator();
            vet[LC.getN()-1].PopFront(&A);
            Lixo.Push(&A);
            funcaoDaCarta(&LC,vet,&Monte,&Lixo,&sentido,A);

            while(LC.size() > 1)
            {
                if(Lixo.isEmpty())
                {
                    sentido="H";
                    Distribui_Cartas(&LC,vet,&Monte);

                    LC.inicializa_Iterator();

                    vet[LC.getN()-1].PopFront(&A);
                    Lixo.Push(&A);
                    funcaoDaCarta(&LC,vet,&Monte,&Lixo,&sentido,A);
                }
                else
                {
                    if(vet[LC.getN()-1].Pop(&A,Lixo.getTop().getValor(),Lixo.getTop().getNaipe()) )
                    {
                        NUM= LC.getN() - 1;
                        Lixo.Push(&A);
                        funcaoDaCarta(&LC,vet,&Monte,&Lixo,&sentido,A);

                        if(vet[NUM].size()==0)
                        {
                            maior=n=0;
                            LC.inicializa_Iterator();
                            for(i=0; i < LC.size();i++,LC++){
                                if(vet[LC.getN()-1].qtdDePts() > maior){
                                    maior= vet[LC.getN()-1].qtdDePts();
                                    n= LC.getN();
                                }
                            }
                            LC.Pop(n);
                            Lixo.esvazia();
                        }

                    }
                    else
                    {
                        Monte.Pop(&A);
                        verificaMonte(&Monte,&Lixo);
                        vet[LC.getN()-1].Push(&A);
                        if(vet[LC.getN()-1].Pop(&A,Lixo.getTop().getValor(),Lixo.getTop().getNaipe()) )
                        {
                            NUM= LC.getN() - 1;
                            Lixo.Push(&A);
                            funcaoDaCarta(&LC,vet,&Monte,&Lixo,&sentido,A);

                            if(vet[NUM].size()==0)
                            {
                                maior=n=0;
                                LC.inicializa_Iterator();
                                for(i=0; i < LC.size();i++,LC++){
                                    if(vet[LC.getN()-1].qtdDePts() > maior){
                                        maior= vet[LC.getN()-1].qtdDePts();
                                        n= LC.getN();
                                    }
                                }
                                LC.Pop(n);
                                Lixo.esvazia();
                            }
                        }
                        else
                        {
                            if(sentido=="H")
                                LC++;
                            else
                                LC--;
                        }
                    }
                }
            }

            LC.inicializa_Iterator();
            cout<<"\n\nVencedor da partida "<<part+1<<": Jogador "<<LC.getN()<<"\n\n";
            part++;

            for(i=0;i<10;i++)
                 vet[i].esvazia();
            LC.Pop(LC.getVencedor());
           // pos=0;

        }


    }
    catch(string &erro)
    {
        cout<<'\n'<<erro<<'\n';
    }

}



