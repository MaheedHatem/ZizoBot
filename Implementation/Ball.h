#pragma once
#ifndef _BALL_H
#define _BALL_H
#include "defs.h"

class Ball {
private:
	BallPosition m_position;
	BallDirection m_direction;
	int m_power;
	
	bool isValidx(unsigned int x) {
		return(x >= 0 && x < MAX_GRID_ROWS);
	}

	bool isValidy(unsigned int y) {
		return(y >= 0 && y < MAX_GRID_COLS);
	}

public:
	Ball() 
	{
		m_direction = BallDirection::FORWARD;
		m_power = 0;
		resetBallPosition();
	};

	void updateBallPosition(BallPosition newPos) {
		if (isValidx(newPos.x) && isValidy(newPos.y))
		{
			m_position.x = newPos.x;
			m_position.y = newPos.y;
		}
	}

	BallPosition getBallPosition() {
		return m_position;
	}

	void resetBallPosition() {
		m_position.x = 3;
		m_position.y = 5;
	}
};
#endif // !_BALL_H
