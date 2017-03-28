#include "puzzle.h"
#include  <cmath>
#include  <assert.h>

using namespace std;

//////////////////////////////////////////////////////////////
//constructor
//////////////////////////////////////////////////////////////
Puzzle::Puzzle(const Puzzle &p) : path(p.path) {
	for(int i=0; i < 3; i++){
		for(int j=0; j < 3; j++){
		    board[i][j] = p.board[i][j];
		    goalBoard[i][j] = p.goalBoard[i][j];
		}
	}
	x0 = p.x0;
	y0 = p.y0;
	pathLength = p.pathLength;
	hCost = p.hCost;
	fCost = p.fCost;
	strBoard = toString(); //uses the board contents to generate the string equivalent
	depth = p.depth;
}

//////////////////////////////////////////////////////////////
//constructor
//inputs:  initial state, goal state
//////////////////////////////////////////////////////////////
Puzzle::Puzzle(string const elements, string const goal) {
	int n = 0;
	for(int i=0; i < 3; i++) {
		for(int j=0; j < 3; j++) {
		    board[i][j] = elements[n] - '0';
		    if(board[i][j] == 0){
			    x0 = j;
			    y0 = i;
			 }
		    n++;
		}
	}
	///////////////////////
	n = 0;
	for(int i=0; i < 3; i++){
		for(int j=0; j < 3; j++){
		    goalBoard[i][j] = goal[n] - '0';
		    n++;
		}
	}
	///////////////////////
	path = "";
	pathLength=0;
	hCost = 0;
	fCost = 0;
	depth = 0;
	strBoard = toString();
}


void Puzzle::setDepth(int d) {
	depth = d;
}

int Puzzle::getDepth() {
	return depth;
}

void Puzzle::updateHCost(heuristicFunction hFunction) {
	hCost = h(hFunction);
}

void Puzzle::updateDepth(){
 depth++;
}

void Puzzle::updateFCost() {
	fCost = hCost + pathLength;
}

int Puzzle::getFCost() {
	return fCost;
}

int Puzzle::getHCost() {
	return hCost;
}

int Puzzle::getGCost() {
	return pathLength;
}

// TODO: A*
//Heuristic function implementation
int Puzzle::h(heuristicFunction hFunction) {
	int sum=0;
	int h=0;
	int numOfMisplacedTiles=0;

	switch(hFunction) { 
		case misplacedTiles:
						//place your implementation here
			//Loop through board and compare with goal board for number of misplaced tiles
			for(int i =0;i<3;++i){
				for(int j = 0;j<3;++j){
					if(board[i][j]!= 0 && board[i][j]!=goalBoard[i][j]){ //ignore empty space in board(0)
						++numOfMisplacedTiles;
					}
				}//end j
			}//end i

            h = numOfMisplacedTiles;
		    break;

		//Case for finding manhatten distance of current board compared to goalboard
		case manhattanDistance:
		        //place your implementation here
			for(int x1 =0;x1<3;++x1){
				for(int y1 = 0;y1<3;++y1){
					if(board[x1][y1]!=0 && board[x1][y1]!=goalBoard[x1][y1]){//ignore empty space in board(0)
						//continue until match is found in GoalBoard
						for(int x2 = 0;x2<3; ++x2){
							for(int y2 = 0;x2<3; ++y2){
								if(board[x1][y1] == goalBoard[x2][y2]){
									sum += (abs(x1-x2)+abs(y1-y2));//Calc manhatten distance with sum of(|x1-x2| + |y1-y2|) 
								}
							}//end loop y2
						}//end loop x2
					}
				}//end loop y1
			}//end loop x1
		    h = sum;
		    break;
	};
	return h;
}


//converts board state into its string representation
string Puzzle::toString() {
  int n = 0;
  string stringPath;
  for(int i=0; i < 3; i++) {
		for(int j=0; j < 3; j++) {
		    stringPath.insert(stringPath.end(), board[i][j] + '0');
		    n++;
		}
  }
//  cout << "toString = " << stringPath << endl;
  return stringPath;
}

string Puzzle::getString() {
	return strBoard;
}

bool Puzzle::goalMatch() {
	for(int i=0; i < 3; i++) {
		for(int j=0; j < 3; j++) {
			if (board[i][j] != goalBoard[i][j]) return false;
		}
  }
	return true;
}

const string Puzzle::getPath() {
	return path;
}

bool Puzzle::canMoveLeft() {
   return (x0 > 0);
}

bool Puzzle::canMoveRight() {
   return (x0 < 2);
}

bool Puzzle::canMoveUp() {
   return (y0 > 0);
}

bool Puzzle::canMoveDown() {
   return (y0 < 2);
}

///////////////////////////////////////////////
//these functions will be useful for Progressive Deepening Search

bool Puzzle::canMoveLeft(int maxDepth) {
		//put your implementations here
		if (depth < maxDepth) {
				return (x0 > 0);
		} else {
				return false;
		}
}

bool Puzzle::canMoveRight(int maxDepth) {
	//put your implementations here
	if (depth < maxDepth) {
			return (x0 < 2);
	} else {
			return false;
	}
}

bool Puzzle::canMoveUp(int maxDepth) {
	//put your implementations here
	if (depth < maxDepth) {
			return (y0 > 0);
	} else {
			return false;
	}
}

bool Puzzle::canMoveDown(int maxDepth) {
	//put your implementations here
	if (depth < maxDepth) {
			return (y0 < 2);
	} else {
			return false;
	}
}

///////////////////////////////////////////////

Puzzle *Puzzle::moveLeft() {
	Puzzle *p = new Puzzle(*this);
   if(x0 > 0) {
		p->board[y0][x0] = p->board[y0][x0-1];
		p->board[y0][x0-1] = 0;
		p->x0--;
		p->path = path + "L";
		p->pathLength = pathLength + 1;
		p->depth = depth + 1;
	}
	p->strBoard = p->toString();

	return p;
}

Puzzle *Puzzle::moveRight() {
   Puzzle *p = new Puzzle(*this);
   if(x0 < 2) {
		p->board[y0][x0] = p->board[y0][x0+1];
		p->board[y0][x0+1] = 0;
		p->x0++;
		p->path = path + "R";
		p->pathLength = pathLength + 1;
		p->depth = depth + 1;
	}
	p->strBoard = p->toString();

	return p;
}

Puzzle *Puzzle::moveUp() {
   Puzzle *p = new Puzzle(*this);
   if(y0 > 0) {
		p->board[y0][x0] = p->board[y0-1][x0];
		p->board[y0-1][x0] = 0;
		p->y0--;
		p->path = path + "U";
		p->pathLength = pathLength + 1;
		p->depth = depth + 1;
	}
	p->strBoard = p->toString();

	return p;
}

Puzzle *Puzzle::moveDown() {
   Puzzle *p = new Puzzle(*this);
   if(y0 < 2) {
		p->board[y0][x0] = p->board[y0+1][x0];
		p->board[y0+1][x0] = 0;
		p->y0++;
		p->path = path + "D";
		p->pathLength = pathLength + 1;
		p->depth = depth + 1;
	}
	p->strBoard = p->toString();

	return p;
}

/////////////////////////////////////////////////////

void Puzzle::printBoard() {
	cout << "board: "<< endl;
	for(int i=0; i < 3; i++){
		for(int j=0; j < 3; j++){
		  cout << endl << "board[" << i << "][" << j << "] = " << board[i][j];
		}
	}
	cout << endl;
}

int Puzzle::getPathLength() {
	return pathLength;
}
