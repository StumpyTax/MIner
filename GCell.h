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
    int x;
    int y;
    QWidget *parent;
public:
    GCell();
    GCell(bool mine,int x,int y,QWidget *parent);
    GCell& operator=(const GCell& other);
   ~GCell();
    explicit GCell(const GCell  &obj){this->mine=obj.mine; this->x=obj.x;this->y=obj.y; this->open=obj.open;};
    bool getMine() const{return mine;}
    void setMine(bool state){mine=state;}
    bool getOpen(){return open;}
    void setOpen(bool state){open=state;}
    int getX(){return x;}
    void setX(int i){x=i;}
    int getY(){return y;}
    void setY(int i){y=i;}

};

#endif // GCELL_H
