/*
 * Board.h
 *
 *  Created on: 25/02/2022
 *      Author: dongmo
 * 		Editor: Eric Nguyen
 */

#ifndef BOARD_H_
#define BOARD_H_

class Board {
private:
	int row, col;
	int player; //1 = white; -1 = black
	int **grid; // 0 = empty; other values for pip count; positive for white; negative for black

public:
	vector<int> emptyIndex;
	Board(int r, int c) :
			row(r), col(c) {
		grid = new int*[row];
		for (int i = 0; i < row; i++)
			grid[i] = new int[col];

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				grid[i][j] = 0;
				emptyIndex.push_back(i*col+j);
			}
		}
		player = 1; // white has the first turn
	}

	~Board() {
		for (int i = 0; i < row; i++)
			delete[] grid[i];
		delete[] grid;
	}

	Board(const Board &cboard) {//Copy constructor
		row = cboard.row;
		col = cboard.col;

		grid = new int*[row];
		for (int i = 0; i < row; i++)
			grid[i] = new int[col];

		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++) {
				grid[i][j] = cboard.grid[i][j];
			}
		emptyIndex = cboard.emptyIndex;
		player = cboard.getTurn();
	}

	bool isBoardFull() {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if(grid[i][j] == 0)
					return false;
			}
		}
		return true;
	}

	int getTurn() const {
		return player;
	}

	bool validMove(int x, int y);

	bool addMove(int player, int x, int y);

	int checkWinningStatus();

	void printBoard();

	int capturingPlacement(int, int);

	int getCol();
	
	int getRow();

	void deleteIndex(int k); //For delete empty cell
	
	int capturingProcessing(unordered_map<string,Cell>);

	void clearCell(int, int);

	double heuristic();
};

int Board::capturingPlacement(int x, int y) {
	int index = x*col+y;
	int sum = 0;
	unordered_map<string,Cell> neighbor;

	if (x>0)
		if (grid[x-1][y] != 0){
			Cell c(x-1,y,abs(grid[x-1][y]));
			neighbor["up"] = c;
			sum = sum + neighbor["up"].value;
		}		

	if (x<row-1)
		if (grid[x+1][y] != 0){
			Cell c(x+1,y,abs(grid[x+1][y]));
			neighbor["down"] = c;
			sum = sum + neighbor["down"].value;
		}

	if (y>0)
		if (grid[x][y-1] != 0){
			Cell c(x,y-1,abs(grid[x][y-1]));
			neighbor["left"] = c;
			sum = sum + neighbor["left"].value;
		}	

	if (y<col-1){
		if (grid[x][y+1] != 0){
			Cell c(x,y+1,abs(grid[x][y+1]));
			neighbor["right"] = c;
			sum = sum + neighbor["right"].value;
		}	
	}

	if (neighbor.size()<2) //Case 1
		return 1;

	if (neighbor.size()==2) //Case 2
		if (sum>6) return 1;
		else {
			for (auto i:neighbor)
				clearCell(i.second.x,i.second.y);
			return sum;
		}
	//Else Case 3
	if (sum>=24) return 1;
	if (sum<=6){
		for (auto i:neighbor)
			clearCell(i.second.x,i.second.y);
	}
	else sum = capturingProcessing(neighbor);

	return sum;
}

int Board::checkWinningStatus() {
	if (!isBoardFull())
		return -2; //error message

	int counter = 0;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (grid[i][j] > 0)
				counter++;
		}
	}

	if (counter * 2 > row * col)
		return 1; //white player won
	else if (counter * 2 < row * col)
		return -1; //black player won
	else
		return 0;//draw
}

bool Board::validMove(int x, int y) {

	if (x < 0 || y < 0 || x > row - 1 || y > col - 1) {
		return false;
	}

	if (grid[x][y] != 0) {
		return false;
	}

	return true;
}

bool Board::addMove(int p, int x, int y) {
	if (p != player) {
		cout << "It is not the player's turn!" << endl;
		return false;
	}

	if (!validMove(x, y))
		return false;

	int pip = capturingPlacement(x,y);
	if (pip==0)
		grid[x][y] = player;
	else grid[x][y] = player * pip;

	player = -1 * player;

	int index = x*col+y;
	deleteIndex(index);

	return true;
}

void Board::deleteIndex(int k) {
	for (int i=0; i<emptyIndex.size(); i++)
		if (k == emptyIndex[i]){
			emptyIndex.erase(emptyIndex.begin()+i);
			break;
		}		
}

void Board::printBoard() {
	cout << "    ";
	for (int j = 0; j < col; j++) {
		cout << j + 1 << "   ";
	}
	cout << endl;

	for (int i = 0; i < row; i++) {
		cout << "  ";
		for (int j = 0; j < col; j++) {
			cout << " ---";
		}
		cout << endl;

		cout << (i + 1) << " |";

		for (int j = 0; j < col; j++) {
			if (grid[i][j] == 0) {
				cout << "   |";
			} else if (grid[i][j] > 0) {
				cout << " " << grid[i][j] << " |";
			} else if (grid[i][j] < 0) {
				cout << "" << grid[i][j] << " |";
			}
		}
		cout << endl;
	}
	cout << "  ";

	for (int j = 0; j < col; j++) {
		cout << " ---";
	}
	cout << endl << endl;
}

int Board::getCol(){
		return col;
	}

int Board::getRow(){
		return row;
	}

int Board::capturingProcessing(unordered_map<string,Cell> neighbor){
	int sum = 0;
	int dices;
	bool pass;
	vector<pair<int,int>>coorList; 
	vector<Cell> cneighbor;
		
		for (auto i: neighbor)
			cneighbor.push_back(i.second);
		if (cneighbor.size()>3){
			for(int i=0; i<cneighbor.size()-2; i++)
				for(int j=i+1; j<cneighbor.size()-1; j++)
					for (int k=j+1; k<cneighbor.size();k++){
						sum = cneighbor[i].value + cneighbor[j].value + cneighbor[k].value;
						if (sum<=6){
							clearCell(cneighbor[i].x,cneighbor[i].y);
							clearCell(cneighbor[j].x,cneighbor[j].y);
							clearCell(cneighbor[k].x,cneighbor[k].y);
							return sum;
						}
					}				
		}

		for (int i=0; i<cneighbor.size()-1; i++)
			for(int j=i+1; j<neighbor.size();j++){
				int tsum = cneighbor[i].value + cneighbor[j].value;
				if (tsum > sum && tsum<=6){
					sum = tsum;
					coorList.clear();
					coorList.push_back({cneighbor[i].x,cneighbor[i].y});
					coorList.push_back({cneighbor[j].x,cneighbor[j].y});
				}
			}

	for (auto i:coorList){
		clearCell(i.first,i.second);
	}
	if (sum>6) return 1;
	return sum;
}

void Board::clearCell(int x, int y){
	grid[x][y] = 0 ;
	emptyIndex.push_back(x*col+y);
}

double Board::heuristic(){
	double maxUtility;
	int pip;
	for (int i = 0; i < row; i++) 
			for (int j = 0; j < col; j++) 
				if (grid[i][j] == player)
					pip++;
	return maxUtility;
}
	
#endif /* BOARD_H_ */
