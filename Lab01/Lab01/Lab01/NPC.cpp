#include "NPC.h"
#include "CollisionAvoidance.h"

NPC::NPC(SteeringBehaviour* t_behaviour, int t_behaviourType, float t_speed, int t_id) : behaviour(t_behaviour), behaviourType(t_behaviourType), speed(t_speed), id(t_id)
{
	init();
}
void NPC::init()
{
	active = true;
	scale = { 0.15f,0.15f };
	position = { 100.0f, 400.0f };
	position.x *= id;
	randomNum = rand() % 360;
	coneAngle = 90.0f;
	velocity = { 1.0f, 1.0f };
	cone.setPointCount(3);

	float radians = randomNum * (3.14f / 180.0f);
	direction = { std::cos(radians), std::sin(radians) };

	rotation = sf::degrees(randomNum + 90.0f);

	if (!tieTexture.loadFromFile("ASSETS\\IMAGES\\TIE.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading Tie" << std::endl;
	}
	tie.setTexture(tieTexture, true);// to reset the dimensions of texture
	tie.setPosition(position);
	tie.setScale(scale);
	tie.setOrigin(sf::Vector2f{ 230.5f, 283.0f });
	tie.setRotation(rotation);
	if (!nameFont.openFromFile("ASSETS\\FONTS\\Jersey20-Regular.ttf"))
	{
		std::cout << "Problem loading font" << std::endl;
	}
	nameText.setFont(nameFont);
	nameText.setCharacterSize(20);
	nameText.setFillColor(sf::Color::White);
	nameText.setPosition(position - textOffset);

	switch (behaviourType)
	{
	case 1:
	{
		nameText.setString("Seeking ID:" + std::to_string(id));
		break;
	}
	case 2:
	{
		nameText.setString("Wandering ID:" + std::to_string(id));
		break;
	}
	case 3:
	{
		nameText.setString("Arriving ID:" + std::to_string(id));
		break;
	}
	case 4:
	{
		nameText.setString("Pursuing ID:" + std::to_string(id));
		pursueNPC = true;
		break;
	}
	}

	std::cout << "Tie Rotation: " << randomNum << std::endl;
}

void NPC::update(sf::Time t_deltaTime)
{
	sf::Vector2f totalSteering;
	if (active)
	{
		steeringOutput behaviourSteering = behaviour->getSteering(position, playerTarget->getPosition(), velocity, playerTarget->getVelocityVector(), speed);
		totalSteering += behaviourSteering.linear;
		nameText.setFillColor(sf::Color::White);

		if (totalSteering.x != 0.0f && totalSteering.y != 0.0f)
		{
			totalSteering = totalSteering.normalized();
		}

		velocity += totalSteering * speed * t_deltaTime.asSeconds();

		if (avoidBehaviour != nullptr)
		{
			velocity += avoidBehaviour->getSteering(position, { 0.0f,0.0f }, velocity, { 0.0f,0.0f }, 500.0f).linear;
		}

		position += velocity * t_deltaTime.asSeconds();
		setRotationInDir();
	}
	else
	{
		nameText.setFillColor(sf::Color::Red);
	}



	if (position.x < -20)
	{
		position.x = 1010;
	}
	else if (position.x > 1020)
	{
		position.x = -10;
	}

	if (position.y < -20)
	{
		position.y = 810;
	}
	else if (position.y > 820)
	{
		position.y = -10;
	}

	tie.setPosition(position);
	nameText.setPosition(position - textOffset);
	velocity.x *= 0.97f;
	velocity.y *= 0.97f;
}

void NPC::setupAvoidance(std::vector<NPC*>* t_npcList)
{
	CollisionAvoidance* avoidance = new CollisionAvoidance;
	avoidance->setParameters(this, t_npcList);
	avoidBehaviour = avoidance;
}

void NPC::setRotationInDir()
{
	rotation = sf::radians(atan2(velocity.y, velocity.x));
	float radians = rotation.asRadians();
	direction = { std::cos(radians), std::sin(radians) };
	rotation = sf::radians(atan2(velocity.y, velocity.x)) + sf::degrees(90.0f);
	tie.setRotation(rotation);
}

bool NPC::checkIfInsideVisionCone(sf::Vector2f t_targetPos)
{
	sf::Vector2f directionToTarget = t_targetPos - position;
	float distance = directionToTarget.length();

	if (distance > 200.0f || distance == 0.0f)
	{
		return false;
	}

	directionToTarget = directionToTarget.normalized();

	float dot = directionToTarget.dot(velocity.normalized());
	float angle = std::acosf(dot) * (180 / sf::priv::pi) - (90 * (sf::priv::pi / 180.0f));

	if (angle < (coneAngle / 2.0f))
	{
		return true;
	}

	return false;
}

void NPC::draw(sf::RenderWindow& t_window)
{
	t_window.draw(tie);

	float halfCone = coneAngle / 2.0f;

	cone.setPoint(0, { position });
	cone.setPoint(1, { position + (direction.rotatedBy(sf::degrees(halfCone)) * 200.0f)});
	cone.setPoint(2, { position + (direction.rotatedBy(sf::degrees(-halfCone)) * 200.0f) });
	if (pursueNPC)
	{
		float lineLength = 500.0f;
		sf::Vector2f normDir = direction.normalized();

		sf::Vector2f endPos = position + (normDir * lineLength);
		
		sf::VertexArray line(sf::PrimitiveType::Lines, 2);

		line[0].position = position;
		line[0].color = sf::Color::White;

		line[1].position = endPos;
		line[1].color = sf::Color::White;

		t_window.draw(line);
	}
	cone.setFillColor(coneColour);
	t_window.draw(cone);
	t_window.draw(nameText);
}
