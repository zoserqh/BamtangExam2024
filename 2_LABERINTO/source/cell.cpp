#include "hSource/cell.h"

Cell::Cell(cellType t, int x, int y){
    myCellType = t;
    posX = x;
    posY = y;
}

cellType Cell::getCellType() const{
    return myCellType;
}

void Cell::setCellType(cellType t){
    myCellType = t;
}

int Cell::getPosX() const{
    return posX;
}
int Cell::getPosY() const{
    return posY;
}