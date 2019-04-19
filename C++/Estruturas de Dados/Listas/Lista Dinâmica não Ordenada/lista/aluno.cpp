#include "aluno.h"

Aluno::Aluno()
{

}

void Aluno::setNome(const char *n)
{
    strcpy(nome,n);
}

void Aluno::setMat(long long m)
{
    matricula= m;
}

void Aluno::setNota(float n1, float n2)
{
    this->n1=n1;
    this->n2=n2;
}

long long Aluno::getMat()
{
    return matricula;
}

const char *Aluno::getNome()
{
    return nome;
}

float Aluno::getN1()
{
    return n1;
}

float Aluno::getN2()
{
    return n2;
}
