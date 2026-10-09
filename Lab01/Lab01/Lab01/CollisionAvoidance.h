#pragma once
#include "SteeringBehaviour.h"
#include "NPC.h"
#include <vector>
#include <cmath>

class CollisionAvoidance : public SteeringBehaviour
{
public:

	void setParameters(NPC* t_me, std::vector<NPC*>* t_npcList)
	{
		character = t_me;
		targets = t_npcList;
	}
	virtual steeringOutput getSteering(sf::Vector2f t_me, sf::Vector2f t_target, sf::Vector2f t_velocity, sf::Vector2f t_targetVelocity, float t_maxAcceleration)
	{
		character->setConeColour(sf::Color(40, 255, 0, 140));
		steeringOutput steering;
		sf::Vector2f avoidance = { 0.1f, 0.1f };

		for (NPC* target : *targets)
		{
			if (target->getPosition() == character->getPosition() || target == character)
			{
				continue;
			}

			if (!character->checkIfInsideVisionCone(target->getPosition()))
				{
					continue;
				}
			character->setConeColour(sf::Color(255, 0, 0, 140));
			sf::Vector2f dirToObject = character->getPosition() - target->getPosition();
			sf::Vector2f dirAwayFromObject = dirToObject.rotatedBy(sf::degrees(60.0f));

			avoidance += dirAwayFromObject;
		}

		sf::Vector2f strengthenedAvoidance = avoidance.normalized();
		strengthenedAvoidance.x *= 2.5f;
		strengthenedAvoidance.y *= 2.5f;

		steering.linear = strengthenedAvoidance;

		return steering;

		//character->setConeColour(sf::Color(40, 255, 0, 140));
		//steering.linear = { 0.0f, 0.0f };
		//steering.angular = 0.0f;

		//float shortestTime = 999999.0f; 
		//NPC* firstTarget = nullptr;  

		//float firstMinSeparation = 0.0f;
		//float firstDistance = 0.0f;
		//sf::Vector2f firstRelativePos;
		//sf::Vector2f firstRelativeVel;
		//sf::Vector2f relativePos;
		//float distance;

		//for (NPC* target : *targets)
		//{
		//	if (target == character)
		//	{
		//		continue;
		//	}

		//	if (!character->checkIfInsideVisionCone(target->getPosition()))
		//	{
		//		continue;
		//	}
		//	character->setConeColour(sf::Color(255, 0, 0, 140));
		//	std::cout << "ID " << character->getID() << " Is Seeing ID " << target->getID() << "\n";

		//	relativePos = target->getPosition() - character->getPosition();
		//	sf::Vector2f relativeVel = target->getVelocity() - character->getVelocity();

		//	float relativeSpeedSq = (relativeVel.x * relativeVel.x) + (relativeVel.y * relativeVel.y);
		//	
		//	float relativeSpeed = std::sqrt(relativeSpeedSq);

		//	float timeToCollision = ((relativePos.x * relativeVel.x) + (relativePos.y * relativeVel.y)) / (relativeSpeed * relativeSpeed);

		//	distance = std::sqrt((relativePos.x * relativePos.x) + (relativePos.y * relativePos.y));

		//	float minSeparation = distance - (relativeSpeed * shortestTime);

		//	if (minSeparation > 2.0f * radius)
		//	{
		//		continue;
		//	}

		//	if (timeToCollision > 0.0f && timeToCollision < shortestTime)
		//	{
		//		shortestTime = timeToCollision;
		//		firstTarget = target;
		//		firstMinSeparation = minSeparation;
		//		firstDistance = distance;
		//		firstRelativePos = relativePos;
		//		firstRelativeVel = relativeVel;
		//	}
		//}

		//if (firstTarget == nullptr)
		//{
		//	return steering;
		//}

		//if (firstMinSeparation <= 0.0f || distance < 2.0f * radius)
		//{
		//	relativePos = firstTarget->getPosition() - character->getPosition();
		//}
		//else
		//{
		//	relativePos = firstRelativePos + (firstRelativeVel * shortestTime);
		//}
		//relativePos = relativePos.normalized();
		//steering.linear = -relativePos * t_maxAcceleration;

		//return steering;
	}
private:
	NPC* character;
	std::vector<NPC*>* targets;
	float radius = 100.0f;
};