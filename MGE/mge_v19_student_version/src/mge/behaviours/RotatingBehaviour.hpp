#ifndef ROTATINGBEHAVIOUR_HPP
#define ROTATINGBEHAVIOUR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/core/GameObject.hpp"
/**
 * Simply rotates the object around its origin with a fixed speed.
 */
class RotatingBehaviour : public AbstractBehaviour
{
private:
	glm::vec3 axis;

	public:
		RotatingBehaviour();
		RotatingBehaviour(glm::vec3 axis);
		virtual ~RotatingBehaviour();

		virtual void update(float pStep);

};

#endif // ROTATINGBEHAVIOUR_HPP
