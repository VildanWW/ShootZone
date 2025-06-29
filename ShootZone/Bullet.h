#pragma once
#include <SFML/Graphics.hpp>

class Bullet {
private:
    sf::Sprite sprite;
    sf::Vector2f velocity;
    float speed = 7000;
public:
    sf::FloatRect getBounds() const;

    Bullet(const sf::Texture& texture, const sf::Vector2f& startPos, bool facingRight);

    void update(float deltaTime);

    void draw(sf::RenderWindow& window) const;

    bool isOffScreen(const sf::RenderWindow& window) const;
};