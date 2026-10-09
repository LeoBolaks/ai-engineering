#pragma once
#include "SteeringBehaviour.h"
#include "NPC.h"
#include <vector>
#include <cmath>

class Flocking : public SteeringBehaviour
{
public:
	virtual void setParameters(NPC* t_me, std::vector<NPC*>* t_npcList)
	{
		character = t_me;
		targets = t_npcList;
	}
	virtual steeringOutput getSteering(sf::Vector2f t_me, sf::Vector2f t_target, sf::Vector2f t_velocity, sf::Vector2f t_targetVelocity, float t_maxAcceleration)
	{
		steering.linear = { 0.0f, 0.0f };

		sf::Vector2f cohesion{ 0.0f, 0.0f };
		sf::Vector2f alignment{ 0.0f, 0.0f };
		sf::Vector2f separation{ 0.0f, 0.0f };
		float neighbours = 0.0f;

		for (NPC* other : *targets)
		{
			if (t_me == other->getPosition() || character == other)
			{
				continue;
			}

			sf::Vector2f difference = t_me - other->getPosition();
			float distance = difference.length();

			if (distance > 0.0f && distance < viewDistance)
			{
				cohesion += other->getPosition();
				alignment += other->getVelocity();

				neighbours++;

				if (distance < separationDistance)
				{
					separation += (difference / distance);

				}
			}
		}

		if (neighbours > 0)
		{
			cohesion = (cohesion / neighbours) - t_me;
			alignment = (alignment / neighbours) - t_velocity;

			steering.linear = cohesion + alignment + (separation * strength);
		}

		return steering;
	}
private:
	NPC* character;
	std::vector<NPC*>* targets;
	float viewDistance = 200.0f;
	float separationDistance = 80.0f;
	float strength = 100.0f;
};