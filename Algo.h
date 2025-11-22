#ifndef ALGO_H
#define ALGO_H

#include "PathNode.h"

// Task 1: Shortest Path Using A* with Adjacency Matrix
PathNode* findShortestPathMatrix(double adjMatrix[100][100], int start, int goal);

// Task 2: Shortest Path in 2D Space with Two Heuristics
PathNode* findShortestPath2D(double adjMatrix[100][100], int coords[100][2], int start, int goal, int mode);

// Task 3: Maze Navigation with Obstacles
PathNode* findPathInMaze(int maze[100][100], int m, int n, int startX, int startY, int goalX, int goalY);

// Task 4: Maze Navigation with Obstacles 2 (convert to graph)
PathNode* findPathInMaze2(int maze[100][100], int m, int n, int startX, int startY, int goalX, int goalY, double weightMatrix[100][100]);

#endif  // ALGO_H
