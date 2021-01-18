#include "EventHandler.h"
#include <iostream>

EventHandler* EventHandler::instance = 0;

EventHandler::EventHandler() {
    //events[sf::Event::MouseWheelScrolled] = [](sf::Event event) {std::cout << "Awesome" << std::endl; };
}

void EventHandler::Subscribe(sf::Event::EventType target, std::function<void(sf::Event)> action)
{
    events[target] = action;
}


EventHandler* EventHandler::GetInstance()
{
		if (!instance) instance = new EventHandler();
		return instance;
}



void EventHandler::ProcessEvents(sf::RenderWindow& window)
{
  


    sf::Event event;
    bool exit = false;

    //we must empty the event queue
    while (window.pollEvent(event)) {
        
        //give all system event listeners a chance to handle events
        //optionally to be implemented by you for example you could implement a
        //SystemEventDispatcher / SystemEventListener pair which allows Listeners to
        //register with the dispatcher and then do something like:
        //SystemEventDispatcher::dispatchEvent(event);
        //EventHandler::GetInstance()->setEvent(event);
        switch (event.type) {
        case sf::Event::Closed:
            exit = true;
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape) {
                exit = true;
            }
            break;
        case sf::Event::Resized:
            //glViewport(0, 0, event.size.width, event.size.height);
            break;
        case sf::Event::MouseWheelScrolled:
         /*   if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                std::cout << "wheel type: vertical" << std::endl;
            else if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel)
                std::cout << "wheel type: horizontal" << std::endl;
            else
                std::cout << "wheel type: unknown" << std::endl;
            std::cout << "wheel movement: " << event.mouseWheelScroll.delta << std::endl;*/

            if (events[sf::Event::MouseWheelScrolled]) {
                events[sf::Event::MouseWheelScrolled](event);
            }

          
            break;
        default:
            break;
        }
    }

    if (exit) {
        window.close();
    }
}
