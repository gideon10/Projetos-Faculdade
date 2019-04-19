#ifndef CARTA_H
#define CARTA_H


class Carta
{
 private:
    char valor;
    char naipe;
 public:
    Carta();
 void setValor(char v);
 void setNaipe(char n);
 char getValor();
 char getNaipe();
 bool operator >=(Carta *C);

};

#endif // CARTA_H
