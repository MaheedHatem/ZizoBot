#pragma once
#ifndef _ROD_H
#define _ROD_H

#include "defs.h"
class Rod
{
private:
	Team m_team; 
	RodPosition m_position; 
	unsigned int m_rodNo;
	unsigned int m_offset;
	unsigned int m_positionInGrid;

	void incrementOffset()
	{
		if (m_offset < 2)
			m_offset++;
	}

	void decrementOffset() 
	{
		if (m_offset > 0)
			m_offset--;
	}

public:
	unsigned int m_from_range;
	unsigned int m_to_range;
	Rod() : m_offset(1), m_from_range(0), m_to_range(0)
	{ };

	void setRodParameters(Team team, RodPosition position)
	{
		m_team = team;
		m_position = position;
		if (m_team == RED && m_position == DEFENSE) {
			m_rodNo = 1;
			m_from_range = 0;
			m_to_range = 2;
			m_positionInGrid = 1;
		}
		else if (m_team == BLUE && m_position == ATTACK) {
			m_rodNo = 2;
			m_from_range = 3;
			m_to_range = 4;
			m_positionInGrid = 4;
		}
		else if (m_team == RED && m_position == ATTACK) {
			m_rodNo = 3;
			m_from_range = 5;
			m_to_range = 7;
			m_positionInGrid = 6;
		}
		else {
			m_rodNo = 4;
			m_from_range = 8;
			m_to_range = 10;
			m_positionInGrid = 9;
		}
	}

	bool isInReach(unsigned int ballPosition) {
		return (ballPosition >= m_from_range && ballPosition <= m_to_range);
	}

	void changeOffset(int direction) 
	{
		if (direction == 1)
			incrementOffset();
		else
			decrementOffset();
	}

	unsigned int getOffset()
	{
		return m_offset;
	}

	unsigned int getRodNo()
	{
		return m_rodNo;
	}

	unsigned int getPositionInGrid()
	{
		return m_positionInGrid;
	}
};

#endif   // ! _ROD_H
