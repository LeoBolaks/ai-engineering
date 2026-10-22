#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include "raylib.h"
#include "raymath.h"

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

	void makeCostField();

	void makeHeatMap();

	void makeIntegrationField();

	void makeVectorField();

	void generatePath();

	void update();

	void resetGrid();

	void draw();

private:
	bool mouseInsideGrid;

	Grid mainGrid;
	Vector2 mousePos;
	int mouseCellIndex;
	int startIndex;
	int goalIndex;
	std::queue<int> costFieldQueue;
	bool costFieldGenerated;
	bool heuristicsGenerated;
	bool pathGenerated;

	float maxCost;

	std::vector<int> algorithmPath;

	// Directions On The Grid
	int upLeft;
	int up;
	int upRight;

	int downLeft;
	int down;
	int downRight;

	int left;
	int right;

	bool viewCosts;
	bool viewHeuristics;
	bool viewDirections;
};