#ifndef FICHA_H
#define FICHA_H


class Ficha
{
 private:
    int Jogador;
    char Cor;
    int Torre;

 public:
    Ficha(){Jogador=' ';Cor=' ';Torre=' '; }
 void setJogador(int j);
 void setCor(char c);
 void setTorre(int t);
 int getJogador()const;
 char getCor()const;
 int getTorre()const;

};

#endif // FICHA_H
