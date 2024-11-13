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

    // Maze generator usign backtracking algorithm
    generator(matrix[startPosition[1]][startPosition[0]], matrix[startPosition[0]][startPosition[0]]);
    //solve cell type undefined and unvisited
    for(int i=0;i<dimension;i++){
        for(int j=0;j<dimension;j++){
            if (matrix[i][j].getCellType() == cellType::UNDEFINED){
                matrix[i][j].setCellType(cellType::WALL);
            }
        }
    }

    //search for the final position of the maze
    searchFinalPosition();
}

void Maze::generator(Cell& targetCell, Cell const& pastCell){
    // delete 2x2 block of PATHS
    int numPATH = 0;
    if(targetCell.up->getCellType() == cellType::PATH){ numPATH++; }
    if(targetCell.down->getCellType() == cellType::PATH){ numPATH++; }
    if(targetCell.left->getCellType() == cellType::PATH){ numPATH++; }
    if(targetCell.right->getCellType() == cellType::PATH){ numPATH++; }
    if(numPATH >=2){
       targetCell.setCellType(cellType::WALL);
       return;
    }

    //hard constraint to explore (that is optional)
    int direcctionX = targetCell.getPosX() - pastCell.getPosX();
    int direcctionY = targetCell.getPosY() - pastCell.getPosY();
    bool isWall = false;
    if(direcctionX == 0 && direcctionY == -1){
        if(targetCell.up->left->getCellType() == cellType::PATH || targetCell.up->right->getCellType() == cellType::PATH){
            targetCell.setCellType(cellType::WALL);
            isWall = true;
        }
    }
    else if(direcctionX == 0 && direcctionY == 1){
        if(targetCell.down->left->getCellType() == cellType::PATH || targetCell.down->right->getCellType() == cellType::PATH){
            targetCell.setCellType(cellType::WALL);
            isWall = true;
        }
    }
    else if(direcctionX == -1 && direcctionY == 0){
        if(targetCell.left->up->getCellType() == cellType::PATH || targetCell.left->down->getCellType() == cellType::PATH){
            targetCell.setCellType(cellType::WALL);
            isWall = true;
        }
    }
    else if(direcctionX == 1 && direcctionY == 0){
        if(targetCell.right->up->getCellType() == cellType::PATH || targetCell.right->down->getCellType() == cellType::PATH){
            targetCell.setCellType(cellType::WALL);
            isWall = true;
        }
    }
    if(isWall){ return; }

    //recursive backtracking
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
        generator(*(options[i]),targetCell);
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

void createMaze2D(int n){
    Maze myMaze(n);
    myMaze.displayMaze();
}

void Maze::searchFinalPosition(){
    vector<int> stackCounters;
    int counter1 = 0;
    vector<pair<Cell const*,int>> possibleEndings;

    navigator(matrix[1][1], matrix[0][1], stackCounters, counter1, possibleEndings);

    cout << "nro PossibleEndings: " << possibleEndings.size() << "\n";
    for(int i=0;i<possibleEndings.size();i++){
        cout << "(" <<possibleEndings[i].first->getPosX() << ", " << possibleEndings[i].first->getPosY() << ") distance: " << possibleEndings[i].second << "\n";
    } cout << endl;
}

void Maze::navigator(Cell const& targetCell, Cell const& pastCell, vector<int>& stackCounters, int& counter, vector<pair<Cell const*,int>>& possibleEndings){
    cout << "counter: " << counter << "("<< targetCell.getPosX() <<","<< targetCell.getPosY() <<")\n";
    int numWALLS = 0;
    if(targetCell.up->getCellType() == cellType::WALL){ numWALLS++; }
    if(targetCell.down->getCellType() == cellType::WALL){ numWALLS++; }
    if(targetCell.left->getCellType() == cellType::WALL){ numWALLS++; }
    if(targetCell.right->getCellType() == cellType::WALL){ numWALLS++; }
    if(numWALLS == 3){
        int sum=0;
        for(int i=0;i<stackCounters.size();i++){ sum+=stackCounters[i]; }    
        pair<Cell const*,int> p = {&targetCell,counter+sum};
        possibleEndings.push_back(p);
        counter=0;
        if( !(targetCell.getPosX() == 1 && targetCell.getPosY() == 1) ){ counter=1; return; }
    }

    vector<Cell*> options;
    if(targetCell.up->getCellType() == cellType::PATH && 
        !((targetCell.up->getPosX() == pastCell.getPosX()) && (targetCell.up->getPosY() == pastCell.getPosY())) ){
        Cell* UP = targetCell.up;
        options.push_back(UP);
    }
    if(targetCell.down->getCellType() == cellType::PATH && 
        !((targetCell.down->getPosX() == pastCell.getPosX()) && (targetCell.down->getPosY() == pastCell.getPosY())) ){
        Cell* DOWN = targetCell.down;
        options.push_back(DOWN);
    }
    if(targetCell.left->getCellType() == cellType::PATH && 
        !((targetCell.left->getPosX() == pastCell.getPosX()) && (targetCell.left->getPosY() == pastCell.getPosY())) ){
        Cell* LEFT = targetCell.left;
        options.push_back(LEFT);
    }
    if(targetCell.right->getCellType() == cellType::PATH && 
        !((targetCell.right->getPosX() == pastCell.getPosX()) && (targetCell.right->getPosY() == pastCell.getPosY())) ){
        Cell* RIGHT = targetCell.right;
        options.push_back(RIGHT);
    }
    
    if(options.size()==1){
        counter++;
        navigator(*(options[0]),targetCell,stackCounters,counter,possibleEndings);
    }
    else if(options.size()>1){
        vector<int> stackCountersInternal = stackCounters;
        stackCountersInternal.push_back(counter);
        counter=1;
        for(int i=0;i<options.size();i++){
            navigator(*(options[i]),targetCell,stackCountersInternal,counter,possibleEndings);
        }
    }
}

void Maze::setFinalPosition(int x , int y){
    finalPosition[0] = x;
    finalPosition[1] = y;
}