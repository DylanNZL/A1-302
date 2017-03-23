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
void Queue::addToFront(Puzzle *data) {
  Node *temp = new Node(data);
  if (rear == NULL) { rear = temp; }
  if (front != NULL) {
    temp->next = front;
    front->prev = temp;
  }
  front = temp;
}

// Used for Breadth-First
void Queue::addToBack(Puzzle *data) {
  Node *temp = new Node(data);
  if (front == NULL) { front = temp; }
  if (rear != NULL) {
    rear->next = temp;
    temp->prev = rear;
  }
  rear = temp;
}

// Delete the first value in the queue and return it
Puzzle * Queue::leave() {
  Node * temp;
  temp = front;
  front = front->next;
  if (front == NULL) { rear = NULL; }

  Puzzle *deleted = temp->data;
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

void Heap::insertIntoHeap(Puzzle mData) {
   last++;
   // What to do with count & max?
   data.at(last) = mData;
   // First value in vector
   if (last == 0) { return; }
   int swappingIndex = last, parentIndex;
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
         Puzzle temp = data[swappingIndex];
         data.at(swappingIndex) = data.at(parentIndex);
         data.at(parentIndex) = temp;
         swapping = true;
         swappingIndex = parentIndex;
       }
     }
   }
}

Puzzle Heap::deleteFromHeap() {
   if (last == 0) { last--; return data.at(0); }

   // Save deleted root and move the last value in tree to the root
   Puzzle deleted = data.at(0);
   data.at(0) = data.at(last);
   data.at(last) = Puzzle("0","0"); last--;

   // Resort tree
   int leftIndex, rightIndex, parentIndex = 0;
   bool swapping = true;
   while (swapping) {
     swapping = false;
     leftIndex = (parentIndex * 2) + 1;
     rightIndex = (parentIndex * 2) + 2;

     Puzzle temp = data.at(parentIndex);

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
 bool Heap::heapCompare(Puzzle one, Puzzle two) {
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
 * Up, Right, Down, then Left
 */
 ////////////////////////////////////////////////////////////////////////////////////////////
 string breadthFirstSearch(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength, float &actualRunningTime) {
    string path;
	  clock_t startTime;
    //add necessary variables here
    Queue Q;
    //algorithm implementation
	  cout << "------------------------------" << endl;
    cout << "<<breadthFirstSearch>>" << endl;
    cout << "------------------------------" << endl;

	  startTime = clock();
	  maxQLength = 0;
    Puzzle * temp = new Puzzle(initialState, goalState);
    Q.addToBack(temp);
    int count = 0;
    while (!Q.isEmpty()) {
      temp = Q.leave();

      if (temp->goalMatch()) {
        break;
      }

      if (temp->canMoveUp()) {
        Q.addToBack(temp->moveUp());
      }
      if (temp->canMoveRight()) {
        Q.addToBack(temp->moveRight());
      }
      if (temp->canMoveDown()) {
        Q.addToBack(temp->moveDown());
      }
      if (temp->canMoveLeft()) {
        Q.addToBack(temp->moveLeft());
      }

      if (count % 1000 == 0) {
        cout << "state: " << count << endl;
      }
      count++;
  }

//***********************************************************************************************************
    if (temp->goalMatch()) { path = temp->getPath(); }
    else { path = "DDRRLLLUUU"; }//this is just a dummy path for testing the function
	  actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
	  return path;
}

///////////////////////////////////////////////////////////////////////////////////////////
//
// Search Algorithm:  Breadth-First Search with VisitedList
//
// Move Generator:
//
////////////////////////////////////////////////////////////////////////////////////////////
string breadthFirstSearch_with_VisitedList(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength, float &actualRunningTime) {
    string path;
	  clock_t startTime;
    //add necessary variables here
    Queue Q;
    vector<string> visited;
    //algorithm implementation
	  cout << "------------------------------" << endl;
    cout << "<<breadthFirstSearch_with_VisitedList>>" << endl;
    cout << "------------------------------" << endl;

	  startTime = clock();
	  maxQLength = 0;
    Puzzle * temp = new Puzzle(initialState, goalState);
    Q.addToBack(temp);
    int count = 0;
    while (!Q.isEmpty()) {
      temp = Q.leave();
      if (temp->goalMatch()) {
        break;
      }

      if (temp->canMoveUp()) {
        Puzzle *p = temp->moveUp();
        if (find(visited.begin(), visited.end(), p->strBoard) != visited.end()) {

        } else {
          Q.addToBack(temp->moveUp());
          visited.push_back(temp->strBoard);
        }
      }
      if (temp->canMoveRight()) {
        Puzzle *p = temp->moveRight();
        if (find(visited.begin(), visited.end(), p->strBoard) != visited.end()) {

        } else {
          Q.addToBack(temp->moveRight());
          visited.push_back(temp->strBoard);
        }
      }
      if (temp->canMoveDown()) {
        Puzzle *p = temp->moveDown();
        if (find(visited.begin(), visited.end(), p->strBoard) != visited.end()) {

        } else {
          Q.addToBack(temp->moveDown());
          visited.push_back(temp->strBoard);
        }
      }
      if (temp->canMoveLeft()) {
        Puzzle *p = temp->moveLeft();
        if (find(visited.begin(), visited.end(), p->strBoard) != visited.end()) {

        } else {
          Q.addToBack(temp->moveLeft());
          visited.push_back(temp->strBoard);
        }
      }
      if (count % 1000 == 0) {
        cout << "state: " << count << endl;
      }
      count++;
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
