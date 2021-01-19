#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(const std::string& pName, const glm::vec3& pPosition) :Light(pName, pPosition)
{}


DirectionalLight::~DirectionalLight() {
}

glm::vec3 DirectionalLight::getDirection()
{
	return direction;
}

void DirectionalLight::setDirection(glm::vec3 newDirection)
{
	direction = newDirection;
}


