#include "PathNode.h"
#include <iostream>

PathNode::PathNode(std::string nodeName, double fVal, double gVal, double hVal)
    : name(nodeName), f(fVal), g(gVal), h(hVal), next(nullptr) {}

PathNode *createPathNode(std::string name, double f, double g, double h) {
  PathNode *node = new PathNode(name, f, g, h);
  return node;
}

void appendNode(PathNode *&head, PathNode *&tail, std::string name, double f,
                double g, double h) {
  PathNode *newNode = createPathNode(name, f, g, h);
  if (head == nullptr) {
    head = tail = newNode;
  } else {
    tail->next = newNode;
    tail = newNode;
  }
}

void deletePathList(PathNode *head) {
  while (head != nullptr) {
    PathNode *temp = head;
    head = head->next;
    delete temp;
  }
}

PathNode *reversePathList(PathNode *head) {
  PathNode *prev = nullptr;
  PathNode *current = head;
  PathNode *next = nullptr;

  while (current != nullptr) {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }

  return prev;
}

void printPath(PathNode *head) {
  std::cout << "Solution Path:\n";
  while (head != nullptr) {
    std::cout << "Node: " << head->name << " | f: " << head->f
              << " | g: " << head->g << " | h: " << head->h << "\n";
    head = head->next;
  }
}
