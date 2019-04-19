#include "PosicaoDoObjeto.h"

PosicaoDoObjeto::PosicaoDoObjeto()
{
    ObjetosDoJogo();
}

bool PosicaoDoObjeto::operator >(ObjetosDoJogo *F)
{
    if(this->getX() > F->getX() || (this->getX()==F->getX() && this->getY() > F->getY()))
        return true;
    return false;
}

bool PosicaoDoObjeto::operator ==(ObjetosDoJogo *C)
{
    if(this->getX()==C->getX() && this->getY()==C->getY())
            return true;
    return false;
}
