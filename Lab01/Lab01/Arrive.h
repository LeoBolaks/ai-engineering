#pragma once
#include "SteeringBehaviour.h"

class Arrive : public SteeringBehaviour
{
public:
	virtual steeringOutput getSteering(sf::Vector2f t_me, sf::Vector2f t_target, sf::Vector2f t_velocity, sf::Vector2f t_targetVelocity, float t_maxAcceleration)
	{
		sf::Vector2f direction = t_target - t_me;
		float distance = std::sqrt((direction.x * direction.x) + (direction.y * direction.y));

		float targetSpeed = 0.0f;

		if (distance < arriveRadius)
		{
			targetSpeed = 0.0f;
		}
		else if (distance > slowRadius)
		{
			targetSpeed = maxSpeed;
		}
		else
		{
			targetSpeed = maxSpeed * (distance / slowRadius);
		}

		sf::Vector2f targetVelocity{ 0.0f, 0.0f };
		if (distance > 0.0f)
		{
			targetVelocity = direction.normalized() * targetSpeed;
		}

		steering.linear = targetVelocity - t_velocity;
		steering.linear /= timeToTarget;

		float linearLength = std::sqrt((steering.linear.x * steering.linear.x) + (steering.linear.y * steering.linear.y));
		if (linearLength > t_maxAcceleration)
		{
			steering.linear = steering.linear.normalized() * t_maxAcceleration;
		}

		steering.angular = 0;

		return steering;
	}
private:
	float arriveRadius = 60.0f;
	float slowRadius = 200.0f;
	float maxSpeed = 300.0f;
	float timeToTarget = 0.1f;
};