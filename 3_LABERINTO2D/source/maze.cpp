
#include "hSource/maze.h"
#include "hSource/cell.h"
#include "hSource/resource_manager.h"

int sizePiece1 = 480;
float* piece1 = new float[sizePiece1]{
    // positions            // colors
    -0.5f, 0.5f,        0.5f, 0.5f, 0.5f,
    -0.5f, -0.5f,       0.5f, 0.5f, 0.5f,
    -0.375f, 0.5f,      0.5f, 0.5f, 0.5f,

    -0.375f, 0.5f,      0.5f, 0.5f, 0.5f,
    -0.5f, -0.5f,       0.5f, 0.5f, 0.5f,
    -0.375f, -0.375f,   0.5f, 0.5f, 0.5f,

    -0.375f, -0.375f,   0.5f, 0.5f, 0.5f,
    -0.5f, -0.5f,       0.5f, 0.5f, 0.5f,
    0.5f, -0.5f,        0.5f, 0.5f, 0.5f,

    0.5f, -0.5f,        0.5f, 0.5f, 0.5f,
    0.375f, -0.375f,    0.5f, 0.5f, 0.5f,
    -0.375f, -0.375f,   0.5f, 0.5f, 0.5f,

    0.375f, -0.375f,    0.5f, 0.5f, 0.5f,
    0.5f, -0.5f,        0.5f, 0.5f, 0.5f,
    0.5f, 0.5f,         0.5f, 0.5f, 0.5f,

    0.5f, 0.5f,         0.5f, 0.5f, 0.5f,
    0.375f, 0.5f,       0.5f, 0.5f, 0.5f,
    0.375f, -0.375f,    0.5f, 0.5f, 0.5f,

    -0.375f, 0.5f,      1.0f, 0.586f, 0.0f,
    -0.375f, -0.375f,   1.0f, 0.586f, 0.0f,
    0.375f, -0.375f,    1.0f, 0.586f, 0.0f,

    0.375f, -0.375f,    1.0f, 0.586f, 0.0f,
    0.375f, 0.5f,       1.0f, 0.586f, 0.0f,
    -0.375f, 0.5f,      1.0f, 0.586f, 0.0f
    };

Maze::Maze(){ }

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

const vector<vector<Cell>>& Maze::getMaze() const{
    return matrix;
}

void Maze::searchFinalPosition(){
    vector<int> stackCounters;
    int counter1 = 0;
    vector<pair<Cell const*,int>> possibleEndings;

    navigator(matrix[1][1], matrix[0][1], stackCounters, counter1, possibleEndings);

    // cout << "nro PossibleEndings: " << possibleEndings.size() << "\n";
    // for(int i=0;i<possibleEndings.size();i++){
    //     cout << "(" <<possibleEndings[i].first->getPosX() << ", " << possibleEndings[i].first->getPosY() << ") distance: " << possibleEndings[i].second << "\n";
    // } cout << endl;

    int maxDistance = 0;
    int iter = 0;
    for(int i=0;i<possibleEndings.size();i++){
        if(possibleEndings[i].second > maxDistance){
            maxDistance = possibleEndings[i].second;
            iter = i;
        }
    }
    finalPosition = {possibleEndings[iter].first->getPosX(),possibleEndings[iter].first->getPosY()};
}

void Maze::navigator(Cell const& targetCell, Cell const& pastCell, vector<int>& stackCounters, int& counter, vector<pair<Cell const*,int>>& possibleEndings){
    //cout << "counter: " << counter << "("<< targetCell.getPosX() <<","<< targetCell.getPosY() <<")\n";
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

void Maze::displayMazeByTerminal() const{
    for(int i=0;i<dimension;i++){
        for(int j=0;j<dimension;j++){
            if( matrix[i][j].getPosX() == startPosition[0] && matrix[i][j].getPosY() == startPosition[1] ){
                cout << "A";
            }
            else if( matrix[i][j].getPosX() == finalPosition[0] && matrix[i][j].getPosY() == finalPosition[1] ){
                cout << "B";
            }
            else{
                if( matrix[i][j].getCellType()==cellType::PATH ){ cout << " "; }
                else if( matrix[i][j].getCellType()==cellType::WALL ){ cout << "*"; }
            }

            if(j==dimension-1){ cout << "\n"; }
        }
    } cout <<"\n";
}

Maze createMaze2D(int n){
    if(n<=3 || n%2==0){
        cout << "invalid value of the dimensions of the maze, valid value is >3 and odd for example 5\n";
        Maze myMaze(5);
        return myMaze;
    }

    Maze myMaze(n);
    return myMaze;
}

void Maze::configRender(unsigned int Width, unsigned int Height)
{
    // load shaders
    ResourceManager::LoadShader("../resources/shaders/piece_vs.glsl", "../resources/shaders/piece_fs.glsl", nullptr, "piece");
    
    ResourceManager::GetShader("piece").Use();
    glm::mat4 projection = glm::ortho(-1*static_cast<float>(Width)/2, static_cast<float>(Width)/2, 
                                      -1*static_cast<float>(Height)/2, static_cast<float>(Height)/2, -1.0f, 1.0f);
    ResourceManager::GetShader("piece").SetMatrix4("projection", projection);

    // configure VAO/VBO
    unsigned int VBO;
    glGenVertexArrays(1, &VAOsPieces[0]);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAOsPieces[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizePiece1, piece1, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    std::cout << "ResourceManager::GetShader(\"piece\").ID: " << ResourceManager::GetShader("piece").ID << "\n";
    std::cout << "VAOsPieces[0]: " << VAOsPieces[0] << "\n";

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Maze::drawMaze2D() const
{
    // for(int i=0;i<dimension*dimension; i++){

    // }
    ResourceManager::GetShader("piece").Use();
    ResourceManager::GetShader("piece").SetFloat("angle", 0.0f);
    ResourceManager::GetShader("piece").SetFloat("scale", 100.0f);
    ResourceManager::GetShader("piece").SetVector2f("translateXY", glm::vec2(100.0f, 200.0f));
    glBindVertexArray(VAOsPieces[0]);
    glDrawArrays(GL_TRIANGLES, 0, sizePiece1);
}