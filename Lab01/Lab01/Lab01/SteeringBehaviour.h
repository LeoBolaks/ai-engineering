#pragma once

#include "SFML/Graphics.hpp"

#include <iostream>
struct steeringOutput
{
	sf::Vector2f linear;
	sf::Vector2f angular;
};
class SteeringBehaviour
{
	SteeringBehaviour() = default;
	virtual ~SteeringBehaviour() {};
	virtual steeringOutput getSteering(sf::Vector2f t_me, sf::Vector2f t_target, float t_maxAcceleration) = 0;

protected:
	steeringOutput steering;
};