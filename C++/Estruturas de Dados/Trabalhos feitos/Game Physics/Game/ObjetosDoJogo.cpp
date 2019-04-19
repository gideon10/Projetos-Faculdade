#include "ObjetosDoJogo.h"

ObjetosDoJogo::ObjetosDoJogo()
{
    numJog=0;
    x=y=0;
    HP=0;
    Dano=0;
    ptsDeAcao=0;
}

bool ObjetosDoJogo::operator <(ObjetosDoJogo *C)
{
    if(x < C->getX() || (x==C->getX() && y < C->getY()))
        return true;
    return false;
}
