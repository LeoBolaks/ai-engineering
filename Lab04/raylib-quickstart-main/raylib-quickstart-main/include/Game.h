#pragma once

#include <iostream>
#include <vector>
#include "Raylib.h"

struct Grid
{
	static const int GRID_SIZE = 100;
	int cellSize = 10;
	Vector2 positions[GRID_SIZE * GRID_SIZE]; // positions
	int indexes[GRID_SIZE * GRID_SIZE]; // numbered Cells
	int costs[GRID_SIZE * GRID_SIZE]; // numbers on grid away from goal
	float heuristics[GRID_SIZE * GRID_SIZE]; // distance
	Vector2 directions[GRID_SIZE * GRID_SIZE]; // direction to goal
	Color colours[GRID_SIZE * GRID_SIZE]; // colours of gridcells.

	int getIndex(int t_x, int t_y) { return t_y * GRID_SIZE + t_x; }
	int getGridSize() { return GRID_SIZE; }
};

class Game
{
public:
	Game();

	void update();

	void draw();

private:
	Grid mainGrid;
};