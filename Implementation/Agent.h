#pragma once
#ifndef _AGENT_H
#define _AGENT_H

#include "Game.h"
#include "defs.h"
class Agent {
	public:
		Game m_game;
		RodAction actions[2];
		Agent(Game g) 
		{
			m_game = g;
		}
		void simpleReflexAgent() {
			BallPosition position = m_game.m_ball.getBallPosition();
			if (m_game.m_homeTeam == RED)
			{
				if (m_game.m_ball)
			}
			else
			{

			}
		}

};



#endif