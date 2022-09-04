/*
 *
 *  Created on: 22/04/2022
 *      Author: Eric
 */

#ifndef MINIMAXPLAYER_H_
#define MINIMAXPLAYER_H_

class MiniMaxPlayer: public Player {
	double maxMove(Board board);
	double minMove(Board board);
	int steps;
	int type;

public:
	MiniMaxPlayer(int t):Player("MiniMax", t){
		type = t;
	}
	void getMove(Board board, int&, int&);
};

void MiniMaxPlayer::getMove(Board board, int& x, int& y)
{
	priority_queue <Cell> moves;
	if(board.isBoardFull())
		return;
	for (int i = 0; i < board.getRow(); i++) {
		for (int j = 0; j < board.getCol(); j++) {
			steps = 1000;
			Board tempBoard(board);
			if (!tempBoard.validMove(i,j))
				continue;
			
			tempBoard.addMove(tempBoard.getTurn(), i, j);
			if (tempBoard.isBoardFull()) {
				if (tempBoard.checkWinningStatus() == type) {
					x = i;
					y = j;
					return;
				} else {
					continue;
				}
			}
			double minUtility = minMove(tempBoard);
			Cell c(i, j, minUtility);
			moves.push(c);
		}
	}

	if (moves.size() > 0) {
		x = moves.top().x;
		y = moves.top().y;
		cout << moves.size() << " MiniMax Utility = " << moves.top().heuristic
				<< " at (" << (x + 1) << "," << (y + 1) << ")" << endl;
	}
}

double MiniMaxPlayer::maxMove(Board board) {
	if (board.isBoardFull() || steps <= 0)
			return board.heuristic();

	double maxUtility = -2;
	for (int i = 0; i < board.getRow(); i++) {
		for (int j = 0; j < board.getCol(); j++) {
			Board tempBoard(board);
			if(!tempBoard.validMove(i,j))
				continue;
			tempBoard.addMove(tempBoard.getTurn(),i, j);
			int gameStatus = tempBoard.checkWinningStatus();
			if (gameStatus != -2) {
				if (gameStatus == type)
					return 1; 
				else if (gameStatus == 0)
					return 0; 
				else
					return -1; 
			}

			double utility;
			utility = minMove(tempBoard);

			if (utility > maxUtility) {
				maxUtility = utility;
			}
		}
	}
	steps--;
	return maxUtility;
}

double MiniMaxPlayer::minMove(Board board) {
	if (board.isBoardFull() || steps <= 0)
			return board.heuristic()*-1;

	double minUtility = 2;
	for (int i = 0; i < board.getRow(); i++) {
		for (int j = 0; j < board.getCol(); j++) {
			Board tempBoard(board);
			if(!tempBoard.validMove(i,j))
				continue;
			tempBoard.addMove(tempBoard.getTurn(),i, j);
			int gameStatus = tempBoard.checkWinningStatus();
			if (gameStatus != -2) {
				if (gameStatus == type)
					return 1; 
				else if (gameStatus == 0)
					return 0; 
				else
					return -1; 
			}

			double utility = maxMove(tempBoard);

			if (utility < minUtility) {
				minUtility = utility;
			}
		}
	}
	return minUtility;
}
#endif /* MINIMAXPLAYER_H_ */