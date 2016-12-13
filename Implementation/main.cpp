#include "Communication.h"
#include "Game.h"
#include  <iostream>
using namespace std;

void Game1()
{
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
	
	//get the opponent actions from the integration.
	//RodAction rodActions = getOpponentActions();
	//RodAction rodActions;
	//agent logic
	//rodActions = game.getActions();
	//game logic
	game.step(rodActions);


	rodActions[2].setNoAction();
	game.step(rodActions);
	rodActions[2].setActionKick(UP, 3);
	game.step(rodActions);
	rodActions[2].setNoAction();
	game.step(rodActions);
	game.step(rodActions);
	game.step(rodActions);
	game.step(rodActions);

	rodActions[3].setActionMove(UP);
	game.step(rodActions);

	rodActions[3].setActionKick(DOWN, 5);
	game.step(rodActions);

	rodActions[3].setNoAction();
	for (int i = 0; i < 4; i++) {
		game.step(rodActions);
	}

	rodActions[1].setActionKick(UP, 3);
	game.step(rodActions);
	rodActions[3].setActionKick(UP, 5);
	rodActions[1].setNoAction();
	game.step(rodActions);
	game.step(rodActions);
}

void Game2()
{
	Team homeTeam = Team::RED;
	Team awayTeam = Team::BLUE;
	Game game(homeTeam, awayTeam);

	game.InitialiseGame();
	game.Print();

	RodAction action1(NO_ACTION);
	RodAction action2(NO_ACTION);
	RodAction action3(KICK, FORWARD, 5);
	RodAction action4(MOVE, UP);

	RodAction rodActions[4] = { action1, action2, action3, action4 };
	game.step(rodActions);
	rodActions[2].setNoAction();
	rodActions[3].setNoAction();
	game.step(rodActions);
	rodActions[2].setActionKick(FORWARD, 5);
	game.step(rodActions);
	rodActions[2].setNoAction();
	game.step(rodActions);
	game.step(rodActions);
	game.step(rodActions);
}

void Game3()
{
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
	
	game.step(rodActions);
	rodActions[2].setNoAction();
	
	game.step(rodActions);
	rodActions[2].setActionKick(UP, 3);
	game.step(rodActions);
	rodActions[2].setNoAction();
	game.step(rodActions);
	game.step(rodActions);
	game.step(rodActions);
	game.step(rodActions);

	rodActions[3].setActionMove(UP);
	game.step(rodActions);

	rodActions[3].setActionKick(DOWN, 5);
	game.step(rodActions);

	rodActions[3].setNoAction();
	for (int i = 0; i < 4; i++) {
		game.step(rodActions);
	}

	rodActions[1].setActionKick(UP, 4);
	game.step(rodActions);
	rodActions[3].setActionKick(UP, 5);
	rodActions[1].setNoAction();
	rodActions[0].setActionMove(UP);
	game.step(rodActions);
	rodActions[0].setNoAction();
	game.step(rodActions);
	rodActions[0].setActionMove(DOWN);
	game.step(rodActions);
}

void Game4()
{
	Team homeTeam = Team::RED;
	Team awayTeam = Team::BLUE;
	float alpha = 0.5f;
	float gamma = 0.2f; 
	float epsilon = 1.0f;
	Game game(homeTeam, awayTeam,alpha, gamma, epsilon);

	game.InitialiseGame();
	game.Print();
	srand(static_cast<unsigned>(time(NULL)));

	RodAction action1(NO_ACTION);
	RodAction action2(MOVE, DOWN);
	RodAction action3(KICK, UP, 5);
	RodAction action4(NO_ACTION);

	RodAction rodActions[4] = { action1, action2, action3, action4 };

	game.getActions(rodActions);
	game.step(rodActions);

	game.getActions(rodActions);
	game.step(rodActions);

	game.getActions(rodActions);
	game.step(rodActions);

	game.getActions(rodActions);
	game.step(rodActions);

	//rodActions[3].setActionMove(DOWN);
	//rodActions[3].setActionKick(UP, 3);
	game.getActions(rodActions);
	game.step(rodActions);


	game.getActions(rodActions);
	game.step(rodActions);

	game.getActions(rodActions);
	game.step(rodActions);

	game.getActions(rodActions);
	game.step(rodActions);

	game.getActions(rodActions);
	game.step(rodActions);

	for (int i=0; i<1000; ++i) {
		int action = rand() % 4;
		if (action == 0) {
			rodActions[1].setActionMove(((Direction)((rand() % 3) - 1)));
			rodActions[3].setActionMove(((Direction)((rand() % 3) - 1)));
		}
		else if (action == 1) {
			rodActions[1].setActionMove(((Direction)((rand() % 3) - 1)));
			rodActions[3].setActionKick(((Direction)((rand() % 3) - 1)), rand() % 5 + 1);
		}
		else if (action == 2) {
			rodActions[1].setActionMove(((Direction)((rand() % 3) - 1)));
			rodActions[3].setActionKick(((Direction)((rand() % 3) - 1)), rand() % 5 + 1);
		}
		else if (action == 3) {
			rodActions[1].setActionKick(((Direction)((rand() % 3) - 1)), rand()%5 + 1);
			rodActions[3].setActionKick(((Direction)((rand() % 3) - 1)), rand() % 5 + 1);
		}
		game.getActions(rodActions);
		game.step(rodActions);
	}
}

// A simple program  to drive the project 
/*
First Game to test the different functionalities included (rebounding, 
colliding with borders, going straight, diagonally upwards and downwards,
colliding with teammate, colliding with opponent)

Second Game to test a very simple case of winning and scoring a goal.
*/
void main() {
	Communication comm;
	comm.GameLoop();
	system("pause");
}