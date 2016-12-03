#pragma once
#ifndef _ACTION_H
#define _ACTION_H

#include <math.h>
#include "defs.h"
class RodAction {
private:
	Action m_actionType;
	Direction m_direction;
	int m_actionForce;

public:
	RodAction(Action actionType = NO_ACTION, Direction direction = FORWARD, int force = 0)
		: m_actionType(actionType), m_direction(direction), m_actionForce(force)
	{ };

	/**
		This function sets the parameters needed for MOVE action.
		@param direction a value of either UP or DOWN to move the rod upwards or downwards.
		@return true if no failure occurs in action.
	*/
	bool setActionMove(Direction direction)
	{
		if (direction != UP && direction != DOWN)
			return false;
		m_actionType = MOVE;
		m_direction = direction;
		m_actionForce = 0;
		return true;
	}
	
	/**
		This function sets the parameters needed for KICK action.
		@param direction to kick the ball either UP, FORWARD, DOWN.
		@param power a force value from 1 to 5 inclusive to kick the ball with.
		@return true if no failure occurs in action.
	*/
	bool setActionKick(Direction direction, int power)
	{
		if (direction != UP && direction != DOWN && direction != FORWARD)
			return false;
		if (power < 1 || power > 5)
			return false;

		m_actionType = KICK;
		m_direction = direction; 
		m_actionForce = power; 
		return true;
	}
	
	bool setNoAction()
	{
		m_actionType = NO_ACTION;
		m_direction = FORWARD;
		m_actionForce = 0;
		return true;
	}

	Action getActionType() const
	{
		return m_actionType;
	}

	Direction getActionDirection() const 
	{
		return m_direction;
	}

	int getActionForce() const 
	{
		return m_actionForce;
	}
};
#endif