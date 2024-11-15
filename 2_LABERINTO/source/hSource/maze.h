#pragma once

#include <vector>
#include <random>
#include <opencv2/opencv.hpp>
#include "cell.h"

using namespace std;
class Maze{
public:
    Maze(int n);
    const vector<vector<Cell>>& getMaze() const;
    void displayMazeByWindow() const;
    void displayMazeByTerminal() const;
private:
    void generator(Cell& targetCell, Cell const& pastCell);
    void searchFinalPosition();
    void navigator(Cell const& targetCell, Cell const& pastCell, vector<int>& counters, int& counter, vector<pair<Cell const*,int>>& possibleEndings);
    vector<vector<Cell>> matrix;
    int dimension;
    vector<int> startPosition = {1,1};
    vector<int> finalPosition = {1,1};
};

void createMaze2D(int n); 