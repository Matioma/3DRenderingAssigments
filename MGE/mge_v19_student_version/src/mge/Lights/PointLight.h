#pragma once
#ifndef POINTLIGHT_HPP
#define POINTLIGHT_HPP

#include "glm.hpp"
#include "mge/core/Light.hpp"

/**
 * Exercise for the student: implement the Light class...
 * Imagine things like setLightType, setLightIntensity, setFalloffAngle etc, see the corresponding lectures
 */
class PointLight : public Light
{

private :
	glm::vec4 color;
	

public:
	PointLight(const std::string& aName = nullptr, const glm::vec3& aPosition = glm::vec3(2.0f, 10.0f, 5.0f));
	virtual ~PointLight();

	glm::vec4 getColor();
	void setColor(glm::vec4);
	

	//override set parent to register/deregister light...
};

#endif // POINTLIGHT_HPP