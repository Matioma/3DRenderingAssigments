#include "OrbitBehaviour.h"
#include "mge/core/GameObject.hpp"
#include "glm.hpp"
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>

OrbitBehaviour::OrbitBehaviour(GameObject& target, glm::vec3 pOffset) :target(target)
{
	this->offset = pOffset;
	
}

OrbitBehaviour::~OrbitBehaviour()
{
}

void OrbitBehaviour::update(float pStep)
{
	std::cout << _owner->getTransform()[0] << " " << _owner->getTransform()[1] << _owner->getTransform()[2] << std::endl;
	//this->_owner->setLocalPosition(glm::vec3(10,10,10));
	//_owner->setLocalPosition(target.getWorldPosition() + this->offset);

	//RotateAround(target.getWorldPosition(), glm::vec3(1, 0, 0), 1*0.01);
	//RotateAround(target.getWorldPosition(), glm::vec3(0, 1, 0), 1 * 0.01);

	//float dx = 10;
	//float dy = 10;
	//_owner->setLocalPosition(target.getWorldPosition() + this->offset);

	

	/*float rotationXSpeed = 0.01;
	float rotationYSpeed = 0.01;
	float rotationZSpeed = 0.00;*/

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		sensitivityY += sensitivityStep;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		sensitivityY -= sensitivityStep;

		if (sensitivityY < 0) {
			sensitivityY = 0;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		sensitivityX += sensitivityStep;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		sensitivityX -= sensitivityStep;
		if (sensitivityX < 0) {
			sensitivityX = 0;
		}
	}



	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		float dx = sf::Mouse::getPosition().x - this->lastMousePos.x;
		float dy = sf::Mouse::getPosition().y - this->lastMousePos.y;


		/*RotateAround(target.getWorldPosition(), dy * rotationXSpeed, 0 * rotationYSpeed, rotationZSpeed);
		RotateAround(target.getWorldPosition(), 0 * rotationXSpeed, dx * rotationYSpeed, rotationZSpeed);*/

		RotateAround(target.getWorldPosition(), dy * sensitivityX, dx * sensitivityY, 0);
	}
	_owner->setLocalPosition(target.getWorldPosition() + this->offset);
	this->lastMousePos = sf::Mouse::getPosition();
}

void OrbitBehaviour::RotateAround(glm::vec3 position, glm::vec3 axis, float speed)
{
	offset = glm::rotate(speed, axis) * glm::vec4(offset.x, offset.y, offset.z, 0);
	
	_owner->setTransform(glm::rotate(speed, axis) * glm::translate(-position) *_owner->getTransform());

	_owner->setLocalPosition(position + this->offset);
}

void OrbitBehaviour::RotateAround(glm::vec3 position, float dx, float dy,float dz)
{
	glm::vec3 right= _owner->getTransform()[0];
	glm::vec3 up = _owner->getTransform()[1];
	glm::vec3 forward = _owner->getTransform()[2];

	/*glm::mat4 rotationMatrix = glm::rotate(dx, right) *
								glm::rotate(dy, glm::vec3(0,1,0)) *
								glm::rotate(dz, forward) * glm::mat4();*/



	glm::mat4 rotationMatrix = glm::rotate(dz, forward) *
		glm::rotate(dy, glm::vec3(0, 1, 0)) *
		glm::rotate(dx, right) * glm::mat4();


	offset = rotationMatrix * glm::vec4(offset, 0);
	_owner->setTransform(glm::translate(position)*rotationMatrix *  glm::translate(-position) * _owner->getWorldTransform());
	

}
