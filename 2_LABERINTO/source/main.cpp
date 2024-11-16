#include <iostream>
#include "hSource/maze.h"

using namespace std;

int main(){
    Maze myMaze;
    myMaze = createMaze2D(11);
    myMaze.displayMazeByTerminal();
    myMaze.displayMazeByWindow();
    return 0;
}