#ifndef ALUNO_H
#define ALUNO_H
#include "string.h"

class Aluno
{
 private:
    char nome[50];
    long long matricula;
    float n1, n2;

 public:
    Aluno();
 void setNome(const char *n);
 void setMat(long long m);
 void setNota(float n1, float n2);
 long long getMat();
 const char* getNome();
 float getN1();
 float getN2();

};


#endif // ALUNO_H
