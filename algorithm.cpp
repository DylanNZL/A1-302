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
      // Check if the 
    }
  }
}

string Heap::deleteFromHeap() {

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

    // Q

    //algorithm implementation
	  // cout << "------------------------------" << endl;
    // cout << "<<breadthFirstSearch>>" << endl;
    // cout << "------------------------------" << endl;
	  startTime = clock();
	  maxQLength = 0;

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
    // Q
    // visited list
    //algorithm implementation
	  // cout << "------------------------------" << endl;
    //    cout << "<<breadthFirstSearch_with_VisitedList>>" << endl;
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
