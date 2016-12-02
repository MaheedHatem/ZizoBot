#pragma once
#ifndef _ACTION_H
#define _ACTION_H

#include <math.h>
#include "defs.h"
class RodAction {
private: 
	Action m_actionType;
	int m_actionForce; 
	int m_direction; 
public:
	RodAction() :m_actionType(NO_ACTION), m_actionForce(0), m_direction(0)
	{ };

	/**
		This function sets the parameters needed for MOVE action. 
		@param direction a value of either 1 or -1 to move the rod upwards or downwards.
		@return true if no failure occurs in action.
	*/
	bool setActionMove(int direction)
	{
		if (abs(direction) != 1)
			return false;
		m_actionType = MOVE;
		m_direction = direction;
		m_actionForce = 0;
		return true;
	}
	
	/**
		This function sets the parameters needed for KICK action.
		@param direction a value of either 1, 0 or -1 to kick the ball to the right, forward, left.
		@param power a force value from 1 to 5 inclusive to kick the ball with.
		@return true if no failure occurs in action.
	*/
	bool setActionKick(int direction, int power)
	{
		if (abs(direction) > 1)
			return false;
		if (power < 1 || power > 5)
			return false;

		m_actionType = KICK;
		m_direction = direction; 
		m_actionForce = power; 
		return true;
	}

	Action getActionType() const
	{
		return m_actionType;
	}

	int getActionDirection() const 
	{
		return m_direction;
	}

	int getActionForce() const 
	{
		return m_actionForce;
	}
};
#endif