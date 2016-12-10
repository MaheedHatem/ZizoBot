#pragma once
#ifndef _QLEARNER_H
#define _QLEARNER_H

#include "defs.h"
#include "Game.h"
#include <time.h>
#include <random>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>

class Qlearner
{
private:
	Team m_homeTeam;
	int m_rewardGrid[MAX_GRID_ROWS][MAX_GRID_COLS];
	float m_alpha;
	float m_gamma;
	float m_epsilon;
	float m_LearningDefender[STATES][ACTIONS];
	float m_LearningAttacker[STATES][ACTIONS];

public:
	Qlearner(Team home_team = RED, float alpha = 0.0f, float gamma = 0.0f, float epsilon = 1.0f) {
		srand(static_cast<unsigned>(time(NULL)));
		setParameters(home_team, alpha, gamma, epsilon);
	}

	void setParameters(Team home_team, float alpha, float gamma, float epsilon) {
		m_homeTeam = home_team;
		m_alpha = alpha;
		m_gamma = gamma;
		m_epsilon = epsilon;
		if (m_homeTeam == RED) {
			readMatrix("red.txt", REWARD);
			readMatrix("q1.txt", QVALUES1);
			readMatrix("q3.txt", QVALUES3);
		}
		else {
			readMatrix("blue.txt", REWARD);
			readMatrix("q2.txt", QVALUES2);
			readMatrix("q4.txt", QVALUES4);
		}
	}
	RodAction getAction(Rod& rod, BallPosition& position) {
		float random = (rand() % 100) / 100.0f;
		if (random < m_epsilon)
		{
			int randomAction = (rand() % 3) - 1;
			return RodAction(KICK, (Direction)randomAction, 5);
		}
		else
		{
			RodAction action = getBestAction(rod, position);
			ostringstream converter;
			converter << rod.getRodNo();
			std::string filePath = "q" + converter.str() + ".txt";
			writeMatrix(filePath, (Matrix)rod.getRodNo());
			return action;
		}
	}

	int getCurrentState (Rod& rod, BallPosition& ballPosition) {
		int offset = rod.getOffset();
		int rowIndex = 0;
		int x = ballPosition.x;
		
		if (offset == 0) {
			if (x == 0) { rowIndex = 0; }
			else if (x == 2) { rowIndex = 1; }
			else if (x == 4) { rowIndex = 2; }
		}
		if (offset == 1) {
			if (x == 1) { rowIndex = 0; }
			else if (x == 3) { rowIndex = 1; }
			else if (x == 5) { rowIndex = 2; }
		}
		if (offset == 2) {
			if (x == 2) { rowIndex = 0; }
			else if (x == 4) { rowIndex = 1; }
			else if (x == 6) { rowIndex = 2; }
		}
		rowIndex += (offset * 3);
		return rowIndex;
	}
	
	RodAction getBestAction(Rod& rod, BallPosition& ballPosition) {
		int currentState = getCurrentState(rod, ballPosition);
		float qValue = 0.0f;
		int bestAction = -1;
		unsigned int from = 0;
		unsigned int to = 3;
		if (currentState == 0) { to = 2; }
		else if (currentState == 8) { from = 1; }

		if (rod.getRodPosition() == DEFENSE) {
			float maxQ = m_LearningDefender[currentState][from];
			for (unsigned int i = from; i < to; ++i) {
				qValue = m_LearningDefender[currentState][i];
				if (maxQ <= qValue) {
					maxQ = qValue;
					bestAction = i-1;
				}
			} 
			int reward = getReward(ballPosition, (Direction)bestAction);
			m_LearningDefender[currentState][bestAction+1] +=
				m_alpha*(reward + (m_gamma*maxQ) - m_LearningDefender[currentState][bestAction+1]);
		}
		
		if (rod.getRodPosition() == ATTACK) {
			float maxQ = m_LearningAttacker[currentState][from];
			for (unsigned int i = from; i < to; ++i) {
				qValue = m_LearningAttacker[currentState][i];
				if (maxQ <= qValue) {
					maxQ = qValue;
					bestAction = i-1;
				}
			}
			int reward = getReward(ballPosition, (Direction)bestAction);
			m_LearningAttacker[currentState][bestAction + 1] +=
				m_alpha*(reward + (m_gamma*maxQ) - m_LearningAttacker[currentState][bestAction + 1]);
		}
		return RodAction(KICK, (Direction)bestAction, 5);
	}

	int getReward(BallPosition& position, Direction direction) {
		int source = (m_homeTeam == RED) ? 1 : -1;

		if (direction == UP && source == 1) {
			position.x-=5;
			position.y+=5;
		}
		else if (direction == UP && source == -1) {
			position.x-=5;
			position.y-=5;
		}
		else if (direction == FORWARD && source == 1) {
			position.y+=5;
		}
		else if (direction == FORWARD && source == -1) {
			position.y-=5;
		}
		else if (direction == DOWN && source == 1) {
			position.x+=5;
			position.y+=5;
		}
		else if (direction == DOWN && source == -1) {
			position.x+=5;
			position.y-=5;
		}
		if (position.x < 0) {
			position.x = 0;
		}
		else if (position.x > MAX_GRID_ROWS - 1) {
			position.x = MAX_GRID_ROWS - 1;
		}
		if (position.y < 0) {
			position.y = 0;
		}
		else if (position.y > MAX_GRID_COLS - 1) {
			position.y = MAX_GRID_COLS - 1;
		}
		return m_rewardGrid[position.x][position.y];
	}

	void readMatrix(std::string Path, Matrix matrix)
	{
		std::ifstream reader;
		reader.open(Path);

		if (matrix == REWARD) {
			for (int i = 0; i < MAX_GRID_ROWS; ++i) {
				for (int j = 0; j < MAX_GRID_COLS; ++j) {
					reader >> m_rewardGrid[i][j];
				}
			}
		}
		else if (matrix == QVALUES1 || matrix == QVALUES4) {
			for (int i = 0; i < STATES; ++i) {
				for (int j = 0; j < ACTIONS; ++j) {
					reader >> m_LearningDefender[i][j];
				}
			}
		}
		else if (matrix == QVALUES2 || matrix == QVALUES3) {
			for (int i = 0; i < STATES; ++i) {
				for (int j = 0; j < ACTIONS; ++j) {
					reader >> m_LearningAttacker[i][j];
				}
			}
		}
		reader.close();
	}

	void writeMatrix(std::string path, Matrix matrix)
	{
		std::ofstream writer;
		writer.open(path);

		if (matrix == QVALUES1 || matrix == QVALUES3) {
			for (int i = 0; i < STATES; ++i) {
				string delimiter = "";
				for (int j = 0; j < ACTIONS; ++j) {
					writer << delimiter << m_LearningDefender[i][j];
					delimiter = " ";
				}
			}
		}
		else if (matrix == QVALUES2 || matrix == QVALUES4) {
			for (int i = 0; i < STATES; ++i) {
				string delimiter = "";
				for (int j = 0; j < ACTIONS; ++j) {
					writer << delimiter << m_LearningAttacker[i][j];
					delimiter = " ";
				}
				writer << endl;
			}
		}
		writer.close();
	}

};
#endif // !_QLEARNER_H