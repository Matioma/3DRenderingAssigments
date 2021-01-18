#pragma once
#ifndef FOLLOWBEHAVIOUR_HPP
#define FOLLOWBEHAVIOUR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "glm.hpp"


class GameObject;
class FollowBehaviour : public AbstractBehaviour
{
public:
	FollowBehaviour(GameObject& target, glm::vec3 pOffset);
	virtual ~FollowBehaviour();
	virtual void update(float pStep);

private:
	GameObject& target;
	glm::vec3 offset;

	float rotationSpeed =-0.05;
};

#endif // FOLLOWBEHAVIOUR_HPP
