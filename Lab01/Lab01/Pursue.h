#pragma once
#include "SteeringBehaviour.h"
#include "Seek.h"

class Pursue : public SteeringBehaviour
{
public:
	virtual steeringOutput getSteering(sf::Vector2f t_me, sf::Vector2f t_target, sf::Vector2f t_velocity, sf::Vector2f t_targetVelocity,  float t_maxAcceleration)
	{
		sf::Vector2f directionToTarget = t_target - t_me;
		float distance = std::sqrt((directionToTarget.x * directionToTarget.x) + (directionToTarget.y * directionToTarget.y));

		float mySpeed = std::sqrt((t_velocity.x * t_velocity.x) + (t_velocity.y * t_velocity.y));

		float timePrediction;
		if (mySpeed <= distance / maxTimePrediction)
		{
			timePrediction = maxTimePrediction;
		}
		else
		{
			timePrediction = distance / mySpeed;
		}

		sf::Vector2f predictedTargetPos = t_target + (t_targetVelocity * timePrediction);


		Seek mySeek;

		return mySeek.getSteering(t_me, predictedTargetPos, t_velocity, t_targetVelocity, t_maxAcceleration);
	}
private:
	float maxTimePrediction = 1.0f;
};