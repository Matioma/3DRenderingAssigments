#include "OrbitBehaviour.h"
#include "mge/core/GameObject.hpp"
#include "glm.hpp"
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include "./mge/EventHandler.h"

OrbitBehaviour::OrbitBehaviour(GameObject& target, glm::vec3 pOffset) :target(target)
{
	this->offset = pOffset;

	EventHandler::GetInstance()->Subscribe(sf::Event::MouseWheelScrolled, [this](sf::Event event) {
		glm::vec4 newOffset = glm::scale(glm::vec3(1 - event.mouseWheelScroll.delta* 0.05)) * glm::vec4(this->offset, 1);
		this->offset = glm::vec3(newOffset);
	});
	
}

OrbitBehaviour::~OrbitBehaviour()
{
}

void OrbitBehaviour::update(float pStep)
{
	//std::cout << _owner->getTransform()[0] << " " << _owner->getTransform()[1] << _owner->getTransform()[2] << std::endl;



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
	
	

	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
		glm::vec4 newOffset = glm::scale(glm::vec3(1 - 0.05)) * glm::vec4(this->offset, 1);
		this->offset = glm::vec3(newOffset);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
		glm::vec4 newOffset = glm::scale(glm::vec3(1 + 0.05)) * glm::vec4(this->offset, 1);
		this->offset = glm::vec3(newOffset);
	}
	

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		float dx = sf::Mouse::getPosition().x - this->lastMousePos.x;
		float dy = sf::Mouse::getPosition().y - this->lastMousePos.y;

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


void OrbitBehaviour::Scale(float amount) {
	_owner->setTransform(glm::translate(_owner->getWorldPosition()) * glm::scale(glm::vec3(1 + amount)) * glm::translate(-_owner->getWorldPosition()) * _owner->getWorldTransform());
}
