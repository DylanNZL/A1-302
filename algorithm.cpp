#include "algorithm.h"
#include <string>
#include <algorithm> // check if vector contains a state
#include <vector> // for visited list
#include <iostream>

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

//===================================================
//                Heap Definitions
//===================================================
Heap::Heap() {
  last = -1;
  max = -1;
}

void Heap::insertIntoHeap(Puzzle *mData){
  ++last;
  data.push_back(mData);
  if(last == 0){ return; }
  int swappingIndex = last, parentIndex;
  bool swapping = true;
  while(swapping){
    swapping = false;
    if(swappingIndex%2 == 0){
      parentIndex = (swappingIndex/2) - 1;
    }else{
      parentIndex = (swappingIndex / 2);
    }
    if(parentIndex>=0){
      if(heapCompare(data[parentIndex], data[swappingIndex])){
        swap(data[swappingIndex], data[parentIndex]);
        swapping = true;
        swappingIndex = parentIndex;
    
      }
    }
  }
}

void Heap::deleteRoot(){
  if(last<0){return;}
  Puzzle * deletedValue = data[0];
  data[0] = data[last];
  data.pop_back();
  --last;
  int parIndex = 0, leftIndex = 1, rightIndex = 2;
  bool swapping = true;

  while((heapCompare(data[parIndex], data[leftIndex]) || (heapCompare(data[parIndex], data[rightIndex]))) && swapping){
    swapping = false;
    if(heapCompare(data[rightIndex], data[leftIndex])){
      swap(data[leftIndex], data[parIndex]);
      parIndex = leftIndex;
      swapping = true;
    } else {
      swap(data[rightIndex], data[parIndex]);
      parIndex = rightIndex;
      swapping = true;
    }
    leftIndex = parIndex*2+1;
    rightIndex = parIndex*2+2;
    if(leftIndex>last){ break; }
    else{
      if(rightIndex>last){
        if(heapCompare(data[parIndex], data[leftIndex])){
          swap(data[parIndex], data[leftIndex]);
        }
        break;
      }
    }
  } 
  return;
}

void Heap::print(){
  for(int i = 0; i< data.size();++i){
    cout<<data[i]->getFCost()<<": "<<data[i]->getString()<<endl;
  }
  return;
}

bool Heap::isEmpty(){
  if(last<0){ return true; }
  return false;
}

bool Heap::heapCompare(Puzzle* one, Puzzle* two){
  if(one->getFCost() > two->getFCost()) {return true;}
  return false;
}

int Heap::getIndex(Puzzle *mData){
  for(int i = 0;i<data.size();++i){
    if((data[i]->getString() == mData->getString()) && (data[i]->getFCost() == mData->getFCost())){
      return i;
    }
  }
  return -1;
}

bool Heap::deleteValue(Puzzle *dPuzzle){
  int index = getIndex(dPuzzle);
  if(index == -1){return false;}
  vector<Puzzle*> newData = data;
  newData.erase(newData.begin() + index);
  data.clear();
  last = 0;
  for(int i = 0;i<newData.size();++i){
    insertIntoHeap(newData[i]);
  }
  newData.clear();

  return true;

}

//=================================================
 // TODO: Alex
 // Hash function
//=================================================
Hash::Hash(){
	for(int i = 0; i < tableSize; ++i) {
		hashTable[i] = new item;
		hashTable[i]->value = "";
		hashTable[i]->cost = -1;
		hashTable[i]->next = nullptr;
	}
}

Hash::~Hash(){
  item *current, *temp;
  for(int i = 0; i < tableSize; ++i) {
    current = hashTable[i];
    while(current != nullptr){
      temp = current;
      current = current->next;
      delete temp;
    }
  }
}

int Hash::hashValue(string key){
	int hash=1;
	int num=0;
	for(int i = 0; i < 3; ++i){
		for(int j = 0; j < 3; ++j){
			num+=(int)key[((i+1)*(j+1))-1];
		}
		hash*= num;
		num = 0;
	}
	hash%=tableSize;
	return hash;
}

bool Hash::addValue(string value, int cost){
  int index = hashValue(value);
	if(hashTable[index]->value==""){
		hashTable[index]->value = value;
    hashTable[index]->cost = cost;
		return true;
	}
	item* current = hashTable[index];
  while (current->next != nullptr) {
    if (current->value == value) {
      if (current->cost > cost) {
        current->cost = cost;
        return true;
      } else if (current->cost == cost) {
        return true;
      }
		  return false;
    }
    current = current->next;
  }
  if (current->value == value){
    if (current->cost > cost) {
      current->cost = cost;
      return true;
    } else if (current->cost == cost){
      return true;
    }
    return false;
  }
	item* newItem = new item;
	current->next = newItem;
	newItem->value = value;
  newItem->cost = cost;
	newItem->next = nullptr;
  return true;
}

bool Hash::valueExists(string value){
	int index = hashValue(value);
	item* current = hashTable[index];
	while(current!=nullptr){
		if(current->value == value){
			return true;
		}
    current = current->next;
	}
  return false;
}

bool Hash::deleteValue(string value, int cost){
	int index = hashValue(value);

	item* current = hashTable[index];
	item* temp = nullptr;

	if(current->value==value && current->cost==cost){
		if(current->next==nullptr){
			current->value="";
      current->cost = -1;
			return true;
		}
		temp=current->next;
		current->value = temp->value;
    current->cost = temp->cost;
		current->next = temp->next;
		delete temp;
		return true;
	}
	temp = current;
	current=current->next;
	while(current!=nullptr){
		if(current->value==value && current->cost==cost){
			temp->next = current->next;
			delete current;
			return true;
		}
		temp = current;
		current = current->next;
	}
  return false;
}

//Print function will print each value in the Hash Table
void Hash::print(){
  item* current;
  int temp = 0;
  for(int i = 0; i < tableSize; ++i) {

    if(hashTable[i]->value != "") {
      temp = 0;
      cout<<"==================="<<endl;
      cout<<"Index: "<<i<<":"<<endl;
      cout<<"Node "<<temp<<endl;
      cout<<hashTable[i]->value<<endl;
      if(hashTable[i]->cost!=-1){
        cout<<"Cost: "<<hashTable[i]->cost<<endl;
      }
      cout<<"==================="<<endl;
      current = hashTable[i]->next;

      while(current!=nullptr){
        ++temp;
        cout<<"==================="<<endl;
        cout<<"Index: "<<i<<":"<<endl;
        cout<<"Node "<<temp<<endl;
        cout<<current->value<<endl;
        if(current->cost!=-1){
          cout<<"Cost: "<<current->cost<<endl;
        }
        cout<<"==================="<<endl;
        current = current->next;
      }
    }
  }
}

int Hash::getCost(string value){
  item *current;
  int index = hashValue(value);
  current = hashTable[index];
  while(current != nullptr){
    if(current->value == value){
      return current->cost;
    }
    current = current->next;
  }
  return -1;
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
    Hash H;
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
        if (H.addValue(p->getString())) {
          Q.addToBack(p);
        }
      }
      if (temp->canMoveRight() && temp->getPath()[temp->getPathLength() - 1] != 'L') {
        Puzzle *p = temp->moveRight();
        if (H.addValue(p->getString())) {
          Q.addToBack(p);
        }
      }
      if (temp->canMoveDown() && temp->getPath()[temp->getPathLength() - 1] != 'U') {
        Puzzle *p = temp->moveDown();
        if (H.addValue(p->getString())) {
          Q.addToBack(p);
        }
      }
      if (temp->canMoveLeft() && temp->getPath()[temp->getPathLength() - 1] != 'R') {
        Puzzle *p = temp->moveLeft();
        if (H.addValue(p->getString())) {
          Q.addToBack(p);
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
    Hash H;

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
            Puzzle *temp = OP->moveUp();
            if (H.addValue(temp->toString(), temp->getDepth())) {
                Q.addToFront(temp);
            }
        }
        if (OP->canMoveRight(depth) && OP->getPath()[OP->getPathLength() - 1] != 'L') {
            Puzzle *temp = OP->moveRight();
            if (H.addValue(temp->toString(), temp->getDepth())) {
                Q.addToFront(temp);
            }
        }
        if (OP->canMoveDown(depth) && OP->getPath()[OP->getPathLength() - 1] != 'U') {
            Puzzle *temp = OP->moveDown();
            if (H.addValue(temp->toString(), temp->getDepth())) {
                Q.addToFront(temp);
            }
        }
        if (OP->canMoveLeft(depth) && OP->getPath()[OP->getPathLength() - 1] != 'R') {
            Puzzle *temp = OP->moveLeft();
            if (H.addValue(temp->toString(), temp->getDepth())) {
                Q.addToFront(temp);
            }
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
    maxQLength = Q.getMax();
    numOfStateExpansions = loop;
    if (OP->goalMatch()) { path = OP->getPath(); }
    else { path = "DDRRLLLUUU"; } //this is just a dummy path for testing the function
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
    temp_puzzle->updateHCost(heuristic);
    temp_puzzle->updateFCost();

    H.insertIntoHeap(temp_puzzle);
    Hash e_list;
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
