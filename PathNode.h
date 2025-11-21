#ifndef PATHNODE_H
#define PATHNODE_H

#include <string>

struct PathNode {
  std::string name;
  double f;
  double g;
  double h;
  PathNode *next;

  // Constructor
  PathNode(std::string nodeName = "", double fVal = 0.0, double gVal = 0.0,
           double hVal = 0.0);
};

// Helper functions
PathNode *createPathNode(std::string name, double f, double g, double h);
void appendNode(PathNode *&head, PathNode *&tail, std::string name, double f,
                double g, double h);
void deletePathList(PathNode *head);
PathNode *reversePathList(PathNode *head);
void printPath(PathNode *head);
#endif // PATHNODE_H
