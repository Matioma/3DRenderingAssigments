#pragma once
#ifndef SIN_MOVEMENTBEHAVIOUR_HPP
#define SIN_MOVEMENTBEHAVIOUR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "glm.hpp"


class GameObject;
class SinMovementBehaviour : public AbstractBehaviour
{
public:
	SinMovementBehaviour(float amplitude, glm::vec3 axis);
	virtual ~SinMovementBehaviour();
	virtual void update(float pStep);

private:
	float timer = 0;
	float amplitude;
	glm::vec3 axis;
};

#endif // SIN_MOVEMENTBEHAVIOUR_HPP
