#pragma once
#include "SteeringBehaviour.h"
#include "Seek.h"
#include <cstdlib>
#include <cmath>

class Wander : public SteeringBehaviour
{
public:
	virtual steeringOutput getSteering(sf::Vector2f t_me, sf::Vector2f t_target, sf::Vector2f t_velocity, sf::Vector2f t_targetVelocity, float t_maxAcceleration)
	{
		sf::Vector2f direction{ 1.0f, 0.0f };
		if (t_velocity.x != 0 || t_velocity.y != 0)
		{
			direction = t_velocity.normalized();
		}

		sf::Vector2f point = t_me + (direction * 75.0f);

		float jitter = ((rand() % 200) / 100.0f) - 1.0f;
		wanderAngle += jitter * 0.3f;

		sf::Vector2f targetOnCircle;
		targetOnCircle.x = point.x + (std::cos(wanderAngle) * 50.0f);
		targetOnCircle.y = point.y + (std::sin(wanderAngle) * 50.0f);

		steering.linear = targetOnCircle - t_me;
		steering.linear = steering.linear.normalized();
		steering.linear *= t_maxAcceleration;

		steering.angular = 0;

		return steering;
	}
private:
	float wanderAngle = 0.0f;
};