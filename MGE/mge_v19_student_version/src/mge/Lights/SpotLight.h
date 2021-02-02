#pragma once
#ifndef SPOTLIGHT_HPP
#define SPOTLIGHT_HPP

#include "glm.hpp"
#include "mge/core/Light.hpp"


class SpotLight : public Light
{

private:
	float _coneAngle;
	float _coneFallOffAngle;	

public:
	SpotLight(const std::string& aName = nullptr, const glm::vec3& aPosition = glm::vec3(2.0f, 10.0f, 5.0f));
	virtual ~SpotLight();

	void setConeAngle(float pConeAngle);
	void setConeFallOffAngle(float pConeFallOfAngle);

	float getConeAngle();
	float getConeFallOffAngle();

};

#endif // SPOTLIGHT_HPP