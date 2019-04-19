#ifndef QUEUE_H
#define QUEUE_H
#include "node.h"

class Queue
{
 private:
   Node *Head;
   Node *Tail;

 public:
    Queue(){Head=Tail=0;}
 bool Push(Ficha *A);
 bool Pop(Ficha *A);
 int size();
 bool IsEmpty();

};

#endif // QUEUE_H
