#include "mge/Lights/PointLight.h"
#include "mge/core/World.hpp"

PointLight::PointLight(const std::string& pName, const glm::vec3& pPosition) :Light(pName,pPosition)
{}

PointLight::~PointLight() {
}


