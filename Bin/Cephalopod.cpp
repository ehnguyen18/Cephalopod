/*
 * Cephalopod.cpp
 *      Author: dongmo
 * 		Edited: Eric Nguyen
 */
/*********** Declaration*******
I hereby certify that no part of this assignment has been copied from any
other student’s work or from any other source. No part of the code has
been written/produced for me by another person.
I hold a copy of this assignment that I can produce if the original is
lost or damaged.
**************************/
#include<iostream>
#include<time.h>
#include<algorithm>
#include<unordered_map>
#include<sstream>
#include<vector>
#include<set>
#include<queue>

using namespace std;

#include "Cell.h"
#include "Board.h"
#include "Player.h"
#include "CephalopodGameLogic.h"
#include "HumanPlayer.h"
#include "RandomPlayer.h"
#include "CompPlayer.h"
#include "MiniMaxPlayer.h"
#include "MonteCarloPlayer.h"

int main() {
	srand(time(0));
	int t1, t2;
	cout<<endl<<"Author: Pham Gia Huy Nguyen / StudentID: 20000820"<<endl<<endl;
	cout<<"---------------Player Types--------------"<<endl;
        cout<<"1. Human"<<endl<<"2. Random AI"<<endl<<"3. Comp AI"
			<<endl<<"4. MiniMax AI"<<endl<<"5. MonteCarlo AI"<<endl
        <<"-----------------------------------------"<<endl;
        cout<<"Please enter the type for player 1: ";
        cin>>t1;
        cout<<"Please enter the type for player -1: ";
        cin>>t2;
        cout<<endl;
	Player *players[2];

	switch (t1){
		case 1:
			players[0] = new HumanPlayer(1);
			break;
		case 2:
			players[0] = new RandomPlayer(1);
			break;
		case 3:
			players[0] = new CompPlayer(1);
			break;
		case 4:
			players[0] = new MiniMaxPlayer(1);
			break;
		case 5:
			players[0] = new MonteCarloPlayer(1);
			break;
		
	}

	switch (t2){
		case 1:
			players[1] = new HumanPlayer(-1);
			break;
		case 2:
			players[1] = new RandomPlayer(-1);
			break;
		case 3:
			players[1] = new CompPlayer(-1);
			break;
		case 4:
			players[1] = new MiniMaxPlayer(-1);
			break;
		case 5:
			players[1] = new MonteCarloPlayer(-1);
			break;
		
	}

	cout << "Input size of the board (say (2,2), (2,3), (3,3), (3,5), (5,5) ... " << endl;

	int row, col;
	cin >> row >> col;

	Board board(row, col);
	CephalopodGame game(board, players);
	game.play();

	delete players[0];
	delete players[1];

	system("pause");
	return 0;
}
