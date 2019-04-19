#ifndef NODE_H
#define NODE_H
#include "ficha.h"


class Node
{
 public:
    Ficha A;
    Node *next;

 public:
    Node();
 static Node *MontaNo(Ficha *B);
 static void DesmontaNo(Node *N, Ficha *C);

};

#endif // NODE_H
