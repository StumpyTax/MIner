#include "mainwindow.h"
#include "game.h"

#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(600,700);

    Game *game=new Game(this);
    auto timer=new QTimer(this);
    connect(timer,  &QTimer::timeout,this,[game,timer]{

    });
}

MainWindow::~MainWindow()
{
}

