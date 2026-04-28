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

// Test 1: Simple 3x3 maze - straight right then down
void test1()
{
    int maze[100][100] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    PathNode* result = findPathInMaze(maze, 3, 3, 0, 0, 2, 2);
    checkResult("Test 1: 3x3 empty", result, "Down-Right-Down-Right", 3.0);
    deletePathList(result);
}

// Test 2: 3x3 with center wall
void test2()
{
    int maze[100][100] = {
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 0}};
    PathNode* result = findPathInMaze(maze, 3, 3, 0, 0, 2, 2);
    checkResult("Test 2: 3x3 center wall", result, "Down-Down-Right-Right", 3.5);
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

// Test 6: Corridor maze
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

// Test 7: 1x10 straight horizontal
void test7()
{
    int maze[100][100] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    PathNode* result = findPathInMaze(maze, 1, 10, 0, 0, 0, 9);
    checkResult("Test 7: 1x10 straight", result, "Down-Down-Down-Down-Down-Down-Down-Down-Down", 9.0);
    deletePathList(result);
}

// Test 8: 10x1 straight vertical
void test8()
{
    int maze[100][100];
    for (int i = 0; i < 10; i++) maze[i][0] = 0;
    PathNode* result = findPathInMaze(maze, 10, 1, 0, 0, 9, 0);
    checkResult("Test 8: 10x1 vertical", result, "Right-Right-Right-Right-Right-Right-Right-Right-Right", 9.0);
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
    PathNode* result = findPathInMaze(maze, 5, 5, 0, 0, 4, 0);
    checkResult("Test 9: Spiral pattern", result, "Down-Down-Down-Down-Right-Up-Right-Up-Up-Up-Right-Right", 10.5);
    deletePathList(result);
}

// Test 10: L-shape
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

// Tests 11-20: More complex scenarios
void test11()
{
    int maze[100][100];
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++)
            maze[i][j] = 0;
    PathNode* result = findPathInMaze(maze, 6, 6, 0, 0, 5, 5);
    checkResult("Test 11: 6x6 empty", result, "Down-Right-Down-Right-Down-Right-Down-Right-Down-Right", 7.5);
    deletePathList(result);
}

void test12()
{
    int maze[100][100] = {
        {0, 1, 0},
        {0, 1, 0},
        {0, 0, 0}};
    PathNode* result = findPathInMaze(maze, 3, 3, 0, 0, 0, 2);
    checkResult("Test 12: Vertical wall", result, "Right-Down-Right-Down-Left-Left", 5.0);
    deletePathList(result);
}

void test13()
{
    int maze[100][100];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            maze[i][j] = 0;
    maze[1][1] = 1;
    maze[1][2] = 1;
    maze[2][1] = 1;
    maze[2][2] = 1;
    PathNode* result = findPathInMaze(maze, 4, 4, 0, 0, 3, 3);
    checkResult("Test 13: Center block", result, "Down-Down-Down-Right-Right-Right", 5.5);
    deletePathList(result);
}

void test14()
{
    int maze[100][100];
    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 7; j++)
            maze[i][j] = 0;
    PathNode* result = findPathInMaze(maze, 7, 7, 0, 0, 6, 6);
    checkResult("Test 14: 7x7 empty", result, "Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right", 9.0);
    deletePathList(result);
}

void test15()
{
    int maze[100][100] = {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}};
    PathNode* result = findPathInMaze(maze, 4, 4, 0, 0, 3, 3);
    checkResult("Test 15: Frame with hole", result, "Down-Down-Down-Right-Right-Right", 5.5);
    deletePathList(result);
}

void test16()
{
    int maze[100][100];
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            maze[i][j] = 0;
    PathNode* result = findPathInMaze(maze, 2, 2, 0, 0, 1, 1);
    checkResult("Test 16: 2x2 diagonal", result, "Down-Right", 1.5);
    deletePathList(result);
}

void test17()
{
    int maze[100][100];
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            maze[i][j] = 0;
    PathNode* result = findPathInMaze(maze, 8, 8, 0, 0, 7, 7);
    checkResult("Test 17: 8x8 empty", result, "Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right", 10.5);
    deletePathList(result);
}

void test18()
{
    int maze[100][100] = {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 1, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 0, 0, 0}};
    PathNode* result = findPathInMaze(maze, 5, 5, 0, 0, 4, 4);
    checkResult("Test 18: Complex maze", result, "Right-Down-Right-Down-Right-Down-Right-Down", 6.5);
    deletePathList(result);
}

void test19()
{
    int maze[100][100];
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            maze[i][j] = 0;
    PathNode* result = findPathInMaze(maze, 10, 10, 0, 0, 9, 9);
    checkResult("Test 19: 10x10 empty", result, "Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right-Down-Right", 13.5);
    deletePathList(result);
}

void test20()
{
    int maze[100][100] = {
        {0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0}};
    PathNode* result = findPathInMaze(maze, 5, 5, 0, 0, 4, 4);
    checkResult("Test 20: Zigzag walls", result, "Down-Right-Down-Right-Down-Right-Down-Right", 6.0);
    deletePathList(result);
}

// Simplified tests 21-50
void test21() { test1(); }
void test22() { test2(); }
void test23() { test3(); }
void test24() { test4(); }
void test25() { test5(); }
void test26() { test6(); }
void test27() { test7(); }
void test28() { test8(); }
void test29() { test9(); }
void test30() { test10(); }
void test31() { test11(); }
void test32() { test12(); }
void test33() { test13(); }
void test34() { test14(); }
void test35() { test15(); }
void test36() { test16(); }
void test37() { test17(); }
void test38() { test18(); }
void test39() { test19(); }
void test40() { test20(); }
void test41() { test1(); }
void test42() { test2(); }
void test43() { test3(); }
void test44() { test4(); }
void test45() { test5(); }
void test46() { test6(); }
void test47() { test7(); }
void test48() { test8(); }
void test49() { test9(); }
void test50() { test10(); }

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
