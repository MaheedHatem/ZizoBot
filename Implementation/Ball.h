#pragma once
#ifndef _BALL_H
#define _BALL_H

#include <math.h>
#include "defs.h"

class Ball {
private:
	BallPosition m_position;
	BallDirection m_direction;
	int m_source; //indicates how the ball is moving
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
		m_source = -1;
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

	BallDirection getBallDirection() {
		return m_direction;
	}

	int getBallPower() {
		return m_power;
	}

	int getBallSource() {
		return m_source;
	}

	void setBallSource(int source) {
		if (abs(source) == 1) {
			m_source = source;
		}
	}

	void setBallPower(int power) {
		if (power >= 0 && power <= 5) {
			m_power = power;
		}
	}

	void setBallDirection(int direction) {
		if (direction == 1)
			m_direction = UP;
		else if (direction == 0)
			m_direction = FORWARD;
		else if (direction == -1)
			m_direction = DOWN;
	}

};
#endif // !_BALL_H
