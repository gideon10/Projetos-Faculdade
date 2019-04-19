#ifndef JOGO_H
#define JOGO_H

#include <AVLTree.h>
#include <stdio.h>
#include <iostream>
#include <list>
#include <Jogadas.h>
#include <ListaCircular.h>

using namespace std;

class Jogo
{
private:
    AVLTree tree;
    int N;
    int X,Y;
    FILE *file;
    list<Jogadas> listaDeJogadas;
    ListaCircular listaDeJogadores;
    list<ObjetosDoJogo> listaDeJogadoresMortos;

public:
    Jogo();
    ~Jogo();
    void LerDadosDoArquivo();
    void MoverUmQuadrado(char direcao);
    void AtacarEmUmaDirecao(char direcao);
    void ConstruirUmBloco(char direcao);
    void DestruirUmBloco(char direcao);
    void Jogar();
};

#endif // JOGO_H
