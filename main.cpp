// Compile: g++ -std=c++11 -o demo main.cpp Algo.cpp PathNode.cpp
// Run: ./demo

#include <iostream>
#include <iomanip>
#include <cstring>
#include "Algo.h"
#include "PathNode.h"

using namespace std;

// ==================== TASK 1 ====================
void testTask1() {
    cout << "\n";
    cout << "========================================\n";
    cout << "       TASK 1: ABSTRACT GRAPH A*       \n";
    cout << "========================================\n\n";
    
    // Initialize adjacency matrix
    double adjMatrix[100][100];
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            adjMatrix[i][j] = 0.0;
        }
    }
    
    // Build sample graph: 0 -> 1 -> 2 -> 3 -> 4
    //                       \-> 5 -> 6 ->/
    cout << "Graph Structure:\n";
    cout << "  0 --2.0--> 1 --3.0--> 2 --2.5--> 3 --1.5--> 4\n";
    cout << "   \\--4.0--> 5 --2.0--> 6 ----------/\n\n";
    
    adjMatrix[0][1] = 2.0;
    adjMatrix[0][5] = 4.0;
    adjMatrix[1][2] = 3.0;
    adjMatrix[2][3] = 2.5;
    adjMatrix[3][4] = 1.5;
    adjMatrix[5][6] = 2.0;
    adjMatrix[6][4] = 3.0;
    
    cout << "Start: Vertex 0\n";
    cout << "Goal:  Vertex 4\n\n";
    
    cout << "Running A* Algorithm...\n";
    cout << "------------------------\n";
    
    PathNode* result = findShortestPathMatrix(adjMatrix, 0, 4);
    
    if (result != nullptr) {
        cout << "\n✓ Path found!\n";
        cout << "\nOptimal Path:\n";
        printPath(result);
        
        // Calculate total cost
        double totalCost = 0.0;
        PathNode* temp = result;
        while (temp != nullptr) {
            totalCost = temp->g;
            temp = temp->next;
        }
        cout << "\nTotal Cost: " << fixed << setprecision(2) << totalCost << "\n";
        
        deletePathList(result);
    } else {
        cout << "\n✗ No path found!\n";
    }
}

// ==================== TASK 2 ====================
void testTask2() {
    cout << "\n";
    cout << "========================================\n";
    cout << "    TASK 2: 2D WEIGHTED GRAPH A*       \n";
    cout << "========================================\n\n";
    
    // Initialize adjacency matrix
    double adjMatrix[100][100];
    int coords[100][2];
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            adjMatrix[i][j] = 0.0;
        }
    }
    
    // Set coordinates for vertices
    coords[0][0] = 0; coords[0][1] = 0;  // A at (0,0)
    coords[1][0] = 1; coords[1][1] = 1;  // B at (1,1)
    coords[2][0] = 0; coords[2][1] = 2;  // C at (0,2)
    coords[3][0] = 2; coords[3][1] = 2;  // D at (2,2)
    coords[4][0] = 3; coords[4][1] = 3;  // E at (3,3)
    
    cout << "2D Graph with Coordinates:\n";
    cout << "  Vertex 0 (A): (0, 0)\n";
    cout << "  Vertex 1 (B): (1, 1)\n";
    cout << "  Vertex 2 (C): (0, 2)\n";
    cout << "  Vertex 3 (D): (2, 2)\n";
    cout << "  Vertex 4 (E): (3, 3)\n\n";
    
    cout << "Edges:\n";
    cout << "  A --2.2--> B\n";
    cout << "  A --2.5--> C\n";
    cout << "  B --2.2--> E\n";
    cout << "  C --2.2--> D\n";
    cout << "  D --1.4--> E\n\n";
    
    adjMatrix[0][1] = 2.2;  // A -> B
    adjMatrix[0][2] = 2.5;  // A -> C
    adjMatrix[1][4] = 2.2;  // B -> E
    adjMatrix[2][3] = 2.2;  // C -> D
    adjMatrix[3][4] = 1.4;  // D -> E
    
    cout << "Start: Vertex 0 (A)\n";
    cout << "Goal:  Vertex 4 (E)\n\n";
    
    cout << "Running A* with Euclidean Heuristic...\n";
    cout << "---------------------------------------\n";
    
    PathNode* result = findShortestPath2D(adjMatrix, coords, 0, 4, 1);
    
    if (result != nullptr) {
        cout << "\n✓ Path found!\n";
        cout << "\nOptimal Path:\n";
        printPath(result);
        
        // Calculate total cost
        double totalCost = 0.0;
        PathNode* temp = result;
        while (temp != nullptr) {
            totalCost = temp->g;
            temp = temp->next;
        }
        cout << "\nTotal Cost: " << fixed << setprecision(2) << totalCost << "\n";
        
        deletePathList(result);
    } else {
        cout << "\n✗ No path found!\n";
    }
}

// ==================== TASK 3 ====================
void testTask3() {
    cout << "\n";
    cout << "========================================\n";
    cout << "      TASK 3: MAZE NAVIGATION A*       \n";
    cout << "========================================\n\n";
    
    int maze[100][100];
    int m = 6, n = 6;
    
    // Initialize maze (0 = free, 1 = obstacle)
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            maze[i][j] = 0;
        }
    }
    
    // Add obstacles
    maze[1][1] = 1;
    maze[2][2] = 1;
    maze[2][3] = 1;
    maze[3][3] = 1;
    
    cout << "Maze Layout (6x6):\n";
    cout << "  S = Start (0,0)\n";
    cout << "  G = Goal (5,5)\n";
    cout << "  # = Obstacle\n";
    cout << "  . = Free cell\n\n";
    
    for (int i = 0; i < m; i++) {
        cout << "  ";
        for (int j = 0; j < n; j++) {
            if (i == 0 && j == 0) {
                cout << "S ";
            } else if (i == 5 && j == 5) {
                cout << "G ";
            } else if (maze[i][j] == 1) {
                cout << "# ";
            } else {
                cout << ". ";
            }
        }
        cout << "\n";
    }
    
    cout << "\nMovement:\n";
    cout << "  - 8 directions (N, S, E, W, NE, NW, SE, SW)\n";
    cout << "  - Cardinal moves: cost 1.0\n";
    cout << "  - Diagonal moves: cost 1.5\n\n";
    
    cout << "Start: (0, 0)\n";
    cout << "Goal:  (5, 5)\n\n";
    
    cout << "Running A* with Manhattan Heuristic...\n";
    cout << "---------------------------------------\n";
    
    PathNode* result = findPathInMaze(maze, m, n, 0, 0, 5, 5);
    
    if (result != nullptr) {
        cout << "\n✓ Path found!\n";
        cout << "\nOptimal Path:\n";
        printPath(result);
        
        // Calculate total cost
        double totalCost = 0.0;
        PathNode* temp = result;
        while (temp != nullptr) {
            totalCost = temp->g;
            temp = temp->next;
        }
        cout << "\nTotal Cost: " << fixed << setprecision(2) << totalCost << "\n";
        
        deletePathList(result);
    } else {
        cout << "\n✗ No path found!\n";
    }
}

// ==================== TASK 4 ====================
void testTask4() {
    cout << "\n";
    cout << "========================================\n";
    cout << "   TASK 4: MAZE TO GRAPH CONVERSION    \n";
    cout << "========================================\n\n";
    
    int maze[100][100];
    double weightMatrix[100][100];
    int m = 5, n = 5;
    
    // Initialize maze
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            maze[i][j] = 0;
        }
    }
    
    // Initialize weight matrix
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            weightMatrix[i][j] = 0.0;
        }
    }
    
    // Add obstacles
    maze[1][2] = 1;  // vertex 7
    maze[2][2] = 1;  // vertex 12
    
    cout << "Maze Layout (5x5):\n";
    cout << "  S = Start (0,0) -> Vertex 0\n";
    cout << "  G = Goal (4,4) -> Vertex 24\n";
    cout << "  # = Obstacle\n";
    cout << "  . = Free cell\n\n";
    
    cout << "Maze with Vertex IDs:\n";
    for (int i = 0; i < m; i++) {
        cout << "  ";
        for (int j = 0; j < n; j++) {
            int vertex = i * n + j;
            if (i == 0 && j == 0) {
                cout << "S" << setw(2) << vertex << " ";
            } else if (i == 4 && j == 4) {
                cout << "G" << setw(2) << vertex << " ";
            } else if (maze[i][j] == 1) {
                cout << " ## ";
            } else {
                cout << setw(3) << vertex << " ";
            }
        }
        cout << "\n";
    }
    
    cout << "\nConversion:\n";
    cout << "  - Each free cell (i,j) becomes vertex v = i*5 + j\n";
    cout << "  - Edges connect adjacent free cells\n";
    cout << "  - Cardinal edges: weight 1.0\n";
    cout << "  - Diagonal edges: weight 1.5\n\n";
    
    cout << "Start: (0, 0) -> Vertex 0\n";
    cout << "Goal:  (4, 4) -> Vertex 24\n\n";
    
    cout << "Running A* on Converted Graph...\n";
    cout << "---------------------------------\n";
    
    PathNode* result = findPathInMaze2(maze, m, n, 0, 0, 4, 4, weightMatrix);
    
    if (result != nullptr) {
        cout << "\n✓ Path found!\n";
        cout << "\nOptimal Path (Vertex IDs):\n";
        printPath(result);
        
        // Calculate total cost
        double totalCost = 0.0;
        PathNode* temp = result;
        while (temp != nullptr) {
            totalCost = temp->g;
            temp = temp->next;
        }
        cout << "\nTotal Cost: " << fixed << setprecision(2) << totalCost << "\n";
        
        deletePathList(result);
    } else {
        cout << "\n✗ No path found!\n";
    }
}

// ==================== MAIN ====================
int main() {
    cout << "\n";
    cout << "********************************************\n";
    cout << "*                                          *\n";
    cout << "*     A* PATHFINDING ALGORITHM DEMO       *\n";
    cout << "*         4 Tasks Implementation           *\n";
    cout << "*                                          *\n";
    cout << "********************************************\n";
    
    // Run all 4 tasks
    testTask1();
    testTask2();
    testTask3();
    testTask4();
    
    cout << "\n";
    cout << "========================================\n";
    cout << "      ALL TASKS COMPLETED!              \n";
    cout << "========================================\n\n";
    
    return 0;
}
