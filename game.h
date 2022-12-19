#ifndef GAME_H
#define GAME_H

#include <QPushButton>
#include <QGridLayout>
#include <QObject>
#include <stdlib.h>
#include <stdio.h>
#include <QMainWindow>
#include "GCell.h"
#include "qthread.h"

class Game : public QObject
{
    Q_OBJECT

private:
    int width;
    int height;
    QVector<GCell*> cells;
    QWidget *menu;
    QMainWindow *parent;
    QGridLayout *layout;
public:
    ~Game()
    {
      delete parent;
    }
    explicit Game(QObject *parent);
    Game(QMainWindow *parent);
    int* resize(QWidget *parent);
    void restart();
    void open(int x,int y,int bombsAround);
    void gameOver();
    void gameStart();
    void BombOrNot(int number);
    int coordinates(int x,int y);
    void winOrNot();
};

#endif // GAME_H
