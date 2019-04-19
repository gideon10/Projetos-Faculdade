#ifndef POSICAODOOBJETO_H
#define POSICAODOOBJETO_H

#include <ObjetosDoJogo.h>

class PosicaoDoObjeto : public ObjetosDoJogo
{
public:
    PosicaoDoObjeto();

    bool operator >(ObjetosDoJogo *F);
    bool operator ==(ObjetosDoJogo *C);
};

#endif // POSICAODOOBJETO_H
