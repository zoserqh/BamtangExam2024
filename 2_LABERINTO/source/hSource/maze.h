#pragma once

#include <vector>
#include <random>
#include <opencv2/opencv.hpp>
#include "cell.h"

using namespace std;
class Maze{
public:
    Maze(int n);
    const vector<vector<Cell>>& getMaze();
    void displayMaze() const;
    void generator(Cell& targetCell);
private:
    vector<vector<Cell>> matrix;
    int dimension;
    vector<int> startPosition = {1,1};
};
