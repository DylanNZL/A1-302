
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
// Queue class
// Add to front(PDS) & back(breadth)
// Take from front
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
  int getCount() { return count; }
  int getMax() { return max; }
};

void Queue::addToFront(string data) {
  Node *temp = new Node(data);
  if (rear == NULL) { rear = temp; }
  if (front != NULL) {
    temp->next = front;
    front->prev = temp;
  }
  front = temp;
}

void Queue::addToBack(string data) {
  Node *temp = new Node(data);
  if (front == NULL) { front = temp; }
  if (rear != NULL) {
    rear->next = temp;
    temp->prev = rear;
  }
  rear = temp;
}

void Queue::leave() {
  Node * temp;
  if (front == NULL) { return; }
  temp = front;
  front = front->next;
  if (front == NULL) { rear = NULL; }
  delete temp;
  count--;
}

string Queue::getFront() {
  if (front != NULL) { return front->data; }
  return "0";
}

bool Queue::isEmpty() {
  if (front == NULL) {
    return true;
  }
  return false;
}

// TODO: Dylan
// Heap class
// A*
class Heap {
private:
  vector<string> data;
  int last, max;
public:
  Heap() {
    last = -1;
    max = -1;
  }
  ~Heap() {}
  void insertIntoHeap(string mData);
  string deleteFromHeap();
  bool heapCompare(string one, string two);
  int getMax() { return max; }
};

void Heap::insertIntoHeap(string mData) {
  last++;
  // What to do with count & max?
  data.at(last) = mData;
  // First value in vector
  if (last == 0) { return; }
  int swappingIndex = last, parentIndex;
  string temp;
  bool swapping = true;
  while (swapping) {
    swapping = false;
    // Find which side it is
    if (swappingIndex % 2 == 0) {
      parentIndex = (swappingIndex / 2) - 1; // right
    } else {
      parentIndex = (swappingIndex / 2); // left
    }
    // do the swap if needed
    if (parentIndex >= 0) {
      // Check if the swappingIndex should be higher in the tree
      if (heapCompare(data.at(parentIndex), data.at(swappingIndex))) {
        temp = data[swappingIndex];
        data.at(swappingIndex) = data.at(parentIndex);
        data.at(parentIndex) = temp;
        swapping = true;
        swappingIndex = parentIndex;
      }
    }
  }
}

string Heap::deleteFromHeap() {
  if (last == 0) { last--; return data.at(0); }

  // Save deleted root and move the last value in tree to the root
  string deleted = data.at(0);
  data.at(0) = data.at(last);
  data.at(last) = "0"; last--;

  // Resort tree
  int leftIndex, rightIndex, parentIndex = 0;
  string temp;
  bool swapping = true;
  while (swapping) {
    swapping = false;
    leftIndex = (parentIndex * 2) + 1;
    rightIndex = (parentIndex * 2) + 2;

    temp = data.at(parentIndex);

    // Check if left or right is bigger than parent
    if (heapCompare(data.at(parentIndex), data.at(leftIndex)) || heapCompare(data.at(parentIndex), data.at(rightIndex))) {
      swapping = true;
      // right is bigger
      if (heapCompare(data.at(leftIndex), data.at(rightIndex))) {
        data.at(parentIndex) = data.at(rightIndex);
        data.at(rightIndex) = temp;
        parentIndex = rightIndex;
      }
      //  left is bigger
      else {
        data.at(parentIndex) = data.at(leftIndex);
        data.at(leftIndex) = temp;
        parentIndex = leftIndex;
      }
    }
  }
}

// Comapare two strings and return true if two should be higher in the tree than one
// TODO: Dylan
bool Heap::heapCompare(string one, string two) {
  return true;
}

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
