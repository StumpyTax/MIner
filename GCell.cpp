#include "GCell.h"

GCell::GCell()
{

}
GCell::~GCell(){

}
GCell::GCell(bool mine,int number)
{
    this->mine=mine;
    this->number=number;
}

GCell& GCell::operator=(const GCell &other)
{
     mine=other.mine;
     open=other.open;
     number=other.number;
     return *this;
}

