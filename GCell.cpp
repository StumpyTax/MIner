#include "GCell.h"

GCell::GCell():QPushButton()
{

}
GCell::~GCell(){

}

int GCell::flagsCount=0;
int GCell::bombsCount=0;


GCell::GCell(const GCell &obj){ this->mine=obj.mine; this->x=obj.x;this->y=obj.y; this->open=obj.open;}

bool GCell::getMine() const{return mine;}

void GCell::setMine(bool state){mine=state;}

bool GCell::getOpen()const {return open;}

void GCell::setOpen(bool state){open=state;}

int GCell::getX()const{return x;}

void GCell::setX(int i){x=i;}

int GCell::getY()const{return y;}

void GCell::setY(int i){y=i;}

bool GCell::getFlag()const {return flag;}
void GCell::setFlag(bool f){flag=f;}
int GCell::getFlagCount(){return flagsCount;}
int GCell::getBombsCount(){return bombsCount;}
void GCell::setBombsCount(int i){bombsCount=i;}
void GCell::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::RightButton){
        if(!flag){
            if(flagsCount<bombsCount){
            flagsCount++;
            flag=true;
            this->setIcon(QIcon("D:\\Git\\MIner\\flag1.png"));
            }
        }
        else{
            flag=false;
            flagsCount--;
            this->setIcon(QIcon());
        }
    }

}

GCell::GCell(bool mine,int x,int y,QWidget *parent):QPushButton(parent)
{
    this->parent=parent;
    this->mine=mine;
    if(mine) bombsCount++;
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
void GCell::toDefault(){
    this->setEnabled(true);
    this->text()="";
    this->setIcon(QIcon());
    this->setMine(rand()%2);
    this->setOpen(false);
    this->setFlag(false);
    flagsCount=0;
    if(this->mine)
        bombsCount++;
}
