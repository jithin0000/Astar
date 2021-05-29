#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

enum  class State{
    EMPTY,
    OBSTACLE,
    PATH,
    CLOSED,
    START,
    FINISH
};

void ReadFromFile(vector<vector<State>>& board);
vector<vector<State>> Search( vector<vector<State>>& grid, int start[2], int goal[2]);
void PrintSolution(vector<vector<State>> board);
int Heuristic(int x1, int x2, int y1, int y2);

int main(int argc, char *argv[])

{
    vector<vector<State>> board;

    ReadFromFile(board);


    int start[2]={0,0};
    int goal[2]={4,3};

    Search(board, start,  goal);

    PrintSolution(board);


    return 0;
};

/**
 * Get board from file 
 * create grid using input 
 */
void ReadFromFile(vector<vector<State>>& board)
{
    int grid[5][5] = {
        { 0,0,0,0,0},
        { 1,0,1,0,0},
        { 1,0,0,1,0},
        { 0,1,0,0,0},
        { 0,0,0,0,1},
    };


    for (int i = 0; i < 5; ++i) {
        
        vector<State> row;
        for (int j = 0; j < 5; ++j) {
            
            if(grid[i][j]==0)
                row.push_back(State::EMPTY);
            else
                row.push_back(State::OBSTACLE);
        }

        board.push_back(row);

    }

};


/**
 * @return  State::EMPTY retun 0 else #
 */
string CellString(State cell)
{

     switch(cell) {
        case State::OBSTACLE: return "⛰   ";
        case State::PATH: return "🚗   ";
        case State::START: return "🚦   ";
        case State::FINISH: return "🏁   ";
        default: return "0   "; 
     }

};

/**
 * Print grid to cmd
 */
void PrintSolution(vector<vector<State>> grid)
{

    for (vector<State> vec : grid) {
        for (State s : vec) {

            cout << CellString(s) ;
        }
        cout << endl;
    }
   
};


/**
 * Add nodes to open nodes List and then mark it as closed
 * @param x current node x value
 * @param y current node y value
 * @param open_list list that tracks open node
 * @grid astar path grid
 */
void AddToOpen(int x, int y , int g, int h, vector<vector<int>>& open_list, vector<vector<State>>& grid)
{
    vector<int> node{x,y,g,h};
    open_list.push_back(node);
    grid[x][y]=State::CLOSED;
};

/**
 * @brief helper function to sort nodes in openList
 * @return true if first's f value is > than second's
 */
bool Compare(const vector<int>& a , const vector<int>& b)
{
    int f_of_a = a[2] + a[3];
    int f_of_b = b[2] + b[3];
    return f_of_a > f_of_b;
};

/**
 * Sort openNodes using theier f-value
 * @param v pointer to openNodes
 */
void CellSort(vector<vector<int>>* v)
{
    std::sort(v->begin(), v->end(), Compare);
};

/**
 * @param x x value of cell
 * @param y y value of cell
 * @param grid ref to grid
 * @return if x and y is inside grid co-ordinates and not an obstacle
 */
bool CheckValidCell(int x, int y , vector<vector<State>>& grid)
{
    bool in_x = (x>=0 && x < grid.size());
    bool in_y = (y >=0 && y < grid.size());

    if(in_x && in_y)
        return grid[x][y] == State::EMPTY;


    return false;

};

const int delta[4][2]={
    {-1,0},{0,-1},
    {1,0},{0,1},

};

/**
 * @param cNode current node
 * @param openList list of open nodes, tracking nodes which open
 * @param grid 
 * @param goal destination co-ordinates
 */
void ExpandNeighbhorNodes(vector<int> cNode, vector<vector<int>>& openList, 
        vector<vector<State>>& grid, int goal[2])
{
    // get current node data
        int x = cNode[0];
        int y = cNode[1];
        int g = cNode[2];
    // loop through current node's potential neighbhoure's 
    
        for (int i = 0; i < 4; ++i) {
            int x2 = x + delta[i][0];
            int y2 = y + delta[i][1];

            if(CheckValidCell(x2,y2,grid))
            {
                g = g+1;
                int h = Heuristic(x2,goal[0],y2, goal[1]);
                AddToOpen(x2,y2,g,h,openList,grid);
            }
        }
     
    
};


/**
 * Astart algorithm
 * @param grid path
 * @param start starting point
 * @param goad destination
 */
vector<vector<State>> Search(vector<vector<State>>& grid, int start[2], int goal[2]){
    
    vector<vector<int>>openList; // tracking open nodes

    int x1 = start[0];
    int y1 = start[1];

    int x2 = goal[0];
    int y2 = goal[1];

    int g =0; int h = Heuristic(x1,x2,y1,y2);
    vector<int> node{x1,y1,g,h}; // it's should be in format x, y, g, h

    AddToOpen(x1,y1,g,h,openList,grid);

    while(!openList.empty())
    {
        //sort open list to get minimum value
        CellSort(&openList);
        //get x and y of current node
        vector<int>cNode = openList.back();
        openList.pop_back();
        int x = cNode[0];
        int y = cNode[1];
        grid[x][y]=State::PATH;


        // return here if reached goal point
        if(x == x2 && y == y2)
        {
            grid[x1][y1] = State::START;
            grid[x][y] = State::FINISH;
            return grid;
        }

        // ExpandNeighbhorNodes()
        ExpandNeighbhorNodes(
                cNode,openList,
                grid,goal
                );

    }

    cout << "No path " << endl;
    return grid;

};


/**
 * Heuristic functions using manhattan Distance
 * @param x1 start x value
 * @param x2 goal  x value
 * @param y1 goal  y value
 * @param y2 goal  y value
 * @return manhattan distance between two coordinates
 *
 */
int Heuristic(int x1, int x2, int y1, int y2)
{
    return  abs(x2-x1) + abs(y2-y1);
};

/**
 *
 * A* Code Structure
 *  ReadBoardFile() -> Read data from a file
 *
 *  Search() -> A * search Function
 *      -- CellSort() -> sort openNodes using h+g value
 *      -- Get nxt node from openNodes ; return if Goal is Reached
 *
 *      -- ExpandNeighbhorNodes()
 *        -- for each neighbhoure:
 *            -- CheckValidCell() -> check grid is not empty and node co-ordinates are in the grid
 *            -- Heuristic() --> The manhattan distance to the goal
 *            -- AddToOpen() --> Add node to open list
 *  
 *
 */
