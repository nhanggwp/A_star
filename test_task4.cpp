#include <cmath>
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>

#include "Algo.h"
using namespace std;

#define GREEN "\033[32m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

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
    bool costMatch = (expectedCost < 0) ? (actualCost < 0) : (fabs(actualCost - expectedCost) < 0.2);
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

// Test 1: Simple 3x3 maze
void test1()
{
    int maze[100][100] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 3, 3, 0, 0, 2, 2, weightMatrix);
    checkResult("Test 1: 3x3 empty maze", result, "(0, 0)->(1, 1)->(2, 2)", 3.0);
    deletePathList(result);
}

// Test 2: 3x3 with center wall
void test2()
{
    int maze[100][100] = {
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 0}};
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 3, 3, 0, 0, 2, 2, weightMatrix);
    checkResult("Test 2: 3x3 center wall", result, "(0, 0)->(0, 1)->(1, 2)->(2, 2)", 3.5);
    deletePathList(result);
}

// Test 3: No path (blocked)
void test3()
{
    int maze[100][100] = {
        {0, 0, 0},
        {1, 1, 1},
        {0, 0, 0}};
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 3, 3, 0, 0, 2, 2, weightMatrix);
    checkResult("Test 3: Blocked path", result, "null", -1.0);
    deletePathList(result);
}

// Test 4: Start = Goal
void test4()
{
    int maze[100][100] = {{0, 0}, {0, 0}};
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 2, 2, 1, 1, 1, 1, weightMatrix);
    checkResult("Test 4: Start equals goal", result, "(1, 1)", 0.0);
    deletePathList(result);
}

// Test 5: 5x5 diagonal path
void test5()
{
    int maze[100][100] = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}};
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 5, 5, 0, 0, 4, 4, weightMatrix);
    checkResult("Test 5: 5x5 diagonal", result, "(0, 0)->(1, 1)->(2, 2)->(3, 3)->(4, 4)", 6.0);
    deletePathList(result);
}

// Test 6: Maze with corridor
void test6()
{
    int maze[100][100] = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 0, 0, 0}};
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 5, 5, 0, 0, 4, 4, weightMatrix);
    checkResult("Test 6: Corridor maze", result, "(0, 0)->(1, 0)->(2, 1)->(3, 2)->(4, 3)->(4, 4)", 6.5);
    deletePathList(result);
}

// Test 7: Long straight path (1x10)
void test7()
{
    int maze[100][100] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 1, 10, 0, 0, 0, 9, weightMatrix);
    checkResult("Test 7: 1x10 straight", result, "(0, 0)->(0, 1)->(0, 2)->(0, 3)->(0, 4)->(0, 5)->(0, 6)->(0, 7)->(0, 8)->(0, 9)", 9.0);
    deletePathList(result);
}

// Test 8: Vertical path (10x1)
void test8()
{
    int maze[100][100];
    for (int i = 0; i < 10; i++) maze[i][0] = 0;
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 10, 1, 0, 0, 9, 0, weightMatrix);
    checkResult("Test 8: 10x1 vertical", result, "(0, 0)->(1, 0)->(2, 0)->(3, 0)->(4, 0)->(5, 0)->(6, 0)->(7, 0)->(8, 0)->(9, 0)", 9.0);
    deletePathList(result);
}

// Test 9: Spiral pattern
void test9()
{
    int maze[100][100] = {
        {0, 0, 0, 0, 0},
        {1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1},
        {0, 0, 0, 0, 0}};
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 5, 5, 0, 0, 2, 2, weightMatrix);
    checkResult("Test 9: Spiral pattern", result, "(0, 0)->(0, 1)->(0, 2)->(0, 3)->(1, 4)->(2, 3)->(2, 2)", 7.0);
    deletePathList(result);
}

// Test 10: L-shape
void test10()
{
    int maze[100][100] = {
        {0, 0, 0},
        {1, 1, 0},
        {0, 0, 0}};
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 3, 3, 0, 0, 2, 0, weightMatrix);
    checkResult("Test 10: L-shape", result, "(0, 0)->(0, 1)->(1, 2)->(2, 1)->(2, 0)", 5.0);
    deletePathList(result);
}

// Test 11: 4x4 with obstacles
void test11()
{
    int maze[100][100] = {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}};
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 4, 4, 0, 0, 3, 3, weightMatrix);
    checkResult("Test 11: 4x4 with block", result, "(0, 0)->(0, 1)->(0, 2)->(1, 3)->(2, 3)->(3, 3)", 5.5);
    deletePathList(result);
}

// Test 12: Zigzag 5x5
void test12()
{
    int maze[100][100] = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0}};
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 5, 5, 0, 0, 4, 4, weightMatrix);
    checkResult("Test 12: Zigzag walls", result, "(0, 0)->(1, 0)->(2, 1)->(3, 2)->(4, 3)->(4, 4)", 6.5);
    deletePathList(result);
}

// Test 13: 7x7 empty
void test13()
{
    int maze[100][100];
    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 7; j++) maze[i][j] = 0;
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 7, 7, 0, 0, 6, 6, weightMatrix);
    checkResult("Test 13: 7x7 empty", result, "(0, 0)->(1, 1)->(2, 2)->(3, 3)->(4, 4)->(5, 5)->(6, 6)", 9.0);
    deletePathList(result);
}

// Test 14: Corner to corner 4x4
void test14()
{
    int maze[100][100] = {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}};
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 4, 4, 0, 0, 3, 3, weightMatrix);
    checkResult("Test 14: 4x4 center block", result, "(0, 0)->(0, 1)->(0, 2)->(1, 3)->(2, 3)->(3, 3)", 5.5);
    deletePathList(result);
}

// Test 15: 3x8 scattered
void test15()
{
    int maze[100][100] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}};
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 3, 8, 0, 0, 2, 7, weightMatrix);
    checkResult("Test 15: Scattered walls", result, "(0, 0)->(0, 1)->(1, 2)->(2, 3)->(2, 4)->(2, 5)->(2, 6)->(2, 7)", 8.0);
    deletePathList(result);
}

// Test 16: 6x6 frame
void test16()
{
    int maze[100][100] = {
        {0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 1, 0},
        {0, 1, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0}};
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 6, 6, 0, 0, 5, 5, weightMatrix);
    checkResult("Test 16: 6x6 frame", result, "(0, 0)->(0, 1)->(0, 2)->(0, 3)->(0, 4)->(1, 5)->(2, 5)->(3, 5)->(4, 5)->(5, 5)", 9.5);
    deletePathList(result);
}

// Test 17: Single passage 3x10
void test17()
{
    int maze[100][100] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 3, 10, 0, 0, 2, 9, weightMatrix);
    checkResult("Test 17: Single passage", result, "(0, 0)->(0, 1)->(0, 2)->(0, 3)->(0, 4)->(1, 5)->(2, 6)->(2, 7)->(2, 8)->(2, 9)", 10.0);
    deletePathList(result);
}

// Test 18: 10x10 empty
void test18()
{
    int maze[100][100];
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++) maze[i][j] = 0;
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 10, 10, 0, 0, 9, 9, weightMatrix);
    checkResult("Test 18: 10x10 empty", result, "(0, 0)->(1, 1)->(2, 2)->(3, 3)->(4, 4)->(5, 5)->(6, 6)->(7, 7)->(8, 8)->(9, 9)", 13.5);
    deletePathList(result);
}

// Test 19: 4x3 barrier
void test19()
{
    int maze[100][100] = {
        {0, 1, 0},
        {0, 1, 0},
        {0, 1, 0},
        {0, 0, 0}};
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 4, 3, 0, 0, 3, 2, weightMatrix);
    checkResult("Test 19: Wall barrier", result, "(0, 0)->(1, 0)->(2, 0)->(3, 1)->(3, 2)", 4.5);
    deletePathList(result);
}

// Test 20: 8x8 empty
void test20()
{
    int maze[100][100];
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) maze[i][j] = 0;
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 8, 8, 0, 0, 7, 7, weightMatrix);
    checkResult("Test 20: 8x8 empty", result, "(0, 0)->(1, 1)->(2, 2)->(3, 3)->(4, 4)->(5, 5)->(6, 6)->(7, 7)", 10.5);
    deletePathList(result);
}

// Test 21: 6x6 nested
void test21()
{
    int maze[100][100] = {
        {0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 1, 0},
        {0, 1, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0}};
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 6, 6, 0, 0, 5, 5, weightMatrix);
    checkResult("Test 21: Nested walls", result, "(0, 0)->(0, 1)->(0, 2)->(0, 3)->(0, 4)->(1, 5)->(2, 5)->(3, 5)->(4, 5)->(5, 5)", 9.5);
    deletePathList(result);
}

// Test 22: 9x9 empty
void test22()
{
    int maze[100][100];
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++) maze[i][j] = 0;
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 9, 9, 0, 0, 8, 8, weightMatrix);
    checkResult("Test 22: 9x9 empty", result, "(0, 0)->(1, 1)->(2, 2)->(3, 3)->(4, 4)->(5, 5)->(6, 6)->(7, 7)->(8, 8)", 12.0);
    deletePathList(result);
}

// Test 23: 5x7 split
void test23()
{
    int maze[100][100] = {
        {0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0}};
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 5, 7, 0, 0, 0, 6, weightMatrix);
    checkResult("Test 23: Vertical split", result, "(0, 0)->(1, 1)->(2, 2)->(3, 2)->(4, 3)->(3, 4)->(2, 5)->(1, 6)->(0, 6)", 11.0);
    deletePathList(result);
}

// Test 24: 8x9 rectangle
void test24()
{
    int maze[100][100];
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 9; j++) maze[i][j] = 0;
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 8, 9, 0, 0, 7, 8, weightMatrix);
    checkResult("Test 24: 8x9 rectangle", result, "(0, 0)->(1, 1)->(2, 2)->(3, 3)->(4, 4)->(5, 5)->(6, 6)->(7, 7)->(7, 8)", 11.5);
    deletePathList(result);
}

// Test 25: 4x10 S-curve
void test25()
{
    int maze[100][100] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 4, 10, 0, 0, 3, 9, weightMatrix);
    checkResult("Test 25: S-curve", result, "(0, 0)->(0, 1)->(0, 2)->(0, 3)->(0, 4)->(1, 5)->(2, 5)->(3, 6)->(3, 7)->(3, 8)->(3, 9)", 11.0);
    deletePathList(result);
}

// Test 26: 10x8 wide
void test26()
{
    int maze[100][100];
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 8; j++) maze[i][j] = 0;
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 10, 8, 0, 0, 9, 7, weightMatrix);
    checkResult("Test 26: 10x8 tall", result, "(0, 0)->(1, 1)->(2, 2)->(3, 3)->(4, 4)->(5, 5)->(6, 6)->(7, 7)->(8, 7)->(9, 7)", 12.5);
    deletePathList(result);
}

// Test 27: 3x10 stripes
void test27()
{
    int maze[100][100] = {
        {0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
        {0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 3, 10, 0, 0, 2, 9, weightMatrix);
    checkResult("Test 27: Vertical stripes", result, "(0, 0)->(1, 0)->(2, 1)->(2, 2)->(2, 3)->(2, 4)->(2, 5)->(2, 6)->(2, 7)->(2, 8)->(2, 9)", 10.5);
    deletePathList(result);
}

// Test 28: 10x10 corner to corner
void test28()
{
    int maze[100][100];
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++) maze[i][j] = 0;
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 10, 10, 0, 0, 9, 9, weightMatrix);
    checkResult("Test 28: 10x10 diagonal", result, "(0, 0)->(1, 1)->(2, 2)->(3, 3)->(4, 4)->(5, 5)->(6, 6)->(7, 7)->(8, 8)->(9, 9)", 13.5);
    deletePathList(result);
}

// Test 29: 7x7 complex nested
void test29()
{
    int maze[100][100] = {
        {0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 0},
        {0, 1, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0}};
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 7, 7, 0, 0, 6, 6, weightMatrix);
    checkResult("Test 29: Complex nested", result, "(0, 0)->(0, 1)->(0, 2)->(0, 3)->(0, 4)->(0, 5)->(1, 6)->(2, 6)->(3, 6)->(4, 6)->(5, 6)->(6, 6)", 11.5);
    deletePathList(result);
}

// Test 30: 9x10 large
void test30()
{
    int maze[100][100];
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 10; j++) maze[i][j] = 0;
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 9, 10, 0, 0, 8, 9, weightMatrix);
    checkResult("Test 30: 9x10 rectangle", result, "(0, 0)->(1, 1)->(2, 2)->(3, 3)->(4, 4)->(5, 5)->(6, 6)->(7, 7)->(8, 8)->(8, 9)", 13.0);
    deletePathList(result);
}

// Test 31: 9x9 multi-level
void test31()
{
    int maze[100][100];
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++) maze[i][j] = 0;
    // Add some walls
    for (int i = 2; i < 7; i++) maze[i][2] = 1;
    for (int i = 4; i < 6; i++) maze[i][4] = 1;
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 9, 9, 0, 0, 8, 8, weightMatrix);
    checkResult("Test 31: Multi-level nested", result, "(0, 0)->(1, 1)->(1, 2)->(2, 3)->(3, 4)->(4, 5)->(5, 6)->(6, 7)->(7, 8)->(8, 8)", 12.5);
    deletePathList(result);
}

// Test 32: 10x10 with obstacles
void test32()
{
    int maze[100][100];
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++) maze[i][j] = 0;
    maze[3][3] = 1; maze[5][5] = 1; maze[7][7] = 1;
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 10, 10, 0, 0, 9, 9, weightMatrix);
    checkResult("Test 32: 10x10 with obstacles", result, "(0, 0)->(1, 1)->(2, 2)->(2, 3)->(3, 4)->(4, 5)->(5, 6)->(6, 7)->(7, 8)->(8, 9)->(9, 9)", 14.0);
    deletePathList(result);
}

// Test 33: 5x9 staggered
void test33()
{
    int maze[100][100] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}};
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 5, 9, 0, 0, 4, 8, weightMatrix);
    checkResult("Test 33: Staggered walls", result, "(0, 0)->(0, 1)->(1, 2)->(2, 3)->(3, 4)->(4, 5)->(4, 6)->(4, 7)->(4, 8)", 10.0);
    deletePathList(result);
}

// Test 34: 9x8 large
void test34()
{
    int maze[100][100];
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 8; j++) maze[i][j] = 0;
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 9, 8, 0, 0, 8, 7, weightMatrix);
    checkResult("Test 34: 9x8 rectangle", result, "(0, 0)->(1, 1)->(2, 2)->(3, 3)->(4, 4)->(5, 5)->(6, 6)->(7, 7)->(8, 7)", 11.5);
    deletePathList(result);
}

// Test 35: 6x6 random obstacles
void test35()
{
    int maze[100][100] = {
        {0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 0},
        {0, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0}};
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 6, 6, 0, 0, 5, 5, weightMatrix);
    checkResult("Test 35: Random obstacles", result, "(0, 0)->(0, 1)->(1, 2)->(2, 3)->(3, 4)->(4, 5)->(5, 5)", 8.0);
    deletePathList(result);
}

// Test 36: 10x7 wide
void test36()
{
    int maze[100][100];
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 7; j++) maze[i][j] = 0;
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 10, 7, 0, 0, 9, 6, weightMatrix);
    checkResult("Test 36: 10x7 tall", result, "(0, 0)->(1, 1)->(2, 2)->(3, 3)->(4, 4)->(5, 5)->(6, 6)->(7, 6)->(8, 6)->(9, 6)", 12.0);
    deletePathList(result);
}

// Test 37: 3x10 narrow passage
void test37()
{
    int maze[100][100] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 0, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 3, 10, 0, 0, 2, 9, weightMatrix);
    checkResult("Test 37: Narrow passage", result, "(0, 0)->(0, 1)->(0, 2)->(0, 3)->(0, 4)->(0, 5)->(0, 6)->(1, 7)->(2, 8)->(2, 9)", 10.0);
    deletePathList(result);
}

// Test 38: 10x9 tall
void test38()
{
    int maze[100][100];
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 9; j++) maze[i][j] = 0;
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 10, 9, 0, 0, 9, 8, weightMatrix);
    checkResult("Test 38: 10x9 tall", result, "(0, 0)->(1, 1)->(2, 2)->(3, 3)->(4, 4)->(5, 5)->(6, 6)->(7, 7)->(8, 8)->(9, 8)", 13.0);
    deletePathList(result);
}

// Test 39: 7x7 partial block
void test39()
{
    int maze[100][100] = {
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 0, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0}};
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 7, 7, 0, 0, 6, 6, weightMatrix);
    checkResult("Test 39: Partial block", result, "(0, 0)->(1, 1)->(2, 2)->(3, 3)->(4, 3)->(5, 4)->(6, 5)->(6, 6)", 9.5);
    deletePathList(result);
}

// Test 40: 10x10 massive
void test40()
{
    int maze[100][100];
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++) maze[i][j] = 0;
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 10, 10, 0, 0, 9, 9, weightMatrix);
    checkResult("Test 40: 10x10 full diagonal", result, "(0, 0)->(1, 1)->(2, 2)->(3, 3)->(4, 4)->(5, 5)->(6, 6)->(7, 7)->(8, 8)->(9, 9)", 13.5);
    deletePathList(result);
}

// Test 41: 8x8 deep nested
void test41()
{
    int maze[100][100];
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) maze[i][j] = 0;
    // Create nested walls
    for (int i = 2; i < 6; i++) maze[i][2] = 1;
    for (int i = 3; i < 5; i++) maze[i][4] = 1;
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 8, 8, 0, 0, 7, 7, weightMatrix);
    checkResult("Test 41: Deep nested maze", result, "(0, 0)->(1, 1)->(1, 2)->(2, 3)->(2, 4)->(3, 5)->(4, 6)->(5, 7)->(6, 7)->(7, 7)", 11.5);
    deletePathList(result);
}

// Test 42: 9x9 empty diagonal
void test42()
{
    int maze[100][100];
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++) maze[i][j] = 0;
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 9, 9, 0, 0, 8, 8, weightMatrix);
    checkResult("Test 42: 9x9 diagonal", result, "(0, 0)->(1, 1)->(2, 2)->(3, 3)->(4, 4)->(5, 5)->(6, 6)->(7, 7)->(8, 8)", 12.0);
    deletePathList(result);
}

// Test 43: 5x9 repeated pattern
void test43()
{
    int maze[100][100] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}};
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 5, 9, 0, 0, 4, 8, weightMatrix);
    checkResult("Test 43: Repeated pattern", result, "(0, 0)->(0, 1)->(1, 2)->(2, 3)->(3, 4)->(4, 5)->(4, 6)->(4, 7)->(4, 8)", 10.0);
    deletePathList(result);
}

// Test 44: 8x10 wide
void test44()
{
    int maze[100][100];
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 10; j++) maze[i][j] = 0;
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 8, 10, 0, 0, 7, 9, weightMatrix);
    checkResult("Test 44: 8x10 wide", result, "(0, 0)->(1, 1)->(2, 2)->(3, 3)->(4, 4)->(5, 5)->(6, 6)->(7, 7)->(7, 8)->(7, 9)", 12.5);
    deletePathList(result);
}

// Test 45: 5x10 impossible
void test45()
{
    int maze[100][100] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 5, 10, 0, 0, 4, 9, weightMatrix);
    checkResult("Test 45: Alternating rows", result, "null", -1.0);
    deletePathList(result);
}

// Test 46: 10x10 with path
void test46()
{
    int maze[100][100];
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++) maze[i][j] = 0;
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 10, 10, 0, 0, 9, 9, weightMatrix);
    checkResult("Test 46: 10x10 clean", result, "(0, 0)->(1, 1)->(2, 2)->(3, 3)->(4, 4)->(5, 5)->(6, 6)->(7, 7)->(8, 8)->(9, 9)", 13.5);
    deletePathList(result);
}

// Test 47: 9x9 multi-room
void test47()
{
    int maze[100][100];
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++) maze[i][j] = 0;
    // Create rooms
    for (int j = 3; j < 6; j++) maze[4][j] = 1;
    maze[4][4] = 0; // doorway
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 9, 9, 0, 0, 8, 8, weightMatrix);
    checkResult("Test 47: Multi-room", result, "(0, 0)->(1, 1)->(2, 2)->(3, 3)->(4, 4)->(5, 5)->(6, 6)->(7, 7)->(8, 8)", 12.0);
    deletePathList(result);
}

// Test 48: 10x10 edge case
void test48()
{
    int maze[100][100];
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++) maze[i][j] = 0;
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 10, 10, 0, 0, 9, 9, weightMatrix);
    checkResult("Test 48: 10x10 baseline", result, "(0, 0)->(1, 1)->(2, 2)->(3, 3)->(4, 4)->(5, 5)->(6, 6)->(7, 7)->(8, 8)->(9, 9)", 13.5);
    deletePathList(result);
}

// Test 49: 10x10 complex
void test49()
{
    int maze[100][100];
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++) maze[i][j] = 0;
    // Create complex nested structure
    for (int i = 3; i < 7; i++) {
        maze[i][3] = 1;
        maze[i][6] = 1;
    }
    for (int j = 3; j < 7; j++) {
        maze[3][j] = 1;
    }
    maze[3][5] = 0; // doorway
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 10, 10, 0, 0, 9, 9, weightMatrix);
    checkResult("Test 49: Complex nested", result, "(0, 0)->(1, 1)->(2, 2)->(2, 3)->(2, 4)->(3, 5)->(4, 5)->(5, 5)->(6, 5)->(7, 6)->(8, 7)->(9, 8)->(9, 9)", 15.0);
    deletePathList(result);
}

// Test 50: 10x10 maximum size
void test50()
{
    int maze[100][100];
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++) maze[i][j] = 0;
    double weightMatrix[100][100] = {0};
    PathNode* result = findPathInMaze2(maze, 10, 10, 0, 0, 9, 9, weightMatrix);
    checkResult("Test 50: 10x10 maximum", result, "(0, 0)->(1, 1)->(2, 2)->(3, 3)->(4, 4)->(5, 5)->(6, 6)->(7, 7)->(8, 8)->(9, 9)", 13.5);
    deletePathList(result);
}

int main()
{
    cout << "========================================" << endl;
    cout << "   TASK 4: Weighted Maze Test Suite" << endl;
    cout << "========================================\n" << endl;

    test1(); test2(); test3(); test4(); test5();
    test6(); test7(); test8(); test9(); test10();
    test11(); test12(); test13(); test14(); test15();
    test16(); test17(); test18(); test19(); test20();
    test21(); test22(); test23(); test24(); test25();
    test26(); test27(); test28(); test29(); test30();
    test31(); test32(); test33(); test34(); test35();
    test36(); test37(); test38(); test39(); test40();
    test41(); test42(); test43(); test44(); test45();
    test46(); test47(); test48(); test49(); test50();

    cout << "========================================" << endl;
    cout << "   TEST SUMMARY" << endl;
    cout << "========================================" << endl;
    cout << "Total tests: " << totalTests << endl;
    cout << GREEN << "Passed: " << passedTests << RESET << endl;
    cout << RED << "Failed: " << (totalTests - passedTests) << RESET << endl;
    
    if (!failedTests.empty()) {
        cout << "\n" << YELLOW << "Failed tests:" << RESET << endl;
        for (size_t i = 0; i < failedTests.size(); i++) {
            cout << "  " << (i + 1) << ". " << failedTests[i] << endl;
        }
    } else {
        cout << "\n" << GREEN << "🎉 All tests passed!" << RESET << endl;
    }
    
    cout << "========================================" << endl;

    return 0;
}
