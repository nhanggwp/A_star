#include <cmath>
#include <cstring>
#include <iostream>
#include <sstream>

#include "Algo.h"
using namespace std;

// ANSI color codes
#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

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
    bool costMatch = (expectedCost < 0) ? (actualCost < 0) : (fabs(actualCost - expectedCost) < 0.001);
    bool pass = pathMatch && costMatch;

    cout << testName << endl;
    cout << "Expected: " << expectedPath << " (cost: " << expectedCost << ")" << endl;
    cout << "Actual:   " << actualPath << " (cost: " << actualCost << ")" << endl;
    cout << (pass ? GREEN "✓ PASS" RESET : RED "✗ FAIL" RESET) << "\n"
         << endl;
}

// Test Case 1: Simple 3-node linear path
void test1()
{
    double adj[100][100] = {0};
    adj[0][1] = 1.0;
    adj[1][2] = 2.0;
    PathNode* result = findShortestPathMatrix(adj, 3, 0, 2);
    checkResult("Test 1: Simple 3-node linear path", result, "0->1->2", 3.0);
    deletePathList(result);
}

// Test Case 2: Start = Goal
void test2()
{
    double adj[100][100] = {0};
    adj[0][1] = 1.0;
    PathNode* result = findShortestPathMatrix(adj, 3, 1, 1);
    checkResult("Test 2: Start equals goal", result, "1", 0.0);
    deletePathList(result);
}

// Test Case 3: No path exists
void test3()
{
    double adj[100][100] = {0};
    adj[0][1] = 1.0;
    adj[2][3] = 1.0;
    PathNode* result = findShortestPathMatrix(adj, 4, 0, 3);
    checkResult("Test 3: No path exists", result, "null", -1.0);
    deletePathList(result);
}

// Test Case 4: Multiple paths, choose shortest
void test4()
{
    double adj[100][100] = {0};
    adj[0][1] = 1.0;
    adj[1][3] = 2.0;  // Path 1: cost 3
    adj[0][2] = 1.5;
    adj[2][3] = 1.0;  // Path 2: cost 2.5 (shorter)
    PathNode* result = findShortestPathMatrix(adj, 4, 0, 3);
    checkResult("Test 4: Multiple paths (choose shortest)", result, "0->2->3", 2.5);
    deletePathList(result);
}

// Test Case 5: Single node
void test5()
{
    double adj[100][100] = {0};
    PathNode* result = findShortestPathMatrix(adj, 1, 0, 0);
    checkResult("Test 5: Single node graph", result, "0", 0.0);
    deletePathList(result);
}

// Test Case 6: Complete graph 4 nodes
void test6()
{
    double adj[100][100] = {0};
    adj[0][1] = 5.0;
    adj[0][2] = 3.0;
    adj[0][3] = 10.0;
    adj[1][2] = 2.0;
    adj[1][3] = 1.0;
    adj[2][3] = 4.0;
    PathNode* result = findShortestPathMatrix(adj, 4, 0, 3);
    checkResult("Test 6: Complete graph (0->1->3)", result, "0->1->3", 6.0);
    deletePathList(result);
}

// Test Case 7: Long chain 6 nodes
void test7()
{
    double adj[100][100] = {0};
    for (int i = 0; i < 5; i++)
    {
        adj[i][i + 1] = 1.0;
    }
    PathNode* result = findShortestPathMatrix(adj, 6, 0, 5);
    checkResult("Test 7: Long chain 0->1->2->3->4->5", result, "0->1->2->3->4->5", 5.0);
    deletePathList(result);
}

// Test Case 8: Diamond shape
void test8()
{
    double adj[100][100] = {0};
    adj[0][1] = 1.0;
    adj[0][2] = 1.0;
    adj[1][3] = 1.0;
    adj[2][3] = 1.0;
    PathNode* result = findShortestPathMatrix(adj, 4, 0, 3);
    checkResult("Test 8: Diamond (equal paths)", result, "0->1->3", 2.0);
    deletePathList(result);
}

// Test Case 9: Weighted diamond (asymmetric)
void test9()
{
    double adj[100][100] = {0};
    adj[0][1] = 1.0;
    adj[0][2] = 4.0;
    adj[1][3] = 5.0;
    adj[2][3] = 1.0;
    PathNode* result = findShortestPathMatrix(adj, 4, 0, 3);
    checkResult("Test 9: Weighted diamond (0->2->3)", result, "0->2->3", 5.0);
    deletePathList(result);
}

// Test Case 10: Cycle graph
void test10()
{
    double adj[100][100] = {0};
    adj[0][1] = 1.0;
    adj[1][2] = 1.0;
    adj[2][3] = 1.0;
    adj[3][0] = 1.0;
    PathNode* result = findShortestPathMatrix(adj, 4, 0, 2);
    checkResult("Test 10: Cycle 0->1->2", result, "0->1->2", 2.0);
    deletePathList(result);
}

// Test Case 11: Large sparse graph (10 nodes)
void test11()
{
    double adj[100][100] = {0};
    adj[0][1] = 1.0;
    adj[1][3] = 2.0;
    adj[3][5] = 1.0;
    adj[5][7] = 3.0;
    adj[7][9] = 1.0;
    PathNode* result = findShortestPathMatrix(adj, 10, 0, 9);
    checkResult("Test 11: Sparse graph (10 nodes)", result, "0->1->3->5->7->9", 8.0);
    deletePathList(result);
}

// Test Case 12: Two equal-cost paths
void test12()
{
    double adj[100][100] = {0};
    adj[0][1] = 2.0;
    adj[1][3] = 2.0;
    adj[0][2] = 2.0;
    adj[2][3] = 2.0;
    PathNode* result = findShortestPathMatrix(adj, 4, 0, 3);
    checkResult("Test 12: Two equal-cost paths", result, "0->1->3", 4.0);
    deletePathList(result);
}

// Test Case 13: All edges same weight
void test13()
{
    double adj[100][100] = {0};
    adj[0][1] = 1.0;
    adj[0][2] = 1.0;
    adj[1][3] = 1.0;
    adj[2][3] = 1.0;
    adj[3][4] = 1.0;
    PathNode* result = findShortestPathMatrix(adj, 5, 0, 4);
    checkResult("Test 13: All edges weight 1.0", result, "0->1->3->4", 3.0);
    deletePathList(result);
}

// Test Case 14: Very large weights
void test14()
{
    double adj[100][100] = {0};
    adj[0][1] = 1000.0;
    adj[1][2] = 2000.0;
    PathNode* result = findShortestPathMatrix(adj, 3, 0, 2);
    checkResult("Test 14: Very large weights", result, "0->1->2", 3000.0);
    deletePathList(result);
}

// Test Case 15: Very small weights
void test15()
{
    double adj[100][100] = {0};
    adj[0][1] = 0.001;
    adj[1][2] = 0.002;
    PathNode* result = findShortestPathMatrix(adj, 3, 0, 2);
    checkResult("Test 15: Very small weights", result, "0->1->2", 0.003);
    deletePathList(result);
}

// Test Case 16: Star topology (hub at center)
void test16()
{
    double adj[100][100] = {0};
    adj[0][1] = 1.0;
    adj[1][2] = 1.0;
    adj[1][3] = 1.0;
    adj[1][4] = 1.0;
    PathNode* result = findShortestPathMatrix(adj, 5, 0, 4);
    checkResult("Test 16: Star topology", result, "0->1->4", 2.0);
    deletePathList(result);
}

// Test Case 17: Directed graph test
void test17()
{
    double adj[100][100] = {0};
    adj[0][1] = 1.0;
    adj[1][2] = 1.0;
    adj[2][0] = 1.0;  // backward edge
    PathNode* result = findShortestPathMatrix(adj, 3, 0, 2);
    checkResult("Test 17: Directed graph", result, "0->1->2", 2.0);
    deletePathList(result);
}

// Test Case 18: Complex 6-node graph
void test18()
{
    double adj[100][100] = {0};
    adj[0][1] = 2.0;
    adj[0][2] = 4.0;
    adj[1][2] = 1.0;
    adj[1][3] = 7.0;
    adj[2][4] = 3.0;
    adj[3][5] = 1.0;
    adj[4][3] = 2.0;
    adj[4][5] = 5.0;
    PathNode* result = findShortestPathMatrix(adj, 6, 0, 5);
    checkResult("Test 18: Complex 6-node graph", result, "0->1->2->4->3->5", 10.0);
    deletePathList(result);
}

// Test Case 19: Graph with self-loop (should ignore)
void test19()
{
    double adj[100][100] = {0};
    adj[0][0] = 100.0;  // self-loop
    adj[0][1] = 1.0;
    adj[1][2] = 1.0;
    PathNode* result = findShortestPathMatrix(adj, 3, 0, 2);
    checkResult("Test 19: Self-loop (ignore)", result, "0->1->2", 2.0);
    deletePathList(result);
}

// Test Case 20: Larger graph (20 nodes)
void test20()
{
    double adj[100][100] = {0};
    for (int i = 0; i < 19; i++)
    {
        adj[i][i + 1] = 1.0 + (i % 3) * 0.5;
    }
    adj[0][5] = 3.0;
    adj[5][10] = 3.0;
    adj[10][19] = 5.0;
    PathNode* result = findShortestPathMatrix(adj, 20, 0, 19);
    checkResult("Test 20: Large graph with shortcuts", result, "0->5->10->19", 11.0);
    deletePathList(result);
}

// Test Case 21: Triangular graph
void test21()
{
    double adj[100][100] = {0};
    adj[0][1] = 3.0;
    adj[1][2] = 4.0;
    adj[0][2] = 6.0;
    PathNode* result = findShortestPathMatrix(adj, 3, 0, 2);
    checkResult("Test 21: Triangle (direct vs indirect)", result, "0->2", 6.0);
    deletePathList(result);
}

// Test Case 22: All disconnected nodes
void test22()
{
    double adj[100][100] = {0};
    PathNode* result = findShortestPathMatrix(adj, 5, 0, 4);
    checkResult("Test 22: All disconnected", result, "null", -1.0);
    deletePathList(result);
}

// Test Case 23: Bidirectional edges (undirected)
void test23()
{
    double adj[100][100] = {0};
    adj[0][1] = 2.0;
    adj[1][0] = 2.0;
    adj[1][2] = 3.0;
    adj[2][1] = 3.0;
    PathNode* result = findShortestPathMatrix(adj, 3, 0, 2);
    checkResult("Test 23: Undirected graph", result, "0->1->2", 5.0);
    deletePathList(result);
}

// Test Case 24: High branching factor
void test24()
{
    double adj[100][100] = {0};
    adj[0][1] = 1.0;
    adj[0][2] = 2.0;
    adj[0][3] = 3.0;
    adj[0][4] = 4.0;
    adj[1][5] = 1.0;
    adj[2][5] = 1.0;
    adj[3][5] = 1.0;
    adj[4][5] = 1.0;
    PathNode* result = findShortestPathMatrix(adj, 6, 0, 5);
    checkResult("Test 24: High branching factor", result, "0->1->5", 2.0);
    deletePathList(result);
}

// Test Case 25: Long path with shortcut
void test25()
{
    double adj[100][100] = {0};
    for (int i = 0; i < 9; i++) adj[i][i + 1] = 1.0;
    adj[0][9] = 8.0;  // shortcut
    PathNode* result = findShortestPathMatrix(adj, 10, 0, 9);
    checkResult("Test 25: Long path vs shortcut", result, "0->9", 8.0);
    deletePathList(result);
}

// Test Case 26: Multiple disconnected components
void test26()
{
    double adj[100][100] = {0};
    adj[0][1] = 1.0;
    adj[1][2] = 1.0;
    adj[3][4] = 1.0;
    adj[4][5] = 1.0;
    PathNode* result = findShortestPathMatrix(adj, 6, 0, 5);
    checkResult("Test 26: Disconnected components", result, "null", -1.0);
    deletePathList(result);
}

// Test Case 27: Fractional weights
void test27()
{
    double adj[100][100] = {0};
    adj[0][1] = 1.5;
    adj[1][2] = 2.3;
    adj[2][3] = 0.7;
    PathNode* result = findShortestPathMatrix(adj, 4, 0, 3);
    checkResult("Test 27: Fractional weights", result, "0->1->2->3", 4.5);
    deletePathList(result);
}

// Test Case 28: Graph with many equal paths
void test28()
{
    double adj[100][100] = {0};
    adj[0][1] = 1.0;
    adj[0][2] = 1.0;
    adj[0][3] = 1.0;
    adj[1][4] = 1.0;
    adj[2][4] = 1.0;
    adj[3][4] = 1.0;
    PathNode* result = findShortestPathMatrix(adj, 5, 0, 4);
    checkResult("Test 28: Many equal paths", result, "0->1->4", 2.0);
    deletePathList(result);
}

// Test Case 29: Backwards only path
void test29()
{
    double adj[100][100] = {0};
    adj[2][1] = 1.0;
    adj[1][0] = 1.0;
    PathNode* result = findShortestPathMatrix(adj, 3, 0, 2);
    checkResult("Test 29: No forward path", result, "null", -1.0);
    deletePathList(result);
}

// Test Case 30: Dense graph
void test30()
{
    double adj[100][100] = {0};
    for (int i = 0; i < 5; i++)
    {
        for (int j = i + 1; j < 5; j++)
        {
            adj[i][j] = (i + 1) * (j + 1) * 0.5;
        }
    }
    PathNode* result = findShortestPathMatrix(adj, 5, 0, 4);
    checkResult("Test 30: Dense graph", result, "0->4", 2.5);
    deletePathList(result);
}

// Test Case 31: Long path through 10 nodes
void test31()
{
    double adj[100][100] = {0};
    adj[0][1] = 1.0;
    adj[1][2] = 1.5;
    adj[2][3] = 2.0;
    adj[3][4] = 1.0;
    adj[4][5] = 2.5;
    adj[5][6] = 1.0;
    adj[6][7] = 1.5;
    adj[7][8] = 2.0;
    adj[8][9] = 1.0;
    PathNode* result = findShortestPathMatrix(adj, 10, 0, 9);
    checkResult("Test 31: Long path 10 nodes", result, "0->1->2->3->4->5->6->7->8->9", 13.5);
    deletePathList(result);
}

// Test Case 32: Multiple shortcuts (complex)
void test32()
{
    double adj[100][100] = {0};
    // Long path
    for (int i = 0; i < 11; i++) adj[i][i + 1] = 1.0;
    // Shortcuts
    adj[0][3] = 2.5;
    adj[3][6] = 2.5;
    adj[6][9] = 2.5;
    adj[9][11] = 1.5;
    PathNode* result = findShortestPathMatrix(adj, 12, 0, 11);
    checkResult("Test 32: Multiple shortcuts", result, "0->3->6->9->11", 9.0);
    deletePathList(result);
}

// Test Case 33: Grid-like structure
void test33()
{
    double adj[100][100] = {0};
    adj[0][1] = 1.0;
    adj[0][2] = 3.0;
    adj[1][3] = 2.0;
    adj[1][4] = 1.0;
    adj[2][4] = 1.0;
    adj[2][5] = 2.0;
    adj[3][6] = 1.0;
    adj[4][6] = 1.0;
    adj[4][7] = 2.0;
    adj[5][7] = 1.0;
    adj[6][8] = 1.0;
    adj[7][8] = 1.0;
    PathNode* result = findShortestPathMatrix(adj, 9, 0, 8);
    checkResult("Test 33: Grid-like structure", result, "0->1->4->6->8", 4.0);
    deletePathList(result);
}

// Test Case 34: Heavy middle, light edges
void test34()
{
    double adj[100][100] = {0};
    adj[0][1] = 0.1;
    adj[1][2] = 0.1;
    adj[2][3] = 0.1;
    adj[3][4] = 0.1;
    adj[4][5] = 10.0;  // expensive middle
    adj[5][6] = 0.1;
    adj[6][7] = 0.1;
    adj[7][8] = 0.1;
    // Alternative path
    adj[0][9] = 1.0;
    adj[9][10] = 1.0;
    adj[10][8] = 1.0;
    PathNode* result = findShortestPathMatrix(adj, 11, 0, 8);
    checkResult("Test 34: Heavy middle bottleneck", result, "0->9->10->8", 3.0);
    deletePathList(result);
}

// Test Case 35: Zig-zag pattern
void test35()
{
    double adj[100][100] = {0};
    adj[0][1] = 1.0;
    adj[1][2] = 1.0;
    adj[2][1] = 1.0;
    adj[1][3] = 1.0;
    adj[3][4] = 1.0;
    adj[4][3] = 1.0;
    adj[3][5] = 1.0;
    adj[5][6] = 1.0;
    adj[6][5] = 1.0;
    adj[5][7] = 1.0;
    adj[7][8] = 1.0;
    PathNode* result = findShortestPathMatrix(adj, 9, 0, 8);
    checkResult("Test 35: Zig-zag pattern", result, "0->1->3->5->7->8", 5.0);
    deletePathList(result);
}

// Test Case 36: Wide then narrow
void test36()
{
    double adj[100][100] = {0};
    adj[0][1] = 1.0;
    adj[0][2] = 1.0;
    adj[0][3] = 1.0;
    adj[0][4] = 1.0;
    adj[1][5] = 2.0;
    adj[2][5] = 3.0;
    adj[3][5] = 4.0;
    adj[4][5] = 5.0;
    adj[5][6] = 1.0;
    adj[6][7] = 1.0;
    adj[7][8] = 1.0;
    adj[8][9] = 1.0;
    PathNode* result = findShortestPathMatrix(adj, 10, 0, 9);
    checkResult("Test 36: Wide then narrow funnel", result, "0->1->5->6->7->8->9", 7.0);
    deletePathList(result);
}

// Test Case 37: Binary tree structure
void test37()
{
    double adj[100][100] = {0};
    adj[0][1] = 1.0;
    adj[0][2] = 1.0;
    adj[1][3] = 2.0;
    adj[1][4] = 3.0;
    adj[2][5] = 1.0;
    adj[2][6] = 2.0;
    adj[3][7] = 1.0;
    adj[4][7] = 1.0;
    adj[5][7] = 3.0;
    adj[6][7] = 1.0;
    PathNode* result = findShortestPathMatrix(adj, 8, 0, 7);
    checkResult("Test 37: Binary tree paths", result, "0->1->3->7", 4.0);
    deletePathList(result);
}

// Test Case 38: Increasing costs
void test38()
{
    double adj[100][100] = {0};
    for (int i = 0; i < 11; i++)
    {
        adj[i][i + 1] = i + 1.0;
    }
    PathNode* result = findShortestPathMatrix(adj, 12, 0, 11);
    checkResult("Test 38: Increasing edge costs", result, "0->1->2->3->4->5->6->7->8->9->10->11", 66.0);
    deletePathList(result);
}

// Test Case 39: Hub and spoke with 10 nodes
void test39()
{
    double adj[100][100] = {0};
    adj[0][1] = 1.0;
    adj[1][2] = 2.0;  // to hub
    // Hub connections
    adj[2][3] = 1.0;
    adj[2][4] = 1.0;
    adj[2][5] = 1.0;
    adj[2][6] = 1.0;
    adj[2][7] = 1.0;
    adj[2][8] = 1.0;
    adj[8][9] = 1.0;
    adj[9][10] = 1.0;
    PathNode* result = findShortestPathMatrix(adj, 11, 0, 10);
    checkResult("Test 39: Hub-spoke 10+ nodes", result, "0->1->2->8->9->10", 6.0);
    deletePathList(result);
}

// Test Case 40: Layered graph (4 layers)
void test40()
{
    double adj[100][100] = {0};
    // Layer 0->1
    adj[0][1] = 1.0;
    adj[0][2] = 2.0;
    // Layer 1->2
    adj[1][3] = 1.0;
    adj[1][4] = 3.0;
    adj[2][4] = 1.0;
    adj[2][5] = 2.0;
    // Layer 2->3
    adj[3][6] = 2.0;
    adj[4][6] = 1.0;
    adj[4][7] = 2.0;
    adj[5][7] = 1.0;
    // Layer 3->4
    adj[6][8] = 1.0;
    adj[7][8] = 2.0;
    PathNode* result = findShortestPathMatrix(adj, 9, 0, 8);
    checkResult("Test 40: Layered graph 4 layers", result, "0->1->3->6->8", 5.0);
    deletePathList(result);
}

// Test Case 41: Spiral path (15 nodes)
void test41()
{
    double adj[100][100] = {0};
    adj[0][1] = 1.0;
    adj[1][2] = 1.0;
    adj[2][3] = 1.0;
    adj[3][4] = 1.0;
    adj[4][5] = 2.0;
    adj[5][6] = 1.0;
    adj[6][7] = 1.0;
    adj[7][8] = 1.0;
    adj[8][9] = 2.0;
    adj[9][10] = 1.0;
    adj[10][11] = 1.0;
    adj[11][12] = 1.0;
    adj[12][13] = 2.0;
    adj[13][14] = 1.0;
    // Shortcut
    adj[0][7] = 6.0;
    adj[7][14] = 6.0;
    PathNode* result = findShortestPathMatrix(adj, 15, 0, 14);
    checkResult("Test 41: Spiral path 15 nodes", result, "0->7->14", 12.0);
    deletePathList(result);
}

// Test Case 42: Diamond cascade (8 levels)
void test42()
{
    double adj[100][100] = {0};
    adj[0][1] = 1.0;
    adj[0][2] = 2.0;
    adj[1][3] = 1.0;
    adj[2][3] = 0.5;
    adj[3][4] = 1.0;
    adj[3][5] = 2.0;
    adj[4][6] = 1.0;
    adj[5][6] = 0.5;
    adj[6][7] = 1.0;
    adj[6][8] = 2.0;
    adj[7][9] = 1.0;
    adj[8][9] = 0.5;
    adj[9][10] = 1.0;
    adj[9][11] = 2.0;
    adj[10][12] = 1.0;
    adj[11][12] = 0.5;
    PathNode* result = findShortestPathMatrix(adj, 13, 0, 12);
    checkResult("Test 42: Diamond cascade", result, "0->1->3->4->6->7->9->10->12", 7.0);
    deletePathList(result);
}

// Test Case 43: Cross connections (complex)
void test43()
{
    double adj[100][100] = {0};
    // Main path
    adj[0][1] = 1.0;
    adj[1][2] = 1.0;
    adj[2][3] = 1.0;
    adj[3][4] = 1.0;
    adj[4][5] = 1.0;
    adj[5][6] = 1.0;
    adj[6][7] = 1.0;
    adj[7][8] = 1.0;
    // Cross connections (shortcuts)
    adj[0][3] = 2.5;
    adj[1][4] = 2.5;
    adj[2][5] = 2.5;
    adj[3][6] = 2.5;
    adj[4][7] = 2.5;
    adj[5][8] = 2.5;
    PathNode* result = findShortestPathMatrix(adj, 9, 0, 8);
    checkResult("Test 43: Cross connections", result, "0->3->6->7->8", 5.5);
    deletePathList(result);
}

// Test Case 44: Very dense small graph
void test44()
{
    double adj[100][100] = {0};
    for (int i = 0; i < 7; i++)
    {
        for (int j = i + 1; j < 7; j++)
        {
            adj[i][j] = (i + j) * 0.3 + 1.0;
        }
    }
    PathNode* result = findShortestPathMatrix(adj, 7, 0, 6);
    checkResult("Test 44: Very dense 7-node graph", result, "0->6", 2.8);
    deletePathList(result);
}

// Test Case 45: Alternating high-low costs
void test45()
{
    double adj[100][100] = {0};
    for (int i = 0; i < 13; i++)
    {
        adj[i][i + 1] = (i % 2 == 0) ? 0.5 : 3.0;
    }
    // Shortcut
    adj[0][6] = 4.0;
    adj[6][13] = 4.0;
    PathNode* result = findShortestPathMatrix(adj, 14, 0, 13);
    checkResult("Test 45: Alternating costs with shortcuts", result, "0->6->13", 8.0);
    deletePathList(result);
}

// Test Case 46: Bottleneck network
void test46()
{
    double adj[100][100] = {0};
    adj[0][1] = 0.5;
    adj[0][2] = 0.5;
    adj[0][3] = 0.5;
    adj[1][4] = 0.5;
    adj[2][4] = 0.5;
    adj[3][4] = 0.5;
    adj[4][5] = 10.0;  // bottleneck
    adj[5][6] = 0.5;
    adj[5][7] = 0.5;
    adj[5][8] = 0.5;
    adj[6][9] = 0.5;
    adj[7][9] = 0.5;
    adj[8][9] = 0.5;
    // Alternative
    adj[0][10] = 2.0;
    adj[10][11] = 2.0;
    adj[11][12] = 2.0;
    adj[12][9] = 2.0;
    PathNode* result = findShortestPathMatrix(adj, 13, 0, 9);
    checkResult("Test 46: Bottleneck bypass", result, "0->10->11->12->9", 8.0);
    deletePathList(result);
}

// Test Case 47: Parallel paths (12 nodes)
void test47()
{
    double adj[100][100] = {0};
    // Path 1
    adj[0][1] = 1.0;
    adj[1][2] = 1.0;
    adj[2][3] = 1.0;
    adj[3][11] = 1.0;
    // Path 2
    adj[0][4] = 1.5;
    adj[4][5] = 1.0;
    adj[5][6] = 1.0;
    adj[6][11] = 1.0;
    // Path 3
    adj[0][7] = 2.0;
    adj[7][8] = 0.5;
    adj[8][9] = 0.5;
    adj[9][10] = 0.5;
    adj[10][11] = 0.5;
    PathNode* result = findShortestPathMatrix(adj, 12, 0, 11);
    checkResult("Test 47: Three parallel paths", result, "0->7->8->9->10->11", 4.0);
    deletePathList(result);
}

// Test Case 48: Mesh network (15 nodes)
void test48()
{
    double adj[100][100] = {0};
    // Row 1
    adj[0][1] = 1.0;
    adj[1][2] = 1.0;
    adj[2][3] = 1.0;
    adj[3][4] = 1.0;
    // Row 2
    adj[5][6] = 1.0;
    adj[6][7] = 1.0;
    adj[7][8] = 1.0;
    adj[8][9] = 1.0;
    // Row 3
    adj[10][11] = 1.0;
    adj[11][12] = 1.0;
    adj[12][13] = 1.0;
    adj[13][14] = 1.0;
    // Vertical connections
    adj[0][5] = 1.5;
    adj[1][6] = 1.5;
    adj[2][7] = 1.5;
    adj[3][8] = 1.5;
    adj[4][9] = 1.5;
    adj[5][10] = 1.5;
    adj[6][11] = 1.5;
    adj[7][12] = 1.5;
    adj[8][13] = 1.5;
    adj[9][14] = 1.5;
    PathNode* result = findShortestPathMatrix(adj, 15, 0, 14);
    checkResult("Test 48: Mesh network 15 nodes", result, "0->1->2->3->4->9->14", 7.5);
    deletePathList(result);
}

// Test Case 49: Exponential weights
void test49()
{
    double adj[100][100] = {0};
    adj[0][1] = 1.0;
    adj[1][2] = 2.0;
    adj[2][3] = 4.0;
    adj[3][4] = 8.0;
    adj[4][5] = 16.0;
    adj[5][6] = 32.0;
    // Cheaper alternative
    for (int i = 0; i < 6; i++)
    {
        adj[i][i + 7] = 3.0;
    }
    adj[7][8] = 1.0;
    adj[8][9] = 1.0;
    adj[9][10] = 1.0;
    adj[10][11] = 1.0;
    adj[11][12] = 1.0;
    adj[12][6] = 1.0;
    PathNode* result = findShortestPathMatrix(adj, 13, 0, 6);
    checkResult("Test 49: Exponential vs linear", result, "0->7->8->9->10->11->12->6", 9.0);
    deletePathList(result);
}

// Test Case 50: Random-like complex (20 nodes)
void test50()
{
    double adj[100][100] = {0};
    adj[0][1] = 2.3;
    adj[0][2] = 1.7;
    adj[1][3] = 3.1;
    adj[1][4] = 2.5;
    adj[2][4] = 1.9;
    adj[2][5] = 2.8;
    adj[3][6] = 1.2;
    adj[4][6] = 2.4;
    adj[4][7] = 1.8;
    adj[5][7] = 3.2;
    adj[5][8] = 1.5;
    adj[6][9] = 2.1;
    adj[7][9] = 1.7;
    adj[7][10] = 2.9;
    adj[8][10] = 1.3;
    adj[8][11] = 3.5;
    adj[9][12] = 1.6;
    adj[10][12] = 2.2;
    adj[10][13] = 1.4;
    adj[11][13] = 2.7;
    adj[12][14] = 1.9;
    adj[13][14] = 1.1;
    adj[13][15] = 2.6;
    adj[14][16] = 1.8;
    adj[15][16] = 2.3;
    adj[15][17] = 1.5;
    adj[16][18] = 2.0;
    adj[17][18] = 1.7;
    adj[18][19] = 1.2;
    PathNode* result = findShortestPathMatrix(adj, 20, 0, 19);
    checkResult("Test 50: Complex 20-node graph", result, "0->2->5->8->10->13->14->16->18->19", 14.6);
    deletePathList(result);
}

int main()
{
    cout << "========================================" << endl;
    cout << "   TASK 1: A* Algorithm Test Suite" << endl;
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
    cout << "   All 50 tests completed!" << endl;
    cout << "========================================" << endl;

    return 0;
}
