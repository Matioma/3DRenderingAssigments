#pragma once
#ifndef DIRECTIONAL_LIGHT_HPP
#define DIRECTIONAL_LIGHT_HPP

#include "mge/core/Light.hpp"
class DirectionalLight : public Light
{

private:
	glm::vec3 direction;

public:
	DirectionalLight(const std::string& aName = nullptr, const glm::vec3& aPosition = glm::vec3(0, 0, 0));
	virtual ~DirectionalLight();

	glm::vec3 getDirection();
	void setDirection(glm::vec3);
};

#endif // DIRECTIONAL_LIGHT_HPP