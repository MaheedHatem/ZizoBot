#include "Game.h"
#include  <iostream>
using namespace std;


// A simple program to drive the code
void main() {
	Team homeTeam = Team::RED;
	Team awayTeam = Team::BLUE;
	Game game(homeTeam, awayTeam);
	
	game.InitialiseGame();
	game.Print();
	
	RodAction action1(NO_ACTION);
	RodAction action2(NO_ACTION);
	RodAction action3(KICK, FORWARD, 2);
	RodAction action4(NO_ACTION);

	RodAction rodActions[4] = { action1, action2, action3, action4 };
	game.GameLoop(rodActions);
	game.Print();

	rodActions[2].setNoAction();
	game.GameLoop(rodActions);
	game.Print();

	rodActions[2].setActionKick(UP, 3);
	game.GameLoop(rodActions);
	game.Print();

	rodActions[2].setNoAction();
	game.GameLoop(rodActions);
	game.Print();

	game.GameLoop(rodActions);
	game.Print();

	game.GameLoop(rodActions);
	game.Print();

	game.GameLoop(rodActions);
	game.Print();

	rodActions[3].setActionMove(UP);
	game.GameLoop(rodActions);
	game.Print();

	rodActions[3].setActionKick(DOWN, 5);
	game.GameLoop(rodActions);
	game.Print();

	rodActions[3].setNoAction();
	for (int i = 0; i < 4; i++) {	
		game.GameLoop(rodActions);
		game.Print();
	}

	rodActions[1].setActionKick(UP, 2);
	game.GameLoop(rodActions);
	game.Print();

	rodActions[3].setActionKick(UP, 5);
	rodActions[1].setNoAction();
	game.GameLoop(rodActions);
	game.Print();

	game.GameLoop(rodActions);
	game.Print();

	system("pause");
}