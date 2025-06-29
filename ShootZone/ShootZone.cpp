#include <iostream>
#include <SFML/Graphics.hpp>
#include "Includes.h"

// Глобальная текстура карты
sf::Texture textureMap;

// Функция показа карты
void showMap(sf::Sprite& spritesMap, sf::RenderWindow& window) {
    spritesMap.setTexture(textureMap);
    setMap(spritesMap, window);
}

// Глобальная текстура героя
sf::Texture textureHero;

// Функция показа героя
void showHero(sf::RenderWindow& window, Hero& entityHero, float time) {
    entityHero.moveSpriteEntity(window, time);
    entityHero.update(time, window);
    entityHero.drawHero(window);
    entityHero.drawHealthHero(window);
    entityHero.updateX(time, window);
    
}

void updateAndRenderBullets(std::vector<Bullet>& bulletsWeaponKalashnikov, float time, sf::RenderWindow& window,sf::Sprite& spriteEarth) {
    if (!bulletsWeaponKalashnikov.empty()) {
        for (auto it = bulletsWeaponKalashnikov.begin(); it != bulletsWeaponKalashnikov.end();) {
            it->update(time);

            bool collided = false;
            for (const auto& tile : collisionTiles) {
                if (it->getBounds().intersects(tile.getGlobalBounds())) {
                    collided = true;
                    break;
                }
            }

            if (it->isOffScreen(window) || collided) {
                it = bulletsWeaponKalashnikov.erase(it);
            }
            else {
                it->draw(window);
                ++it;
            }
        }
    }
}

// Функция для прыжка героя
void heroCanJump(Hero& entityHero){
    entityHero.heroEntityCanJump();
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "ShootZone");

    if (!textureMap.loadFromFile("image/map.png")) {
        std::cerr << "Ошибка: не удалось загрузить image/map.png" << std::endl;
        return -1;
    }

    if (!textureHero.loadFromFile("image/OIPP1.PNG")) {
        std::cerr << "Ошибка: не удалось загрузить image/OIPP1.PNG" << std::endl;
        return -1;
    }

    // Спрайт карты
    sf::Sprite spritesMap;
    sf::Sprite spriteHero(textureHero);
    Hero entityHero(spriteHero);

    // Время
    sf::Clock clock;

    // Текстура и спрайт пули
    sf::Texture textureBullet;
    if (!textureBullet.loadFromFile("image/ammo.png")) {
        std::cerr << "Ошибка: не удалось загрузить image/map.png" << std::endl;
    }
    sf::Sprite spriteBullet(textureBullet);

    // Создание автомата Калашникова
    WeaponsKalashnikov kalashnikov;
    std::vector<Bullet> bulletsWeaponKalashnikov;
    Weapons* weaponKalashnikov = &kalashnikov;
    
    // Создание земли для коллизии с пулей
    sf::Sprite spriteEarth;
    spriteEarth.setTexture(textureMap);
    spriteEarth.setTextureRect(sf::IntRect(64, 0, 32, 32));
    

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                bool shootRight = entityHero.isFacingRight();
                sf::Vector2f heroPos = entityHero.getPosition();
                sf::FloatRect heroBounds = entityHero.getBounds();

                weaponKalashnikov->shoot(window, heroPos, heroBounds, spriteBullet, bulletsWeaponKalashnikov, shootRight);
            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                if (entityHero.onGround) {
                    heroCanJump(entityHero);
                }
            }
        }

        float time = clock.restart().asSeconds();

        window.clear();
        window.draw(spriteEarth);

        showMap(spritesMap, window);
        showHero(window, entityHero, time);
        updateAndRenderBullets(bulletsWeaponKalashnikov, time, window, spriteEarth);

        
        window.display();
    }
    return 0;
}
