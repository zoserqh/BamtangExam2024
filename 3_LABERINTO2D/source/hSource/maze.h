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
    unsigned int VBOsPieces[5];
    unsigned int VAOsPieces[5];
    void configRender(unsigned int Width, unsigned int Height);
    void drawMaze2D() const;
private:
    void generator(Cell& targetCell, Cell const& pastCell);
    void searchFinalPosition();
    void navigator(Cell const& targetCell, Cell const& pastCell, vector<int>& counters, int& counter, vector<pair<Cell const*,int>>& possibleEndings);
    vector<vector<Cell>> matrix;
    int dimension;
    vector<int> startPosition = {1,1};
    vector<int> finalPosition = {1,1};
};

Maze createMaze2D(int n); 