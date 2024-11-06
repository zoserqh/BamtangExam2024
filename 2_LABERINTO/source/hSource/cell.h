#pragma once

#include "global.h"

class Cell {
public:
    Cell(cellType t, int x, int y);
    cellType getCellType() const;
    void setCellType(cellType t);
    int getPosX() const;
    int getPosY() const;
    Cell* up = nullptr;
    Cell* down = nullptr;
    Cell* left = nullptr;
    Cell* right = nullptr;
private:
    cellType myCellType= cellType::UNDEFINED;
    int posX = 0;
    int posY = 0;
};