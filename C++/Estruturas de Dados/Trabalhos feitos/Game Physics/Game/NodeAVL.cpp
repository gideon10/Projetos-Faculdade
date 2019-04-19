#include "NodeAVL.h"

NodeAVL::NodeAVL()
{
    Left=Right=0;
    fb=0;
}

NodeAVL *NodeAVL::MontaNo(ObjetosDoJogo *A)
{
    NodeAVL *p= new NodeAVL();
    if(!p)
        return p;

    p->D= *A;
    p->Left=p->Right=0;
    return p;
}

void NodeAVL::DesmontaNo(NodeAVL *N, ObjetosDoJogo *Obj)
{
    *Obj= N->D;
    delete N;
}

void NodeAVL::ImprimeNo(ObjetosDoJogo *S,NodeAVL *N)
{
    //cout<<S->getX()<<" "<<S->getY()<<'\n';
   //cout<<N->fb<<'\n';
    //cout<<"Pts de acao = "<<S->getPtsDeAcao()<<'\n';
   // cout<<"\nx e y: "<<S->getX()<<" "<<S->getY()<<'\n';
    cout<<"\nNum jog= "<<S->getNumeroDoJogador()<<'\n';
    cout<<"\nx e y: "<<S->getX()<<" "<<S->getY()<<'\n';
    cout<<"pts: "<<S->getPtsDeAcao()<<'\n';
    cout<<"\nHP= "<<S->getHP()<<'\n';
}
