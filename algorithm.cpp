#include "algorithm.h"
#include <algorithm> // check if vector contains a state
#include <vector> // for visited list

using namespace std;

/**
 * 6 & 1 might not work
 */
// Queue Definitions
// TODO: Dylan

Queue::Queue() {
  count = -1;  max = -1;
  front = NULL; rear = NULL;
}

Queue::~Queue(){
}

// Used for PDS
void Queue::addToFront(string data) {
  Node *temp = new Node(data);
  if (rear == NULL) { rear = temp; }
  if (front != NULL) {
    temp->next = front;
    front->prev = temp;
  }
  front = temp;
}

// Used for Breadth-First
void Queue::addToBack(string data) {
  Node *temp = new Node(data);
  if (front == NULL) { front = temp; }
  if (rear != NULL) {
    rear->next = temp;
    temp->prev = rear;
  }
  rear = temp;
}

// Delete the first value in the queue and return it
string Queue::leave() {
  Node * temp;
  if (front == NULL) { return "0"; }
  temp = front;
  front = front->next;
  if (front == NULL) { rear = NULL; }

  string deleted = temp->data;
  delete temp;
  count--;

  return deleted;
}

bool Queue::isEmpty() {
  if (front == NULL) {
    return true;
  }
  return false;
}

// Heap Definitions
Heap::Heap() {
  last = -1;
  max = -1;
}

Heap::~Heap() {
}

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

// Move the '0' in the string left by one place.
 string moveLeft(string temp, int pos) {
   char zero = temp[pos];
   temp[pos] = temp [pos-1];
   temp[pos-1] = zero;
 }
 // Move the '0' in the string up by one place.
 string moveUp(string temp, int pos) {
   char zero = temp[pos];
   temp[pos] = temp [pos-3];
   temp[pos-3] = zero;
 }
 // Move the '0' in the string right by one place.
 string moveRight(string temp, int pos) {
   char zero = temp[pos];
   temp[pos] = temp [pos+1];
   temp[pos+1] = zero;
 }
 // Move the '0' in the string down by one place.
 string moveDown(string temp, int pos){
   char zero = temp[pos];
   temp[pos] = temp [pos+3];
   temp[pos+3] = zero;
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
      temp = Q.leave();
      if (temp == goalState) {
        break;
      }

      string right = "0", up = "0", left = "0", down = "0";
      if (temp[0] == '0') {
        right = moveRight(temp, 0);
        down = moveDown(temp, 0);
      }
      else if (temp[1] == '0') {
        left = moveLeft(temp, 1);
        right = moveRight(temp, 1);
        down = moveDown(temp, 1);
      }
      else if (temp[2] == '0') {
        left = moveLeft(temp, 2);
        down = moveDown(temp, 2);
      }
      else if (temp[3] == '0') {
        up = moveUp(temp, 3);
        right = moveRight(temp, 3);
        down = moveDown(temp, 3);
      }
      else if (temp[4] == '0') {
        left = moveLeft(temp, 4);
        up = moveUp(temp, 4);
        right = moveRight(temp, 4);
        down = moveDown(temp, 4);
      }
      else if (temp[5] == '0') {
        left = moveLeft(temp, 5);
        up = moveUp(temp, 5);
        down = moveDown(temp, 5);
      }
      else if (temp[6] == '0') {
        up = moveUp(temp, 6);
        right = moveRight(temp, 6);
      }
      else if (temp[7] == '0') {
        left = moveLeft(temp, 7);
        up = moveUp(temp, 7);
        right = moveRight(temp, 7);
      }
      else if (temp[8] == '0') {
        left = moveLeft(temp, 8);
        up = moveUp(temp, 8);
      }

      // Add new states to Q
      if (left != "0") {
        Q.addToBack(left);
      }
      if (up != "0") {
        Q.addToBack(up);
      }
      if (right != "0") {
        Q.addToBack(right);
      }
      if (down != "0") {
        Q.addToBack(down);
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
      temp = Q.leave();
      if (temp == goalState) {
        break;
      }

      string right = "0", up = "0", left = "0", down = "0";
      if (temp[0] == '0') {
        right = moveRight(temp, 0);
        down = moveDown(temp, 0);
      }
      else if (temp[1] == '0') {
        left = moveLeft(temp, 1);
        right = moveRight(temp, 1);
        down = moveDown(temp, 1);
      }
      else if (temp[2] == '0') {
        left = moveLeft(temp, 2);
        down = moveDown(temp, 2);
      }
      else if (temp[3] == '0') {
        up = moveUp(temp, 3);
        right = moveRight(temp, 3);
        down = moveDown(temp, 3);
      }
      else if (temp[4] == '0') {
        left = moveLeft(temp, 4);
        up = moveUp(temp, 4);
        right = moveRight(temp, 4);
        down = moveDown(temp, 4);
      }
      else if (temp[5] == '0') {
        left = moveLeft(temp, 5);
        up = moveUp(temp, 5);
        down = moveDown(temp, 5);
      }
      else if (temp[6] == '0') {
        up = moveUp(temp, 6);
        right = moveRight(temp, 6);
      }
      else if (temp[7] == '0') {
        left = moveLeft(temp, 7);
        up = moveUp(temp, 7);
        right = moveRight(temp, 7);
      }
      else if (temp[8] == '0') {
        left = moveLeft(temp, 8);
        up = moveUp(temp, 8);
      }

      // Check if the state is in visited, if not add it to Q and visited
      //
      if ((left != "0") && !(find(visited.begin(), visited.end(), left) != visited.end())) {
        Q.addToBack(left);
        visited.push_back(left);
      }
      if ((up != "0") && !(find(visited.begin(), visited.end(), up) != visited.end())) {
        Q.addToBack(up);
        visited.push_back(up);
      }
      if ((right != "0") && !(find(visited.begin(), visited.end(), right) != visited.end())) {
        Q.addToBack(right);
        visited.push_back(right);
      }
      if ((down != "0") && !(find(visited.begin(), visited.end(), down) != visited.end())) {
        Q.addToBack(down);
        visited.push_back(down);
      }
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
