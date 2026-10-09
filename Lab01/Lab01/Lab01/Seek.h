#pragma once
#include "SteeringBehaviour.h"

class Seek : public SteeringBehaviour
{
public:
	virtual steeringOutput getSteering(sf::Vector2f t_me, sf::Vector2f t_target, sf::Vector2f t_velocity, sf::Vector2f t_targetVelocity, float t_maxAcceleration)
	{
		steering.linear = t_target - t_me;
		steering.linear = steering.linear.normalized();
		steering.linear *= t_maxAcceleration;

		steering.angular = 0;

		return steering;
	}
};