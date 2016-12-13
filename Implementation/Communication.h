#pragma once

#ifndef _COMMUNICATION_H
#define _COMMUNICATION_H

#include <string>
#include "Game.h"
#include <Windows.h>



#define PIPE_UPSTREAM "\\\\.\\pipe\\ImplementationToIntegrationUpPipe";
#define PIPE_DOWNSTREAM "\\\\.\\pipe\\ImplementationToIntegrationDownPipe";

class Communication {
private:
	HANDLE hUpPipe;
	HANDLE hDownPipe;
	string getMessageToInterface(RodAction rodActions[4]) {
		string message = "";
		for (int i = 0; i < 4; i++) {
			message = message + to_string(i + 1);
			int d = 0;
			switch (rodActions[i].getActionDirection()) {
			case UP:
				d = 1;
				break;
			case DOWN:
				d = -1;
				break;
			case FORWARD:
				d = 0;
				break;
			}
			switch (rodActions[i].getActionType()) {
			case NO_ACTION:
				message = message + " NoAction";
				break;
			case MOVE:
				message = message + " Move " + to_string(d);
				break;
			case KICK:
				message = message + " Kick " + to_string(d) + " " + to_string(rodActions[i].getActionForce());
				break;
			}
			message = message + ",";
		}

		return message;
	}

	Game initGame() {
		char buffer[1024];
		DWORD dwRead;
		ReadFile(hDownPipe, buffer, sizeof(buffer) - 1, &dwRead, NULL);
		buffer[dwRead] = '\0';
		stringstream ss(buffer);
		string team; float alpha, gamma, epsilon;
		ss >> team >> alpha >> gamma >> epsilon;
		Team homeTeam;
		Team awayTeam;
		if (team == "RED") {
			homeTeam = Team::RED;
			awayTeam = Team::BLUE;
		}
		else {
			homeTeam = Team::BLUE;
			awayTeam = Team::RED;
		}

		Game game(homeTeam, awayTeam);//, alpha, gamma, epsilon);

		game.InitialiseGame();
		return game;
	}

	void ParseActions(RodAction rodActions[4], char buffer[1024]) {
		stringstream ss(buffer);
		for (int i = 0; i < 4; i++) {
			int rod;
			ss >> rod;
			rod--;
			string action;
			ss >> action;
			if (action == "NoAction") {
				rodActions[rod].setNoAction();
			}
			else if (action == "Move") {
				int d;
				ss >> d;
				Direction dir;
				if (d == 1) {
					dir = UP;
				}
				else if (d == -1) {
					dir = DOWN;
				}
				rodActions[rod].setActionMove(dir);
			}
			else if (action == "Kick") {
				int d;
				int power;
				ss >> d >> power;
				Direction dir;
				if (d == 1) {
					dir = UP;
				}
				else if (d == -1) {
					dir = DOWN;
				}
				else if (d == 0) {
					dir = FORWARD;
				}
				rodActions[rod].setActionKick(dir, power);
			}
		}
	}

public:
	Communication() {
		while (!WaitNamedPipe(TEXT("\\\\.\\pipe\\ImplementationToIntegrationUpPipe"), NMPWAIT_WAIT_FOREVER)) {

		}
		Sleep(500);
		hUpPipe = CreateFile(TEXT("\\\\.\\pipe\\ImplementationToIntegrationUpPipe"),
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			0,
			NULL);
		while (!WaitNamedPipe(TEXT("\\\\.\\pipe\\ImplementationToIntegrationDownPipe"), NMPWAIT_WAIT_FOREVER)) {

		}
		Sleep(500);
		hDownPipe = CreateFile(TEXT("\\\\.\\pipe\\ImplementationToIntegrationDownPipe"),
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			0,
			NULL);
	}

	void GameLoop()
	{
		char buffer[1024];
		RodAction action1(NO_ACTION);
		RodAction action2(NO_ACTION);
		RodAction action3(NO_ACTION);
		RodAction action4(NO_ACTION);
		RodAction rodActions[4] = { action1, action2, action3, action4 };
		DWORD dwRead;
		DWORD dwWritten;
		Game game = initGame();
		while (1) {
			ReadFile(hDownPipe, buffer, sizeof(buffer) - 1, &dwRead, NULL);
			buffer[dwRead] = '\0';
			ParseActions(rodActions, buffer);
			game.step(rodActions);
			BallPosition ballPosition = game.m_ball.getBallPosition();
			string message = to_string(ballPosition.x) + " " + to_string(ballPosition.y) + " " + to_string(game.m_homeScore) + " " + to_string(game.m_awayScore) +"\n";
			WriteFile(hUpPipe, message.c_str(), message.length(), &dwWritten, NULL);
			game.getActions(rodActions);
			message = getMessageToInterface(rodActions) + "\n";
			WriteFile(hUpPipe, message.c_str(), message.length(), &dwWritten, NULL);
		}
		CloseHandle(hUpPipe);
		CloseHandle(hDownPipe);
	}

};
#endif