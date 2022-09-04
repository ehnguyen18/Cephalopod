/*
 *
 *  Created on: 17/04/2022
 *      Author: Eric
 */

#ifndef RANDOMPLAYER_H_
#define RANDOMPLAYER_H_

class RandomPlayer: public Player {
public:
	RandomPlayer(int t):Player("Random", t){}
	void getMove(Board board, int&, int&);
};

void RandomPlayer::getMove(Board board, int& x, int& y)
{
	
	if(board.isBoardFull())
		return;

	int randomIndex = rand() % board.emptyIndex.size();
	int index = board.emptyIndex[randomIndex];
		x = index / board.getCol();
		y = index % board.getCol();
		}

#endif /* RANDOMPLAYER_H_ */
