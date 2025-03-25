#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "cell.h"
#include "resource_manager.h"

using namespace std;
class Maze{
public:
    Maze();
    Maze(int n);
    const vector<vector<Cell>>& getMaze() const;
    void displayMazeByTerminal() const;

    //render
    int lengthPieces[5];
    float* pieces[5];
    unsigned int VBOsPieces[5];
    unsigned int VAOsPieces[5];
    float sidePiece;
    void configRender(unsigned int Width, unsigned int Height);
    void drawMaze2D() const;
private:
    void generator(Cell& targetCell, Cell const& pastCell);
    void searchFinalPosition();
    void navigator(Cell const& targetCell, Cell const& pastCell, vector<int>& counters, int& counter, vector<pair<Cell const*,int>>& possibleEndings);
    void configCorner(int _i, int _j, float& _currAngle, unsigned int& _currVAO, int& _currLength) const;
    void configPerimeter(int _i, int _j, float& _currAngle, unsigned int& _currVAO, int& _currLength) const;
    void configInterior(int _i, int _j, float& _currAngle, unsigned int& _currVAO, int& _currLength) const;
    vector<vector<Cell>> matrix;
    int dimension;
    vector<int> startPosition = {1,1};
    vector<int> finalPosition = {1,1};
};

Maze createMaze2D(int n); 