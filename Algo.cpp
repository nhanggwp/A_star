#include "Algo.h"

#include <algorithm>
#include <cmath>
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
        int min_idx = 0;
        for (int i = 0; i < openList.size(); i++)
        {
            if (openList[i].f < openList[min_idx].f)
            {
                min_idx = i;
            }
            else if (openList[i].f == openList[min_idx].f)
            {
                min_idx = i < min_idx ? i : min_idx;
            }
        }
        AStarNode currentNode = openList[min_idx];
        int current_vertex = currentNode.vertex;
        openList.erase(openList.begin() + min_idx);
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
                node = parent[node];
                path.push_back(node);
            }
            reverse(path.begin(), path.end());

            PathNode* head = nullptr;
            PathNode* tail = nullptr;
            for (int i = 0; i < path.size(); i++)
            {
                appendNode(head, tail, to_string(path[i]), gCost[i] + heuristicTask1(i, goal), gCost[i], heuristicTask1(i, goal));
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
        int min_idx = 0;
        for (int i = 0; i < openList.size(); i++)
        {
            if (openList[i].f < openList[min_idx].f)
            {
                min_idx = i;
            }
            else if (openList[i].f == openList[min_idx].f)
            {
                min_idx = i < min_idx ? i : min_idx;
            }
        }
        AStarNode currentNode = openList[min_idx];
        int current_vertex = currentNode.vertex;
        openList.erase(openList.begin() + min_idx);
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
                node = parent[node];
                path.push_back(node);
            }
            reverse(path.begin(), path.end());

            PathNode* head = nullptr;
            PathNode* tail = nullptr;
            for (int i = 0; i < path.size(); i++)
            {
                appendNode(head, tail, to_string(path[i]), gCost[i] + heuristicTask2(coords, i, goal, mode), gCost[i], heuristicTask2(coords, i, goal, mode));
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
}
