#pragma once
#include "SteeringBehaviour.h"

class Seek : public SteeringBehaviour
{
	virtual sf::Vector2f getSteering(sf::Vector2f t_me, sf::Vector2f t_target, float t_maxAcceleration)
	{
		steering = t_target - t_me;
		steering = steering.normalized();
		steering *= t_speed;

		return steering;
	}
};