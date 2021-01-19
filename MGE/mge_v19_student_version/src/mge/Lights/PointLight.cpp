#include "mge/Lights/PointLight.h"
#include "mge/core/World.hpp"

PointLight::PointLight(const std::string& pName, const glm::vec3& pPosition) :Light(pName,pPosition)
{}

PointLight::~PointLight() {
}

glm::vec4 PointLight::getColor()
{
	return color;
}

void PointLight::setColor(glm::vec4 newColor)
{
	color = newColor;
}



