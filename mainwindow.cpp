#include "mainwindow.h"
#include "game.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(600,700);

    auto game=new Game(parent);

}

MainWindow::~MainWindow()
{
}

