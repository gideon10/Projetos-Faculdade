#include "aluno.h"

Aluno::Aluno()
{
    mat=0;
}

void Aluno::setNome(const char *n)
{
    strcpy(nome,n);
}

void Aluno::setMat(long long mat)
{
    this->mat= mat;
}

const char *Aluno::getNome()
{
    return nome;
}

long long Aluno::getMat()
{
    return mat;
}
