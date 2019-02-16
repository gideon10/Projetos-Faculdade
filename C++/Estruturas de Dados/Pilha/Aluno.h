#ifndef ALUNO_H
#define ALUNO_H

#include <string.h>

class Aluno
{
private:
    char nome[50];
    long long matricula;

public:
    Aluno();
    void setNome(const char *nome){strcpy(this->nome,nome);}
    void setMatricula(long long mat){matricula=mat;}
    const char *getNome()const{return nome;}
    long long getMatricula()const{return matricula;}
};

#endif // ALUNO_H
