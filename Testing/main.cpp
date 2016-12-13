#include "../Implementation/Game.h"
#include  <iostream>
#include  "assert.h"
using namespace std;


void TestCase1()
{
	Team homeTeam = Team::RED;
	Team awayTeam = Team::BLUE;
	Game game(homeTeam, awayTeam);

	game.InitialiseGame();
	BallPosition x = game.getBallPosition();
	assert(x.x == 3 && x.y == 5);


	RodAction action1(KICK, FORWARD, 2);
	RodAction action2(NO_ACTION);
	RodAction action3(NO_ACTION);
	RodAction action4(NO_ACTION);

	RodAction rodActions[4] = { action1, action2, action3, action4 };
	x.x = 1;
	x.y = 2;
	game.m_ball.updateBallPosition(x);
	game.m_ball.setBallSource(1);
	assert(x.x == 1 && x.y == 2);
	game.step(rodActions);
	x = game.m_ball.getBallPosition();
	assert(x.y == 3 && x.x == 1);
	assert(FORWARD == game.m_ball.getBallDirection());
	assert(1 == game.m_ball.getBallPower());


	rodActions[0].setActionKick(UP, 3);
	x.x = 1;
	x.y = 2;
	game.m_ball.updateBallPosition(x);
	game.m_ball.setBallSource(1);
	game.step(rodActions);
	x = game.m_ball.getBallPosition();
	assert(x.x == 0 && x.y == 3);
	assert(UP == game.m_ball.getBallDirection());
	assert(0 == game.m_ball.getBallPower());

	rodActions[0].setActionKick(DOWN, 3);
	x.x = 1;
	x.y = 2;
	game.m_ball.setBallSource(1);
	game.m_ball.updateBallPosition(x);
	game.step(rodActions);
	x = game.m_ball.getBallPosition();
	assert(x.x == 2 && x.y == 3);
	assert(DOWN == game.m_ball.getBallDirection());
	assert(2 == game.m_ball.getBallPower());

	x.x = 3;
	x.y = 2;
	game.m_ball.updateBallPosition(x);
	rodActions[0].setActionKick(FORWARD, 2);
	game.step(rodActions);
	x = game.m_ball.getBallPosition();
	assert(x.x == 3 && x.y == 3);
	assert(FORWARD == game.m_ball.getBallDirection());
	assert(1 == game.m_ball.getBallPower());


	rodActions[0].setActionKick(UP, 3);
	x.x = 3;
	x.y = 2;
	game.m_ball.updateBallPosition(x);
	game.step(rodActions);
	x = game.m_ball.getBallPosition();
	assert(x.x == 2 && x.y == 3);
	assert(UP == game.m_ball.getBallDirection());
	assert(2 == game.m_ball.getBallPower());

	rodActions[0].setActionKick(DOWN, 3);
	x.x = 3;
	x.y = 2;
	game.m_ball.updateBallPosition(x);
	game.step(rodActions);
	x = game.m_ball.getBallPosition();
	assert(x.x == 4 && x.y == 3);
	assert(DOWN == game.m_ball.getBallDirection());
	assert(2 == game.m_ball.getBallPower());



	x.x = 5;
	x.y = 2;
	game.m_ball.updateBallPosition(x);
	rodActions[0].setActionKick(FORWARD, 2);
	game.step(rodActions);
	x = game.m_ball.getBallPosition();
	assert(x.x == 5 && x.y == 3);
	assert(FORWARD == game.m_ball.getBallDirection());
	assert(1 == game.m_ball.getBallPower());


	rodActions[0].setActionKick(UP, 3);
	x.x = 5;
	x.y = 2;
	game.m_ball.updateBallPosition(x);
	game.step(rodActions);
	x = game.m_ball.getBallPosition();
	assert(x.x == 4 && x.y == 3);
	assert(UP == game.m_ball.getBallDirection());
	assert(2 == game.m_ball.getBallPower());

	rodActions[0].setActionKick(DOWN, 3);
	x.x = 5;
	x.y = 2;
	game.m_ball.updateBallPosition(x);
	game.step(rodActions);
	x = game.m_ball.getBallPosition();
	assert(x.x == 6 && x.y == 3);
	assert(DOWN == game.m_ball.getBallDirection());
	assert(0 == game.m_ball.getBallPower());

	x.x = 1;
	x.y = 4;
	game.m_ball.updateBallPosition(x);
	game.m_ball.setBallSource(-1);
	rodActions[1].setActionKick(FORWARD, 2);
	game.step(rodActions);
	x = game.m_ball.getBallPosition();
	assert(x.x == 1 && x.y == 3);
	assert(FORWARD == game.m_ball.getBallDirection());
	assert(1 == game.m_ball.getBallPower());


	rodActions[1].setActionKick(UP, 3);
	x.x = 1;
	x.y = 4;
	game.m_ball.updateBallPosition(x);
	game.step(rodActions);
	x = game.m_ball.getBallPosition();
	assert(x.x == 0 && x.y == 3);
	assert(UP == game.m_ball.getBallDirection());
	assert(0 == game.m_ball.getBallPower());

	rodActions[1].setActionKick(DOWN, 3);
	x.x = 1;
	x.y = 4;
	game.m_ball.updateBallPosition(x);
	game.step(rodActions);
	x = game.m_ball.getBallPosition();
	assert(x.x == 2 && x.y == 3);
	assert(DOWN == game.m_ball.getBallDirection());
	assert(2 == game.m_ball.getBallPower());

	x.x = 3;
	x.y = 4;
	game.m_ball.updateBallPosition(x);
	rodActions[1].setActionKick(FORWARD, 2);
	game.step(rodActions);
	x = game.m_ball.getBallPosition();
	assert(x.x == 3 && x.y == 3);
	assert(FORWARD == game.m_ball.getBallDirection());
	assert(1 == game.m_ball.getBallPower());


	rodActions[1].setActionKick(UP, 3);
	x.x = 3;
	x.y = 4;
	game.m_ball.updateBallPosition(x);
	game.step(rodActions);
	x = game.m_ball.getBallPosition();
	assert(x.x == 2 && x.y == 3);
	assert(UP == game.m_ball.getBallDirection());
	assert(2 == game.m_ball.getBallPower());

	rodActions[1].setActionKick(DOWN, 3);
	x.x = 3;
	x.y = 4;
	game.m_ball.updateBallPosition(x);
	game.step(rodActions);
	x = game.m_ball.getBallPosition();
	assert(x.x == 4 && x.y == 3);
	assert(DOWN == game.m_ball.getBallDirection());
	assert(2 == game.m_ball.getBallPower());



	x.x = 5;
	x.y = 4;
	game.m_ball.updateBallPosition(x);
	rodActions[1].setActionKick(FORWARD, 2);
	game.step(rodActions);
	x = game.m_ball.getBallPosition();
	assert(x.x == 5 && x.y == 3);
	assert(FORWARD == game.m_ball.getBallDirection());
	assert(1 == game.m_ball.getBallPower());


	rodActions[1].setActionKick(UP, 3);
	x.x = 5;
	x.y = 4;
	game.m_ball.updateBallPosition(x);
	game.step(rodActions);
	x = game.m_ball.getBallPosition();
	assert(x.x == 4 && x.y == 3);
	assert(UP == game.m_ball.getBallDirection());
	assert(2 == game.m_ball.getBallPower());

	rodActions[1].setActionKick(DOWN, 3);
	x.x = 5;
	x.y = 4;
	game.m_ball.updateBallPosition(x);
	game.step(rodActions);
	x = game.m_ball.getBallPosition();
	assert(x.x == 6 && x.y == 3);
	assert(DOWN == game.m_ball.getBallDirection());
	assert(0 == game.m_ball.getBallPower());

	x.x = 1;
	x.y = 7;
	game.m_ball.updateBallPosition(x);
	rodActions[2].setActionKick(FORWARD, 2);
	game.m_ball.setBallSource(1);
	game.step(rodActions);
	x = game.m_ball.getBallPosition();
	assert(x.x == 1 && x.y == 8);
	assert(FORWARD == game.m_ball.getBallDirection());
	assert(1 == game.m_ball.getBallPower());


	rodActions[2].setActionKick(UP, 3);
	x.x = 1;
	x.y = 7;
	game.m_ball.updateBallPosition(x);
	game.step(rodActions);
	x = game.m_ball.getBallPosition();
	assert(x.x == 0 && x.y == 8);
	assert(UP == game.m_ball.getBallDirection());
	assert(0 == game.m_ball.getBallPower());

	rodActions[2].setActionKick(DOWN, 3);
	x.x = 1;
	x.y = 7;
	game.m_ball.updateBallPosition(x);
	game.step(rodActions);
	x = game.m_ball.getBallPosition();
	assert(x.x == 2 && x.y == 8);
	assert(DOWN == game.m_ball.getBallDirection());
	assert(2 == game.m_ball.getBallPower());

	x.x = 3;
	x.y = 7;
	game.m_ball.updateBallPosition(x);
	rodActions[2].setActionKick(FORWARD, 2);
	game.step(rodActions);
	x = game.m_ball.getBallPosition();
	assert(x.x == 3 && x.y == 8);
	assert(FORWARD == game.m_ball.getBallDirection());
	assert(1 == game.m_ball.getBallPower());


	rodActions[2].setActionKick(UP, 3);
	x.x = 3;
	x.y = 7;
	game.m_ball.updateBallPosition(x);
	game.step(rodActions);
	x = game.m_ball.getBallPosition();
	assert(x.x == 2 && x.y == 8);
	assert(UP == game.m_ball.getBallDirection());
	assert(2 == game.m_ball.getBallPower());

	rodActions[2].setActionKick(DOWN, 3);
	x.x = 3;
	x.y = 7;
	game.m_ball.updateBallPosition(x);
	game.step(rodActions);
	x = game.m_ball.getBallPosition();
	assert(x.x == 4 && x.y == 8);
	assert(DOWN == game.m_ball.getBallDirection());
	assert(2 == game.m_ball.getBallPower());



	x.x = 5;
	x.y = 7;
	game.m_ball.updateBallPosition(x);
	rodActions[2].setActionKick(FORWARD, 2);
	game.step(rodActions);
	x = game.m_ball.getBallPosition();
	assert(x.x == 5 && x.y == 8);
	assert(FORWARD == game.m_ball.getBallDirection());
	assert(1 == game.m_ball.getBallPower());


	rodActions[2].setActionKick(UP, 3);
	x.x = 5;
	x.y = 7;
	game.m_ball.updateBallPosition(x);
	game.step(rodActions);
	x = game.m_ball.getBallPosition();
	assert(x.x == 4 && x.y == 8);
	assert(UP == game.m_ball.getBallDirection());
	assert(2 == game.m_ball.getBallPower());

	rodActions[2].setActionKick(DOWN, 3);
	x.x = 5;
	x.y = 7;
	game.m_ball.updateBallPosition(x);
	game.step(rodActions);
	x = game.m_ball.getBallPosition();
	assert(x.x == 6 && x.y == 8);
	assert(DOWN == game.m_ball.getBallDirection());
	assert(0 == game.m_ball.getBallPower());

	x.x = 1;
	x.y = 9;
	game.m_ball.setBallSource(-1);
	game.m_ball.updateBallPosition(x);
	rodActions[3].setActionKick(FORWARD, 2);
	game.step(rodActions);
	x = game.m_ball.getBallPosition();
	assert(x.x == 1 && x.y == 8);
	assert(FORWARD == game.m_ball.getBallDirection());
	assert(1 == game.m_ball.getBallPower());


	rodActions[3].setActionKick(UP, 3);
	x.x = 1;
	x.y = 9;
	game.m_ball.updateBallPosition(x);
	game.step(rodActions);
	x = game.m_ball.getBallPosition();
	assert(x.x == 0 && x.y == 8);
	assert(UP == game.m_ball.getBallDirection());
	assert(0 == game.m_ball.getBallPower());

	rodActions[3].setActionKick(DOWN, 3);
	x.x = 1;
	x.y = 9;
	game.m_ball.updateBallPosition(x);
	game.step(rodActions);
	x = game.m_ball.getBallPosition();
	assert(x.x == 2 && x.y == 8);
	assert(DOWN == game.m_ball.getBallDirection());
	assert(2 == game.m_ball.getBallPower());

	x.x = 3;
	x.y = 9;
	game.m_ball.updateBallPosition(x);
	rodActions[3].setActionKick(FORWARD, 2);
	game.step(rodActions);
	x = game.m_ball.getBallPosition();
	assert(x.x == 3 && x.y == 8);
	assert(FORWARD == game.m_ball.getBallDirection());
	assert(1 == game.m_ball.getBallPower());


	rodActions[3].setActionKick(UP, 3);
	x.x = 3;
	x.y = 9;
	game.m_ball.updateBallPosition(x);
	game.step(rodActions);
	x = game.m_ball.getBallPosition();
	assert(x.x == 2 && x.y == 8);
	assert(UP == game.m_ball.getBallDirection());
	assert(2 == game.m_ball.getBallPower());

	rodActions[3].setActionKick(DOWN, 3);
	x.x = 3;
	x.y = 9;
	game.m_ball.updateBallPosition(x);
	game.step(rodActions);
	x = game.m_ball.getBallPosition();
	assert(x.x == 4 && x.y == 8);
	assert(DOWN == game.m_ball.getBallDirection());
	assert(2 == game.m_ball.getBallPower());



	x.x = 5;
	x.y = 9;
	game.m_ball.updateBallPosition(x);
	rodActions[3].setActionKick(FORWARD, 2);
	game.step(rodActions);
	x = game.m_ball.getBallPosition();
	assert(x.x == 5 && x.y == 8);
	assert(FORWARD == game.m_ball.getBallDirection());
	assert(1 == game.m_ball.getBallPower());


	rodActions[3].setActionKick(UP, 3);
	x.x = 5;
	x.y = 9;
	game.m_ball.updateBallPosition(x);
	game.step(rodActions);
	x = game.m_ball.getBallPosition();
	assert(x.x == 4 && x.y == 8);
	assert(UP == game.m_ball.getBallDirection());
	assert(2 == game.m_ball.getBallPower());

	rodActions[3].setActionKick(DOWN, 3);
	x.x = 5;
	x.y = 9;
	game.m_ball.updateBallPosition(x);
	game.step(rodActions);
	x = game.m_ball.getBallPosition();
	assert(x.x == 6 && x.y == 8);
	assert(DOWN == game.m_ball.getBallDirection());
	assert(0 == game.m_ball.getBallPower());

}

void TestCase2()
{
	Team homeTeam = Team::RED;
	Team awayTeam = Team::BLUE;
	Game game(homeTeam, awayTeam);

	game.InitialiseGame();
	assert(game.m_rods[0].getOffset() == 1);
	assert(game.m_rods[1].getOffset() == 1);
	assert(game.m_rods[2].getOffset() == 1);
	assert(game.m_rods[3].getOffset() == 1);



	RodAction action1(KICK, FORWARD, 2);
	RodAction action2(NO_ACTION);
	RodAction action3(NO_ACTION);
	RodAction action4(NO_ACTION);

	RodAction rodActions[4] = { action1, action2, action3, action4 };

	rodActions[0].setActionMove(DOWN);
	rodActions[1].setActionMove(DOWN);
	rodActions[2].setActionMove(DOWN);
	rodActions[3].setActionMove(DOWN);
	game.step(rodActions);

	assert(game.m_rods[0].getOffset() == 2);
	assert(game.m_rods[1].getOffset() == 2);
	assert(game.m_rods[2].getOffset() == 2);
	assert(game.m_rods[3].getOffset() == 2);

	game.step(rodActions);

	assert(game.m_rods[0].getOffset() == 2);
	assert(game.m_rods[1].getOffset() == 2);
	assert(game.m_rods[2].getOffset() == 2);
	assert(game.m_rods[3].getOffset() == 2);

	BallPosition x;
	x.x = 6;
	x.y = 2;
	game.m_ball.updateBallPosition(x);
	rodActions[0].setActionKick(FORWARD, 3);
	game.step(rodActions);
	x = game.m_ball.getBallPosition();
	assert(x.x == 6 && x.y == 3);
	game.m_ball.setBallSource(1);
	assert(FORWARD == game.m_ball.getBallDirection());
	assert(2 == game.m_ball.getBallPower());

	rodActions[0].setActionMove(UP);
	rodActions[1].setActionMove(UP);
	rodActions[2].setActionMove(UP);
	rodActions[3].setActionMove(UP);
	game.step(rodActions);

	assert(game.m_rods[0].getOffset() == 1);
	assert(game.m_rods[1].getOffset() == 1);
	assert(game.m_rods[2].getOffset() == 1);
	assert(game.m_rods[3].getOffset() == 1);

	game.step(rodActions);

	assert(game.m_rods[0].getOffset() == 0);
	assert(game.m_rods[1].getOffset() == 0);
	assert(game.m_rods[2].getOffset() == 0);
	assert(game.m_rods[3].getOffset() == 0);

	game.step(rodActions);

	assert(game.m_rods[0].getOffset() == 0);
	assert(game.m_rods[1].getOffset() == 0);
	assert(game.m_rods[2].getOffset() == 0);
	assert(game.m_rods[3].getOffset() == 0);

	x.x = 0;
	x.y = 2;
	game.m_ball.updateBallPosition(x);
	game.m_ball.setBallSource(1);
	rodActions[0].setActionKick(FORWARD, 3);
	game.step(rodActions);
	x = game.m_ball.getBallPosition();
	assert(x.x == 0 && x.y == 3);
	assert(FORWARD == game.m_ball.getBallDirection());
	assert(2 == game.m_ball.getBallPower());


}

void TestCase3()
{
	Team homeTeam = Team::RED;
	Team awayTeam = Team::BLUE;
	Game game(homeTeam, awayTeam);

	game.InitialiseGame();

	BallPosition x;
	x.x = 3;
	x.y = 0;
	game.m_ball.updateBallPosition(x);
	game.m_ball.setBallPower(2);
	game.m_ball.setBallDirection(FORWARD);

	RodAction action1(NO_ACTION);
	RodAction action2(NO_ACTION);
	RodAction action3(NO_ACTION);
	RodAction action4(NO_ACTION);

	RodAction rodActions[4] = { action1, action2, action3, action4 };

	game.step(rodActions);
	assert(game.m_homeScore == 0 && game.m_awayScore == 1);

	x.x = 3;
	x.y = 10;
	game.m_ball.updateBallPosition(x);
	game.m_ball.setBallPower(2);
	game.m_ball.setBallDirection(FORWARD);
	game.m_ball.setBallSource(1);

	rodActions[0].setNoAction();
	rodActions[1].setNoAction();
	rodActions[2].setNoAction();
	rodActions[3].setNoAction();

	game.step(rodActions);
	assert(game.m_homeScore == 1 && game.m_awayScore == 1);
}

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
	TestCase1();
	TestCase2();
	TestCase3();
	ActiveActionsTests();
}