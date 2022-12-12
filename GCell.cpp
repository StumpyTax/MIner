#include "GCell.h"

GCell::GCell()
{

}
GCell::~GCell(){

}
GCell::GCell(bool mine,int x,int y,QWidget *parent)
{
    this->parent=parent;
    this->setParent(parent);
    this->mine=mine;
    this->x=x;
    this->y=y;
}

GCell& GCell::operator=(const GCell &other)
{
     mine=other.mine;
     open=other.open;
     x=other.x;
     y=other.y;
     return *this;
}

