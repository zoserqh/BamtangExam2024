#include "hSource/maze.h"
#include "hSource/cell.h"

Maze::Maze(int n){
    dimension = n;

    //creation of matrix of nxn cell unconnected
    for(int i=0;i<dimension;i++){
        vector<Cell> rowCells;
        for(int j=0;j<dimension;j++){
            if( i==0 || i==dimension-1 || j==0 || j==dimension-1){
                Cell c(cellType::WALL,j,i);
                rowCells.push_back(c);
            }
            else {
                Cell c(cellType::UNDEFINED,j,i);
                rowCells.push_back(c);
            }
        }
        matrix.push_back(rowCells);
    }

    //matrix with conected cells
    for(int i=0;i<dimension;i++){
        for(int j=0;j<dimension;j++){
            int upPos=i-1;
            int downPos=i+1;
            int leftPos= j-1;
            int rightPos= j+1;
            if(upPos >= 0){ matrix[i][j].up = &matrix[upPos][j]; }
            if(downPos < dimension){ matrix[i][j].down = &matrix[downPos][j]; }
            if(leftPos >= 0){ matrix[i][j].left = &matrix[i][leftPos]; }
            if(rightPos < dimension){ matrix[i][j].right = &matrix[i][rightPos]; }
        }
    }

    generator(matrix[startPosition[1]][startPosition[0]]);

    //solve cell type undefined and unvisited
    for(int i=0;i<dimension;i++){
        for(int j=0;j<dimension;j++){
            if (matrix[i][j].getCellType() == cellType::UNDEFINED){
                matrix[i][j].setCellType(cellType::WALL);
            }
        }
    }
}

void Maze::generator(Cell& targetCell){
    int numPATH = 0;
    if(targetCell.up->getCellType() == cellType::PATH){ numPATH++; }
    if(targetCell.down->getCellType() == cellType::PATH){ numPATH++; }
    if(targetCell.left->getCellType() == cellType::PATH){ numPATH++; }
    if(targetCell.right->getCellType() == cellType::PATH){ numPATH++; }

    if(numPATH >=2){
       targetCell.setCellType(cellType::WALL);
       return; 
    }
    // bool cornerPath = false;
    // if(targetCell.up->left->getCellType() == cellType::PATH){ cornerPath=true; }
    // else if(targetCell.up->right->getCellType() == cellType::PATH){ cornerPath=true; }
    // else if(targetCell.down->left->getCellType() == cellType::PATH){ cornerPath=true; }
    // else if(targetCell.down->right->getCellType() == cellType::PATH){ cornerPath=true; }
    // if(cornerPath){
    //    targetCell.setCellType(cellType::WALL);
    //    return; 
    // }

    //
    targetCell.setCellType(cellType::PATH); 
    vector<Cell*> options;
    if(targetCell.up->getCellType() == cellType::UNDEFINED){
        Cell* UP = targetCell.up;
        options.push_back(UP);
    }
    if(targetCell.down->getCellType() == cellType::UNDEFINED){
        Cell* DOWN = targetCell.down;
        options.push_back(DOWN);
    }
    if(targetCell.left->getCellType() == cellType::UNDEFINED){
        Cell* LEFT = targetCell.left;
        options.push_back(LEFT);
    }
    if(targetCell.right->getCellType() == cellType::UNDEFINED){
        Cell* RIGHT = targetCell.right;
        options.push_back(RIGHT);
    }

    random_device rd;
    mt19937 g(rd());
    shuffle(options.begin(), options.end(),g);
    for(int i=0;i<options.size();i++){
        generator(*(options[i]));
    }
}

const vector<vector<Cell>>& Maze::getMaze(){
    return matrix;
}

void Maze::displayMaze() const {
    double arr[dimension][dimension];
    for(int i=0;i<dimension;i++){
        for(int j=0;j<dimension;j++){
            if(matrix[i][j].getCellType() == cellType::WALL) {
                arr[i][j] = 0;
            }
            else if(matrix[i][j].getCellType() == cellType::PATH) {
                arr[i][j] = 1;
            }
            else if(matrix[i][j].getCellType() == cellType::UNDEFINED) {
                arr[i][j] = 0.5;
            }
        }
    }

    cv::namedWindow("Maze",cv::WINDOW_NORMAL);
    cv::Mat myMathMatrix(dimension,dimension,CV_64F,arr);
    cv::imshow("Maze", myMathMatrix);
    cv::waitKey(0);
}