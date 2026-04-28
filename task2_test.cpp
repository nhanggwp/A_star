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
    checkResult("Test 1: Straight line Euclidean", result, "(0, 0)->(5, 0)->(10, 0)", 10.0);
    deletePathList(result);
}

// Test 2: Manhattan distance mode
void test2()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{0, 0}, {3, 4}, {6, 8}};
    adj[0][1] = 5.0;
    adj[1][0] = 5.0;
    adj[1][2] = 5.0;
    adj[2][1] = 5.0;
    PathNode* result = findShortestPath2D(adj, coords, 0, 2, 1);
    checkResult("Test 2: Manhattan mode", result, "(0, 0)->(3, 4)->(6, 8)", 10.0);
    deletePathList(result);
}

// Test 3: Triangle with shortcut
void test3()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{0, 0}, {3, 0}, {0, 4}, {3, 4}};
    adj[0][1] = 3.0;
    adj[1][0] = 3.0;
    adj[1][3] = 4.0;
    adj[3][1] = 4.0;
    adj[0][2] = 4.0;
    adj[2][0] = 4.0;
    adj[2][3] = 3.0;
    adj[3][2] = 3.0;
    PathNode* result = findShortestPath2D(adj, coords, 0, 3, 0);
    checkResult("Test 3: Triangle shortcut", result, "(0, 0)->(3, 0)->(3, 4)", 7.0);
    deletePathList(result);
}

// Test 4: Start equals goal
void test4()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{5, 5}, {10, 10}};
    adj[0][1] = 7.07;
    adj[1][0] = 7.07;
    PathNode* result = findShortestPath2D(adj, coords, 1, 1, 0);
    checkResult("Test 4: Start equals goal", result, "(10, 10)", 0.0);
    deletePathList(result);
}

// Test 5: No path exists
void test5()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{0, 0}, {1, 1}, {5, 5}, {6, 6}};
    adj[0][1] = 1.41;
    adj[1][0] = 1.41;
    adj[2][3] = 1.41;
    adj[3][2] = 1.41;
    PathNode* result = findShortestPath2D(adj, coords, 0, 3, 0);
    checkResult("Test 5: No path", result, "null", -1.0);
    deletePathList(result);
}

// Test 6-10: More complex scenarios
void test6()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{0, 0}, {2, 0}, {4, 0}, {0, 2}, {2, 2}, {4, 2}};
    adj[0][1] = 2;
    adj[1][0] = 2;
    adj[1][2] = 2;
    adj[2][1] = 2;
    adj[0][3] = 2;
    adj[3][0] = 2;
    adj[1][4] = 2;
    adj[4][1] = 2;
    adj[2][5] = 2;
    adj[5][2] = 2;
    adj[3][4] = 2;
    adj[4][3] = 2;
    adj[4][5] = 2;
    adj[5][4] = 2;
    PathNode* result = findShortestPath2D(adj, coords, 0, 5, 0);
    checkResult("Test 6: Grid 3x2", result, "(0, 0)->(2, 0)->(4, 0)->(4, 2)", 6.0);
    deletePathList(result);
}

void test7()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{0, 0}, {1, 0}, {0, 1}, {1, 1}};
    adj[0][1] = 1;
    adj[1][0] = 1;
    adj[0][2] = 1;
    adj[2][0] = 1;
    adj[1][3] = 1;
    adj[3][1] = 1;
    adj[2][3] = 1;
    adj[3][2] = 1;
    PathNode* result = findShortestPath2D(adj, coords, 0, 3, 0);
    checkResult("Test 7: Diamond Euclidean", result, "(0, 0)->(1, 0)->(1, 1)", 2.0);
    deletePathList(result);
}

void test8()
{
    double adj[100][100] = {0};
    int coords[100][2];
    for (int i = 0; i < 10; i++)
    {
        coords[i][0] = i;
        coords[i][1] = 0;
        if (i < 9)
        {
            adj[i][i + 1] = 1.0;
            adj[i + 1][i] = 1.0;
        }
    }
    PathNode* result = findShortestPath2D(adj, coords, 0, 9, 0);
    checkResult("Test 8: 10-node chain", result, "(0, 0)->(1, 0)->(2, 0)->(3, 0)->(4, 0)->(5, 0)->(6, 0)->(7, 0)->(8, 0)->(9, 0)", 9.0);
    deletePathList(result);
}

void test9()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{5, 5}, {5, 0}, {10, 5}, {5, 10}, {0, 5}, {5, 2}};
    adj[0][1] = 5;
    adj[1][0] = 5;
    adj[0][2] = 5;
    adj[2][0] = 5;
    adj[0][3] = 5;
    adj[3][0] = 5;
    adj[0][4] = 5;
    adj[4][0] = 5;
    adj[1][5] = 2;
    adj[5][1] = 2;
    PathNode* result = findShortestPath2D(adj, coords, 4, 5, 0);
    checkResult("Test 9: Star topology", result, "(0, 5)->(5, 5)->(5, 0)->(5, 2)", 12.0);
    deletePathList(result);
}

void test10()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{0, 0}, {2, 0}, {2, 2}, {0, 2}};
    adj[0][1] = 2;
    adj[1][0] = 2;
    adj[1][2] = 2;
    adj[2][1] = 2;
    adj[2][3] = 2;
    adj[3][2] = 2;
    adj[3][0] = 2;
    adj[0][3] = 2;
    PathNode* result = findShortestPath2D(adj, coords, 0, 2, 1);
    checkResult("Test 10: Square cycle", result, "(0, 0)->(2, 0)->(2, 2)", 4.0);
    deletePathList(result);
}

// Tests 11-50: Add more edge cases and complex scenarios
void test11()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{0, 0}, {10, 0}, {5, 5}, {10, 10}};
    adj[0][1] = 10;
    adj[1][0] = 10;
    adj[1][3] = 10;
    adj[3][1] = 10;
    adj[0][2] = 7.07;
    adj[2][0] = 7.07;
    adj[2][3] = 7.07;
    adj[3][2] = 7.07;
    PathNode* result = findShortestPath2D(adj, coords, 0, 3, 0);
    checkResult("Test 11: Diagonal shortcut", result, "(0, 0)->(5, 5)->(10, 10)", 14.14);
    deletePathList(result);
}

void test12()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{0, 0}, {1, 1}, {2, 0}, {3, 1}, {4, 0}};
    for (int i = 0; i < 4; i++)
    {
        adj[i][i + 1] = 1.41;
        adj[i + 1][i] = 1.41;
    }
    PathNode* result = findShortestPath2D(adj, coords, 0, 4, 0);
    checkResult("Test 12: Zigzag pattern", result, "(0, 0)->(1, 1)->(2, 0)->(3, 1)->(4, 0)", 5.64);
    deletePathList(result);
}

// Continue with more tests (13-50)...
void test13()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{0, 0}, {5, 0}, {10, 0}, {15, 0}, {20, 0}};
    for (int i = 0; i < 4; i++)
    {
        adj[i][i + 1] = 5;
        adj[i + 1][i] = 5;
    }
    PathNode* result = findShortestPath2D(adj, coords, 0, 4, 1);
    checkResult("Test 13: Long straight Manhattan", result, "(0, 0)->(5, 0)->(10, 0)->(15, 0)->(20, 0)", 20.0);
    deletePathList(result);
}

void test14()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{0, 0}, {1, 0}, {2, 0}, {1, 1}};
    adj[0][1] = 1;
    adj[1][0] = 1;
    adj[1][2] = 1;
    adj[2][1] = 1;
    adj[1][3] = 1;
    adj[3][1] = 1;
    PathNode* result = findShortestPath2D(adj, coords, 0, 3, 0);
    checkResult("Test 14: T-junction", result, "(0, 0)->(1, 0)->(1, 1)", 2.0);
    deletePathList(result);
}

void test15()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{0, 0}, {2, 2}, {4, 4}, {6, 6}};
    for (int i = 0; i < 3; i++)
    {
        adj[i][i + 1] = 2.83;
        adj[i + 1][i] = 2.83;
    }
    PathNode* result = findShortestPath2D(adj, coords, 0, 3, 0);
    checkResult("Test 15: Diagonal line", result, "(0, 0)->(2, 2)->(4, 4)->(6, 6)", 8.49);
    deletePathList(result);
}

// Add remaining tests 16-50 following similar patterns
void test16()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{0, 0}, {1, 1}, {2, 2}};
    adj[0][1] = 1.41;
    adj[1][0] = 1.41;
    adj[1][2] = 1.41;
    adj[2][1] = 1.41;
    PathNode* result = findShortestPath2D(adj, coords, 0, 2, 0);
    checkResult("Test 16: Small diagonal", result, "(0, 0)->(1, 1)->(2, 2)", 2.82);
    deletePathList(result);
}

void test17()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{0, 0}};
    PathNode* result = findShortestPath2D(adj, coords, 0, 0, 0);
    checkResult("Test 17: Single node", result, "(0, 0)", 0.0);
    deletePathList(result);
}

void test18()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{0, 0}, {5, 12}};
    adj[0][1] = 13;
    adj[1][0] = 13;
    PathNode* result = findShortestPath2D(adj, coords, 0, 1, 0);
    checkResult("Test 18: 5-12-13 triangle", result, "(0, 0)->(5, 12)", 13.0);
    deletePathList(result);
}

void test19()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};
    adj[0][1] = 1;
    adj[1][0] = 1;
    adj[1][2] = 1;
    adj[2][1] = 1;
    adj[2][3] = 1;
    adj[3][2] = 1;
    adj[3][0] = 1;
    adj[0][3] = 1;
    PathNode* result = findShortestPath2D(adj, coords, 0, 2, 1);
    checkResult("Test 19: Unit square Manhattan", result, "(0, 0)->(1, 0)->(1, 1)", 2.0);
    deletePathList(result);
}

void test20()
{
    double adj[100][100] = {0};
    int coords[100][2] = {{0, 0}, {3, 4}, {6, 0}};
    adj[0][1] = 5;
    adj[1][0] = 5;
    adj[1][2] = 5;
    adj[2][1] = 5;
    adj[0][2] = 6;
    adj[2][0] = 6;
    PathNode* result = findShortestPath2D(adj, coords, 0, 2, 0);
    checkResult("Test 20: Triangle shortcut 3-4-5", result, "(0, 0)->(6, 0)", 6.0);
    deletePathList(result);
}

// Tests 21-50 (simplified - add more as needed)
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
    cout << "   TASK 2: 2D Path Test Suite" << endl;
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
