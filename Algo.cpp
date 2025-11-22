#include "Algo.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
using namespace std;

const double INF = std::numeric_limits<double>::infinity();
// Tassk 1: Shortest Path Using A* with Adjacency Matrix
// This is the same with PathNode but using index instead of name and also
// parent pointer parent pointer is used to reconstruct the path after reaching
// the goal, if we dont use Astart node , we need to store parent in a array for
// later backtracking
struct AStarNode
{
    int vertex;
    double f;
    double g;
    double h;
    int parent;

    AStarNode(int vertex = -1, double f = 0, double g = 0, double h = 0, int parent = -1)
    {
        this->vertex = vertex;
        this->f = f;
        this->g = g;
        this->h = h;
        this->parent = parent;
    }
};

double heuristicTask1(int current, int goal)
{
    // Simple heuristic: return 0 for Dijkstra-like behavior
    return 0.0;
}
PathNode* findShortestPathMatrix(double adjMatrix[100][100], int n, int start, int goal)
{
    std::vector<bool> visited(n, false);
    std::vector<AStarNode> openList;
    std::vector<int> parent(n, -1);
    std::vector<double> gCost(n, INF);
    gCost[start] = 0.0;
    double hCost = heuristicTask1(start, goal);
    gCost[start] = 0;
    double f_begin = gCost[start] + hCost;
    openList.push_back(AStarNode(start, f_begin, gCost[start], hCost, -1));

    while (!openList.empty())
    {
        sort(openList.begin(), openList.end(), [](const AStarNode& a, const AStarNode& b)
             {
            if (a.f == b.f)
                return a.vertex < b.vertex;
            return a.f < b.f; });

        int current_vertex = openList[0].vertex;
        AStarNode currentNode = openList[0];
        openList.erase(openList.begin());

        if (visited[current_vertex])
            continue;
        visited[current_vertex] = 1;
        parent[current_vertex] = currentNode.parent;

        if (current_vertex == goal)
        {
            vector<int> path;
            int node = goal;
            while (node != -1)
            {
                path.push_back(node);
                node = parent[node];
            }

            reverse(path.begin(), path.end());

            PathNode* head = nullptr;
            PathNode* tail = nullptr;
            for (int i = 0; i < path.size(); i++)
            {
                appendNode(head, tail, to_string(path[i]), gCost[path[i]] + heuristicTask1(path[i], goal), gCost[path[i]], heuristicTask1(path[i], goal));
            }
            return head;
        }
        for (int v = 0; v < n; v++)
        {
            if (adjMatrix[current_vertex][v] > 0 && !visited[v])
            {
                double newG = gCost[current_vertex] + adjMatrix[current_vertex][v];
                if (newG < gCost[v])
                {
                    gCost[v] = newG;
                    double f_new = newG + heuristicTask1(v, goal);
                    openList.push_back(AStarNode(v, f_new, newG, heuristicTask1(v, goal), current_vertex));
                }
            }
        }
    }
    return nullptr;
}

// Task 2: Shortest Path in 2D Space with Two Heuristics
double euclideanHeuristic(int coords[100][2], int current, int goal)
{
    double dx = coords[current][0] - coords[goal][0];
    double dy = coords[current][1] - coords[goal][1];
    return sqrt(dx * dx + dy * dy);
}
double manhattanHeuristic(int coords[100][2], int current, int goal)
{
    double dx = abs(coords[current][0] - coords[goal][0]);
    double dy = abs(coords[current][1] - coords[goal][1]);
    return dx + dy;
}

double heuristicTask2(int coords[100][2], int current, int goal, int mode)
{
    if (mode == 1)
    {
        return manhattanHeuristic(coords, current, goal);
    }
    else
    {
        return euclideanHeuristic(coords, current, goal);
    }
}
PathNode* findShortestPath2D(double adjMatrix[100][100], int coords[100][2], int n, int start, int goal, int mode)
{
    vector<bool> visited(n, false);
    vector<AStarNode> openList;
    vector<int> parent(n, -1);
    vector<double> gCost(n, INF);
    gCost[start] = 0.0;
    double hCost = heuristicTask2(coords, start, goal, mode);
    double f_begin = gCost[start] + hCost;
    openList.push_back(AStarNode(start, f_begin, gCost[start], hCost, -1));

    while (!openList.empty())
    {
        sort(openList.begin(), openList.end(), [](const AStarNode& a, const AStarNode& b)
             {
            if (a.f == b.f)
                return a.vertex < b.vertex;
            return a.f < b.f; });
        AStarNode currentNode = openList[0];

        int current_vertex = currentNode.vertex;
        openList.erase(openList.begin());
        if (visited[current_vertex])
            continue;
        visited[current_vertex] = 1;
        parent[current_vertex] = currentNode.parent;

        if (current_vertex == goal)
        {
            vector<int> path;
            int node = goal;
            while (node != -1)
            {
                path.push_back(node);
                node = parent[node];
            }
            reverse(path.begin(), path.end());

            PathNode* head = nullptr;
            PathNode* tail = nullptr;
            for (int i = 0; i < path.size(); i++)
            {
                double g_rounded = round(gCost[path[i]] * 100) / 100;
                double h_val = heuristicTask2(coords, path[i], goal, mode);
                double f_rounded = round((g_rounded + h_val) * 100) / 100;
                appendNode(head, tail, to_string(path[i]), f_rounded, g_rounded, h_val);
            }
            return head;
        }
        for (int v = 0; v < n; v++)
        {
            if (adjMatrix[current_vertex][v] > 0 && !visited[v])
            {
                double newG = gCost[current_vertex] + adjMatrix[current_vertex][v];
                if (newG < gCost[v])
                {
                    gCost[v] = newG;
                    double f_new = newG + heuristicTask2(coords, v, goal, mode);
                    openList.push_back(AStarNode(v, f_new, newG, heuristicTask2(coords, v, goal, mode), current_vertex));
                }
            }
        }
    }
    return nullptr;
}

// Task 3: Maze Navigation with Obstacles
struct MazeNode
{
    int x;
    int y;
    double f;
    double g;
    double h;
    int parentX;
    int parentY;
    string direction;

    MazeNode(int x = -1, int y = -1, double f = 0, double g = 0, double h = 0, int parentX = -1, int parentY = -1, string direction = "")
    {
        this->x = x;
        this->y = y;
        this->f = f;
        this->g = g;
        this->h = h;
        this->parentX = parentX;
        this->parentY = parentY;
        this->direction = direction;
    }
};

// direction vectors for moving in 8 possible directions
//  quy ước (maze coordinate: x=row, y=column)
//  0 : Up      (x-1, y)
//  1 : Down    (x+1, y)
//  2 : Left    (x, y-1)
//  3 : Right   (x, y+1)
//  4 : Up-Left (x-1, y-1)
//  5 : Up-Right (x-1, y+1)
//  6 : Down-Left (x+1, y-1)
//  7 : Down-Right (x+1, y+1)
int dirX[8] = {-1, 1, 0, 0, -1, -1, 1, 1};
int dirY[8] = {0, 0, -1, 1, -1, 1, -1, 1};
string directionNames[8] = {"Up", "Down", "Left", "Right", "Up-Left", "Up-Right", "Down-Left", "Down-Right"};
//

double heuristicTask3_4(int x1, int y1, int x2, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}
PathNode* findPathInMaze(int maze[100][100], int m, int n, int startX, int startY, int goalX, int goalY)
{
    // Handle start = goal case
    if (startX == goalX && startY == goalY)
    {
        PathNode* head = nullptr;
        PathNode* tail = nullptr;
        appendNode(head, tail, "", 0.0, 0.0, 0.0);
        return head;
    }

    vector<vector<bool>> visited(m, vector<bool>(n, false));
    vector<MazeNode> openList;
    vector<vector<MazeNode>> NodesInfo(m, vector<MazeNode>(n, MazeNode(-1, -1, 0, 0, 0, -1, -1, "")));
    double gCost[100][100];
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            gCost[i][j] = INF;

    gCost[startX][startY] = 0.0;
    double hCost = heuristicTask3_4(startX, startY, goalX, goalY);
    double f_begin = gCost[startX][startY] + hCost;
    MazeNode startNode(startX, startY, f_begin, gCost[startX][startY], hCost, -1, -1, "");
    openList.push_back(startNode);
    NodesInfo[startX][startY] = startNode;
    openList.push_back(startNode);

    while (!openList.empty())
    {
        sort(openList.begin(), openList.end(), [](const MazeNode& a, const MazeNode& b)
             {
            if (a.f == b.f)
                return a.g < b.g;
            return a.f < b.f; });

        MazeNode current_Node = openList[0];
        openList.erase(openList.begin());

        if (visited[current_Node.x][current_Node.y])
            continue;
        visited[current_Node.x][current_Node.y] = 1;

        if (current_Node.x == goalX && current_Node.y == goalY)
        {
            vector<MazeNode> path;
            int x_it = goalX;
            int y_it = goalY;
            while (x_it != startX || y_it != startY)
            {
                path.push_back(NodesInfo[x_it][y_it]);
                int parent_AssignX = NodesInfo[x_it][y_it].parentX;
                int parent_AssignY = NodesInfo[x_it][y_it].parentY;
                x_it = parent_AssignX;
                y_it = parent_AssignY;
            }
            reverse(path.begin(), path.end());

            PathNode* head;
            PathNode* tail;
            head = nullptr;
            tail = nullptr;
            for (int i = 0; i < path.size(); i++)
            {
                // name is direcion up or down ...
                appendNode(head, tail, path[i].direction, path[i].g + path[i].h, path[i].g, path[i].h);
            }
            return head;
        }

        for (int dir = 0; dir < 8; dir++)
        {
            int newX = current_Node.x + dirX[dir];
            int newY = current_Node.y + dirY[dir];

            // at here we need to check if newX and newY are within bounds and not an obstacle
            if (newX >= 0 && newX < m && newY >= 0 && newY < n && maze[newX][newY] == 0 && !visited[newX][newY])
            {
                double cost_to_move = (dir < 4) ? 1.0 : 1.5;  // 1 is cost for moving up, down, left, right ; 1.5 is cost for moving diagonally
                double newG = gCost[current_Node.x][current_Node.y] + cost_to_move;
                if (newG < gCost[newX][newY])
                {
                    gCost[newX][newY] = newG;
                    double f_new = newG + heuristicTask3_4(newX, newY, goalX, goalY);
                    MazeNode neighborNode(newX, newY, f_new, newG, heuristicTask3_4(newX, newY, goalX, goalY), current_Node.x, current_Node.y, directionNames[dir]);
                    openList.push_back(neighborNode);
                    NodesInfo[newX][newY] = neighborNode;
                }
            }
        }
    }
    return nullptr;
}

//  0 : Up
//  1 : Down
//  2 : Left
//  3 : Right
//  4 : Up-Left
//  5 : Up-Right
//  6 : Down-Left
//  7 : Down-Right
// Di chuyển bằng dirX và dirY

// Task 4 : Maze Navigation with Obstacles 2
PathNode* findPathInMaze2(int maze[100][100], int m, int n, int startX, int startY, int goalX, int goalY, double weightMatrix[100][100])
{
    // Implementation would be similar to Task 3, but when calculating newG, we would add the weight from weightMatrix
    // very easy to implement, just add weightMatrix[newX][newY] to newG calculation
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    vector<MazeNode> openList;
    vector<vector<MazeNode>> NodeInfo(m, vector<MazeNode>(n, MazeNode(-1, -1, 0, 0, 0, -1, -1, "")));
    // initialize gcost
    int gCost[m][n];
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            gCost[i][j] = INF;

    gCost[startX][startY] = 0;
    MazeNode startNode = MazeNode(startX, startY, 0, 0, 0, -1, -1, "");
    openList.push_back(startNode);
    NodeInfo[startX][startY] = startNode;
    while (!openList.empty())
    {
        sort(openList.begin(), openList.end(), [](const MazeNode& a, const MazeNode& b)
             {
            if (a.f == b.f)
                return a.g < b.g;
            return a.f < b.f; });

        MazeNode current_Node = openList[0];
        openList.erase(openList.begin());
        if (current_Node.x == goalX && current_Node.y == goalY)
        {
            vector<MazeNode> path;
            int x_it = goalX;
            int y_it = goalY;
            while (x_it != startX || y_it != startY)
            {
                path.push_back(NodeInfo[x_it][y_it]);
                int parent_AssignX = NodeInfo[x_it][y_it].parentX;
                int parent_AssignY = NodeInfo[x_it][y_it].parentY;
                x_it = parent_AssignX;
                y_it = parent_AssignY;
            }
            reverse(path.begin(), path.end());

            PathNode* head;
            PathNode* tail;
            head = nullptr;
            tail = nullptr;
            for (int i = 0; i < path.size(); i++)
            {
                // name is direcion up or down ...
                string vertex_name = "(" + to_string(path[i].x) + "," + to_string(path[i].y) + ")";
                appendNode(head, tail, vertex_name, path[i].g + path[i].h, path[i].g, path[i].h);
            }
            return head;
        }

        // Handle traversing neighbors
        for (int dir = 0; dir < 8; dir++)
        {
            int newX = current_Node.x + dirX[dir];
            int newY = current_Node.y + dirY[dir];

            // Check bounds and obstacles
            if (newX >= 0 && newX < m && newY >= 0 && newY < n && maze[newX][newY] == 0 && !visited[newX][newY])
            {
                double cost_to_move = (dir < 4) ? 1.0 : 1.5;  // Cost for moving
                double newG = gCost[current_Node.x][current_Node.y] + cost_to_move + weightMatrix[newX][newY];
                if (newG < gCost[newX][newY])
                {
                    gCost[newX][newY] = newG;
                    double f_new = newG + heuristicTask3_4(newX, newY, goalX, goalY);
                    MazeNode neighborNode(newX, newY, f_new, newG, heuristicTask3_4(newX, newY, goalX, goalY), current_Node.x, current_Node.y, directionNames[dir]);
                    openList.push_back(neighborNode);
                    NodeInfo[newX][newY] = neighborNode;
                }
            }
        }
    }
    return nullptr;
}
