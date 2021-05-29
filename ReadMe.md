__Astar Using C++__

#### Search Algorithm ####

Search(grid, initial_point, gol_point):
  1. Initialize list for open nodes
  2. Initialize a starting node with the following:
      * x and y values given by the initial_point
      * g=0 where g is cost for each move , it will increment by each step
      * h given by heuristic functon ( Here Euclidian distance )
  3. Add new node to list of open nodes

  4. While the list of open nodes is nonEmpty:
  
      1 Sort the open list by f-value
      2 Pop the optimal cell ( Called current cell )
      3 Mark the cell's co-ordinate in the grid as part of path
      4 if the current cell is the goal cell:
          return grid;
      5 else, Expand search to the current nodes neighbhours , Which is:
        
          * check each neighbhour cell in the grid
              * chekc it's empty , not closed  and not an obstacle
          * If the cell is empty compute cost(g value ) and heuristic and add to list of open
            nodes
          * Mark the cell closed

    5 if you exit the while loop because the list open nodes is empty , you have run out of new
    nodes to explore and not found path




