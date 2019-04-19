#include "carta.h"

Carta::Carta()
{

}

void Carta::setValor(char v)
{
    valor= v;
}

void Carta::setNaipe(char n)
{
    naipe= n;
}

char Carta::getValor()
{
    return valor;
}

char Carta::getNaipe()
{
    return naipe;
}

bool Carta::operator >=(Carta *C)
{
    if(valor > C->getValor())
        return true;
    if(valor==C->getValor() && naipe <= C->getNaipe())
        return true;
    return false;
}
