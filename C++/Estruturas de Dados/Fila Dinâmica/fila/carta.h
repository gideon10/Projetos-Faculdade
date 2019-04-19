#ifndef CARTA_H
#define CARTA_H


class Carta
{
 private:
   int num;
   char naipe;

 public:
   Carta();
   bool setNum(int n);
   bool setNaipe(char n);
   int getNum()const;
   char getNaipe()const;

};

#endif // CARTA_H
