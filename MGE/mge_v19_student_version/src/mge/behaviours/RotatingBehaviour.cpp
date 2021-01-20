#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/core/GameObject.hpp"

RotatingBehaviour::RotatingBehaviour():AbstractBehaviour()
{
	//ctor
	this->axis = glm::vec3(1.0f, 1.0f, 0.0f);
}

RotatingBehaviour::RotatingBehaviour(glm::vec3 axis)
{
	this->axis = axis;
}

//RotatingBehaviour::RotatingBehaviour(glm::vec3 axis) AbstractBehaviour()
//{
//}

RotatingBehaviour::~RotatingBehaviour()
{
	//dtor
}

void RotatingBehaviour::update(float pStep)
{
    //rotates 45° per second
	_owner->rotate(pStep * glm::radians(45.0f), axis);
}
