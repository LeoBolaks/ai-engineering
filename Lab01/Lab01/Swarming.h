#pragma once
#include "SteeringBehaviour.h"
#include "NPC.h"
#include <vector>
#include <cmath>

class Swarming : public SteeringBehaviour
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

		float A = 2000.0f; // Strength Of Attraction
		float B = 100000.0f; // Strength Of Repulsion
		float N = 1.0f; // Rate Of Fall Off
		float M = 2.0f; // Repulsion Fall Off Rate

		for (NPC* other : *targets)
		{
			if (t_me == other->getPosition() || character == other)
			{
				continue;
			}

			sf::Vector2f R = t_me - other->getPosition();

			float D = R.length();
			if (D < 3.0f)
			{
				D = 3.0f;
			}

			if (D > 0.0f)
			{
				float U = (-A / std::pow(D, N)) + (B / std::pow(D, M));
				sf::Vector2f normalizedR = R / D;

				steering.linear += normalizedR * U;
			}
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