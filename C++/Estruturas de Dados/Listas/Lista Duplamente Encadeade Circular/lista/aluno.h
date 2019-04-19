#ifndef ALUNO_H
#define ALUNO_H
#include "string.h"

class Aluno
{
 private:
   char nome[50];
   long long mat;

 public:
    Aluno(){mat=0;}
 void setNome(const char *n);
 void setMat(long long mat);
 const char *getNome();
 long long getMat();

};

#endif // ALUNO_H
