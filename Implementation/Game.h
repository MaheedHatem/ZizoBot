#pragma once
#ifndef _GAME_H
#define _GAME_H

#include "Ball.h"
#include "Rod.h"
#include "Action.h"
#include "defs.h"
class Game 
{
private:
	int m_grid[MAX_GRID_ROWS][MAX_GRID_COLS];
	Team m_homeTeam;
	Team m_awayTeam;
	Ball m_ball;
	Rod m_rods[RODS];

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
			unsigned int offset = 2 - m_rods[k].getOffset(); //calculated from the top
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
			if (m_rods[i].isInReach(ballPosition))
			{
				return i;
			}
		}
		return -1;
	}

public:
	Game(Team home, Team away) {
		initialiseGrid();
		m_homeTeam = home;
		m_awayTeam = away; 
		m_rods[0].setRodParameters(RED, DEFENSE);
		m_rods[1].setRodParameters(BLUE, ATTACK);
		m_rods[2].setRodParameters(RED, ATTACK);
		m_rods[3].setRodParameters(BLUE, DEFENSE);
	};

	void InitialiseGame() {
		m_ball.resetBallPosition();
		updateGrid();
	}

	void Print() {
		printMatrix(m_grid, m_ball.getBallPosition());
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
	*/
	void GameLoop(RodAction actions[]) {
		/* Find the rod that can do something with the ball */
		int rodinControl = getRodInControl();

		/* Perform the kick action first if exists */
		if (actions[rodinControl].getActionType() == KICK)
			updateGame(actions[rodinControl], rodinControl);

		/* updates the ball position accordingly */
		updateBall();

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
	}

	void moveBall() {
		BallPosition position = m_ball.getBallPosition();
		Direction direction = m_ball.getBallDirection();
		int source = m_ball.getBallSource();

		if (direction == UP && source == 1) {
			position.x--;
			position.y++;
			m_ball.updateBallPosition(position);
		}
		else if (direction == UP && source == -1) {
			position.x--;
			position.y--;
			m_ball.updateBallPosition(position);
		}
		else if (direction == FORWARD && source == 1) {
			position.y++;
			m_ball.updateBallPosition(position);
		}
		else if (direction == FORWARD && source == -1) {
			position.y--;
			m_ball.updateBallPosition(position);
		}
		else if (direction == DOWN && source == 1) {
			position.x++;
			position.y++;
			m_ball.updateBallPosition(position);
		}
		else if (direction == DOWN && source == -1) {
			position.x++;
			position.y--;
			m_ball.updateBallPosition(position);
		}
		int power = m_ball.getBallPower();
		power--;
		m_ball.setBallPower(power);
	}
};
#endif // ! _GAME_H
