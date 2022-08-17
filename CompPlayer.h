/*
 *
 *  Created on: 21/04/2022
 *      Author: Eric
 */

#ifndef COMPPLAYER_H_
#define COMPPLAYER_H_

class CompPlayer: public Player {
public:
	CompPlayer(int t):Player("Comp", t){}
	void getMove(Board board, int&, int&);
};

void CompPlayer::getMove(Board board, int& x, int& y)
{
	priority_queue < Cell > moves;
	if(board.isBoardFull())
		return;
		
	for (int i = 0; i < board.getRow(); i++) {
		for (int j = 0; j < board.getCol(); j++) {
			Board tempBoard(board);
			if (tempBoard.validMove(i,j)){
				tempBoard.addMove(tempBoard.getTurn(), i, j);
				Cell c(i, j, tempBoard.heuristic());
				moves.push(c);
			}
		}
	}

	if (moves.size() > 0) {
		x = moves.top().x;
		y = moves.top().y;
		cout << moves.size() << " Utility = " << moves.top().heuristic
				<< " at (" << (x + 1) << "," << (y + 1) << ")" << endl;
	}
}
#endif /* COMPPLAYER_H_ */