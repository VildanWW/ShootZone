#include <SFML/Graphics.hpp>
#include <iostream>
#include "Includes.h"

// Показать карту
sf::Texture textureMap; // Глобальная текстура. Важно сделать текстуру глобальной, а не локальной, чтобы она жила дольше самого спрайта, который еще ушел в другую функцию(иначе краш). Либо передавать из main() по ссылке. void showMap(sf::RenderWindow& window) {
void showMap(sf::Sprite spritesMap, sf::RenderWindow& window) {
    spritesMap.setTexture(textureMap);
    setMap(spritesMap, window);
}

// Показать героя
sf::Texture textureHero;
void showHero(sf::RenderWindow& window, Hero& entityHero, sf::Event event, float time) {
    entityHero.drawHero(window);
    entityHero.drawHealthHero(window);
    entityHero.moveSpriteEntity(window, time);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1920,1080), "ShootZone");

    if (!textureMap.loadFromFile("image/map.png")) { // Обязательно
        std::cerr << "Ошибка: не удалось загрузить image/map.png" << std::endl;
        return -1;
    }
    
    if (!textureHero.loadFromFile("image/OIPP1.PNG")) { // Обязательно
        std::cerr << "Ошибка: не удалось загрузить image/OIP.JPG" << std::endl;
        return -1;
    }
    
    // Спрайт карты
    sf::Sprite spritesMap;

    // Спрайт героя
    sf::Sprite spriteHero(textureHero);
    Hero entityHero(spriteHero);

    // Время
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float time = clock.restart().asSeconds();
        window.clear();

        // Работа с картой
        showMap(spritesMap, window);

        //Работа с героем
        showHero(window, entityHero, event, time);
        window.display();
    }

    return 0;
}


