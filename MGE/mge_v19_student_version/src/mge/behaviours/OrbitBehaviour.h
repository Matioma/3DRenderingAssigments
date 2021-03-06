#pragma once
#ifndef ORBITBEHAVIOUR_HPP
#define ORBITBEHAVIOUR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "glm.hpp"
#include "SFML/System/Vector2.hpp"


class GameObject;
class OrbitBehaviour : public AbstractBehaviour
{
public:
	//move speed is in units per second, turnspeed in degrees per second
	OrbitBehaviour(GameObject& target, glm::vec3 pOffset, bool isRestricted=true);
	virtual ~OrbitBehaviour();
	virtual void update(float pStep);

	void ControllSensitivity();
	


private:
	GameObject& target;
	glm::vec3 offset;
	bool isRestricted = false;


	float rotationSpeed = 0.01;
	sf::Vector2i lastMousePos;

	void RotateAround(glm::vec3 position, glm::vec3 axis, float speed = 0.01f);


	void RotateAround(glm::vec3 position, float dx, float dy, float dz);

	void Scale(float amount);
	
	float sensitivityX = 0.01;
	float sensitivityY = 0.01;

	float sensitivityStep = 0.001;

	float zoomStep = 0.001;
};

#endif // ORBITBEHAVIOUR_HPP