#ifndef NODED_H
#define NODED_H
#include "aluno.h"

class NodeD
{
 public:
   NodeD *prev,*next;
   Aluno A;

   NodeD();
 static NodeD *MontaNo(Aluno *obj);
 static void DesmontaNo(NodeD *N, Aluno *B);
};

#endif // NODED_H
