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
        if (temp->next) ss << "-";
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
    bool costMatch = (expectedCost < 0) ? (actualCost < 0) : (fabs(actualCost - expectedCost) < 0.1);
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
    PathNode* result = findPathInMaze(maze, 3, 3, 0, 0, 2, 2);
    checkResult("Test 1: 3x3 empty maze", result, "Down-Right-Down-Right", 3.0);
    deletePathList(result);
}

// Test 2: 3x3 with wall
void test2()
{
    int maze[100][100] = {
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 0}};
    PathNode* result = findPathInMaze(maze, 3, 3, 0, 0, 2, 2);
    checkResult("Test 2: 3x3 with center wall", result, "Down-Down-Right-Right", 3.5);
    deletePathList(result);
}

// Test 3: No path (blocked)
void test3()
{
    int maze[100][100] = {
        {0, 0, 0},
        {1, 1, 1},
        {0, 0, 0}};
    PathNode* result = findPathInMaze(maze, 3, 3, 0, 0, 2, 2);
    checkResult("Test 3: Blocked path", result, "null", -1.0);
    deletePathList(result);
}

// Test 4: Start = Goal
void test4()
{
    int maze[100][100] = {{0, 0}, {0, 0}};
    PathNode* result = findPathInMaze(maze, 2, 2, 1, 1, 1, 1);
    checkResult("Test 4: Start equals goal", result, "", 0.0);
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
    PathNode* result = findPathInMaze(maze, 5, 5, 0, 0, 4, 4);
    checkResult("Test 5: 5x5 diagonal", result, "Down-Right-Down-Right-Down-Right-Down-Right", 6.0);
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
    PathNode* result = findPathInMaze(maze, 5, 5, 0, 0, 4, 4);
    checkResult("Test 6: Corridor maze", result, "Right-Down-Right-Down-Right-Down-Right-Down", 6.5);
    deletePathList(result);
}

// Test 7: Long straight path
void test7()
{
    int maze[100][100] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    PathNode* result = findPathInMaze(maze, 1, 10, 0, 0, 0, 9);
    checkResult("Test 7: 1x10 straight", result, "Down-Down-Down-Down-Down-Down-Down-Down-Down", 9.0);
    deletePathList(result);
}

// Test 8: Vertical path
void test8()
{
    int maze[100][100] = {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}};
    PathNode* result = findPathInMaze(maze, 10, 1, 0, 0, 9, 0);
    checkResult("Test 8: 10x1 vertical", result, "Right-Right-Right-Right-Right-Right-Right-Right-Right", 9.0);
    deletePathList(result);
}

// Test 9: Spiral maze
void test9()
{
    int maze[100][100] = {
        {0, 0, 0, 0, 0},
        {1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1},
        {0, 0, 0, 0, 0}};
    PathNode* result = findPathInMaze(maze, 5, 5, 0, 0, 2, 2);
    checkResult("Test 9: Spiral pattern", result, "Down-Down-Down-Down-Right-Up-Right-Up", 7.0);
    deletePathList(result);
}

// Test 10: L-shaped path
void test10()
{
    int maze[100][100] = {
        {0, 0, 0},
        {1, 1, 0},
        {0, 0, 0}};
    PathNode* result = findPathInMaze(maze, 3, 3, 0, 0, 2, 0);
    checkResult("Test 10: L-shape", result, "Down-Down-Right-Up-Right-Up", 5.0);
    deletePathList(result);
}

// Tests 11-20
void test11()
{
    int maze[100][100] = {
        {0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 1, 0},
        {0, 1, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0}};
    PathNode* result = findPathInMaze(maze, 6, 6, 0, 0, 5, 5);
    checkResult("Test 11: Frame maze", result, "Down-Down-Down-Down-Down-Right-Right-Right-Right-Right", 9.5);
    deletePathList(result);
}

void test12()
{
    int maze[100][100] = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0}};
    PathNode* result = findPathInMaze(maze, 5, 5, 0, 0, 4, 4);
    checkResult("Test 12: Zigzag walls", result, "Right-Down-Right-Down-Right-Down-Right-Down", 6.5);
    deletePathList(result);
}

void test13()
{
    int maze[100][100];
    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 7; j++) maze[i][j] = 0;
    PathNode* result = findPathInMaze(maze, 7, 7, 0, 0, 6, 6);
    checkResult("Test 13: 7x7 empty", result, "Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right", 9.0);
    deletePathList(result);
}

void test14()
{
    int maze[100][100] = {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}};
    PathNode* result = findPathInMaze(maze, 4, 4, 0, 0, 3, 3);
    checkResult("Test 14: 2x2 block in center", result, "Down-Down-Down-Right-Right-Right", 5.5);
    deletePathList(result);
}

void test15()
{
    int maze[100][100] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}};
    PathNode* result = findPathInMaze(maze, 3, 8, 0, 0, 2, 7);
    checkResult("Test 15: Scattered walls", result, "Down-Down-Right-Down-Right-Down-Down-Down-Down", 8.0);
    deletePathList(result);
}

void test16()
{
    int maze[100][100];
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            maze[i][j] = ((i + j) % 2 == 1 && i > 0 && i < 7 && j > 0 && j < 7) ? 1 : 0;
        }
    PathNode* result = findPathInMaze(maze, 8, 8, 0, 0, 7, 7);
    checkResult("Test 16: Checkerboard walls", result, "Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right", 10.5);
    deletePathList(result);
}

void test17()
{
    int maze[100][100] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    PathNode* result = findPathInMaze(maze, 3, 10, 0, 0, 2, 9);
    checkResult("Test 17: Single passage", result, "Down-Down-Down-Down-Down-Right-Down-Right-Down-Down-Down", 10.0);
    deletePathList(result);
}

void test18()
{
    int maze[100][100];
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++) maze[i][j] = 0;
    PathNode* result = findPathInMaze(maze, 10, 10, 0, 0, 9, 9);
    checkResult("Test 18: 10x10 empty", result, "Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right", 13.5);
    deletePathList(result);
}

void test19()
{
    int maze[100][100] = {
        {0, 1, 0},
        {0, 1, 0},
        {0, 1, 0},
        {0, 0, 0}};
    PathNode* result = findPathInMaze(maze, 4, 3, 0, 0, 3, 2);
    checkResult("Test 19: Wall barrier", result, "Right-Right-Down-Right-Down", 4.5);
    deletePathList(result);
}

void test20()
{
    int maze[100][100];
    for (int i = 0; i < 12; i++)
        for (int j = 0; j < 12; j++) maze[i][j] = 0;
    PathNode* result = findPathInMaze(maze, 12, 12, 0, 0, 11, 11);
    checkResult("Test 20: 12x12 large empty", result, "Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right", 16.5);
    deletePathList(result);
}

// Tests 21-30 (harder)
void test21()
{
    int maze[100][100] = {
        {0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 0},
        {0, 1, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0}};
    PathNode* result = findPathInMaze(maze, 7, 7, 0, 0, 6, 6);
    checkResult("Test 21: Nested walls", result, "Down-Down-Down-Down-Down-Down-Right-Right-Right-Right-Right-Right", 11.5);
    deletePathList(result);
}

void test22()
{
    int maze[100][100];
    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 15; j++) maze[i][j] = 0;
    PathNode* result = findPathInMaze(maze, 15, 15, 0, 0, 14, 14);
    checkResult("Test 22: 15x15 empty", result, "Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right", 21);
    deletePathList(result);
}

void test23()
{
    int maze[100][100] = {
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0}};
    PathNode* result = findPathInMaze(maze, 5, 5, 0, 0, 4, 4);
    checkResult("Test 23: Central vertical split", result, "Down-Right-Down-Right-Down-Right-Down-Right", 6);
    deletePathList(result);
}

void test24()
{
    int maze[100][100];
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 12; j++) maze[i][j] = 0;
    PathNode* result = findPathInMaze(maze, 8, 12, 0, 0, 7, 11);
    checkResult("Test 24: 8x12 rectangle", result, "Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Down-Down-Down", 14.5);
    deletePathList(result);
}

void test25()
{
    int maze[100][100] = {
        {0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0}};
    PathNode* result = findPathInMaze(maze, 5, 6, 0, 0, 4, 5);
    checkResult("Test 25: S-curve", result, "Down-Down-Down-Down-Down-Right-Up-Right-Up-Up-Up-Up-Right-Down-Right-Down-Down-Down-Down", 17);
    deletePathList(result);
}

void test26()
{
    int maze[100][100];
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 15; j++) maze[i][j] = 0;
    PathNode* result = findPathInMaze(maze, 10, 15, 0, 0, 9, 14);
    checkResult("Test 26: 10x15 wide", result, "Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Down-Down-Down-Down", 18.5);
    deletePathList(result);
}

void test27()
{
    int maze[100][100] = {
        {0, 1, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 0}};
    PathNode* result = findPathInMaze(maze, 5, 7, 0, 0, 4, 6);
    checkResult("Test 27: Vertical stripes", result, "Right-Down-Right-Down-Down-Down-Down-Down-Right-Right", 9);
    deletePathList(result);
}

void test28()
{
    int maze[100][100];
    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 20; j++) maze[i][j] = 0;
    PathNode* result = findPathInMaze(maze, 20, 20, 0, 0, 19, 19);
    checkResult("Test 28: 20x20 massive empty", result, "Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right", 28.5);
    deletePathList(result);
}

void test29()
{
    int maze[100][100] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 1, 1, 0, 1, 0},
        {0, 1, 0, 1, 1, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}};
    PathNode* result = findPathInMaze(maze, 8, 8, 0, 0, 7, 7);
    checkResult("Test 29: Complex nested", result, "Down-Down-Down-Down-Down-Down-Down-Right-Right-Right-Right-Right-Right-Right", 13.5);
    deletePathList(result);
}

void test30()
{
    int maze[100][100];
    for (int i = 0; i < 12; i++)
        for (int j = 0; j < 18; j++) maze[i][j] = 0;
    PathNode* result = findPathInMaze(maze, 12, 18, 0, 0, 11, 17);
    checkResult("Test 30: 12x18 wide rectangle", result, "Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Down-Down-Down-Down-Down", 22.5);
    deletePathList(result);
}

// Tests 31-40 (complex)
void test31()
{
    int maze[100][100] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 1, 1, 1, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 1, 1, 1, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    PathNode* result = findPathInMaze(maze, 10, 10, 0, 0, 9, 9);
    checkResult("Test 31: Multi-level nested", result, "Down-Down-Down-Down-Down-Down-Down-Down-Down-Right-Right-Right-Right-Right-Right-Right-Right-Right", 17.5);
    deletePathList(result);
}

void test32()
{
    int maze[100][100];
    for (int i = 0; i < 25; i++)
        for (int j = 0; j < 25; j++) maze[i][j] = 0;
    PathNode* result = findPathInMaze(maze, 25, 25, 0, 0, 24, 24);
    checkResult("Test 32: 25x25 huge empty", result, "Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right", 36);
    deletePathList(result);
}

void test33()
{
    int maze[100][100] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    PathNode* result = findPathInMaze(maze, 5, 12, 0, 0, 4, 11);
    checkResult("Test 33: Staggered walls", result, "Down-Down-Right-Down-Right-Down-Down-Right-Down-Right-Down-Down-Down-Down-Down", 13);
    deletePathList(result);
}

void test34()
{
    int maze[100][100];
    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 20; j++) maze[i][j] = 0;
    PathNode* result = findPathInMaze(maze, 15, 20, 0, 0, 14, 19);
    checkResult("Test 34: 15x20 large", result, "Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Down-Down-Down-Down", 26);
    deletePathList(result);
}

void test35()
{
    int maze[100][100] = {
        {0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0},
        {0, 1, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0}};
    PathNode* result = findPathInMaze(maze, 7, 7, 0, 0, 6, 6);
    checkResult("Test 35: Random obstacles", result, "Right-Right-Right-Right-Right-Down-Right-Down-Down-Down-Down-Down", 11.5);
    deletePathList(result);
}

void test36()
{
    int maze[100][100];
    for (int i = 0; i < 18; i++)
        for (int j = 0; j < 18; j++) maze[i][j] = 0;
    PathNode* result = findPathInMaze(maze, 18, 18, 0, 0, 17, 17);
    checkResult("Test 36: 18x18 empty", result, "Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right", 25.5);
    deletePathList(result);
}

void test37()
{
    int maze[100][100] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    PathNode* result = findPathInMaze(maze, 3, 15, 0, 0, 2, 14);
    checkResult("Test 37: Single narrow passage", result, "Down-Down-Down-Down-Down-Down-Down-Right-Down-Right-Down-Down-Down-Down-Down-Down", 15);
    deletePathList(result);
}

void test38()
{
    int maze[100][100];
    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 15; j++) maze[i][j] = 0;
    PathNode* result = findPathInMaze(maze, 20, 15, 0, 0, 19, 14);
    checkResult("Test 38: 20x15 tall", result, "Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Right-Right-Right-Right-Right", 26);
    deletePathList(result);
}

void test39()
{
    int maze[100][100] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 1, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1}};
    PathNode* result = findPathInMaze(maze, 8, 8, 0, 0, 6, 7);
    checkResult("Test 39: Partial block bottom", result, "Down-Down-Down-Down-Down-Down-Down-Right-Right-Right-Right-Right-Right", 12.5);
    deletePathList(result);
}

void test40()
{
    int maze[100][100];
    for (int i = 0; i < 30; i++)
        for (int j = 0; j < 30; j++) maze[i][j] = 0;
    PathNode* result = findPathInMaze(maze, 30, 30, 0, 0, 29, 29);
    checkResult("Test 40: 30x30 massive", result, "Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right", 43.5);
    deletePathList(result);
}

// Tests 41-50 (very complex)
void test41()
{
    int maze[100][100] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    PathNode* result = findPathInMaze(maze, 14, 15, 0, 0, 13, 14);
    checkResult("Test 41: Deep nested maze", result, "Right-Right-Right-Right-Right-Right-Right-Right-Right-Right-Right-Right-Down-Right-Down-Down-Down-Down-Down-Down-Down-Down-Down-Down-Down-Down-Down", 26.5);
    deletePathList(result);
}

void test42()
{
    int maze[100][100];
    for (int i = 0; i < 22; i++)
        for (int j = 0; j < 22; j++) maze[i][j] = 0;
    PathNode* result = findPathInMaze(maze, 22, 22, 0, 0, 21, 21);
    checkResult("Test 42: 22x22 empty", result, "Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right", 31.5);
    deletePathList(result);
}

void test43()
{
    int maze[100][100] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 0, 1, 1, 1, 1, 0, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 0, 1, 1, 1, 1, 0, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 0, 1, 1, 1, 1, 0, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    PathNode* result = findPathInMaze(maze, 7, 10, 0, 0, 6, 9);
    checkResult("Test 43: Repeated pattern", result, "Down-Down-Right-Down-Right-Down-Down-Down-Down-Right-Right-Right-Down-Right-Down", 13);
    deletePathList(result);
}

void test44()
{
    int maze[100][100];
    for (int i = 0; i < 16; i++)
        for (int j = 0; j < 24; j++) maze[i][j] = 0;
    PathNode* result = findPathInMaze(maze, 16, 24, 0, 0, 15, 23);
    checkResult("Test 44: 16x24 wide", result, "Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Down-Down-Down-Down-Down-Down-Down", 30.5);
    deletePathList(result);
}

void test45()
{
    int maze[100][100] = {
        {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1}};
    PathNode* result = findPathInMaze(maze, 5, 12, 0, 0, 4, 11);
    checkResult("Test 45: Alternating pattern", result, "null", -1);
    deletePathList(result);
}

void test46()
{
    int maze[100][100];
    for (int i = 0; i < 28; i++)
        for (int j = 0; j < 28; j++) maze[i][j] = 0;
    PathNode* result = findPathInMaze(maze, 28, 28, 0, 0, 27, 27);
    checkResult("Test 46: 28x28 huge", result, "Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right", 40.5);
    deletePathList(result);
}

void test47()
{
    int maze[100][100] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    PathNode* result = findPathInMaze(maze, 11, 16, 0, 0, 10, 15);
    checkResult("Test 47: Complex multi-room", result, "Right-Right-Right-Right-Right-Right-Right-Right-Right-Down-Right-Down-Down-Down-Down-Down-Down-Down-Down-Down-Down-Down-Down-Down-Down", 24.5);
    deletePathList(result);
}

void test48()
{
    int maze[100][100];
    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 25; j++) maze[i][j] = 0;
    PathNode* result = findPathInMaze(maze, 20, 25, 0, 0, 19, 24);
    checkResult("Test 48: 20x25 very wide", result, "Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Down-Down-Down-Down", 33.5);
    deletePathList(result);
}

void test49()
{
    int maze[100][100] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    PathNode* result = findPathInMaze(maze, 14, 20, 0, 0, 13, 19);
    checkResult("Test 49: Ultra complex nested", result, "Right-Right-Right-Right-Right-Right-Right-Right-Right-Right-Right-Right-Down-Right-Down-Down-Down-Down-Down-Down-Down-Down-Down-Down-Down-Down-Down-Down-Down-Down-Down-Down", 31.5);
    deletePathList(result);
}

void test50()
{
    int maze[100][100];
    for (int i = 0; i < 35; i++)
        for (int j = 0; j < 35; j++) maze[i][j] = 0;
    PathNode* result = findPathInMaze(maze, 35, 35, 0, 0, 34, 34);
    checkResult("Test 50: 35x35 ultimate massive", result, "Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right", 51);
    deletePathList(result);
}

int main()
{
    cout << "========================================" << endl;
    cout << "   TASK 3: Maze Navigation Test Suite" << endl;
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
