#include "..\Implementation\Game.h"
#include  <iostream>
#include  "assert.h"
using namespace std;
void ActiveActionsTests()
{
	Team homeTeam = Team::RED;
	Team awayTeam = Team::BLUE;
	float alpha = 0.5f;
	float gamma = 0.2f;
	float epsilon = 0.0f;
	Game game(homeTeam, awayTeam, alpha, gamma, epsilon);

	game.InitialiseGame();
	game.Print();

	RodAction action1(NO_ACTION);
	RodAction action2(NO_ACTION);
	RodAction action3(NO_ACTION);
	RodAction action4(NO_ACTION);

	RodAction rodActions[4] = { action1, action2, action3, action4 };
	//simple reflex offense from the back
	game.getActions(rodActions);
	game.step(rodActions);
	BallPosition b = game.getBallPosition();
	BallPosition c;
	assert(rodActions[2].getActionType() == KICK && rodActions[2].getActionForce() == 1 && rodActions[2].getActionDirection() == FORWARD && b.x == 3 && b.y == 6);

	//simple reflex offense on rod position
	game.getActions(rodActions);
	game.step(rodActions);
	b = game.getBallPosition();
	assert(rodActions[2].getActionType() == KICK && rodActions[2].getActionForce() == 1 && rodActions[2].getActionDirection() == FORWARD && b.x == 3 && b.y == 7);
	//simple reflex defence movement rod in case of forward ball movement
	c.x = 2;
	c.y = 8;
	game.m_ball.setBallSource(1);
	game.m_ball.setBallPower(5);
	game.m_ball.setBallDirection(FORWARD);
	game.m_ball.updateBallPosition(c);
	game.getActions(rodActions);
	game.step(rodActions);
	assert(rodActions[2].getActionType() == MOVE && rodActions[2].getActionDirection() == UP);
	//Q learning in case of having the ball in front of player
	BallPosition q;
	q.x = 2;
	q.y = 7;
	game.m_ball.setBallSource(-1);
	game.m_ball.updateBallPosition(q);
	game.getActions(rodActions);
	game.step(rodActions);
	assert(rodActions[2].getActionType() == KICK);
}


void main() {
	ActiveActionsTests();
}