#include "ficha.h"

void Ficha::setJogador(int j)
{
    Jogador= j;
}

void Ficha::setCor(char c)
{
    Cor= c;
}

void Ficha::setTorre(int t)
{
    Torre= t;
}

int Ficha::getJogador() const
{
    return Jogador;
}

char Ficha::getCor() const
{
    return Cor;
}

int Ficha::getTorre() const
{
    return Torre;
}
