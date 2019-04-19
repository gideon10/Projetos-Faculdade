#ifndef OBJETOSDOJOGO_H
#define OBJETOSDOJOGO_H


class ObjetosDoJogo
{
private:
    int numJog;
    int x,y; //x -> coluna e y-> linha
    char identificador;
    int Dano;

public:
    int ptsDeAcao;
    int HP;

    ObjetosDoJogo();
    void setNumeroDoJogador(int n){numJog=n;}
    void setX(int x){this->x= x;}
    void setY(int y){this->y= y;}
    void setIdentificador(char id){identificador=id;}
    void setHP(int hp){HP=hp;}
    void setDano(int dano){Dano=dano;}
    void setPontosDeAcao(int pts){ptsDeAcao= pts;}
    int getNumeroDoJogador()const{return numJog;}
    int getX()const{return x;}
    int getY()const{return y;}
    char getIdentificador()const{return identificador;}
    int getHP()const{return HP;}
    int getDano()const{return Dano;}
    int getPtsDeAcao()const{return ptsDeAcao;}
    bool operator <(ObjetosDoJogo *C);
};

#endif // OBJETOSDOJOGO_H
