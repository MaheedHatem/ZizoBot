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
	unsigned int m_grid[MAX_GRID_ROWS][MAX_GRID_COLS];
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
		m_rods[0].setRodParameters(home, DEFENSE);
		m_rods[1].setRodParameters(away, ATTACK);
		m_rods[2].setRodParameters(home, ATTACK);
		m_rods[3].setRodParameters(away, DEFENSE);
	};

	void InitialiseGame() {
		m_ball.resetBallPosition();
	}

	void updateBall(RodAction action)
	{
		int rodIndex = getRodInControl();
		BallPosition ball = m_ball.getBallPosition();
		Action actionType = action.getActionType();
		if (actionType = Action::MOVE) {
			/*
				Write the move logic here
			*/
		}

		if (actionType == Action::KICK && m_grid[ball.x][ball.y]) {
			/*
				Write the kick logic here
			*/
		}

		if (actionType == Action::NO_ACTION)
		{
			/*
				Write the No Action logic here
			*/

			/*
			*/
		}
	}
};
#endif // ! _GAME_H
