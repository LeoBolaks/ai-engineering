#include "Game.h"

Game::Game()
{
	for (int x = 0; x < mainGrid.getGridSize(); x++)
	{
		for (int y = 0; y < mainGrid.getGridSize(); y++)
		{
			int i = mainGrid.getIndex(x, y);
			mainGrid.positions[i].x = (x * mainGrid.cellSize);
			mainGrid.positions[i].y = (y * mainGrid.cellSize);
		}
	}
}

void Game::update()
{

}

void Game::draw()
{
	for (int i = 0; i < mainGrid.getGridSize() * mainGrid.getGridSize(); i++)
	{
		DrawRectangleLines(mainGrid.positions[i].x, mainGrid.positions[i].y, mainGrid.cellSize, mainGrid.cellSize, WHITE);
	}
}
