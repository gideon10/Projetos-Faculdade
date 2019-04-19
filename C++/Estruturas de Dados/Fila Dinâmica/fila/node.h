#ifndef NODE_H
#define NODE_H
#include "carta.h"


class Node
{
 public:
    Carta A;
    Node *next;

 public:
    Node();
 void setA(Carta *A);
 void setNext(Node *next);
 static Node *MontaNo(Carta *B);
 static void DesmontaNo(Node *n);


};

#endif // NODE_H
