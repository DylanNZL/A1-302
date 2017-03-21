
#ifndef __ALGORITHM_H__
#define __ALGORITHM_H__

#include <ctime>
#include <string>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <vector>

#include "puzzle.h"

struct Node {
  Node() {}
  Node(string mData) : data(mData), next(NULL), prev(NULL) {}
  Node(string mData, Node *mNext, Node *mPrev) : data(mData), next(mNext), prev(mPrev) {}
  string data;
  Node *next, *prev;
};

// TODO Dylan
class Queue {
private:
  Node *front, *rear;
  int count, max;
public:
  Queue();
  ~Queue();
  void addToFront(string data);
  void addToBack(string data);
  void leave();
  string getFront();
  bool isEmpty();
  int getCount();
  int getMax();
};

// TODO: Dylan
// Heap class
// A*
class Heap {
private:
  vector<string> data;
  int last, max;
public:
  Heap();
  ~Heap();
  void insertIntoHeap(string mData);
  string deleteFromHeap();
  bool heapCompare(string one, string two);
  int getMax() { return max; }
};

string hash(string toHash);

const heuristicFunction HEURISTIC_FUNCTION=manhattanDistance;


//Function prototypes
string progressiveDeepeningSearch_No_VisitedList(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength, float &actualRunningTime, int ultimateMaxDepth);
string progressiveDeepeningSearch_with_NonStrict_VisitedList(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength, float &actualRunningTime, int ultimateMaxDepth);

string breadthFirstSearch_with_VisitedList(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength, float &actualRunningTime);
string breadthFirstSearch(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength, float &actualRunningTime);

string aStar_ExpandedList(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength,
                               float &actualRunningTime, int &numOfDeletionsFromMiddleOfHeap, int &numOfLocalLoopsAvoided, int &numOfAttemptedNodeReExpansions, heuristicFunction heuristic);

#endif
