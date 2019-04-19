#ifndef NODE_H
#define NODE_H
#include "aluno.h"

class Node
{
 public:
    Aluno A;
    Node *next;

 public:
    Node(){next=0;}
 static Node* MontaNo(Aluno *B);
 static void DesmontaNo(Node *P, Aluno *B);
};

#endif // NODE_H
