#ifndef QUEUE_H
#define QUEUE_H
#include "node.h"
//#include "carta.h"

class Queue
{

 private:
   Node *head;
   Node *tail;

 public:
   Queue(){head=tail=0;}
   bool Push(Carta *A);
   bool Pop_Front();
   bool empty();
   Carta getFront();
   int size();

};

#endif // QUEUE_H
