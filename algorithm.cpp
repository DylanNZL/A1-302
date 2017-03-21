#include "algorithm.h"
#include <vector>

using namespace std;

/**
 * 6 & 1 might not work
 */

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
 // TODO: Alex
 // Hash function
 string hash(string toHash) {
   return toHash;
 }
///////////////////////////////////////////////////////////////////////////////////////////
//
// Search Algorithm:  Breadth-First Search
//
// Move Generator:
//
/**
 * Steps:
 * 1. Initialise Q with search node (S) as only entry; set Visited = (S).​
 * 2. If Q is empty, fail.  Else, pick FIRST node N from Q.​
 * 3. If state (N) is a goal, return N (we’ve reached the goal).​
 * 4. (Otherwise) Remove N from Q.
 * 5. Find all the descendants of state (N) not in Visited and create all the one-step extensions of N to each descendant.
 * 6. Add the extended paths to END of Q; add children of state (N) to Visited.
 * 7. Go to Step 2
 */
 ////////////////////////////////////////////////////////////////////////////////////////////
string breadthFirstSearch(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength, float &actualRunningTime) {
    string path;
	  clock_t startTime;
    //add necessary variables here
    Queue Q;
    string temp;
    //algorithm implementation
	  // cout << "------------------------------" << endl;
    // cout << "<<breadthFirstSearch>>" << endl;
    // cout << "------------------------------" << endl;

	  startTime = clock();
	  maxQLength = 0;
    Q.addToBack(initialState);
    // While queue is not empty search for goal state
    while (!Q.isEmpty()) {
      if (Q.getFront() == goalState) {
        break;
      }
      else {
        temp = Q.getFront();
        if (temp == goalState) {
          break;
        }
        // add temps children to Q
      }
    }

//***********************************************************************************************************
	  actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
	  path = "DDRRLLLUUU";  //this is just a dummy path for testing the function
	  return path;
}

///////////////////////////////////////////////////////////////////////////////////////////
//
// Search Algorithm:  Breadth-First Search with VisitedList
//
// Move Generator:
/**
 *
 */
//
////////////////////////////////////////////////////////////////////////////////////////////
string breadthFirstSearch_with_VisitedList(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength, float &actualRunningTime) {
    string path;
	  clock_t startTime;
    //add necessary variables here
    Queue Q;
    string temp;
    vector<string> visited;
    //algorithm implementation
	  // cout << "------------------------------" << endl;
    //    cout << "<<breadthFirstSearch_with_VisitedList>>" << endl;
    //    cout << "------------------------------" << endl;
	  startTime = clock();
	  maxQLength = 0;
    Q.addToBack(initialState);

    while (!Q.isEmpty()) {
      temp = Q.getFront();
      if (temp == goalState) {
        break;
      }
      // add temps children to Q if their states aren't in the visited list, add each child state to visited list
    }
//***********************************************************************************************************
	  actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
	  path = "DDRRLLLUUU";  //this is just a dummy path for testing the function
	  return path;
}

///////////////////////////////////////////////////////////////////////////////////////////
//
// Search Algorithm:
//
// Move Generator:
//
////////////////////////////////////////////////////////////////////////////////////////////
string progressiveDeepeningSearch_No_VisitedList(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength, float &actualRunningTime, int ultimateMaxDepth){
    string path;
	  clock_t startTime;
    //add necessary variables here
    // Q
    // Depth
    //algorithm implementation
	  // cout << "------------------------------" << endl;
    //    cout << "<<progressiveDeepeningSearch_No_VisitedList>>" << endl;
    //    cout << "------------------------------" << endl;
	  startTime = clock();
    maxQLength = 0;
//***********************************************************************************************************
	  actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
	  path = "DDRRLLLUUU";  //this is just a dummy path for testing the function
	  return path;
}

///////////////////////////////////////////////////////////////////////////////////////////
//
// Search Algorithm:
//
// Move Generator:
//
////////////////////////////////////////////////////////////////////////////////////////////
string progressiveDeepeningSearch_with_NonStrict_VisitedList(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength, float &actualRunningTime, int ultimateMaxDepth){
    string path;
	  clock_t startTime;
    //add necessary variables here
    // Q
    // visited list with depths assosiated
    // depth
    //algorithm implementation
	  // cout << "------------------------------" << endl;
    //    cout << "<<progressiveDeepeningSearch_with_NonStrict_VisitedList>>" << endl;
    //    cout << "------------------------------" << endl;
	  startTime = clock();
	  maxQLength = 0;
//***********************************************************************************************************
    actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
    path = "DDRRLLLUUU"; //this is just a dummy path for testing the function
	  return path;
}

//TODO: Alex
string aStar_ExpandedList(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength,
                               float &actualRunningTime, int &numOfDeletionsFromMiddleOfHeap, int &numOfLocalLoopsAvoided, int &numOfAttemptedNodeReExpansions, heuristicFunction heuristic){
		string path;
    clock_t startTime;
    numOfDeletionsFromMiddleOfHeap = 0;
    numOfLocalLoopsAvoided = 0;
    numOfAttemptedNodeReExpansions = 0;
    // cout << "------------------------------" << endl;
    // cout << "<<aStar_ExpandedList>>" << endl;
    // cout << "------------------------------" << endl;
	  actualRunningTime = 0.0;
	  startTime = clock();
	  maxQLength = 0;
//***********************************************************************************************************
	  actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
	  path = "DDRRLLLUUU"; //this is just a dummy path for testing the function
	  return path;
}
