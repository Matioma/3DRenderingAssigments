#pragma once
#ifndef EVENTHANDER_HPP
#define EVENTHANDER_HPP
#include <SFML/Window/Event.hpp>
#include <map>
#include <SFML/Graphics/RenderWindow.hpp>
#include <functional>



class EventHandler {

private:
	std::map<sf::Event::EventType, std::function<void(sf::Event)>> events;
	static EventHandler* instance;
	EventHandler();

public:
	void Subscribe(sf::Event::EventType target, std::function<void(sf::Event)> action);
	
	

	static EventHandler* GetInstance();

	~EventHandler() { delete instance; };
	void ProcessEvents(sf::RenderWindow& window);
};



#endif // EVENTHANDER_HPP