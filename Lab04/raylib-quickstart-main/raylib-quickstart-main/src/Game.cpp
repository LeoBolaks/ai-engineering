#include "include/Game.h"

Game::Game()
{
	costFieldGenerated = false;
	heuristicsGenerated = false;
	flowFieldGenerated = false;
	pathGenerated = false;
	startIndex = -1;
	goalIndex = -1;
	mouseCellIndex = 0;

	viewCosts = false;
	viewHeuristics = false;
	viewDirections = false;

	//set up grid direction variables based on the size of the grid
	upLeft = -mainGrid.getGridSize() - 1;
	up = -mainGrid.getGridSize();
	upRight = -mainGrid.getGridSize() + 1;

	downLeft = mainGrid.getGridSize() - 1;
	down = mainGrid.getGridSize();
	downRight = mainGrid.getGridSize() + 1;

	left = -1;
	right = 1;

	for (int x = 0; x < mainGrid.getGridSize(); x++)
	{
		for (int y = 0; y < mainGrid.getGridSize(); y++)
		{
			int i = mainGrid.getIndex(x, y);
			mainGrid.positions[i].x = (x * mainGrid.cellSize);
			mainGrid.positions[i].y = (y * mainGrid.cellSize);

			mainGrid.colours[i] = Color{ 60, 60, 255, 255 };
			mainGrid.costs[i] = -1;
			mainGrid.indexes[i] = i;
			mainGrid.directions[i] = { 0,0 };
		}
	}
	npc.setDirections(mainGrid.directions, mainGrid.getGridSize() * mainGrid.getGridSize());
}

void Game::makeCostField()
{
	maxCost = 0.0f;
	heuristicsGenerated = false;
	flowFieldGenerated = false;
	pathGenerated = false;
	costFieldQueue.push(goalIndex);
	mainGrid.costs[goalIndex] = 0;

	while (!costFieldQueue.empty())
	{
		int currentIndex = costFieldQueue.front();
		costFieldQueue.pop();

		int currentX = currentIndex % mainGrid.getGridSize();
		int currentY = currentIndex / mainGrid.getGridSize();
		int currentCost = mainGrid.costs[currentIndex];

		// check gridcell up
		if (currentY > 0)
		{
			int upIndex = currentIndex + up;
			if (mainGrid.costs[upIndex] != 999 && mainGrid.costs[upIndex] == -1)
			{
				mainGrid.costs[upIndex] = currentCost + 1;
				costFieldQueue.push(upIndex);
			}
		}
		// check gridcell up right
		if (currentY > 0 && currentX < mainGrid.getGridSize() - 1)
		{
			int upRightIndex = currentIndex + upRight;
			if (mainGrid.costs[upRightIndex] != 999 && mainGrid.costs[upRightIndex] == -1)
			{
				mainGrid.costs[upRightIndex] = currentCost + 1;
				costFieldQueue.push(upRightIndex);
			}
		}
		// check gridcell right
		if (currentX < mainGrid.getGridSize() - 1)
		{
			int rightIndex = currentIndex + right;
			if (mainGrid.costs[rightIndex] != 999 && mainGrid.costs[rightIndex] == -1)
			{
				mainGrid.costs[rightIndex] = currentCost + 1;
				costFieldQueue.push(rightIndex);
			}
		}
		// check gridcell down right
		if (currentY < mainGrid.getGridSize() - 1 && currentX < mainGrid.getGridSize() - 1)
		{
			int downRightIndex = currentIndex + downRight;
			if (mainGrid.costs[downRightIndex] != 999 && mainGrid.costs[downRightIndex] == -1)
			{
				mainGrid.costs[downRightIndex] = currentCost + 1;
				costFieldQueue.push(downRightIndex);
			}
		}
		// check gridcell down
		if (currentY < mainGrid.getGridSize() - 1)
		{
			int downIndex = currentIndex + down;
			if (mainGrid.costs[downIndex] != 999 && mainGrid.costs[downIndex] == -1)
			{
				mainGrid.costs[downIndex] = currentCost + 1;
				costFieldQueue.push(downIndex);
			}
		}
		// check gridcell down left
		if (currentY < mainGrid.getGridSize() - 1 && currentX > 0)
		{
			int downLeftIndex = currentIndex + downLeft;
			if (mainGrid.costs[downLeftIndex] != 999 && mainGrid.costs[downLeftIndex] == -1)
			{
				mainGrid.costs[downLeftIndex] = currentCost + 1;
				costFieldQueue.push(downLeftIndex);
			}
		}
		// check gridcell left
		if (currentX > 0)
		{
			int leftIndex = currentIndex + left;
			if (mainGrid.costs[leftIndex] != 999 && mainGrid.costs[leftIndex] == -1)
			{
				mainGrid.costs[leftIndex] = currentCost + 1;
				costFieldQueue.push(leftIndex);
			}
		}
		// check gridcell up left
		if (currentY > 0 && currentX > 0)
		{
			int upLeftIndex = currentIndex + upLeft;
			if (mainGrid.costs[upLeftIndex] != 999 && mainGrid.costs[upLeftIndex] == -1)
			{
				mainGrid.costs[upLeftIndex] = currentCost + 1;
				costFieldQueue.push(upLeftIndex);
			}
		}
		maxCost = currentCost + 1;
	}
	makeHeatMap();
	costFieldGenerated = true;
}

void Game::makeHeatMap()
{
	for (int i = 0; i < mainGrid.getGridSize() * mainGrid.getGridSize(); i++)
	{
		float ratio = static_cast<float>(mainGrid.costs[i]) / maxCost;

		Color lightBlue = { 60, 60, 255, 255 }; 
		Color darkBlue = { 0, 0, 40, 255 };   

		mainGrid.colours[i].r = 0;
		mainGrid.colours[i].g = 0;
		mainGrid.colours[i].b = lightBlue.b + (darkBlue.b - lightBlue.b) * ratio;
		mainGrid.colours[i].a = 255;
	}
}

void Game::makeIntegrationField()
{
	float halfCellSize = mainGrid.cellSize / 2;
	for (int i = 0; i < mainGrid.getGridSize() * mainGrid.getGridSize(); i++)
	{
		if (i == goalIndex)
		{
			mainGrid.heuristics[i] = 0.0f;
		}
		else if (mainGrid.costs[i] == 999 || mainGrid.costs[i] == -1)
		{
			mainGrid.heuristics[i] = 99999.0f;
		}

		else
		{
			float currentX = (i % mainGrid.getGridSize());
			float currentY = (i / mainGrid.getGridSize());

			float gX = (goalIndex % mainGrid.getGridSize());
			float gY = (goalIndex / mainGrid.getGridSize());

			float distance = Vector2Distance({ currentX, currentY }, { gX, gY });

			mainGrid.heuristics[i] = mainGrid.costs[i] + (distance * 0.5f);
		}
	}
	makeVectorField();
	heuristicsGenerated = true;
}

void Game::makeVectorField()
{
	for (int i = 0; i < mainGrid.getGridSize() * mainGrid.getGridSize(); i++)
	{
		if (mainGrid.costs[i] == 999 || mainGrid.costs[i] == -1 || i == goalIndex)
		{
			mainGrid.directions[i] = { 0.0f, 0.0f };
			continue;
		}

		float lowestHeuristic = 99999.0f;
		int bestNeighbourIndex = -1;

		int currentX = i % mainGrid.getGridSize();
		int currentY = i / mainGrid.getGridSize();

		// check gridcell up
		if (currentY > 0)
		{
			int upIndex = i + up;
			if (mainGrid.heuristics[upIndex] < lowestHeuristic)
			{
				lowestHeuristic = mainGrid.heuristics[upIndex];
				bestNeighbourIndex = upIndex;
			}
		}
		// check gridcell up right
		if (currentY > 0 && currentX < mainGrid.getGridSize() - 1)
		{
			int upRightIndex = i + upRight;
			if (mainGrid.heuristics[upRightIndex] < lowestHeuristic)
			{
				lowestHeuristic = mainGrid.heuristics[upRightIndex];
				bestNeighbourIndex = upRightIndex;
			}
		}
		// check gridcell right
		if (currentX < mainGrid.getGridSize() - 1)
		{
			int rightIndex = i + right;
			if (mainGrid.heuristics[rightIndex] < lowestHeuristic)
			{
				lowestHeuristic = mainGrid.heuristics[rightIndex];
				bestNeighbourIndex = rightIndex;
			}
		}
		// check gridcell down right
		if (currentY < mainGrid.getGridSize() - 1 && currentX < mainGrid.getGridSize() - 1)
		{
			int downRightIndex = i + downRight;
			if (mainGrid.heuristics[downRightIndex] < lowestHeuristic)
			{
				lowestHeuristic = mainGrid.heuristics[downRightIndex];
				bestNeighbourIndex = downRightIndex;
			}
		}
		// check gridcell down
		if (currentY < mainGrid.getGridSize() - 1)
		{
			int downIndex = i + down;
			if (mainGrid.heuristics[downIndex] < lowestHeuristic)
			{
				lowestHeuristic = mainGrid.heuristics[downIndex];
				bestNeighbourIndex = downIndex;
			}
		}
		// check gridcell down left
		if (currentY < mainGrid.getGridSize() - 1 && currentX > 0)
		{
			int downLeftIndex = i + downLeft;
			if (mainGrid.heuristics[downLeftIndex] < lowestHeuristic)
			{
				lowestHeuristic = mainGrid.heuristics[downLeftIndex];
				bestNeighbourIndex = downLeftIndex;
			}
		}
		// check gridcell left
		if (currentX > 0)
		{
			int leftIndex = i + left;
			if (mainGrid.heuristics[leftIndex] < lowestHeuristic)
			{
				lowestHeuristic = mainGrid.heuristics[leftIndex];
				bestNeighbourIndex = leftIndex;
			}
		}
		// check gridcell up left
		if (currentY > 0 && currentX > 0)
		{
			int upLeftIndex = i + upLeft;
			if (mainGrid.heuristics[upLeftIndex] < lowestHeuristic)
			{
				lowestHeuristic = mainGrid.heuristics[upLeftIndex];
				bestNeighbourIndex = upLeftIndex;
			}
		}

		if (bestNeighbourIndex != -1)
		{
			float halfCellSize = mainGrid.cellSize / 2;

			Vector2 currentCellCenter = { mainGrid.positions[i].x + halfCellSize, mainGrid.positions[i].y + halfCellSize };
			Vector2 neighbourCellCenter = { mainGrid.positions[bestNeighbourIndex].x + halfCellSize, mainGrid.positions[bestNeighbourIndex].y + halfCellSize };

			Vector2 direction = Vector2Subtract(neighbourCellCenter, currentCellCenter);

			mainGrid.directions[i] = Vector2Normalize(direction);
		}
	}
	flowFieldGenerated = true;
}

void Game::generatePath()
{
	int maxStep = 1000;
	int counter = 0;
	algorithmPath.clear();

	int currentIndex = startIndex;

	while (currentIndex != goalIndex && counter < maxStep)
	{
		algorithmPath.push_back(currentIndex);

		int stepX = std::round(mainGrid.directions[currentIndex].x);
		int stepY = std::round(mainGrid.directions[currentIndex].y);

		if (stepX == 0 && stepY == 0)
		{
			break;
		}

		currentIndex = currentIndex + (stepY * mainGrid.getGridSize()) + stepX;
		counter++;
	}
	pathGenerated = true;
}

void Game::update()
{

	npc.update();
	npc.setFlowFlag(flowFieldGenerated);
	if (IsKeyPressed(KEY_C))
	{
		viewCosts = !viewCosts;
	}
	if (IsKeyPressed(KEY_V))
	{
		viewHeuristics = !viewHeuristics;
	}
	if (IsKeyPressed(KEY_B))
	{
		viewDirections = !viewDirections;
	}
	if (goalIndex > -1 && !costFieldGenerated)
	{
		makeCostField();
	}
	if (goalIndex > -1 && costFieldGenerated)
	{
		makeIntegrationField();
	}
	if (heuristicsGenerated && startIndex > -1 && goalIndex > -1 && !pathGenerated)
	{
		generatePath();
	}
	mousePos = GetMousePosition();

	int gridX = static_cast<int>(mousePos.x) / mainGrid.cellSize;
	int gridY = static_cast<int>(mousePos.y) / mainGrid.cellSize;

	if (gridX >= 0 && gridX < mainGrid.getGridSize() && gridY >= 0 && gridY < mainGrid.getGridSize())
	{
		mouseCellIndex = mainGrid.getIndex(gridX, gridY);
		mouseInsideGrid = true;
	}
	else
	{
		mouseInsideGrid = false;
	}

	if (mouseInsideGrid && IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT) && mainGrid.costs[mouseCellIndex] != 999 && mouseCellIndex != goalIndex)
	{
		if (pathGenerated)
		{
			pathGenerated = false;
		}
		startIndex = mouseCellIndex;
		npc.setPosition({ mainGrid.positions[startIndex].x + (mainGrid.cellSize / 2), mainGrid.positions[startIndex].y});
	}
	if (mouseInsideGrid && IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_RIGHT) && mainGrid.costs[mouseCellIndex] != 999 && mouseCellIndex != startIndex)
	{
		if (costFieldGenerated)
		{
			resetGrid();
			costFieldGenerated = false;
		}
		goalIndex = mouseCellIndex;
	}
	if (mouseInsideGrid && IsMouseButtonDown(MouseButton::MOUSE_BUTTON_MIDDLE))
	{
		mainGrid.costs[mouseCellIndex] = 999;
		if (costFieldGenerated)
		{
			resetGrid();
			costFieldGenerated = false;
		}
	}
	if (mouseInsideGrid && IsMouseButtonDown(MouseButton::MOUSE_BUTTON_MIDDLE) && IsKeyDown(KEY_LEFT_SHIFT))
	{
		if (mainGrid.costs[mouseCellIndex] == 999)
		{
			mainGrid.costs[mouseCellIndex] = -1;
			if (costFieldGenerated)
			{
				resetGrid();
				costFieldGenerated = false;
			}
			return;
		}
	}

}

void Game::resetGrid()
{
	for (int i = 0; i < mainGrid.getGridSize() * mainGrid.getGridSize(); i++)
	{
		if (mainGrid.costs[i] != 999)
		{
			mainGrid.costs[i] = -1;
		}
	}
}

void Game::draw()
{
	for (int i = 0; i < mainGrid.getGridSize() * mainGrid.getGridSize(); i++)
	{
		DrawRectangle(mainGrid.positions[i].x, mainGrid.positions[i].y, mainGrid.cellSize, mainGrid.cellSize, mainGrid.colours[i]);
		if (mainGrid.costs[i] == 999)
		{
			DrawRectangle(mainGrid.positions[i].x, mainGrid.positions[i].y, mainGrid.cellSize, mainGrid.cellSize, BLACK);
		}
		//DrawText(TextFormat("%i", mainGrid.indexes[i]), mainGrid.positions[i].x + 4, mainGrid.positions[i].y + 4, 1, WHITE);
		if (viewCosts)
		{
			DrawText(TextFormat("%i", mainGrid.costs[i]), mainGrid.positions[i].x + 1, mainGrid.positions[i].y, 0.5, WHITE);
		}
		if (viewHeuristics)
		{
			DrawText(TextFormat("%f", mainGrid.heuristics[i]), mainGrid.positions[i].x + 1, mainGrid.positions[i].y, 0.5, WHITE);
		}
		if (heuristicsGenerated && viewDirections)
		{
			float centerX = mainGrid.positions[i].x + (mainGrid.cellSize / 2.0f);
			float centerY = mainGrid.positions[i].y + (mainGrid.cellSize / 2.0f);

			float lineLength = mainGrid.cellSize / 2.5f;
			float endX = centerX + (mainGrid.directions[i].x * lineLength);
			float endY = centerY + (mainGrid.directions[i].y * lineLength);

			DrawLineEx(Vector2{ centerX, centerY }, Vector2{ endX, endY }, 1.0f, WHITE);
		}
	}
	for (int i = 0; i < mainGrid.getGridSize() * mainGrid.getGridSize(); i++)
	{
		DrawRectangleLines(mainGrid.positions[i].x, mainGrid.positions[i].y, mainGrid.cellSize, mainGrid.cellSize, BLACK);
	}
	if (pathGenerated)
	{
		for (int i = 0; i < algorithmPath.size(); i++)
		{
			DrawRectangle(mainGrid.positions[algorithmPath[i]].x, mainGrid.positions[algorithmPath[i]].y, mainGrid.cellSize, mainGrid.cellSize, YELLOW);
		}
	}
	if (startIndex > -1)
	{
		DrawRectangle(mainGrid.positions[startIndex].x, mainGrid.positions[startIndex].y, mainGrid.cellSize, mainGrid.cellSize, GREEN);
	}
	if (goalIndex > -1)
	{
		DrawRectangle(mainGrid.positions[goalIndex].x, mainGrid.positions[goalIndex].y, mainGrid.cellSize, mainGrid.cellSize, RED);
	}
	DrawRectangle(mainGrid.positions[mouseCellIndex].x, mainGrid.positions[mouseCellIndex].y, mainGrid.cellSize, mainGrid.cellSize, YELLOW);

	npc.draw();
}
