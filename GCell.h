#ifndef GCELL_H
#define GCELL_H
#include <QPushButton>
#include <stdlib.h>
#include <stdio.h>

class GCell:public QPushButton
{
private:
    bool mine;
    bool open=false;
    int number;
public:

    GCell();
    GCell(bool mine,int number);
    GCell& operator=(const GCell& other);
   ~GCell();
    GCell(const GCell  &obj){this->mine=obj.mine; this->number=obj.number; this->open=obj.open;};
    bool getMine() const{return mine;}
    void setMine(bool state){mine=state;}
    bool getOpen(){return open;}
    void setOpen(bool state){open=state;}
    int getNumber(){return number;}
    void setNumber(int i){number=i;}

};

#endif // GCELL_H
