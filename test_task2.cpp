#include <cmath>
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>

#include "Algo.h"
using namespace std;

// ANSI color codes
#define GREEN "\033[32m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

// Global test tracking
int totalTests = 0;
int passedTests = 0;
vector<string> failedTests;

string pathToString(PathNode* head)
{
    if (!head) return "null";
    stringstream ss;
    PathNode* temp = head;
    while (temp)
    {
        ss << temp->name;
        if (temp->next) ss << "->";
        temp = temp->next;
    }
    return ss.str();
}

double getPathCost(PathNode* head)
{
    if (!head) return -1.0;
    PathNode* temp = head;
    while (temp->next) temp = temp->next;
    return temp->g;
}

void checkResult(const string& testName, PathNode* result, const string& expectedPath, double expectedCost)
{
    string actualPath = pathToString(result);
    double actualCost = getPathCost(result);

    bool pathMatch = (actualPath == expectedPath);
    bool costMatch = (expectedCost < 0) ? (actualCost < 0) : (fabs(actualCost - expectedCost) < 0.01);
    bool pass = pathMatch && costMatch;

    totalTests++;
    if (pass)
    {
        passedTests++;
    }
    else
    {
        failedTests.push_back(testName);
    }

    cout << testName << endl;
    cout << "Expected: " << expectedPath << " (cost: " << expectedCost << ")" << endl;
    cout << "Actual:   " << actualPath << " (cost: " << actualCost << ")" << endl;
    cout << (pass ? GREEN "✓ PASS" RESET : RED "✗ FAIL" RESET) << "\n"
         << endl;
}

// Test 1: Simple straight line - Euclidean
void test1()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{0, 0}, {5, 0}, {10, 0}};
    adj[0][1] = 5.0;
    adj[1][0] = 5.0;
    adj[1][2] = 5.0;
    adj[2][1] = 5.0;
    PathNode* result = findShortestPath2D(adj, coords, 0, 2, 0);
    checkResult("Test 1: Straight line Euclidean", result, "0->1->2", 10.0);
    deletePathList(result);
}

// Test Case 2: Manhattan distance
void test2()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{0, 0}, {3, 4}, {6, 8}};
    adj[0][1] = 5.0;
    adj[1][2] = 5.0;
    PathNode* result = findShortestPath2D(adj, coords, 0, 2, 1);
    checkResult("Test 2: Manhattan distance", result, "0->1->2", 10.0);
    deletePathList(result);
}

// Test Case 3: Triangle with shortcut
void test3()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{0, 0}, {3, 0}, {0, 4}, {3, 4}};
    adj[0][1] = 3.0;
    adj[1][3] = 4.0;
    adj[0][2] = 4.0;
    adj[2][3] = 3.0;
    PathNode* result = findShortestPath2D(adj, coords, 0, 3, 0);
    checkResult("Test 3: Triangle shortcut", result, "0->1->3", 7.0);
    deletePathList(result);
}

// Test Case 4: Start equals goal
void test4()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{5, 5}, {10, 10}};
    adj[0][1] = 7.07;
    PathNode* result = findShortestPath2D(adj, coords, 1, 1, 0);
    checkResult("Test 4: Start equals goal", result, "1", 0.0);
    deletePathList(result);
}

// Test Case 5: No path exists
void test5()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{0, 0}, {1, 1}, {5, 5}, {6, 6}};
    adj[0][1] = 1.41;
    adj[2][3] = 1.41;
    PathNode* result = findShortestPath2D(adj, coords, 0, 3, 0);
    checkResult("Test 5: No path", result, "null", -1.0);
    deletePathList(result);
}

// Test Case 6: Grid 3x3
void test6()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{0, 0}, {1, 0}, {2, 0}, {0, 1}, {1, 1}, {2, 1}, {0, 2}, {1, 2}, {2, 2}};
    adj[0][1] = 1;
    adj[1][2] = 1;
    adj[0][3] = 1;
    adj[1][4] = 1;
    adj[2][5] = 1;
    adj[3][4] = 1;
    adj[4][5] = 1;
    adj[3][6] = 1;
    adj[4][7] = 1;
    adj[5][8] = 1;
    adj[6][7] = 1;
    adj[7][8] = 1;
    PathNode* result = findShortestPath2D(adj, coords, 0, 8, 1);
    checkResult("Test 6: 3x3 grid Manhattan", result, "0->1->2->5->8", 4.0);
    deletePathList(result);
}

// Test Case 7: Diagonal preferred (Euclidean)
void test7()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{0, 0}, {1, 0}, {0, 1}, {1, 1}};
    adj[0][1] = 1;
    adj[0][2] = 1;
    adj[1][3] = 1;
    adj[2][3] = 1;
    PathNode* result = findShortestPath2D(adj, coords, 0, 3, 0);
    checkResult("Test 7: Diamond Euclidean", result, "0->1->3", 2.0);
    deletePathList(result);
}

// Test Case 8: Long chain 10 nodes
void test8()
{
    double adj[100][100] = {0};
    int coords[100][2];
    for (int i = 0; i < 10; i++)
    {
        coords[i][0] = i;
        coords[i][1] = 0;
        if (i < 9) adj[i][i + 1] = 1.0;
    }
    PathNode* result = findShortestPath2D(adj, coords, 0, 9, 0);
    checkResult("Test 8: 10-node chain", result, "0->1->2->3->4->5->6->7->8->9", 9.0);
    deletePathList(result);
}

// Test Case 9: Star topology
void test9()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{5, 5}, {5, 0}, {10, 5}, {5, 10}, {0, 5}, {5, 2}};
    adj[0][1] = 5;
    adj[0][2] = 5;
    adj[0][3] = 5;
    adj[0][4] = 5;
    adj[4][0] = 5;
    adj[1][5] = 2;
    adj[5][1] = 2;
    PathNode* result = findShortestPath2D(adj, coords, 4, 5, 0);
    checkResult("Test 9: Star topology", result, "4->0->1->5", 12.0);
    deletePathList(result);
}

// Test Case 10: Circle path
void test10()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{0, 0}, {2, 0}, {2, 2}, {0, 2}};
    adj[0][1] = 2;
    adj[1][2] = 2;
    adj[2][3] = 2;
    adj[3][0] = 2;
    PathNode* result = findShortestPath2D(adj, coords, 0, 2, 1);
    checkResult("Test 10: Square cycle", result, "0->1->2", 4.0);
    deletePathList(result);
}

// Test Case 11-20: More complex tests
void test11()
{
    double adj[100][100] = {0};
    int coords[100][2];
    for (int i = 0; i < 8; i++)
    {
        coords[i][0] = i % 4;
        coords[i][1] = i / 4;
    }
    adj[0][1] = 1;
    adj[1][2] = 1;
    adj[2][3] = 1;
    adj[0][4] = 1;
    adj[1][5] = 1;
    adj[2][6] = 1;
    adj[3][7] = 1;
    adj[4][5] = 1;
    adj[5][6] = 1;
    adj[6][7] = 1;
    PathNode* result = findShortestPath2D(adj, coords, 0, 7, 0);
    checkResult("Test 11: Grid 4x2", result, "0->1->2->3->7", 4.0);
    deletePathList(result);
}

void test12()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{0, 0}, {10, 0}, {5, 5}, {10, 10}};
    adj[0][1] = 10;
    adj[1][3] = 10;
    adj[0][2] = 7.07;
    adj[2][3] = 7.07;
    PathNode* result = findShortestPath2D(adj, coords, 0, 3, 0);
    checkResult("Test 12: Diagonal shortcut", result, "0->2->3", 14.14);
    deletePathList(result);
}

void test13()
{
    double adj[100][100] = {0};
    int coords[100][2];
    for (int i = 0; i < 12; i++)
    {
        coords[i][0] = i;
        coords[i][1] = i % 2;
        if (i < 11) adj[i][i + 1] = 1.41;
    }
    PathNode* result = findShortestPath2D(adj, coords, 0, 11, 0);
    checkResult("Test 13: Zigzag 12 nodes", result, "0->1->2->3->4->5->6->7->8->9->10->11", 15.51);
    deletePathList(result);
}

void test14()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {1, 1}, {2, 1}};
    adj[0][1] = 1;
    adj[1][2] = 1;
    adj[2][3] = 1;
    adj[1][4] = 1;
    adj[4][5] = 1;
    adj[5][2] = 1;
    PathNode* result = findShortestPath2D(adj, coords, 0, 3, 1);
    checkResult("Test 14: Detour path", result, "0->1->2->3", 3.0);
    deletePathList(result);
}

void test15()
{
    double adj[100][100] = {0};
    int coords[100][2];
    for (int i = 0; i < 15; i++)
    {
        coords[i][0] = i / 5;
        coords[i][1] = i % 5;
    }
    adj[0][1] = 1;
    adj[0][5] = 1;
    adj[1][2] = 1;
    adj[1][6] = 1;
    adj[5][10] = 1;
    adj[10][11] = 1;
    adj[11][12] = 1;
    adj[12][13] = 1;
    adj[13][14] = 1;
    PathNode* result = findShortestPath2D(adj, coords, 0, 14, 0);
    checkResult("Test 15: Sparse 15 nodes", result, "0->5->10->11->12->13->14", 6.0);
    deletePathList(result);
}

void test16()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{0, 0}, {5, 0}, {10, 0}, {5, 5}, {5, 10}};
    adj[0][1] = 5;
    adj[1][2] = 5;
    adj[1][3] = 5;
    adj[3][4] = 5;
    PathNode* result = findShortestPath2D(adj, coords, 0, 4, 0);
    checkResult("Test 16: L-shape path", result, "0->1->3->4", 15.0);
    deletePathList(result);
}

void test17()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{0, 0}, {1, 1}, {2, 0}, {3, 1}, {4, 0}};
    adj[0][1] = 1.41;
    adj[1][2] = 1.41;
    adj[2][3] = 1.41;
    adj[3][4] = 1.41;
    PathNode* result = findShortestPath2D(adj, coords, 0, 4, 0);
    checkResult("Test 17: Wave pattern", result, "0->1->2->3->4", 5.64);
    deletePathList(result);
}

void test18()
{
    double adj[100][100] = {0};
    int coords[100][2];
    for (int i = 0; i < 16; i++)
    {
        coords[i][0] = i % 4;
        coords[i][1] = i / 4;
    }
    for (int i = 0; i < 12; i++) adj[i][i + 4] = 1;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 3; j++) adj[i * 4 + j][i * 4 + j + 1] = 1;
    PathNode* result = findShortestPath2D(adj, coords, 0, 15, 1);
    checkResult("Test 18: 4x4 grid Manhattan", result, "0->1->2->3->7->11->15", 6.0);
    deletePathList(result);
}

void test19()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{0, 0}, {10, 0}, {20, 0}, {10, 10}, {10, 20}};
    adj[0][1] = 10;
    adj[1][2] = 10;
    adj[1][3] = 10;
    adj[3][4] = 10;
    adj[0][3] = 14.14;
    PathNode* result = findShortestPath2D(adj, coords, 0, 4, 0);
    checkResult("Test 19: Cross with shortcut", result, "0->3->4", 24.14);
    deletePathList(result);
}
void test20()
{
    double adj[100][100] = {0};
    int coords[100][2];

    // Zig-zag coordinates
    for (int i = 0; i < 20; i++)
    {
        coords[i][0] = i * 2;        // x = 0,2,4,...
        coords[i][1] = (i % 2) * 3;  // y = 0,3,0,3,0,3,...
    }

    // Unequal edge weights (sum = 60.80)
    double w[19] = {
        3.1, 2.8, 3.2, 3.0, 2.9, 3.3, 3.4, 3.1, 3.0, 2.7, 3.2, 3.1, 3.5, 3.0, 3.3, 3.4, 2.9, 3.2, 3.0};

    for (int i = 0; i < 19; i++)
        adj[i][i + 1] = w[i];

    PathNode* result = findShortestPath2D(adj, coords, 0, 19, 0);

    checkResult(
        "Test 20: 20-node zigzag (unequal weights)",
        result,
        "0->1->2->3->4->5->6->7->8->9->10->11->12->13->14->15->16->17->18->19",
        59.10);

    deletePathList(result);
}

// Tests 21-30
void test21()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{0, 0}, {3, 4}, {6, 0}, {9, 4}, {12, 0}};
    adj[0][1] = 5;
    adj[1][2] = 5;
    adj[2][3] = 5;
    adj[3][4] = 5;
    adj[0][2] = 6;
    adj[2][4] = 6;
    PathNode* result = findShortestPath2D(adj, coords, 0, 4, 0);
    checkResult("Test 21: Mountain path", result, "0->2->4", 12.0);
    deletePathList(result);
}

void test22()
{
    double adj[100][100] = {0};
    int coords[100][2];
    for (int i = 0; i < 25; i++)
    {
        coords[i][0] = i % 5;
        coords[i][1] = i / 5;
    }
    for (int i = 0; i < 20; i++) adj[i][i + 5] = 1;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 4; j++) adj[i * 5 + j][i * 5 + j + 1] = 1;
    PathNode* result = findShortestPath2D(adj, coords, 0, 24, 1);
    checkResult("Test 22: 5x5 grid", result, "0->1->2->3->4->9->14->19->24", 8.0);
    deletePathList(result);
}

void test23()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{0, 0}, {1, 0}, {2, 0}, {1, 1}, {1, 2}};
    adj[0][1] = 1;
    adj[1][2] = 1;
    adj[1][3] = 1;
    adj[3][4] = 1;
    PathNode* result = findShortestPath2D(adj, coords, 0, 4, 0);
    checkResult("Test 23: T-junction", result, "0->1->3->4", 3.0);
    deletePathList(result);
}

void test24()
{
    double adj[100][100] = {0};
    int coords[100][2];

    // Manually defined circular-like coordinates (no for-loop)
    coords[0][0] = 10;
    coords[0][1] = 0;
    coords[1][0] = 8;
    coords[1][1] = 5;
    coords[2][0] = 3;
    coords[2][1] = 9;
    coords[3][0] = -3;
    coords[3][1] = 9;
    coords[4][0] = -8;
    coords[4][1] = 5;
    coords[5][0] = -10;
    coords[5][1] = 0;
    coords[6][0] = -8;
    coords[6][1] = -5;
    coords[7][0] = -3;
    coords[7][1] = -9;
    coords[8][0] = 3;
    coords[8][1] = -9;
    coords[9][0] = 8;
    coords[9][1] = -5;

    // Set main circular edges (all = 6.28)
    adj[0][1] = 6.28;
    adj[1][2] = 6.28;
    adj[2][3] = 6.28;
    adj[3][4] = 6.28;
    adj[4][5] = 6.28;
    adj[5][6] = 6.28;
    adj[6][7] = 6.28;
    adj[7][8] = 6.28;
    adj[8][9] = 6.28;

    // One long shortcut (should NOT be chosen by A*)
    adj[0][5] = 20.0;

    PathNode* result =
        findShortestPath2D(adj, coords, 0, 9, 0);  // mode 0 → Euclidean heuristic

    checkResult(
        "Test 24: Circular path (manual coords)",
        result,
        "0->5->6->7->8->9",
        45.12);

    deletePathList(result);
}

void test25()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{0, 0}, {5, 0}, {10, 0}, {15, 0}, {20, 0}, {10, 5}, {10, 10}};
    adj[0][1] = 5;
    adj[1][2] = 5;
    adj[2][3] = 5;
    adj[3][4] = 5;
    adj[2][5] = 5;
    adj[5][6] = 5;
    PathNode* result = findShortestPath2D(adj, coords, 0, 6, 0);
    checkResult("Test 25: Straight then perpendicular", result, "0->1->2->5->6", 20.0);
    deletePathList(result);
}

void test26()
{
    double adj[100][100] = {0};
    int coords[100][2];

    // ----- Manual coords: 3x4 grid -----
    // Row 0
    coords[0][0] = 0;
    coords[0][1] = 0;  // (0,0)
    coords[3][0] = 1;
    coords[3][1] = 0;  // (1,0)
    coords[6][0] = 2;
    coords[6][1] = 0;  // (2,0)
    coords[9][0] = 3;
    coords[9][1] = 0;  // (3,0)

    // Row 1
    coords[1][0] = 0;
    coords[1][1] = 1;  // (0,1)
    coords[4][0] = 1;
    coords[4][1] = 1;  // (1,1)
    coords[7][0] = 2;
    coords[7][1] = 1;  // (2,1)
    coords[10][0] = 3;
    coords[10][1] = 1;  // (3,1)

    // Row 2
    coords[2][0] = 0;
    coords[2][1] = 2;  // (0,2)
    coords[5][0] = 1;
    coords[5][1] = 2;  // (1,2)
    coords[8][0] = 2;
    coords[8][1] = 2;  // (2,2)
    coords[11][0] = 3;
    coords[11][1] = 2;  // (3,2)

    // ----- Edges: down (cost = 1) -----
    // Column x = 0: 0->1, 1->2
    adj[0][1] = 1.0;
    adj[1][2] = 1.0;

    // Column x = 1: 3->4, 4->5
    adj[3][4] = 1.0;
    adj[4][5] = 1.0;

    // Column x = 2: 6->7, 7->8
    adj[6][7] = 1.0;
    adj[7][8] = 1.0;

    // Column x = 3: 9->10, 10->11
    adj[9][10] = 1.0;
    adj[10][11] = 1.0;

    // ----- Edges: right (cost = 1) -----
    // Row y = 0: 0->3, 3->6, 6->9
    adj[0][3] = 1.0;
    adj[3][6] = 1.0;
    adj[6][9] = 1.0;

    // Row y = 1: 1->4, 4->7, 7->10
    adj[1][4] = 1.0;
    adj[4][7] = 1.0;
    adj[7][10] = 1.0;

    // Row y = 2: 2->5, 5->8, 8->11
    adj[2][5] = 1.0;
    adj[5][8] = 1.0;
    adj[8][11] = 1.0;

    PathNode* result = findShortestPath2D(adj, coords, 0, 11, 0);

    checkResult(
        "Test 26: 3x4 grid (manual init)",
        result,
        "0->3->4->7->8->11",
        5.0);

    deletePathList(result);
}

void test27()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{0, 0}, {2, 2}, {4, 4}, {6, 6}, {8, 8}};
    for (int i = 0; i < 4; i++) adj[i][i + 1] = 2.83;
    adj[0][4] = 11.31;
    PathNode* result = findShortestPath2D(adj, coords, 0, 4, 0);
    checkResult("Test 27: Diagonal line", result, "0->4", 11.31);
    deletePathList(result);
}

void test28()
{
    double adj[100][100] = {0};
    int coords[100][2];

    // ----- Manual coords (6 columns × 3 rows) -----
    // Row 0
    coords[0][0] = 0;
    coords[0][1] = 0;
    coords[1][0] = 1;
    coords[1][1] = 0;
    coords[2][0] = 2;
    coords[2][1] = 0;
    coords[3][0] = 3;
    coords[3][1] = 0;
    coords[4][0] = 4;
    coords[4][1] = 0;
    coords[5][0] = 5;
    coords[5][1] = 0;

    // Row 1
    coords[6][0] = 0;
    coords[6][1] = 1;
    coords[7][0] = 1;
    coords[7][1] = 1;
    coords[8][0] = 2;
    coords[8][1] = 1;
    coords[9][0] = 3;
    coords[9][1] = 1;
    coords[10][0] = 4;
    coords[10][1] = 1;
    coords[11][0] = 5;
    coords[11][1] = 1;

    // Row 2
    coords[12][0] = 0;
    coords[12][1] = 2;
    coords[13][0] = 1;
    coords[13][1] = 2;
    coords[14][0] = 2;
    coords[14][1] = 2;
    coords[15][0] = 3;
    coords[15][1] = 2;
    coords[16][0] = 4;
    coords[16][1] = 2;
    coords[17][0] = 5;
    coords[17][1] = 2;

    // ----- Vertical edges (down), cost = 1 -----
    adj[0][6] = 1;
    adj[1][7] = 1;
    adj[2][8] = 1;
    adj[3][9] = 1;
    adj[4][10] = 1;
    adj[5][11] = 1;

    adj[6][12] = 1;
    adj[7][13] = 1;
    adj[8][14] = 1;
    adj[9][15] = 1;
    adj[10][16] = 1;
    adj[11][17] = 1;

    // ----- Horizontal edges (right), cost = 1 -----
    // Row 0
    adj[0][1] = 1;
    adj[1][2] = 1;
    adj[2][3] = 1;
    adj[3][4] = 1;
    adj[4][5] = 1;

    // Row 1
    adj[6][7] = 1;
    adj[7][8] = 1;
    adj[8][9] = 1;
    adj[9][10] = 1;
    adj[10][11] = 1;

    // Row 2
    adj[12][13] = 1;
    adj[13][14] = 1;
    adj[14][15] = 1;
    adj[15][16] = 1;
    adj[16][17] = 1;

    // mode = 1 → Manhattan heuristic
    PathNode* result = findShortestPath2D(adj, coords, 0, 17, 1);

    checkResult(
        "Test 28: 6x3 grid (manual init)",
        result,
        "0->1->2->3->4->5->11->17",
        7.0);

    deletePathList(result);
}

void test29()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{0, 0}, {1, 0}, {0, 1}, {2, 0}, {0, 2}, {3, 0}, {0, 3}};
    adj[0][1] = 1;
    adj[0][2] = 1;
    adj[1][3] = 1;
    adj[2][4] = 1;
    adj[3][5] = 1;
    adj[4][6] = 1;
    PathNode* result = findShortestPath2D(adj, coords, 0, 6, 1);
    checkResult("Test 29: Binary tree path", result, "0->2->4->6", 3.0);
    deletePathList(result);
}

void test30()
{
    double adj[100][100] = {0};
    int coords[100][2];

    // ---------- Manual coords: 6 columns × 5 rows ----------
    // Row 0
    coords[0][0] = 0;
    coords[0][1] = 0;
    coords[1][0] = 1;
    coords[1][1] = 0;
    coords[2][0] = 2;
    coords[2][1] = 0;
    coords[3][0] = 3;
    coords[3][1] = 0;
    coords[4][0] = 4;
    coords[4][1] = 0;
    coords[5][0] = 5;
    coords[5][1] = 0;

    // Row 1
    coords[6][0] = 0;
    coords[6][1] = 1;
    coords[7][0] = 1;
    coords[7][1] = 1;
    coords[8][0] = 2;
    coords[8][1] = 1;
    coords[9][0] = 3;
    coords[9][1] = 1;
    coords[10][0] = 4;
    coords[10][1] = 1;
    coords[11][0] = 5;
    coords[11][1] = 1;

    // Row 2
    coords[12][0] = 0;
    coords[12][1] = 2;
    coords[13][0] = 1;
    coords[13][1] = 2;
    coords[14][0] = 2;
    coords[14][1] = 2;
    coords[15][0] = 3;
    coords[15][1] = 2;
    coords[16][0] = 4;
    coords[16][1] = 2;
    coords[17][0] = 5;
    coords[17][1] = 2;

    // Row 3
    coords[18][0] = 0;
    coords[18][1] = 3;
    coords[19][0] = 1;
    coords[19][1] = 3;
    coords[20][0] = 2;
    coords[20][1] = 3;
    coords[21][0] = 3;
    coords[21][1] = 3;
    coords[22][0] = 4;
    coords[22][1] = 3;
    coords[23][0] = 5;
    coords[23][1] = 3;

    // Row 4
    coords[24][0] = 0;
    coords[24][1] = 4;
    coords[25][0] = 1;
    coords[25][1] = 4;
    coords[26][0] = 2;
    coords[26][1] = 4;
    coords[27][0] = 3;
    coords[27][1] = 4;
    coords[28][0] = 4;
    coords[28][1] = 4;
    coords[29][0] = 5;
    coords[29][1] = 4;

    // ---------- Vertical edges (down), cost = 1 ----------
    adj[0][6] = 1;
    adj[1][7] = 1;
    adj[2][8] = 1;
    adj[3][9] = 1;
    adj[4][10] = 1;
    adj[5][11] = 1;

    adj[6][12] = 1;
    adj[7][13] = 1;
    adj[8][14] = 1;
    adj[9][15] = 1;
    adj[10][16] = 1;
    adj[11][17] = 1;

    adj[12][18] = 1;
    adj[13][19] = 1;
    adj[14][20] = 1;
    adj[15][21] = 1;
    adj[16][22] = 1;
    adj[17][23] = 1;

    adj[18][24] = 1;
    adj[19][25] = 1;
    adj[20][26] = 1;
    adj[21][27] = 1;
    adj[22][28] = 1;
    adj[23][29] = 1;

    // ---------- Horizontal edges (right), cost = 1 ----------
    // Row 0
    adj[0][1] = 1;
    adj[1][2] = 1;
    adj[2][3] = 1;
    adj[3][4] = 1;
    adj[4][5] = 1;

    // Row 1
    adj[6][7] = 1;
    adj[7][8] = 1;
    adj[8][9] = 1;
    adj[9][10] = 1;
    adj[10][11] = 1;

    // Row 2
    adj[12][13] = 1;
    adj[13][14] = 1;
    adj[14][15] = 1;
    adj[15][16] = 1;
    adj[16][17] = 1;

    // Row 3
    adj[18][19] = 1;
    adj[19][20] = 1;
    adj[20][21] = 1;
    adj[21][22] = 1;
    adj[22][23] = 1;

    // Row 4
    adj[24][25] = 1;
    adj[25][26] = 1;
    adj[26][27] = 1;
    adj[27][28] = 1;
    adj[28][29] = 1;

    // mode = 0 → Euclidean heuristic
    PathNode* result = findShortestPath2D(adj, coords, 0, 29, 0);

    checkResult(
        "Test 30: 6x5 grid large (manual init)",
        result,
        "0->1->2->8->9->15->16->22->23->29",
        9.0);

    deletePathList(result);
}

// Tests 31-40
void test31()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{0, 0}, {10, 0}, {5, 5}, {0, 10}, {10, 10}};
    adj[0][1] = 10;
    adj[0][2] = 7.07;
    adj[2][4] = 7.07;
    adj[1][4] = 10;
    adj[0][3] = 10;
    adj[3][4] = 10;
    PathNode* result = findShortestPath2D(adj, coords, 0, 4, 0);
    checkResult("Test 31: Diamond with center", result, "0->2->4", 14.14);
    deletePathList(result);
}

void test32()
{
    double adj[100][100] = {0};
    int coords[100][2];
    for (int i = 0; i < 15; i++)
    {
        coords[i][0] = i;
        coords[i][1] = (i % 3 == 0) ? 0 : ((i % 3 == 1) ? 2 : 0);
    }
    for (int i = 0; i < 14; i++) adj[i][i + 1] = 2.83;
    PathNode* result = findShortestPath2D(adj, coords, 0, 14, 0);
    checkResult("Test 32: Triangle wave", result, "0->1->2->3->4->5->6->7->8->9->10->11->12->13->14", 39.62);
    deletePathList(result);
}

void test33()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{0, 0}, {2, 1}, {4, 0}, {6, 1}, {8, 0}, {10, 1}, {12, 0}};
    for (int i = 0; i < 6; i++) adj[i][i + 1] = 2.24;
    adj[0][6] = 12;
    PathNode* result = findShortestPath2D(adj, coords, 0, 6, 0);
    checkResult("Test 33: Sawtooth vs straight", result, "0->6", 12.0);
    deletePathList(result);
}

void test34()
{
    double adj[100][100] = {0};
    int coords[100][2];
    for (int i = 0; i < 20; i++)
    {
        coords[i][0] = i % 5;
        coords[i][1] = i / 5;
    }
    for (int i = 0; i < 16; i++) adj[i][i + 4] = 1;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) adj[i * 5 + j][i * 5 + j + 1] = 1;
    PathNode* result = findShortestPath2D(adj, coords, 0, 19, 0);
    checkResult("Test 34: 5x4 grid", result, "0->4->8->9->13->14->18->19", 7.0);
    deletePathList(result);
}

void test35()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{0, 0}, {3, 0}, {6, 0}, {3, 3}, {6, 3}, {9, 3}, {6, 6}, {9, 6}, {12, 6}};
    adj[0][1] = 3;
    adj[1][2] = 3;
    adj[1][3] = 3;
    adj[3][4] = 3;
    adj[2][4] = 3;
    adj[4][5] = 3;
    adj[4][6] = 3;
    adj[6][7] = 3;
    adj[5][7] = 3;
    adj[7][8] = 3;
    PathNode* result = findShortestPath2D(adj, coords, 0, 8, 0);
    checkResult("Test 35: Staircase structure", result, "0->1->2->4->5->7->8", 18.0);
    deletePathList(result);
}

void test36()
{
    double adj[100][100] = {0};
    int coords[100][2];
    for (int i = 0; i < 16; i++)
    {
        coords[i][0] = (i % 4) * 3;
        coords[i][1] = (i / 4) * 3;
    }
    for (int i = 0; i < 12; i++) adj[i][i + 4] = 3;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 3; j++) adj[i * 4 + j][i * 4 + j + 1] = 3;
    PathNode* result = findShortestPath2D(adj, coords, 0, 15, 0);
    checkResult("Test 36: Wide-spaced 4x4 grid", result, "0->1->5->6->10->11->15", 18.0);
    deletePathList(result);
}

void test37()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{0, 0}, {5, 0}, {10, 0}, {15, 0}, {5, 5}, {10, 5}, {5, 10}};
    adj[0][1] = 5;
    adj[1][2] = 5;
    adj[2][3] = 5;
    adj[1][4] = 5;
    adj[4][5] = 5;
    adj[5][2] = 5;
    adj[4][6] = 5;
    PathNode* result = findShortestPath2D(adj, coords, 0, 6, 0);
    checkResult("Test 37: H-shape network", result, "0->1->4->6", 15.0);
    deletePathList(result);
}

void test38()
{
    double adj[100][100] = {0};
    int coords[100][2];
    for (int i = 0; i < 12; i++)
    {
        coords[i][0] = i / 4;
        coords[i][1] = i % 4;
    }
    for (int i = 0; i < 8; i++) adj[i][i + 4] = 1;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) adj[i * 4 + j][i * 4 + j + 1] = 1;
    PathNode* result = findShortestPath2D(adj, coords, 0, 11, 1);
    checkResult("Test 38: 4x3 grid Manhattan", result, "0->1->2->3->7->11", 5.0);
    deletePathList(result);
}

void test39()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{0, 0}, {4, 3}, {8, 0}, {12, 3}, {16, 0}, {20, 3}, {24, 0}};
    for (int i = 0; i < 6; i++) adj[i][i + 1] = 5;
    adj[0][2] = 8;
    adj[2][4] = 8;
    adj[4][6] = 8;
    PathNode* result = findShortestPath2D(adj, coords, 0, 6, 0);
    checkResult("Test 39: Wave with shortcuts", result, "0->2->4->6", 24.0);
    deletePathList(result);
}

void test40()
{
    double adj[100][100] = {0};
    int coords[100][2];
    for (int i = 0; i < 35; i++)
    {
        coords[i][0] = i % 7;
        coords[i][1] = i / 7;
    }
    for (int i = 0; i < 28; i++) adj[i][i + 7] = 1;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 6; j++) adj[i * 7 + j][i * 7 + j + 1] = 1;
    PathNode* result = findShortestPath2D(adj, coords, 0, 34, 0);
    checkResult("Test 40: 7x5 grid large", result, "0->1->2->3->10->11->18->19->26->27->34", 10.0);
    deletePathList(result);
}

// Tests 41-50
void test41()
{
    double adj[100][100] = {0};
    int coords[100][2];

    // ----- Diagonal coordinates: (0,0), (1,1), ..., (7,7) -----
    coords[0][0] = 0;
    coords[0][1] = 0;
    coords[1][0] = 1;
    coords[1][1] = 1;
    coords[2][0] = 2;
    coords[2][1] = 2;
    coords[3][0] = 3;
    coords[3][1] = 3;
    coords[4][0] = 4;
    coords[4][1] = 4;
    coords[5][0] = 5;
    coords[5][1] = 5;
    coords[6][0] = 6;
    coords[6][1] = 6;
    coords[7][0] = 7;
    coords[7][1] = 7;

    // ----- Base diagonal edges i -> i+1, cost = 1.5 -----
    for (int i = 0; i < 7; i++)
        adj[i][i + 1] = 1.5;

    adj[0][2] = 2.6;
    adj[2][5] = 3.4;

    adj[5][7] = 2.5;

    adj[0][3] = 6.0;

    adj[3][7] = 7.0;

    // mode = 0 → Euclidean heuristic
    PathNode* result = findShortestPath2D(adj, coords, 0, 7, 0);

    checkResult(
        "Test 41: Diagonal line with good & bad shortcuts",
        result,
        "0->2->5->7",
        8.5);

    deletePathList(result);
}

void test42()
{
    double adj[100][100] = {0};
    int coords[100][2];

    // --------- Manual coords: 8 columns × 3 rows ----------
    // Row 0
    coords[0][0] = 0;
    coords[0][1] = 0;
    coords[1][0] = 1;
    coords[1][1] = 0;
    coords[2][0] = 2;
    coords[2][1] = 0;
    coords[3][0] = 3;
    coords[3][1] = 0;
    coords[4][0] = 4;
    coords[4][1] = 0;
    coords[5][0] = 5;
    coords[5][1] = 0;
    coords[6][0] = 6;
    coords[6][1] = 0;
    coords[7][0] = 7;
    coords[7][1] = 0;

    // Row 1
    coords[8][0] = 0;
    coords[8][1] = 1;
    coords[9][0] = 1;
    coords[9][1] = 1;
    coords[10][0] = 2;
    coords[10][1] = 1;
    coords[11][0] = 3;
    coords[11][1] = 1;
    coords[12][0] = 4;
    coords[12][1] = 1;
    coords[13][0] = 5;
    coords[13][1] = 1;
    coords[14][0] = 6;
    coords[14][1] = 1;
    coords[15][0] = 7;
    coords[15][1] = 1;

    // Row 2
    coords[16][0] = 0;
    coords[16][1] = 2;
    coords[17][0] = 1;
    coords[17][1] = 2;
    coords[18][0] = 2;
    coords[18][1] = 2;
    coords[19][0] = 3;
    coords[19][1] = 2;
    coords[20][0] = 4;
    coords[20][1] = 2;
    coords[21][0] = 5;
    coords[21][1] = 2;
    coords[22][0] = 6;
    coords[22][1] = 2;
    coords[23][0] = 7;
    coords[23][1] = 2;

    for (int i = 0; i < 16; i++)
        adj[i][i + 8] = 1;
    for (int base = 0; base <= 16; base += 8)
        for (int j = 0; j < 7; j++)
            adj[base + j][base + j + 1] = 1;

    adj[0][10] = 4;
    adj[8][18] = 1.2;
    adj[12][23] = 2.0;

    // mode = 1 → Manhattan heuristic
    PathNode* result = findShortestPath2D(adj, coords, 0, 23, 1);

    checkResult(
        "Test 42: Wide grid with good & bad shortcuts",
        result,
        "0->8->18->19->20->21->22->23",
        7.2);

    deletePathList(result);
}

void test43()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{0, 0}, {2, 0}, {4, 0}, {2, 2}, {4, 2}, {6, 2}, {4, 4}, {6, 4}, {8, 4}};
    adj[0][1] = 2;
    adj[1][2] = 2;
    adj[1][3] = 2;
    adj[3][4] = 2;
    adj[2][4] = 2;
    adj[4][5] = 2;
    adj[4][6] = 2;
    adj[6][7] = 2;
    adj[5][7] = 2;
    adj[7][8] = 2;
    PathNode* result = findShortestPath2D(adj, coords, 0, 8, 1);
    checkResult("Test 43: Multi-level stairs", result, "0->1->2->4->5->7->8", 12.0);
    deletePathList(result);
}

void test44()
{
    double adj[100][100] = {0};
    int coords[100][2];

    // ---------- Manual coords: 9 columns × 2 rows ----------
    // Row 0 (y = 0)
    coords[0][0] = 0;
    coords[0][1] = 0;
    coords[1][0] = 1;
    coords[1][1] = 0;
    coords[2][0] = 2;
    coords[2][1] = 0;
    coords[3][0] = 3;
    coords[3][1] = 0;
    coords[4][0] = 4;
    coords[4][1] = 0;
    coords[5][0] = 5;
    coords[5][1] = 0;
    coords[6][0] = 6;
    coords[6][1] = 0;
    coords[7][0] = 7;
    coords[7][1] = 0;
    coords[8][0] = 8;
    coords[8][1] = 0;

    // Row 1 (y = 1)
    coords[9][0] = 0;
    coords[9][1] = 1;
    coords[10][0] = 1;
    coords[10][1] = 1;
    coords[11][0] = 2;
    coords[11][1] = 1;
    coords[12][0] = 3;
    coords[12][1] = 1;
    coords[13][0] = 4;
    coords[13][1] = 1;
    coords[14][0] = 5;
    coords[14][1] = 1;
    coords[15][0] = 6;
    coords[15][1] = 1;
    coords[16][0] = 7;
    coords[16][1] = 1;
    coords[17][0] = 8;
    coords[17][1] = 1;

    // ---------- Vertical edges (down), cost = 1 ----------
    adj[0][9] = 1;
    adj[1][10] = 1;
    adj[2][11] = 1;
    adj[3][12] = 1;
    adj[4][13] = 1;
    adj[5][14] = 1;
    adj[6][15] = 1;
    adj[7][16] = 1;
    adj[8][17] = 1;

    // ---------- Horizontal edges (right), cost = 1 ----------
    // Row 0
    adj[0][1] = 1;
    adj[1][2] = 1;
    adj[2][3] = 1;
    adj[3][4] = 1;
    adj[4][5] = 1;
    adj[5][6] = 1;
    adj[6][7] = 1;
    adj[7][8] = 1;

    // Row 1
    adj[9][10] = 1;
    adj[10][11] = 1;
    adj[11][12] = 1;
    adj[12][13] = 1;
    adj[13][14] = 1;
    adj[14][15] = 1;
    adj[15][16] = 1;
    adj[16][17] = 1;

    // mode = 0 → Euclidean heuristic
    PathNode* result = findShortestPath2D(adj, coords, 0, 17, 0);

    checkResult(
        "Test 44: 9x2 long grid (manual init)",
        result,
        "0->1->2->3->4->5->6->7->8->17",
        9.0);

    deletePathList(result);
}

void test45()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{0, 0}, {5, 0}, {10, 0}, {15, 0}, {5, 5}, {10, 5}, {15, 5}, {10, 10}};
    adj[0][1] = 5;
    adj[1][2] = 5;
    adj[2][3] = 5;
    adj[1][4] = 5;
    adj[4][5] = 5;
    adj[5][2] = 5;
    adj[2][6] = 5;
    adj[6][3] = 5;
    adj[5][7] = 5;
    PathNode* result = findShortestPath2D(adj, coords, 0, 7, 0);
    checkResult("Test 45: Complex mesh", result, "0->1->4->5->7", 20.0);
    deletePathList(result);
}

void test46()
{
    double adj[100][100] = {0};
    int coords[100][2];
    for (int i = 0; i < 21; i++)
    {
        coords[i][0] = i % 7;
        coords[i][1] = i / 7;
    }
    for (int i = 0; i < 14; i++) adj[i][i + 7] = 1;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 6; j++) adj[i * 7 + j][i * 7 + j + 1] = 1;
    PathNode* result = findShortestPath2D(adj, coords, 0, 20, 1);
    checkResult("Test 46: 7x3 grid", result, "0->1->2->3->4->5->6->13->20", 8.0);
    deletePathList(result);
}

void test47()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{0, 0}, {3, 4}, {6, 8}, {9, 12}, {12, 16}, {15, 20}};
    for (int i = 0; i < 5; i++) adj[i][i + 1] = 5;
    adj[0][2] = 10;
    adj[2][4] = 10;
    adj[0][4] = 20;
    PathNode* result = findShortestPath2D(adj, coords, 0, 5, 0);
    checkResult("Test 47: Steep climb shortcuts", result, "0->4->5", 25.0);
    deletePathList(result);
}

void test48()
{
    double adj[100][100] = {0};
    int coords[100][2];
    for (int i = 0; i < 40; i++)
    {
        coords[i][0] = i % 8;
        coords[i][1] = i / 8;
    }
    for (int i = 0; i < 32; i++) adj[i][i + 8] = 1;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 7; j++) adj[i * 8 + j][i * 8 + j + 1] = 1;
    PathNode* result = findShortestPath2D(adj, coords, 0, 39, 0);
    checkResult("Test 48: 8x5 large grid", result, "0->1->2->3->4->12->13->21->22->30->31->39", 11.0);
    deletePathList(result);
}

void test49()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{0, 0}, {1, 0}, {2, 0}, {1, 1}, {2, 1}, {3, 1}, {2, 2}, {3, 2}, {4, 2}};
    adj[0][1] = 1;
    adj[1][2] = 1;
    adj[1][3] = 1;
    adj[3][4] = 1;
    adj[2][4] = 1;
    adj[4][5] = 1;
    adj[4][6] = 1;
    adj[6][7] = 1;
    adj[5][7] = 1;
    adj[7][8] = 1;
    PathNode* result = findShortestPath2D(adj, coords, 0, 8, 0);
    checkResult("Test 49: Diagonal staircase", result, "0->1->2->4->5->7->8", 6.0);
    deletePathList(result);
}

void test50()
{
    double adj[100][100] = {0};
    int coords[100][2];
    for (int i = 0; i < 50; i++)
    {
        coords[i][0] = i % 10;
        coords[i][1] = i / 10;
    }
    for (int i = 0; i < 40; i++) adj[i][i + 10] = 1;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 9; j++) adj[i * 10 + j][i * 10 + j + 1] = 1;
    PathNode* result = findShortestPath2D(adj, coords, 0, 49, 0);
    checkResult("Test 50: 10x5 massive grid", result, "0->1->2->3->4->5->6->16->17->27->28->38->39->49", 13.0);
    deletePathList(result);
}

int main()
{
    cout << "========================================" << endl;
    cout << "   TASK 2: 2D Heuristic Test Suite" << endl;
    cout << "========================================\n"
         << endl;

    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();
    test11();
    test12();
    test13();
    test14();
    test15();
    test16();
    test17();
    test18();
    test19();
    test20();
    test21();
    test22();
    test23();
    test24();
    test25();
    test26();
    test27();
    test28();
    test29();
    test30();
    test31();
    test32();
    test33();
    test34();
    test35();
    test36();
    test37();
    test38();
    test39();
    test40();
    test41();
    test42();
    test43();
    test44();
    test45();
    test46();
    test47();
    test48();
    test49();
    test50();

    cout << "========================================" << endl;
    cout << "   TEST SUMMARY" << endl;
    cout << "========================================" << endl;
    cout << "Total tests: " << totalTests << endl;
    cout << GREEN << "Passed: " << passedTests << RESET << endl;
    cout << RED << "Failed: " << (totalTests - passedTests) << RESET << endl;

    if (!failedTests.empty())
    {
        cout << "\n"
             << YELLOW << "Failed tests:" << RESET << endl;
        for (size_t i = 0; i < failedTests.size(); i++)
        {
            cout << "  " << (i + 1) << ". " << failedTests[i] << endl;
        }
    }
    else
    {
        cout << "\n"
             << GREEN << "🎉 All tests passed!" << RESET << endl;
    }

    cout << "========================================" << endl;

    return 0;
}
