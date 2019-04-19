#include "carta.h"

Carta::Carta()
{

}

bool Carta::setNum(int n)
{
    if(n>=1 && n<=13)
    {
       num= n;
       return true;
    }
    return false;
}

bool Carta::setNaipe(char n)
{
    if(n=='O'||n=='E'||n=='C'||n=='P')
    {
        naipe= n;
        return true;
    }
    return false;
}

int Carta::getNum() const
{
    return num;
}

char Carta::getNaipe() const
{
    return naipe;
}
