#ifndef NODE_H
#define NODE_H
#include "aluno.h"

class Node
{
 public:
    Aluno A;
    Node *next;

    Node();
 static Node* MontaNo(Aluno *B);
 static void DesmontaNo(Node *N,Aluno *C);
};

#endif // NODE_H
