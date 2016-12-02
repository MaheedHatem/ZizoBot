#include "Game.h"
#include  <iostream>
using namespace std;


void main() {
	Team homeTeam = Team::RED;
	Team awayTeam = Team::BLUE;
	Game game(homeTeam, awayTeam);
	
	game.InitialiseGame();
	game.Print();
	
	RodAction rodActions[4];
	RodAction action1(Action::NO_ACTION);
	RodAction action2(Action::NO_ACTION);
	RodAction action3(Action::KICK, 0, 2);
	RodAction action4(Action::NO_ACTION);

	rodActions[0] = action1;
	rodActions[1] = action2;
	rodActions[2] = action3;
	rodActions[3] = action4;

	game.GameLoop(rodActions);
	game.Print();

	rodActions[2].setNoAction();
	game.GameLoop(rodActions);
	game.Print();

	rodActions[2].setActionKick(1, 3);
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

	rodActions[3].setActionMove(1);
	game.GameLoop(rodActions);
	game.Print();

	rodActions[2].setNoAction();
	rodActions[3].setActionKick(-1, 5);
	game.GameLoop(rodActions);
	game.Print();

	rodActions[2].setNoAction();
	rodActions[3].setNoAction();

	for (int i = 0; i < 5; i++) {	
		game.GameLoop(rodActions);
		game.Print();
	}

	rodActions[1].setActionKick(1, 2);
	game.GameLoop(rodActions);
	game.Print();

	rodActions[3].setActionKick(1, 5);
	rodActions[1].setNoAction();
	game.GameLoop(rodActions);
	game.Print();

	rodActions[1].setNoAction();
	game.GameLoop(rodActions);
	game.Print();

	system("pause");
}