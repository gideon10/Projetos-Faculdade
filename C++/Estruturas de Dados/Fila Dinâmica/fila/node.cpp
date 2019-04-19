#include "node.h"

Node::Node()
{

}

void Node::setA(Carta *A)
{
    this->A= *A;
}

void Node::setNext(Node *next)
{
    this->next= next;
}

Node *Node::MontaNo(Carta *B)
{
   Node *p;
   p= new Node;
   if(!p)
      return p;

   p->setA(B);
   return p;
}

void Node::DesmontaNo(Node *n)
{
    delete n;
}
