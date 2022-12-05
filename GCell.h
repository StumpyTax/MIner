#ifndef GCELL_H
#define GCELL_H
#include <QPushButton>
#include <stdlib.h>
#include <stdio.h>

class GCell:public QPushButton
{
public:
    bool mine;
    bool open=false;
    int number;
    GCell();
    GCell(const GCell&);
    GCell(bool mine,int number);
    GCell& operator=(const GCell& other);
   ~GCell();
//  GCell(GCell const&);

};

#endif // GCELL_H
