#pragma once
#include <SFML/Graphics.hpp>
#include <string>

extern const int height;
extern const int width;  
extern std::vector<sf::Sprite> collisionTiles;
extern std::string arr[];
       
void setMap(sf::Sprite& spritesMap, sf::RenderWindow& window); 
