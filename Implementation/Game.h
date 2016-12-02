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

	void updateBall()
	{
		BallPosition position = m_ball.getBallPosition();
		int source = m_ball.getBallSource();
		int power = m_ball.getBallPower();
		BallDirection direction = m_ball.getBallDirection();
		if (power <= 0)
			return;
		/* If the ball hit a player position */
		if (m_grid[position.x][position.y] == 5)
		{
			int rodIndex = getRodInControl();
			if (m_rods[rodIndex].m_team != source) {
				rebound();
				source = m_ball.getBallSource();
			}
		}
		/* If the ball has remaining power */
		if (m_ball.getBallPower() > 0) {
			moveBall(position, source, direction);
		}
	}

	void updateGame(RodAction action, int rodIndex)
	{
		Action actionType = action.getActionType();
		BallPosition ballPosition = m_ball.getBallPosition();
		if (actionType == Action::MOVE) {
			int direction = action.getActionDirection();
			m_rods[rodIndex].changeOffset(direction);
			return;
		} 

		if (actionType == Action::KICK && m_grid[ballPosition.x][ballPosition.y]) 
		{
			m_ball.setBallPower(action.getActionForce());
			m_ball.setBallDirection(action.getActionDirection());
			if (m_rods[rodIndex].m_team == Team::RED)
			{
				m_ball.setBallSource(1);
			}
			else
			{
				m_ball.setBallSource(-1);
			}
		}
	}

	void GameLoop(RodAction actions[]) {
		int rodinControl = getRodInControl();
		if (actions[rodinControl].getActionType() == Action::KICK)
			updateGame(actions[rodinControl], rodinControl);

		updateBall();
		for (int i = 0; i < RODS; ++i) {
			/* Skips the rod in control */
			if (i == rodinControl && actions[i].getActionType() == Action::KICK)
				continue;

			/* Changes the Kick Action into No Action */
			if (actions[i].getActionType() == Action::KICK)
				continue;

			/* Otherwise, Update the rods accordingly*/
			updateGame(actions[i], i);
		}
		updateGrid();
	}

	void rebound() {
		int source = -1 * m_ball.getBallSource();
		m_ball.setBallSource(source);
		m_ball.setBallPower(2);
	}

	void moveBall(BallPosition position, int source, BallDirection direction) {
		BallPosition pos = position;
		if (direction == UP && source == 1) {
			pos.x--;
			pos.y++;
			m_ball.updateBallPosition(pos);
		}
		else if (direction == UP && source == -1) {
			pos.x--;
			pos.y--;
			m_ball.updateBallPosition(pos);
		}
		else if (direction == FORWARD && source == 1) {
			pos.y++;
			m_ball.updateBallPosition(pos);
		}
		else if (direction == FORWARD && source == -1) {
			pos.y--;
			m_ball.updateBallPosition(pos);
		}
		else if (direction == DOWN && source == 1) {
			pos.x++;
			pos.y++;
			m_ball.updateBallPosition(pos);
		}
		else if (direction == DOWN && source == -1) {
			pos.x++;
			pos.y--;
			m_ball.updateBallPosition(pos);
		}
		int power = m_ball.getBallPower();
		power--;
		m_ball.setBallPower(power);
	}
};
#endif // ! _GAME_H
