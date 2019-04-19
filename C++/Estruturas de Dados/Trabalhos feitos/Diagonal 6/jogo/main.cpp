#include <iostream>
#include "stack.h"
#include "queue.h"
#include <fstream>
using namespace std;

void imprimeCor(int i){
    switch(i){
       case 0: cout<<"\nAZUL.\n";
               break;
       case 1: cout<<"\nVERMELHO.\n";
               break;
       case 2: cout<<"\nROXO.\n";
               break;
       case 3: cout<<"\nBRANCO.\n";
               break;
    }
}

int main()
{
    Stack Torre[6];
    Queue Fila[4];
    string n;
    string aux=" ";
    Ficha C,D;
    int a=0,v=0,r=0,b=0,j=0,k=0;
    int i=0,A=0,V=0,R=0,B=0;
    int para=0, cont=0;

    ifstream file;
    file.open("fichas.d6a", ios::in);

    if(file.is_open()){
        file.seekg(0);
        while(!file.eof()){ ///LENDO DO ARQUIVO.
           getline(file,n);
           aux= aux + n;
        }
        for(i=2;aux[i]!='A';i+=3); ///PROCURA AZUL.
        a= aux[i-1]-48;
        for(i=2;aux[i]!='V';i+=3); ///PROCURA VERMELHO.
        v= aux[i-1]-48;
        for(i=2;aux[i]!='R';i+=3); ///PROCURA ROXO.
        r= aux[i-1]-48;
        for(i=2;aux[i]!='B';i+=3); ///PROCURA BRANCO.
        b= aux[i-1]-48;
        a--, v--, r--, b--;
        ///// GUARDANDO AS FICHAS NAS FILAS.
        for(i=1;aux[i]!='\0';i+=3) {
            C.setJogador(aux[i]-48);
            C.setCor(aux[i+1]);
            C.setTorre(aux[i+2]-48);
            if(aux[i+1]=='A'||(aux[i+1]=='P' && aux[i]-48==a+1)){
                if(!Fila[0].Push(&C))
                   cout<<"\nMemória cheia.\n";
            }
            else{
                if(aux[i+1]=='V'||(aux[i+1]=='P' && aux[i]-48==v+1)){
                    if(!Fila[1].Push(&C))
                        cout<<"\nMemória cheia.\n";
                }
                else{
                    if(aux[i+1]=='R'||(aux[i+1]=='P' && aux[i]-48==r+1)){
                        if(!Fila[2].Push(&C))
                            cout<<"\nMemória cheia.\n";
                    }
                    else{
                        if(!Fila[3].Push(&C))
                            cout<<"\nMemória cheia.\n";
                    }
                }
            }
        } 
        ///// EMPILHANDO AS FICHAS NAS TORRES.
        while(para!=-1){
            if(Fila[j].Pop(&C))
            {
                if(C.getCor()!='P')
                {
                    i= C.getTorre()-1;
                    while(Torre[i].size()==6){
                        if(i==5)
                            i=0;
                        else
                            i++;
                    }
                    if(!Torre[i].Push(&C))
                        cout<<"\nMemória cheia.\n";
                }
                else
                {
                    i= C.getTorre()-1;
                    Torre[i].Pop(&C);
                }
            }
            if(j==3)
                j=0;
            else
                j++;

            for(i=0,cont=0;i<6;i++){  /// VERIFICA SE AS TORRES ESTÃO CHEIAS.
                if(Torre[i].size()==6)
                    cont++;
            }
            if(cont==6) para=-1;
        }
        cout<<"\n                         CONTEÚDO DAS TORRES\n";
        cout<<'\n';
        for(i=0;i<6;i++)
            cout<<" TORRE "<<i+1<<"     ";
        cout<<'\n';
        for(i=0;i<6;i++){
            j=0;
            for(k=0;k<6;k++){
                Torre[k].Pop(&C);
                cout<<" "<<C.getJogador();
                cout<<C.getCor();
                cout<<C.getTorre()<<"         ";
                if(j==i)
                    D= C;
                j++;
            }
            cout<<'\n';
            switch(D.getCor()){
                case 'A': A++;
                        break;
                case 'V': V++;
                        break;
                case 'R': R++;
                        break;
                case 'B': B++;
                        break;
            }
        }
        cout<<"\n------------------------------------------------------------------------------\n";
        cout<<"\n                FICHAS QUE SOBRARAM NA FILA DE CADA JOGADOR\n";
        cout<<"\nINFORMAÇÕES:\nFILA 1: Jogador Azul.\nFILA 2: Jogador Vermelho.\nFILA 3: Jogador Roxo.\nFILA 4: Jogador Branco.\n";
        for(i=0;i<4;i++){
            cout<<"\nFILA "<<i+1<<": \n";
            if(!Fila[i].IsEmpty())
                cout<<"\nNenhuma ficha.\n";
            else{
                while(Fila[i].Pop(&C)){
                    cout<<C.getJogador();
                    cout<<C.getCor();
                    cout<<C.getTorre()<<'\n';
                }
            }
        }

        cout<<"\n-----------------------------------------------------------------------------\n";
        int vet[4]={A,V,R,B};
        int maior=0;
        for(i=0;i<4;i++){
            if(vet[i]>maior)
            {    maior= vet[i];
                 j=i; /// posição do maior.
            }
        }
        for(i=0,cont=0;i<4;i++){
            if(vet[i]==maior)
                cont++;
        }
        if(cont==2)
        {/// Houve um empate duplo.
            cout<<"\n\nEMPATE!!!\n";
            cout<<"\nCOR DOS JOGADORES EMPATADOS:\n";
            imprimeCor(j);
            vet[j]=0;
            for(i=0;i<4 && vet[i]!=maior;i++);
            imprimeCor(i);
        }
        else
        {
            if(cont==3)
            {/// Houve um empate triplo.
                cout<<"\n\nEMPATE!!!\n";
                cout<<"\nCOR DOS JOGADORES EMPATADOS:\n";
                imprimeCor(j);
                vet[j]=0;
                for(i=0;i<4 && vet[i]!=maior;i++);
                imprimeCor(i);
                vet[i]=0;
                for(i=0;i<4 && vet[i]!=maior;i++);
                imprimeCor(i);
            }
            else
            {
                cout<<"\nCOR DO JOGADOR VENCEDOR:\n";
                imprimeCor(j);
            }
        }

        file.close();
    }
    else
        cout<<"\nERRO: Falha na abertura do arquivo.\n";

    return 0;
}
