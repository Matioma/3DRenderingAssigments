#include "FollowBehaviour.h"
#include <iostream>
#include "mge/core/GameObject.hpp"

FollowBehaviour::FollowBehaviour(GameObject& pTarget, glm::vec3 pOffset) :target(pTarget)
{
	this->offset = pOffset;
	//this->offset = glm::vec3(0,10 , 10);
}
FollowBehaviour::~FollowBehaviour()
{
}

void FollowBehaviour::update(float pStep)
{
	_owner->setLocalPosition(target.getWorldPosition()+this->offset);
	

	/*this->offset =  glm::rotate(rotationSpeed, glm::vec3(0, 1, 0)) * glm::vec4(offset.x, offset.y, offset.z,0) ;
	_owner->setTransform(glm::rotate(rotationSpeed, glm::vec3(0, 1, 0))* _owner->getTransform()) ;*/
}
