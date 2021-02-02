#include "SinMovementBehaviour.h"
#include "mge/core/GameObject.hpp"


SinMovementBehaviour::SinMovementBehaviour(float amplitude, glm::vec3 axis):amplitude(amplitude), axis(axis)
{
}

SinMovementBehaviour::~SinMovementBehaviour()
{
}

void SinMovementBehaviour::update(float pStep)
{
	timer += pStep;
	_owner->setLocalPosition(axis*sin(timer)*amplitude +glm::vec3(0,amplitude,0));
}
