#include "algorithm.h"
#include <string>
#include <algorithm> // check if vector contains a state
#include <vector> // for visited list

using namespace std;

/**
 * 6 & 1 might not work
 */
// Queue Definitions
// TODO: Dylan

Queue::Queue() {
  count = 0;  max = 0;
  front = NULL; rear = NULL;
}

Queue::~Queue() {
}

// Used for PDS
void Queue::addToFront(Puzzle *data) {
  count++;
  // If the current size of Q is bigger than the max size, increment max
  if (count > max) { max++; }
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
  count++;
  // If the current size of Q is bigger than the max size, increment max
  if (count > max) { max++; }
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
  if (count < 0) { cout << count << endl; }
  count--;
  Node * temp;
  temp = front;
  front = front->next;
  if (front == NULL) { rear = NULL; }

  Puzzle *deleted = temp->data;
  delete temp;

  return deleted;
}

bool Queue::isEmpty() {
  if (front == NULL) {
    return true;
  }
  return false;
}

int Queue::getCount() { return count; }

int Queue::getMax() { return max; }

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

bool Heap::isEmpty(){
  if (last<0){
    return true;
  }
  return false;
}

 // Comapare two strings and return true if two should be higher in the tree than one
 // TODO: Dylan
 bool Heap::heapCompare(Puzzle one, Puzzle two) {
   if (one.getFCost() < two.getFCost()) return true;
   return false;
 }

 // TODO: Alex
 // Hash function
Hash::Hash(){
	
	for(int i =0;i<tableSize;++i){
		hashTable[i] = new item;
		hashTable[i]->value = "";
		hashTable[i]->depth = -1;
		hashTable[i]->next = nullptr;
	}
}

int Hash::hashValue(string key){
	int total = 0;
	string temp ="";
	for(int i =0;i<key.length();++i){
		if(key[i] !='0'){
			temp = temp+key[i];
		}
	}
	int hash=1;
	int num=0;
	for(int i =0;i<3;++i){
		for(int j =0;j<3;++j){
			num+=(int)temp[j];
		}
		hash*= num;
		num = 0;
	}
	
	hash%=tableSize;
	return hash;
}

bool Hash::addValue(string value){
  int index = hashValue(value);
	
	if(hashTable[index]->value==""){
		hashTable[index]->value = value;
		return true;
	}
	
	item* current = hashTable[index]->next;
	if(current->value == value){
		return false;
	}
	while(current!=nullptr){
		current = current->next;
		if(current->value == value){
			return false;
		}
	}
	
	item* newItem = new item;
	current->next = newItem;
	newItem->value = value;
	newItem->next = nullptr;
	
  return true;
}

bool Hash::valueExists(string value){
	int index = hashValue(value);
	item* current = hashTable[index];
	while(current!=nullptr){
		current = current->next;
		if(current->value == value){
			return true;
		}
	}
  return false;
}


bool Hash::deleteValue(string value){
	int index = hashValue(value);
	
	item* current = hashTable[index];
	item* temp = nullptr;
	
	if(current->value==value){
		if(current->next==nullptr){
			current->value="";
			return true;
		}
		temp=current->next;
		current->value =temp->value;
		current->next = temp->next;
		delete temp;
		return true;
	}
	temp = current;
	current=current->next;
	while(current!=nullptr){
		if(current->value==value){
			temp->next = current->next;
			delete current;
			return true;
		}
		temp = current;
		current = current->next;
	}
  return false;
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
    int loop = 1;
    while (!Q.isEmpty()) {
      loop++;
      temp = Q.leave();

      if (temp->goalMatch()) {
        break;
      }

      if (temp->canMoveUp() && temp->getPath()[temp->getPathLength() - 1] != 'D') {
        Q.addToBack(temp->moveUp());
      }
      if (temp->canMoveRight() && temp->getPath()[temp->getPathLength() - 1] != 'L') {
        Q.addToBack(temp->moveRight());
      }
      if (temp->canMoveDown() && temp->getPath()[temp->getPathLength() - 1] != 'U') {
        Q.addToBack(temp->moveDown());
      }
      if (temp->canMoveLeft() && temp->getPath()[temp->getPathLength() - 1] != 'R') {
        Q.addToBack(temp->moveLeft());
      }
      delete temp;
      // DEBUG:
      /*if (loop % 10000 == 0) {
        cout << "state: " << loop << " current Q " << Q.getCount() << " maxQ: " << Q.getMax() << endl;
      }*/
  }
//***********************************************************************************************************
    if (temp->goalMatch()) { path = temp->getPath(); }
    else { path = "DDRRLLLUUU"; }//this is just a dummy path for testing the function
	  actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
    numOfStateExpansions = loop;
    maxQLength = Q.getMax();
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
	  maxQLength = 1;
    Puzzle * temp = new Puzzle(initialState, goalState);
    Q.addToBack(temp);
    int loop = 1;
    while (!Q.isEmpty()) {
      loop++;
      temp = Q.leave();
      if (temp->goalMatch()) {
        break;
      }

      if (temp->canMoveUp() && temp->getPath()[temp->getPathLength() - 1] != 'D') {
        Puzzle *p = temp->moveUp();
        if (find(visited.begin(), visited.end(), p->strBoard) == visited.end()) {
          Q.addToBack(p);
          visited.push_back(p->strBoard);
        }
      }
      if (temp->canMoveRight() && temp->getPath()[temp->getPathLength() - 1] != 'L') {
        Puzzle *p = temp->moveRight();
        if (find(visited.begin(), visited.end(), p->strBoard) == visited.end()) {
          Q.addToBack(p);
          visited.push_back(p->strBoard);
        }
      }
      if (temp->canMoveDown() && temp->getPath()[temp->getPathLength() - 1] != 'U') {
        Puzzle *p = temp->moveDown();
        if (find(visited.begin(), visited.end(), p->strBoard) == visited.end()) {
          Q.addToBack(p);
          visited.push_back(p->strBoard);
        }
      }
      if (temp->canMoveLeft() && temp->getPath()[temp->getPathLength() - 1] != 'R') {
        Puzzle *p = temp->moveLeft();
        if (find(visited.begin(), visited.end(), p->strBoard) == visited.end()) {
          Q.addToBack(p);
          visited.push_back(p->strBoard);
        }
      }
      delete temp;
      // DEBUG:
    /*  if (loop % 1000 == 0) {
        cout << " state: " << loop << " current Q " << Q.getCount() << " maxQ: " << Q.getMax() << " visited: " << visited.size() << endl;
      }
      */
  }
//***********************************************************************************************************
	  actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
    if (temp->goalMatch()) { path = temp->getPath(); }
    else { path = "DDRRLLLUUU"; } //this is just a dummy path for testing the function
    numOfStateExpansions = loop;
    maxQLength = Q.getMax();
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
    Queue Q;
    //algorithm implementation
	  cout << "------------------------------" << endl;
    cout << "<<progressiveDeepeningSearch_No_VisitedList>>" << endl;
    cout << "------------------------------" << endl;
	  startTime = clock();
    maxQLength = 1;
    int depth = 1, loop = 0;

    Puzzle *OP = new Puzzle (initialState, goalState);
    Q.addToFront(OP);
    while (!Q.isEmpty() && depth < ultimateMaxDepth) {
        loop++;
        OP = Q.leave();
        if (OP->goalMatch()) {
            break;
        }
        //cout << "OP depth is " << OP->getDepth() << " general depth is " << depth << OP->getPath() << " data is " << OP->toString() << endl;
        if (OP->canMoveUp(depth) && OP->getPath()[OP->getPathLength() - 1] != 'D') {
            Q.addToFront(OP->moveUp());
        }
        if (OP->canMoveRight(depth) && OP->getPath()[OP->getPathLength() - 1] != 'L') {
            Q.addToFront(OP->moveRight());
        }
        if (OP->canMoveDown(depth) && OP->getPath()[OP->getPathLength() - 1] != 'U') {
            Q.addToFront(OP->moveDown());
        }
        if (OP->canMoveLeft(depth) && OP->getPath()[OP->getPathLength() - 1] != 'R') {
            Q.addToFront(OP->moveLeft());
        }
        OP->updateDepth();
        /*if (loop % 1000000 == 0) {
          cout << " state: " << loop << " current Q " << Q.getCount() << " maxQ: " << Q.getMax() << " depth: " << depth << " current path = " << OP->getPath() << " data is " << OP->toString() << endl;
          //cout << "Solving equation... currently at state number: " << loop << " and depth: " << depth << endl;
        }*/
        delete OP;
        if (Q.isEmpty()) {
            depth++;
            Puzzle *OS = new Puzzle (initialState, goalState);
            OS->setDepth(0);
            Q.addToFront(OS);
        }
    }

//***********************************************************************************************************
    actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
    maxQLength = Q.getMax();
    numOfStateExpansions = loop;
    if (OP->goalMatch()) { path = OP->getPath(); }
    else { path = "DDRRLLLUUU"; } //this is just a dummy path for testing the function
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
	  startTime = clock();
    maxQLength = 1;
    int depth = 1, loop = 0;
    Queue Q;

    //vector<visited> v;

    struct visited {
        int vDepth = 0;
        string vData;
    };

    // visited list with depths assosiated
	  cout << "------------------------------" << endl;
    cout << "<<progressiveDeepeningSearch_with_NonStrict_VisitedList>>" << endl;
    cout << "------------------------------" << endl;

    Puzzle *OP = new Puzzle (initialState, goalState);
    Q.addToFront(OP);
    while (!Q.isEmpty() && depth < ultimateMaxDepth) {
        OP = Q.leave();
        if (OP->goalMatch()) {
            break;
        }
        //cout << "OP depth is " << OP->getDepth() << " general depth is " << depth << OP->getPath() << " data is " << OP->toString() << endl;
        if (OP->canMoveUp(depth) && OP->getPath()[OP->getPathLength() - 1] != 'D') {
            /*if (find(v.begin(), v.end(), OP->toString()) == v.end()) {
              if (OP->getDepth() < v.vDepth) {
                Q.addToFront(OP->moveUp());
              }
            }*/
        }
        if (OP->canMoveRight(depth) && OP->getPath()[OP->getPathLength() - 1] != 'L') {
            Q.addToFront(OP->moveRight());
        }
        if (OP->canMoveDown(depth) && OP->getPath()[OP->getPathLength() - 1] != 'U') {
            Q.addToFront(OP->moveDown());
        }
        if (OP->canMoveLeft(depth) && OP->getPath()[OP->getPathLength() - 1] != 'R') {
            Q.addToFront(OP->moveLeft());
        }
        OP->updateDepth();
        if (loop % 1000000 == 0) {
          cout << " state: " << loop << " current Q " << Q.getCount() << " maxQ: " << Q.getMax() << " depth: " << depth << " current path = " << OP->getPath() << " data is " << OP->toString() << endl;
          //cout << "Solving equation... currently at state number: " << loop << " and depth: " << depth << endl;
        }
        delete OP;
        loop++;
        if (Q.isEmpty()) {
            depth++;
            Puzzle *OS = new Puzzle (initialState, goalState);
            OS->setDepth(0);
            Q.addToFront(OS);
        }
    }
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
    cout << "------------------------------" << endl;
    cout << "<<aStar_ExpandedList>>" << endl;
    cout << "------------------------------" << endl;

	  actualRunningTime = 0.0;
	  startTime = clock();
	  maxQLength = 0;
//***********************************************************************************************************

    Heap H;
    Puzzle *temp_puzzle = new Puzzle(initialState, goalState);
    H.insertIntoHeap(*temp_puzzle);
    vector<string> e_list;
    int loop = 0;

    while(!H.isEmpty()){




      if(temp_puzzle->canMoveUp() && temp_puzzle->getLastDirec() != 'D'){

      }
      if(temp_puzzle->canMoveRight() && temp_puzzle->getLastDirec() != 'L'){

      }
      if(temp_puzzle->canMoveDown() && temp_puzzle->getLastDirec() != 'U'){

      }
      if(temp_puzzle->canMoveLeft() && temp_puzzle->getLastDirec() != 'R'){

      }

    } //H is empty

	  actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
	  path = "DDRRLLLUUU"; //this is just a dummy path for testing the function
	  return path;
}
