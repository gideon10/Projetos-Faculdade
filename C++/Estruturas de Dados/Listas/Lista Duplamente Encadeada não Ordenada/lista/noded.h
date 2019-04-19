#ifndef NODED_H
#define NODED_H
#include "aluno.h"

class NodeD
{
 public:
   Aluno A;
   NodeD *next, *prev;

 NodeD(){next=prev=0;}
 static NodeD *MontaNo(Aluno *A);
 static void DesmontaNo(NodeD *N,Aluno *Obj);
};

#endif // NODED_H
