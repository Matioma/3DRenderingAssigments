#include "SpotLight.h"

SpotLight::SpotLight(const std::string& aName, const glm::vec3& aPosition):Light(aName, aPosition),_coneAngle(0),_coneFallOffAngle(0)
{
}

SpotLight::~SpotLight()
{
}

void SpotLight::setConeAngle(float pConeAngle)
{
	_coneAngle = pConeAngle;
}

void SpotLight::setConeFallOffAngle(float pConeFallOfAngle)
{
	_coneFallOffAngle = pConeFallOfAngle;
}

float SpotLight::getConeAngle()
{
	return _coneAngle;
}

float SpotLight::getConeFallOffAngle()
{
	return _coneFallOffAngle;
}
