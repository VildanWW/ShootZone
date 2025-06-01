#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map.h"

sf::Texture textureMap; // Глобальная текстура. Важно сделать текстуру глобальной, а не локальной, чтобы она жила дольше самого спрайта, который еще ушел в другую функцию(иначе краш). Либо передавать из main() по ссылке. void showMap(sf::RenderWindow& window) {

void showMap(sf::RenderWindow& window) {
    sf::Sprite sprite;
    sprite.setTexture(textureMap);
    setMap(sprite, window);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(640, 480), "ShootZone");

    if (!textureMap.loadFromFile("image/map.png")) { // Обязательно
        std::cerr << "Ошибка: не удалось загрузить image/map.png" << std::endl;
        return -1;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        showMap(window);
        window.display();
    }

    return 0;
}
