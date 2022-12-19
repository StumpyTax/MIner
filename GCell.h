#ifndef GCELL_H
#define GCELL_H

#include <QMouseEvent>
#include <QPushButton>
#include <stdlib.h>
#include <stdio.h>

class GCell:public QPushButton
{
private:
    bool mine;
    bool open=false;
    bool flag=false;
    static int flagsCount;
    static int bombsCount;
    int x;
    int y;
    QWidget *parent;
public:
    GCell();
    GCell(bool mine,int x,int y,QWidget *parent);
    GCell& operator=(const GCell& other);
   ~GCell();
    explicit GCell(const GCell  &obj);
    bool getMine() const;
    void setMine(bool state);
    bool getOpen() const;
    void setOpen(bool state);
    int getX() const;
    void setX(int i);
    int getY() const;
    void setY(int i);
    bool getFlag()const;
    void setFlag(bool);
    static int getFlagCount();
    static int getBombsCount();
    static void setBombsCount(int i);
    void toDefault();

    // QWidget interface
protected:
    void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // GCELL_H
