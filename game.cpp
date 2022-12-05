#include "game.h"

Game::Game(QObject *parent)
    : QObject{parent}
{

}

Game::Game(QWidget *parent)
{
    this->parent=parent;

    auto size=resize(parent);

    this->width=size[0];
    this->height=size[1];

    for(int i=0;i<height;i++)
        for(int j=0;j<width;j++)
        {
            auto bomb=new GCell((bool)rand()%2,i+j*(this->layout->columnCount()));
            this->bombs->append(*bomb);
            this->layout->addWidget(bomb);
            bomb->show();
        }

    this->layout->setGeometry( QRect(QPoint(30,50),QPoint(parent->width()-30,parent->height()-30)));
    this->parent->setLayout(this->layout);
}



int* Game::resize(QWidget *parent)
{
    int* res;

    auto btn16x16=new QPushButton("16x16",parent);
    auto btn64x64=new QPushButton("64x64",parent);
    auto btn64x128=new QPushButton("64x128",parent);
    auto btns={btn16x16,btn64x64,btn64x128};

    for(auto btn:btns){
        btn->show();
        connect(btn, &QPushButton::pressed,parent,
                [btn,btns,parent,res]{
            auto resStr=btn->text().split('x');
            res[0]=resStr[0].toInt();
            res[1]=resStr[1].toInt();
        });
    }
    for(auto btn:btns)
    {
        btn->deleteLater();
    }
//    delete btn16x16;
//    delete btn64x64;
//    delete btn64x128;
    return res;
}

void Game::restart(QWidget *parent)
{
    delete this->layout;
    this->layout=new QGridLayout();
    this->layout->setGeometry( QRect(QPoint(30,50),QPoint(parent->width()-30,parent->height()-30)));
    this->parent->setLayout(this->layout);

    for(int i=0;i<height;i++)
        for(int j=0;j<width;j++)
        {
            auto bomb=new GCell((bool)rand()%2,i+j);
            this->bombs->append(*bomb);
            this->layout->addWidget(bomb);
            bomb->show();

        }
}

void Game::open(int number, int bombsAround)
{

    for(int i=-1;i<1;i++)
        for(int j=-1;j<1;j++)
        {
           if(number+j+i*(this->layout->columnCount())<0 || number+j+i*(this->layout->columnCount())>=bombs->length() || (i==0 && j==0))
                continue;
            if(this->bombs->at(number+j+i*(this->layout->columnCount())).mine)
                bombsAround++;
            else
                open(number+j+i*(this->layout->columnCount()),0);
        }

    auto data=bombs->data();
    data[number].open=true;
}

void Game::gameOver(GCell &cell)
{
    auto *data=bombs->data();
    for(auto i=0;i<bombs->length();i++)
    {
        data[i].setEnabled(false);
        if(bombs->at(i).mine)
            data[i].setIcon(QIcon());
    }
    cell.setIcon(QIcon());
}

void Game::BombOrNot(int x, int y)
{
    auto data=bombs->data();
    if(this->bombs->at(x+y*(this->layout->columnCount())).mine){
        this->gameOver(data[x+y*(this->layout->columnCount())]);
    }
    this->open(x+y*(this->layout->columnCount()),0);

}
