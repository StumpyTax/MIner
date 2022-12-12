#ifndef GAME_H
#define GAME_H

#include <QPushButton>
#include <QGridLayout>
#include <QObject>
#include <stdlib.h>
#include <stdio.h>
#include "GCell.h"

class Game : public QObject
{
    Q_OBJECT

private:
    int width;
    int height;
    QVector<GCell> *cells;
    QWidget *parent;
public:
    ~Game()
    {
      delete cells;
      delete parent;
    }
    explicit Game(QObject *parent);
    Game(QWidget *parent);
    int* resize(QWidget *parent);
    void restart(QWidget *parent);
    void open(int number,int bombsAround);
    void gameOver( GCell &cell);
    QGridLayout *layout=new QGridLayout;


public slots:
   void BombOrNot(int number);
};

#endif // GAME_H
