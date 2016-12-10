#pragma once
#ifndef _GAME_H
#define _GAME_H

#include "Ball.h"
#include "Rod.h"
#include "Action.h"
#include "Qlearner.h"
#include "defs.h"
class Game
{
private:
	void initialiseGrid() {
		for (unsigned int i = 0; i < MAX_GRID_ROWS; ++i) {
			for (unsigned int j = 0; j < MAX_GRID_COLS; ++j) {
				m_grid[i][j] = 0;
			}
		}
	}

	void updateGrid() {
		initialiseGrid();
		for (unsigned int k = 0; k < RODS; ++k)
		{
			unsigned int from = m_rods[k].m_from_range;
			unsigned int to = m_rods[k].m_to_range;
			unsigned int offset = m_rods[k].getOffset(); //calculated from the top
			for (unsigned int i = 0; i < 3; ++i) {
				for (unsigned int j = from; j <= to; ++j) {
					int index = (i * 2) + offset;
					if (j == m_rods[k].getPositionInGrid())    // to indicate there is a player
						m_grid[index][j] = 5;
					else                                   // a valid kicking position
						m_grid[index][j] = 1;
				}
			}
		}
	}

	unsigned int getRodInControl() {
		int ballPosition = m_ball.getBallPosition().y;
		for (unsigned int i = 0; i < 4; ++i)
		{
			if (m_rods[i].isInRange(ballPosition))
			{
				return i;
			}
		}
		return -1;
	}

public:
	int m_grid[MAX_GRID_ROWS][MAX_GRID_COLS];
	Ball m_ball;
	Rod m_rods[RODS];
	Team m_homeTeam;
	Team m_awayTeam;
	Team m_winningTeam;
	RodAction m_lastKickPosition;
	Qlearner m_LearningAgent;

	Game(Team home = RED, Team away = BLUE, float alpha = 0.0f, float gamma = 0.0f, float epsilon = 1.0f) {
		initialiseGrid();
		m_homeTeam = home;
		m_awayTeam = away;
		m_winningTeam = home;
		m_rods[0].setRodParameters(RED, DEFENSE);
		m_rods[1].setRodParameters(BLUE, ATTACK);
		m_rods[2].setRodParameters(RED, ATTACK);
		m_rods[3].setRodParameters(BLUE, DEFENSE);
		m_LearningAgent.setParameters(m_homeTeam, alpha, gamma, epsilon);
	};

	bool isBallInReach(Rod& rod)
	{
		BallPosition position = m_ball.getBallPosition();
		if (rod.isInRange(position.y)) {
			if (m_grid[position.x][position.y])
				return true;
		}
		return false;
	}

	void InitialiseGame() {
		m_ball.resetBallPosition();
		updateGrid();
	}

	void Print() {
		printMatrix(m_grid, m_ball.getBallPosition());
	}

	void step(RodAction rodActions[]) {
		bool gameEnd = false;
		if (GameLoop(rodActions))
			gameEnd = true;
		printMatrix(m_grid, m_ball.getBallPosition());

		if (gameEnd) {
			if (m_winningTeam == RED)
				cout << "WINNER : RED TEAM" << endl;
			else
				cout << "WINNER : BLUE TEAM" << endl;
		}

	}

	/**
	This function UPDATES the position of the ball according to the status of the game.
	*/
	void updateBall()
	{
		/* Get current ball position */
		BallPosition position = m_ball.getBallPosition();

		/* The ball moves if and only if it has some remaining power */
		if (m_ball.getBallPower() <= 0)
			return;

		/* If the ball hit a player position */
		if (m_grid[position.x][position.y] == 5)
		{
			int rodIndex = getRodInControl();
			/* The ball rebounds only if it hits an opponent player */
			if (m_rods[rodIndex].m_team != m_ball.getBallSource()) {
				reboundBall();
			}
		}

		/* Do the actual moving */
		if (m_ball.getBallPower() > 0) {
			moveBall();
		}
	}

	void reboundBall() {
		int source = m_ball.getBallSource() * -1;
		m_ball.setBallSource(source);
		m_ball.setBallPower(2);
	}

	/**
	This function performs an action on a specific rod
	@param action to performed on a rod (KICK, MOVE, NO_ACTION)
	@param rodIndex the index of the rod to be acted upon (1, 2, 3, 4)
	*/
	void updateGame(RodAction action, int rodIndex)
	{
		/* Get the type of action performed */
		Action actionType = action.getActionType();

		/* Get the current ball position */
		BallPosition ballPosition = m_ball.getBallPosition();

		if (actionType == Action::MOVE) {
			Direction direction = action.getActionDirection();
			m_rods[rodIndex].changeOffset(direction);
		}

		if (actionType == Action::KICK && m_grid[ballPosition.x][ballPosition.y])
		{
			m_ball.setBallPower(action.getActionForce());
			m_ball.setBallDirection(action.getActionDirection());
			m_ball.setBallSource(m_rods[rodIndex].m_team);
		}
	}

	/**
	This function is responsible for one iteration of the game.
	@param actions[] an array of actions to be performed on every rod successively.
	@return true if the current iteration ended with scoring a goal, false otherwise.
	*/
	bool GameLoop(RodAction actions[]) {
		/* Find the rod that can do something with the ball */
		int rodinControl = getRodInControl();

		/* Find the position of the ball before updating */
		BallPosition oldPosition = m_ball.getBallPosition();

		/* Perform the kick action first if exists */
		if (actions[rodinControl].getActionType() == KICK)
			updateGame(actions[rodinControl], rodinControl);

		/* updates the ball position accordingly */
		updateBall();

		/* check if the ball is a goal position and announce the winner */
		if (isGoal() && (oldPosition == m_ball.getBallPosition()))
		{
			if (rodinControl == 0)
				m_winningTeam = BLUE;
			else
				m_winningTeam = RED;
			return true;
		}

		/* updates the remaining rods */
		for (int i = 0; i < RODS; ++i) {
			/* Skips the rod in control */
			if (i == rodinControl && actions[i].getActionType() == KICK)
				continue;

			/* Changes the Kick Action into No Action */
			if (actions[i].getActionType() == KICK)
				continue;

			/* Otherwise, Update the rods accordingly*/
			updateGame(actions[i], i);
		}

		/* updates the game grid */
		updateGrid();
		return false;
	}

	void moveBall() {
		BallPosition position = m_ball.getBallPosition();
		Direction direction = m_ball.getBallDirection();
		int source = m_ball.getBallSource();

		if (direction == UP && source == 1) {
			position.x--;
			position.y++;
		}
		else if (direction == UP && source == -1) {
			position.x--;
			position.y--;
		}
		else if (direction == FORWARD && source == 1) {
			position.y++;
		}
		else if (direction == FORWARD && source == -1) {
			position.y--;
		}
		else if (direction == DOWN && source == 1) {
			position.x++;
			position.y++;
		}
		else if (direction == DOWN && source == -1) {
			position.x++;
			position.y--;
		}

		/*If the ball new position is inside the grid */
		if (m_ball.updateBallPosition(position))
		{
			int power = m_ball.getBallPower();
			power--;
			m_ball.setBallPower(power);
		}
	}

	bool isGoal()
	{
		/* Check if the ball has power enough to be scored */
		if (m_ball.getBallPower() <= 0)
			return false;

		/* Get the current position of the ball */
		BallPosition position = m_ball.getBallPosition();

		/* Check the positions where a ball can be a goal*/
		if (position.x >= 2 && position.x <= 4
			&& (position.y == 0 || position.y == MAX_GRID_COLS - 1))
			return true;
		else
			return false;
	}

	void getActions(RodAction(&rodActions)[4]) {
		BallPosition position = m_ball.getBallPosition();
		/* Set the actions of the home team rods to No Action */
		if (m_homeTeam == RED)
		{
			rodActions[0].setNoAction();
			rodActions[2].setNoAction();
			if ((isBallInReach(m_rods[0]) && position.y == m_rods[0].getPositionInGrid() + 1)
				|| (isBallInReach(m_rods[2]) && position.y == m_rods[2].getPositionInGrid() + 1))
				Qlearning(rodActions);
			else
				simpleReflex(rodActions);
		}
		else
		{
			rodActions[1].setNoAction();
			rodActions[3].setNoAction();
			if ((isBallInReach(m_rods[1]) && position.y == m_rods[1].getPositionInGrid() + 1)
				|| (isBallInReach(m_rods[3]) && position.y == m_rods[3].getPositionInGrid() + 1))
				Qlearning(rodActions);
			else
				simpleReflex(rodActions);
		}
	}

	void Qlearning(RodAction(&rodActions)[4]) {
		int index = getRodInControl();
		BallPosition position = m_ball.getBallPosition();
		rodActions[index] = m_LearningAgent.getAction(m_rods[index], position);
	}

	void simpleReflex(RodAction(&rodActions)[4])
	{
		BallPosition position = m_ball.getBallPosition();
		if (m_homeTeam == RED)
		{
			if (position.y == 0 || position.y == 1)
			{
				if (isBallInReach(m_rods[0])) {
					rodActions[0].setActionKick(FORWARD, 1);
				}
				else
					rodActions[0] = Match(m_rods[0]);
			}
			if (position.y == 2)
			{
				if (m_ball.getBallPower() == 0)
					rodActions[0] = Match(m_rods[0]);
				else
					rodActions[0].setNoAction();
			}
			if (position.y == 3)
			{
				rodActions[0] = Match(m_rods[0]);
			}
			if (position.y == 5 || position.y == 6)
			{
				if (isBallInReach(m_rods[2])) {
					rodActions[2].setActionKick(FORWARD, 1);
				}
				else
					rodActions[2] = Match(m_rods[2]);
			}
			if (position.y == 7)
			{
				if (m_ball.getBallPower() == 0)
					rodActions[2] = Match(m_rods[2]);
				else
					rodActions[2].setNoAction();
			}
			if (position.y == 8)
			{
				rodActions[2] = Match(m_rods[2]);
			}
		}
		else
		{
			if (position.y == 10 || position.y == 9)
			{
				if (isBallInReach(m_rods[3])) {
					rodActions[3].setActionKick(FORWARD, 1);
				}
				else
					rodActions[3] = Match(m_rods[3]);
			}

			if (position.y == 8)
			{
				if (m_ball.getBallPower() == 0)
					rodActions[3] = Match(m_rods[3]);
				else
					rodActions[3].setNoAction();
			}
			if (position.y == 7)
			{
				rodActions[3] = Match(m_rods[3]);
			}
			if (position.y == 4)
			{
				if (isBallInReach(m_rods[1])) {
					rodActions[1].setActionKick(FORWARD, 1);
				}
				else
					rodActions[1] = Match(m_rods[1]);
			}
			if (position.y == 3)
			{
				if (m_ball.getBallPower() == 0)
					rodActions[1] = Match(m_rods[1]);
				else
					rodActions[1].setNoAction();
			}
			if (position.y == 2)
			{
				rodActions[1] = Match(m_rods[1]);
			}
		}

	}

	/** This function aligns the position of the ball such that it eventually comes to a player
	in Rod rod.
	@param rod to be aligned such that the ball always hits.
	@returns RodAction to be acted accordingly.
	*/
	RodAction Match(Rod rod) {
		/* Get the position of the ball */
		BallPosition position = m_ball.getBallPosition();

		/* If there is a player in the same row as the ball */
		if (m_grid[position.x][rod.getPositionInGrid()] == 5)
			return RodAction(NO_ACTION);

		/* else move the rod either downwards or upwards */
		if (rod.getOffset() == 0) {
			return RodAction(MOVE, DOWN);
		}
		else if (rod.getOffset() == 2) {
			return RodAction(MOVE, UP);
		}
		else
		{
			int middlePlayer = rod.getOffset() + 2;
			if (position.x < middlePlayer)
				return RodAction(MOVE, UP);
			else
				return RodAction(MOVE, DOWN);
		}
	}
};

#endif // ! _GAME_H