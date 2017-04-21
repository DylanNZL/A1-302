
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
  Node(Puzzle *&mData) : data(mData), next(nullptr), prev(nullptr) {}
  Puzzle *data;
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
  void addToFront(Puzzle *data);
  void addToBack(Puzzle *data);
  Puzzle * leave();
  bool isEmpty();
  int getCount();
  int getMax();
};

// TODO: Dylan
// Heap class
// A*
class Heap {
private:
  vector<Puzzle*> data;
  int last, max;
  void deleteValue(int index);
  void fixHeapDown(int index);
  void fixHeapUp(int index);
public:
  Heap();
  ~Heap(){ data.clear(); };
  void insertIntoHeap(Puzzle *mData);
  bool isEmpty();
  bool heapCompare(Puzzle* one, Puzzle* two);
  void deleteRoot();
  Puzzle* getFront();
  int getMax() { return max; }
  bool replaceAndInsert(Puzzle *mPuzzle);
};

class Hash{
private:
  static const int tableSize = 1024;
  struct item{
    string value;
	  int cost;
    item *next;
  };
  item *hashTable[tableSize];
  int hashValue(string key);
public:
  Hash();
  ~Hash();
	bool addValue (string value, int cost = -1);
  bool valueExists(string value);
	bool deleteValue(string value, int cost = -1);
  int getCost(string value);
  void clear();
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
