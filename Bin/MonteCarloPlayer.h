/*
 *
 *  Created on: 22/04/2022
 *      Author: Eric
 */

#ifndef MONTECARLOPLAYER_H_
#define MONTECARLOPLAYER_H_

class MonteCarloPlayer: public Player {
	double simulation(Board board);
	double expansion(int player, Board board);
	int type;

public:
	MonteCarloPlayer(int t):Player("MonteCarlo", t){
		type = t;
	}
	void getMove(Board board, int&, int&);
};

void MonteCarloPlayer::getMove(Board board, int& x, int& y)
{
	priority_queue <Cell> moves;
	if(board.isBoardFull())
		return;

	for (int i = 0; i < board.getRow(); i++) {
		for (int j = 0; j < board.getCol(); j++) {
			Board tempBoard(board);
			if (!tempBoard.validMove(i,j))
				continue;
			
			tempBoard.addMove(type, i, j);
			if (tempBoard.isBoardFull()) {
				if (tempBoard.checkWinningStatus() == type) {
					x = i;
					y = j;
					return;
				} else {
					continue;
				}
			}
			double Utillity = simulation(tempBoard);
			Cell c(i, j, Utillity);
			moves.push(c);
		}
	}

	if (moves.size() > 0) {
		x = moves.top().x;
		y = moves.top().y;
		cout << moves.size() << " MonteCarlo Utility = " << moves.top().heuristic
				<< " at (" << (x + 1) << "," << (y + 1) << ")" << endl;
	}
}

double MonteCarloPlayer::simulation(Board board) {
	int times = 1000;
	double winning = 0.0;

	for (int i = 0; i < times; i++) {
		Board tempBoard(board);
		int player = board.getTurn();
		winning += expansion(player, tempBoard);
	}
	return (winning / (double) times);
}

double MonteCarloPlayer::expansion(int player, Board board) {
	if (board.checkWinningStatus() == type) {
		return 1.0;
	} else if (board.checkWinningStatus() == 0) { 
		return 0.5;
	} else if (board.checkWinningStatus() != -2) { 
		return 0.0;
	}
	int x, y;

	int randomIndex = rand() % board.emptyIndex.size();
	int index = board.emptyIndex[randomIndex];
		x = index / board.getCol();
		y = index % board.getCol();

	board.addMove(player, x, y);
	player = board.getTurn();

	return expansion(player, board);
}
#endif /* MONTECARLOPLAYER_H_ */