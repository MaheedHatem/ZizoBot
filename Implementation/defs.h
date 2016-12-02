#pragma once

#define MAX_GRID_ROWS 7
#define MAX_GRID_COLS 11
#define RODS 4
#include <iostream>
using namespace std;

struct BallPosition {
	unsigned int x; 
	unsigned int y;
};

void printMatrix(int matrix[MAX_GRID_ROWS][MAX_GRID_COLS], BallPosition ball) {
	for (int i = 0; i < MAX_GRID_ROWS; ++i) {
		for (int j = 0; j < MAX_GRID_COLS; ++j) {
			if (i == ball.x && j == ball.y)
				cout << "X" << " ";
			else
				cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << "====================================" << endl;
}

enum Team {RED = 1, BLUE = -1};

enum RodPosition {DEFENSE, ATTACK};

enum Action {MOVE, KICK, NO_ACTION};

enum BallDirection {UP, FORWARD, DOWN};

