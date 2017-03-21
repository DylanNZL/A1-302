#include "algorithm.h"

using namespace std;

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

    // QUEUE for Q
    // Visited list ?? Vector?

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
//
////////////////////////////////////////////////////////////////////////////////////////////
string breadthFirstSearch_with_VisitedList(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength, float &actualRunningTime) {
    string path;
	  clock_t startTime;
    //add necessary variables here

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
