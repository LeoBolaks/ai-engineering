#pragma once

#include <iostream>

#include "raylib.h"

class NPC
{
public:
	NPC();

	void setFlowFlag(bool t_flowGenerated)
	{
		flowGenerated = t_flowGenerated;
	}
	void setDirections(Vector2 t_arr[], int t_size)
	{
		for (int i = 0; i < t_size; i++)
		{
			directions[i] = &t_arr[i];
		}
	}

	void setPosition(Vector2 t_pos)
	{
		position = t_pos;
	}

	int getIndex(int t_x, int t_y) { return t_y * 100 + t_x; }

	void update()
	{
		if (flowGenerated)
		{
			int posX = (static_cast<int>(position.x + 0.5f) / 10);
			int posY = (static_cast<int>(position.y + 0.5f) / 10);

			if (posX >= 0 && posX < 100 && posY >= 0 && posY < 100)
			{
				index = getIndex(posX, posY);
			}
			direction = *directions[index];

			position.x += direction.x * speed;
			position.y += direction.y * speed;
		}
	}

	void draw()
	{
		DrawCircle(position.x, position.y, 5, RED);
	}

private:

	Vector2* directions[10000];
	bool flowGenerated = false;
	float speed = 3.0f;
	Vector2 direction;
	Vector2 position;
	int index;
};