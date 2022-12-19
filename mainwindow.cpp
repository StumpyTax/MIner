#include "mainwindow.h"
#include "game.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(600,700);

    Game *game=new Game(this);

}

MainWindow::~MainWindow()
{
}



