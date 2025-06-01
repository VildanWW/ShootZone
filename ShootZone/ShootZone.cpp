#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(640,480), "ShootZone");
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        
        window.clear();
        window.display();
    }

    return 0;
}