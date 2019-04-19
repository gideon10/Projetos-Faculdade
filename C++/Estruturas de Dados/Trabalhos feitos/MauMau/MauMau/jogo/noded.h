#ifndef NODED_H
#define NODED_H

class NodeD
{
 public:
  NodeD *next,*prev;
  int n;

    NodeD();
  static NodeD *MontaNo(int i);
  static void DesmontaNo(NodeD *N);
};

#endif // NODED_H
