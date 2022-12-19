#include "game.h"
#include <QMessageBox>
#include <QTimer>
#include <QLabel>

Game::Game(QObject *parent)
    : QObject{parent}
{

}

Game::Game(QMainWindow *parent)
{
    this->parent=parent;
    auto btn16x16=new QPushButton("8x8",parent);
    auto btn64x64=new QPushButton("16x16",parent);
    auto btn64x128=new QPushButton("30x16",parent);
    auto btns={btn16x16,btn64x64,btn64x128};
    auto i=0;

    for(auto btn:btns){
        btn->setGeometry(parent->width()/4,300+i*50,300,50);
        i++;
        btn->show();
        connect(btn, &QPushButton::pressed,parent,
                [btn,this,btn16x16,btn64x64,btn64x128]{
            auto resStr=btn->text().split('x');
            this->width=resStr[0].toInt();
            this->height=resStr[1].toInt();
            delete btn16x16;
            delete btn64x64;
            delete btn64x128;
            this->gameStart();
        });
    }
}

int* Game::resize(QWidget *parent)
{
    int* res;

    auto btn16x16=new QPushButton("8x8",parent);
    auto btn64x64=new QPushButton("16x16",parent);
    auto btn64x128=new QPushButton("16x30",parent);
    auto btns={btn16x16,btn64x64,btn64x128};
    auto i=0;

    for(auto btn:btns){
        btn->setGeometry(parent->width()/4,300+i*50,300,50);
        i++;
        btn->show();
        connect(btn, &QPushButton::pressed,parent,
                [btn,btns,&res,btn16x16,btn64x64,btn64x128]{
            auto resStr=btn->text().split('x');
            res[0]=resStr[0].toInt();
            res[1]=resStr[1].toInt();
            delete btn16x16;
            delete btn64x64;
            delete btn64x128;
            return res;
        });
    }
}

void Game::restart()
{
    GCell::setBombsCount(0);
    auto data=cells.data();
    for(int i=0;i<cells.length();i++){
        data[i]->toDefault();
    }

}


void Game::gameOver()
{
    auto *data=cells.data();
    for(auto i=0;i<cells.length();i++)
    {
        data[i]->setEnabled(false);
        if(data[i]->getMine())
            data[i]->setIcon(QIcon());
    }
}

void Game::gameStart()
{
    auto grid=new QGridLayout(parent);
    auto size=QRect(QPoint(30,200),QPoint(parent->width()-30,parent->height()-10));
    grid->setGeometry(size);

    menu=new QWidget;
    auto restart=new QPushButton(menu);
    restart->setFixedSize(50,50);

    connect(restart,&QPushButton::pressed,this,&Game::restart);    
    const QPalette color(Qt::gray);
    menu->setPalette(color);
    menu->setAutoFillBackground(true);

    auto timer=new QTimer(this);
    connect(timer,  &QTimer::timeout,this,[this,timer]{
        this->winOrNot();
    });

    timer->setInterval(500);
    timer->start();

    auto gridMenu= new QGridLayout(menu);

    auto label=new QLabel();

//    gridMenu->addWidget();
    gridMenu->addWidget(restart);
    menu->setLayout(gridMenu);

    for(int i=1;i<height+1;i++)
        for(int j=0;j<width;j++)
        {
            bool bomb=rand()%2;
            auto cell=new GCell(bomb,j,i-1,parent);
            cell->setFixedSize(30,30);
            if(cell->getMine())
                cell->setIcon(QIcon("D:\\Git\\MIner\\mine.png"));
            cells.append(cell);
            grid->addWidget(cell,i,j);


            connect(cell,&QPushButton::pressed,parent,
                    [cell,this]{
                this->BombOrNot(coordinates(cell->getX(),cell->getY()));
            });
        }



    grid->addWidget(menu,0,0,1,width-1);
    grid->setSpacing(0);
    auto central = new QWidget;
    central->setGeometry(size);
    central->setLayout(grid);
    parent->setCentralWidget(central);
    menu->setFixedSize(parent->width(),100);

}

int Game::coordinates(int x,int y)
{
    return x+y*width;
}



void Game::open(int x,int y, int bombsAround)
{
    auto number=coordinates(x,y);
    auto data=cells.data();
    data[number]->setOpen(true);
    data[number]->setDisabled(true);

    for(int i=-1;i<=1;i++)
        for(int j=-1;j<=1;j++)
        {
           if(x+j<0 || y+i<0 || x+j>=width || y+i>=height || (i==0 && j==0))
                continue;
            if(this->cells.at(coordinates(x+j,y+i))->getMine())
                bombsAround++;
            else
                if(!data[coordinates(x+j,y+i)]->getOpen())
                    if(abs(i)==1 && j==0 || abs(j)!=-1 && i==0)
                        open(x+j,y+i,0);
        }
    if(bombsAround!=0)
        data[number]->setText(QString('0'+(char)bombsAround));
   data[number]->setIcon(QIcon());
}

void Game::BombOrNot(int number)
{
    auto data=cells.data();
    if(data[number]->getMine()){
        gameOver();
        return;
    }
    open(data[number]->getX(),data[number]->getY(),0);
}

void Game::winOrNot()
{
    auto count=0;
    auto open=0;
    auto data=cells.data();
    for(int i=0;i<cells.length();i++)
    {
        if(data[i]->getMine() && data[i]->getFlag())
            count++;
        if(data[i]->getOpen())
            open++;
    }
    if(open==(cells.length()-GCell::getBombsCount()) && count==GCell::getFlagCount())
        QMessageBox::information(parent,"","Машина, ты победил в этой жизни.");
}

