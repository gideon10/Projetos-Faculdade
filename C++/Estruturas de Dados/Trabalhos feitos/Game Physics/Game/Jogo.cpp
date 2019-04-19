#include "Jogo.h"

Jogo::Jogo():
    N(0),
    X(0),
    Y(0)
{
   try{
      file= fopen("Dados.txt","r");
      if(!file) throw string("ERRO: Arquivo de Dados não aberto!");
    }
   catch(string &erro)
   {
       cout<<"\n"<<erro<<"\n";
   }
}

Jogo::~Jogo()
{
    fclose(file);
}

void Jogo::LerDadosDoArquivo()
{
    char c;
    string s="";

    while((c=fgetc(file))!='\n'){
        s+=c;
    }
    N= stoi(s);

    try
    {
        if(N!=0)
        {
            int i=0;
            int x=0,y=0;
            int hp=0,dano=0;

            // LENDO JOGADORES.
            while(i<N)
            {   s="";
                while((c=fgetc(file))!=' '){ // LENDO COORDENADA X
                     s+=c;
                }
                x= stoi(s);

                s="";
                while((c=fgetc(file))!=' '){ // LENDO COORDENADA Y
                     s+=c;
                }
                y= stoi(s);

                s="";
                while((c=fgetc(file))!=' '){ // LENDO PONTOS DE VIDA
                      s+=c;
                }
                hp= stoi(s);

                s="";
                while((c=fgetc(file))!='\n'){ // LENDO PODER DE ATAQUE
                      s+=c;
                }
                dano= stoi(s);

                ObjetosDoJogo A;
                A.setNumeroDoJogador(i+1);
                A.setIdentificador('J');
                A.setX(x);
                A.setY(y);
                A.setHP(hp);
                A.setDano(dano);
                A.setPontosDeAcao(5);
                tree.InsereAVL(&A);

                PosicaoDoObjeto B;
                B.setNumeroDoJogador(i+1);
                B.setX(x);
                B.setY(y);
                listaDeJogadores.Push_Back(&B);
                i++;
            }

            // LENDO LIMITES DO MAPA.
            s="";
            while((c=fgetc(file))!=' '){
                s+=c;
            }
            X= stoi(s);
            s="";
            while((c=fgetc(file))!='\n'){
                s+=c;
            }
            Y= stoi(s);

            while((c=fgetc(file))!='-')             // LENDO OBJETOS(PEDRAS) DO MAPA.
            {
                s="";
                do{                      // LENDO COORDENADA X
                    s+=c;
                }while((c=fgetc(file))!=' ');
                x= stoi(s);

                s="";
                while((c=fgetc(file))!=' '){  // LENDO COORDENADA Y
                    s+=c;
                }
                y= stoi(s);

                ObjetosDoJogo C;
                C.setIdentificador('P');
                C.setX(x);
                C.setY(y);
                tree.InsereAVL(&C);
            }

            while((c=fgetc(file))!='\n');

            // LENDO JOGADAS.

            string jogadas="";
            while((c=fgetc(file))!='F'){
                if(c!=' ')
                    jogadas+=c;
            }

            for(int i=0;jogadas[i]!='\0';i+=2){
                Jogadas J;
                J.setLetra(jogadas[i]);
                J.setDirecao(jogadas[i+1]);
                listaDeJogadas.push_back(J);
            }

            while((c=fgetc(file))!='\n');
        }

    }
    catch(std::bad_alloc&){
        throw string("Memória insfuciente!!");
    }
    catch(string &erro){
        throw(erro);
    }

}

void Jogo::MoverUmQuadrado(char direcao)
{
    bool E;
    ObjetosDoJogo A,Obj;
    PosicaoDoObjeto B;
    
    switch(direcao)
    { // MOVER PARA BAIXO.
        case '2': if(!tree.Search(listaDeJogadores.getDado(),&A)) throw string("ERRO: Jogador ñ encontrado!!");
                  if(!(A.getY() + 1 == Y))
                  {
                     B.setX(A.getX());
                     B.setY(A.getY()+1);
                     if(!tree.Search(&B,&Obj))
                     {
                         tree.DeleteAVL(listaDeJogadores.getDado(),&A,&E);
                         A.setY(A.getY()+1);
                         tree.InsereAVL(&A);
                         listaDeJogadores.getDado()->setY(A.getY());
                     }
                  }
                  break;
         // MOVER PARA ESQUERDA.
         case '4': if(!tree.Search(listaDeJogadores.getDado(),&A)) throw string("ERRO: Jogador ñ encontrado!!");
                   if(A.getX()!=0)
                   {
                       B.setX(A.getX()-1);
                       B.setY(A.getY());
                       if(!tree.Search(&B,&Obj))
                       {
                           tree.DeleteAVL(listaDeJogadores.getDado(),&A,&E);
                           A.setX(A.getX()-1);
                           tree.InsereAVL(&A);
                           listaDeJogadores.getDado()->setX(A.getX());
                       }
                   }
                    break;
          // MOVER PARA CIMA.
         case '8': if(!tree.Search(listaDeJogadores.getDado(),&A)) throw string("ERRO: Jogador ñ encontrado!!");
                   if(A.getY()!=0)
                   {
                       B.setX(A.getX());
                       B.setY(A.getY()-1);
                       if(!tree.Search(&B,&Obj))
                       {
                           tree.DeleteAVL(listaDeJogadores.getDado(),&A,&E);
                           A.setY(A.getY()-1);
                           tree.InsereAVL(&A);
                           listaDeJogadores.getDado()->setY(A.getY());
                       }
                   }
                   break;
          // MOVER PARA DIREITA.
         case '6': if(!tree.Search(listaDeJogadores.getDado(),&A)) throw string("ERRO: Jogador ñ encontrado!!");
                   if(!(A.getX() + 1 == X))
                   {
                       B.setX(A.getX()+1);
                       B.setY(A.getY());
                       if(!tree.Search(&B,&Obj))
                       {
                           tree.DeleteAVL(listaDeJogadores.getDado(),&A,&E);
                           A.setX(A.getX()+1);
                           tree.InsereAVL(&A);
                           listaDeJogadores.getDado()->setX(A.getX());
                       }
                   }
                   break;
    }

    int *pts=0;
    if(!tree.AlterarPtsDeAcao(listaDeJogadores.getDado(),&pts)) throw string("ERRO: Jogador ñ encontrado!!");

    *pts= *pts - 1;
    pts=0;
}

void Jogo::AtacarEmUmaDirecao(char direcao)
{
    bool E;
    ObjetosDoJogo A,Obj;
    PosicaoDoObjeto B,Aux;
    int *hp=0;

    switch (direcao)
    {    // ATACAR PARA BAIXO.
        case '2': if(!tree.Search(listaDeJogadores.getDado(),&A)) throw string("ERRO: Jogador ñ encontrado!!");
                  if(!(A.getY() + 1 == Y))
                  {
                      for(int i=A.getY()+1;i<Y;i++)
                      {
                          B.setX(A.getX());
                          B.setY(i);
                          if(tree.Search(&B,&Obj))
                          {
                              if(Obj.getIdentificador()!='P')
                              {
                                  tree.AlterarHP(&B,&hp);
                                  *hp= *hp - A.getDano();
                                  if(*hp <=0)
                                  {
                                      listaDeJogadores.Pop(Obj.getNumeroDoJogador(),&Aux);
                                      tree.DeleteAVL(&B,&Obj,&E);
                                      listaDeJogadoresMortos.push_back(Obj);
                                  }
                              }
                              i=Y;
                          }
                      }
                  }
                  break;
          // ATACAR PARA ESQUERDA.
        case '4': if(!tree.Search(listaDeJogadores.getDado(),&A)) throw string("ERRO: Jogador ñ encontrado!!");
                  if(A.getX()!=0)
                  {
                      for(int i=A.getX()-1;i>=0;i--)
                      {
                          B.setX(i);
                          B.setY(A.getY());
                          if(tree.Search(&B,&Obj))
                          {
                              if(Obj.getIdentificador()!='P')
                              {
                                  tree.AlterarHP(&B,&hp);
                                  *hp= *hp - A.getDano();
                                  if(*hp<=0)
                                  {
                                      listaDeJogadores.Pop(Obj.getNumeroDoJogador(),&Aux);
                                      tree.DeleteAVL(&B,&Obj,&E);
                                      listaDeJogadoresMortos.push_back(Obj);
                                  }
                              }
                              i=-1;
                          }
                      }
                  }
                  break;
         // ATACAR PARA CIMA.
        case '8': if(!tree.Search(listaDeJogadores.getDado(),&A)) throw string("ERRO: Jogador ñ encontrado!!");
                  if(A.getY()!=0)
                  {
                      for(int i=A.getY()-1;i>=0;i--)
                      {
                          B.setX(A.getX());
                          B.setY(i);
                          if(tree.Search(&B,&Obj))
                          {
                              if(Obj.getIdentificador()!='P')
                              {
                                  tree.AlterarHP(&B,&hp);
                                  *hp= *hp - A.getDano();
                                  if(*hp<=0)
                                  {hp=0;
                                      listaDeJogadores.Pop(Obj.getNumeroDoJogador(),&Aux);
                                      tree.DeleteAVL(&B,&Obj,&E);
                                      listaDeJogadoresMortos.push_back(Obj);
                                  }
                              }
                              i=-1;
                          }
                      }
                  }
                  break;
          // ATACAR PARA DIREITA.
        case '6': if(!tree.Search(listaDeJogadores.getDado(),&A)) throw string("ERRO: Jogador ñ encontrado!!");
                  if(!(A.getX() + 1 == X))
                  {
                     for(int i=A.getX()+1;i<X;i++)
                     {
                        B.setX(i);
                        B.setY(A.getY());
                        if(tree.Search(&B,&Obj))
                        {
                            if(Obj.getIdentificador()!='P')
                            {
                                tree.AlterarHP(&B,&hp);
                                *hp= *hp - A.getDano();
                                if(*hp<=0)
                                {hp=0;
                                    listaDeJogadores.Pop(Obj.getNumeroDoJogador(),&Aux);
                                    tree.DeleteAVL(&B,&Obj,&E);
                                    listaDeJogadoresMortos.push_back(Obj);
                                }
                            }
                            i=X;
                        }
                     }
                  }
                  break;

    }

    int *pts=0;
    if(!tree.AlterarPtsDeAcao(listaDeJogadores.getDado(),&pts)) throw string("ERRO: Jogador ñ encontrado!!");

    *pts= *pts - 1;
    pts=0;

}

void Jogo::ConstruirUmBloco(char direcao)
{
    ObjetosDoJogo A,Obj,pedra;
    PosicaoDoObjeto B;

    switch (direcao)
    {   // CONSTRUIR PARA BAIXO.
        case '2': if(!tree.Search(listaDeJogadores.getDado(),&A)) throw string("ERRO: Jogador ñ encontrado!!");
                  if(!(A.getY() + 1 == Y))
                  {
                      B.setX(A.getX());
                      B.setY(A.getY()+1);
                      if(!tree.Search(&B,&Obj))
                      {
                          pedra.setX(A.getX());
                          pedra.setY(A.getY()+1);
                          pedra.setIdentificador('P');
                          tree.InsereAVL(&pedra);
                      }
                  }
                  break;
        // CONSTRUIR PARA ESQUERDA.
        case '4': if(!tree.Search(listaDeJogadores.getDado(),&A)) throw string("ERRO: Jogador ñ encontrado!!");
                  if(A.getX()!=0)
                  {
                      B.setX(A.getX()-1);
                      B.setY(A.getY());
                      if(!tree.Search(&B,&Obj))
                      {
                          pedra.setX(A.getX()-1);
                          pedra.setY(A.getY());
                          pedra.setIdentificador('P');
                          tree.InsereAVL(&pedra);
                      }
                  }
                  break;
        // CONSTRUIR PARA CIMA.
        case '8': if(!tree.Search(listaDeJogadores.getDado(),&A)) throw string("ERRO: Jogador ñ encontrado!!");
                  if(A.getY()!=0)
                  {
                      B.setX(A.getX());
                      B.setY(A.getY()-1);
                      if(!tree.Search(&B,&Obj))
                      {
                          pedra.setX(A.getX());
                          pedra.setY(A.getY()-1);
                          pedra.setIdentificador('P');
                          tree.InsereAVL(&pedra);
                      }
                  }
                  break;
        // CONSTRUIR PARA DIREITA.
        case '6': if(!tree.Search(listaDeJogadores.getDado(),&A)) throw string("ERRO: Jogador ñ encontrado!!");
                  if(!(A.getX() + 1 == X))
                  {
                      B.setX(A.getX()+1);
                      B.setY(A.getY());
                      if(!tree.Search(&B,&Obj))
                      {
                          pedra.setX(A.getX()+1);
                          pedra.setY(A.getY());
                          pedra.setIdentificador('P');
                          tree.InsereAVL(&pedra);
                      }
                  }
                  break;
    }

    int *pts=0;
    if(!tree.AlterarPtsDeAcao(listaDeJogadores.getDado(),&pts)) throw string("ERRO: Jogador ñ encontrado!!");

    *pts= *pts - 4;
    pts=0;
}

void Jogo::DestruirUmBloco(char direcao)
{
    bool E;
    ObjetosDoJogo A,Obj;
    PosicaoDoObjeto B;

    switch (direcao)
    {  // DESTRUIR PARA BAIXO.
        case '2': if(!tree.Search(listaDeJogadores.getDado(),&A)) throw string("ERRO: Jogador ñ encontrado!!");
                  if(!(A.getY()+1 == Y))
                  {
                      B.setX(A.getX());
                      B.setY(A.getY()+1);
                      if(tree.Search(&B,&Obj))
                      {
                          if(Obj.getIdentificador()=='P')
                            tree.DeleteAVL(&B,&Obj,&E);
                      }
                  }
                  break;
         // DESTRUIR PARA ESQUERDA.
        case '4': if(!tree.Search(listaDeJogadores.getDado(),&A)) throw string("ERRO: Jogador ñ encontrado!!");
                  if(A.getX()!=0)
                  {
                      B.setX(A.getX()-1);
                      B.setY(A.getY());
                      if(tree.Search(&B,&Obj))
                      {
                          if(Obj.getIdentificador()=='P')
                              tree.DeleteAVL(&B,&Obj,&E);
                      }
                  }
                  break;
        // DESTRUIR PARA CIMA.
        case '8': if(!tree.Search(listaDeJogadores.getDado(),&A)) throw string("ERRO: Jogador ñ encontrado!!");
                  if(A.getY()!=0)
                  {
                      B.setX(A.getX());
                      B.setY(A.getY()-1);
                      if(tree.Search(&B,&Obj))
                      {
                          if(Obj.getIdentificador()=='P')
                              tree.DeleteAVL(&B,&Obj,&E);
                      }
                  }
                  break;
         // DESTRUIR PARA DIREITA.
        case '6': if(!tree.Search(listaDeJogadores.getDado(),&A)) throw string("ERRO: Jogador ñ encontrado!!");
                  if(!(A.getX()+1 == X))
                  {
                      B.setX(A.getX()+1);
                      B.setY(A.getY());
                      if(tree.Search(&B,&Obj))
                      {
                          if(Obj.getIdentificador()=='P')
                               tree.DeleteAVL(&B,&Obj,&E);
                      }
                  }
                  break;

    }

    int *pts=0;
    if(!tree.AlterarPtsDeAcao(listaDeJogadores.getDado(),&pts)) throw string("ERRO: Jogador ñ encontrado!!");

    *pts= *pts - 3;
    pts=0;
}

void Jogo::Jogar()
{
    try{

        LerDadosDoArquivo();

        while(N!=0)
        {
            ObjetosDoJogo B;
            Jogadas A;
            listaDeJogadores.IteratorRecebeHead();
            while(!listaDeJogadas.empty() && !listaDeJogadores.isEmpty())
            {
                bool ok=true;
                while(ok && !listaDeJogadas.empty())
                {
                    A= listaDeJogadas.front();

                    switch(A.getLetra())
                    {

                        case 'M': if(!tree.Search(listaDeJogadores.getDado(),&B)) throw string("Jogador ñ encontrado!");
                                  if(B.getPtsDeAcao()==0 || B.getPtsDeAcao() < 1) // JOGADOR PERDE A VEZ.
                                  {
                                      ok=false;
                                      if(B.getPtsDeAcao()!=0)
                                          listaDeJogadas.pop_front();
                                  }
                                  else
                                  {
                                      MoverUmQuadrado(A.getDirecao());
                                      listaDeJogadas.pop_front();
                                  }
                                  break;

                        case 'A': if(!tree.Search(listaDeJogadores.getDado(),&B)) throw string("Jogador ñ encontrado!");
                                  if(B.getPtsDeAcao()==0 || B.getPtsDeAcao() < 1) // JOGADOR PERDE A VEZ.
                                  {
                                      ok=false;
                                      if(B.getPtsDeAcao()!=0)
                                          listaDeJogadas.pop_front();

                                  }else
                                  {
                                      AtacarEmUmaDirecao(A.getDirecao());
                                      listaDeJogadas.pop_front();
                                  }
                                  break;

                        case 'C': if(!tree.Search(listaDeJogadores.getDado(),&B)) throw string("Jogador ñ encontrado!");
                                  if(B.getPtsDeAcao()==0 || B.getPtsDeAcao() < 4)  // JOGADOR PERDE A VEZ.
                                  {
                                      ok=false;
                                      if(B.getPtsDeAcao()!=0)
                                          listaDeJogadas.pop_front();
                                  }
                                  else
                                  {
                                      ConstruirUmBloco(A.getDirecao());
                                      listaDeJogadas.pop_front();
                                  }
                                  break;

                        case 'D': if(!tree.Search(listaDeJogadores.getDado(),&B)) throw string("Jogador ñ encontrado!");
                                  if(B.getPtsDeAcao()==0 || B.getPtsDeAcao() < 3)
                                  {
                                      ok=false;
                                      if(B.getPtsDeAcao()!=0)
                                          listaDeJogadas.pop_front();
                                  }
                                  else
                                  {
                                      DestruirUmBloco(A.getDirecao());
                                      listaDeJogadas.pop_front();
                                  }
                                  break;

                    }

                }
                int *pts=0;
                if(!tree.AlterarPtsDeAcao(listaDeJogadores.getDado(),&pts)) throw string("Jogador ñ encontrado!");
                *pts=5;
                listaDeJogadores++;
            }

            // RESULTADO FINAL   !!!!

            listaDeJogadores.IteratorRecebeHead();
            cout<<"\n\nSaída:\n";
            for(int i=0;i < listaDeJogadores.size();i++)
            {
                if(!tree.Search(listaDeJogadores.getDado(),&B)) throw string("Jogador ñ enontrado!!");
                cout<<"Jogador "<<B.getNumeroDoJogador()<<": ("<<B.getX()<<","<<B.getY()<<") HP: "<<B.getHP()<<'\n';
                listaDeJogadores++;
            }

            while(!listaDeJogadoresMortos.empty()){
                B= listaDeJogadoresMortos.front();
                listaDeJogadoresMortos.pop_front();
                cout<<"Jogador "<<B.getNumeroDoJogador()<<": MORTO\n";
            }

            tree.Esvazia();
            listaDeJogadores.Esvazia();
            listaDeJogadores.IteratorRecebeHead();
            LerDadosDoArquivo();
        }


    }
    catch(string &erro){
        cout<<'\n'<<erro<<'\n';
    }

}









