#ifndef JOGADAS_H
#define JOGADAS_H


class Jogadas
{
private:
    char letra;
    char direcao;

public:
    Jogadas();
    void setLetra(char l){letra=l;}
    void setDirecao(char d){direcao=d;}
    char getLetra()const{return letra;}
    char getDirecao()const{return direcao;}
};

#endif // JOGADAS_H
