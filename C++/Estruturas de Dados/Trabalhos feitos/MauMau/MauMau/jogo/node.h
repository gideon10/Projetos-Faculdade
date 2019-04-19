#ifndef NODE_H
#define NODE_H
#include "carta.h"

class Node
{
 public:
   Carta A;
   Node *next;

    Node();
  static Node *MontaNo(Carta *A);
  static void DesmontaNo(Node *N,Carta *B);

};

#endif // NODE_H
