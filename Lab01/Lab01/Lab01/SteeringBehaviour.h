#pragma once

#include "SFML/Graphics.hpp"

#include <iostream>
struct steeringOutput
{
	sf::Vector2f linear;
	float angular;
};
class SteeringBehaviour
{
public:
	SteeringBehaviour() = default;
	virtual ~SteeringBehaviour() {};
	virtual steeringOutput getSteering(sf::Vector2f t_me, sf::Vector2f t_target, sf::Vector2f t_velocity, sf::Vector2f t_targetVelocity, float t_maxAcceleration) = 0;

protected:
	steeringOutput steering;
};