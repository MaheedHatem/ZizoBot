#pragma once

#define MAX_GRID_ROWS 7
#define MAX_GRID_COLS 11
#define RODS 4

struct BallPosition {
	unsigned int x; 
	unsigned int y;
};

enum Team {RED, BLUE};

enum RodPosition {DEFENSE, ATTACK};

enum Action {MOVE, KICK, NO_ACTION};

enum BallDirection {RIGHT, FORWARD, LEFT};