#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Hero : public Entity {
private:
    sf::Font fontHero;
    sf::Text textHealthHero;

    // ��� ��������� ��������
    float CurrentFrame = 0;

    // ��� ����������� �������� �����
    bool notMove = true;
    bool facingRight = true;

    // ��� ���������� ������
    float velocityY = 0;
    const float gravity = 981; // ��������/���^2

    // ������ ������� �����
    const int frameWidth = 143;
    const int frameHeight = 164;

    // ������� ����� ��� ��������(����� ������) 
    sf::RectangleShape hitboxShape;
public:
    bool onGround = false;
    bool isFacingRight() const;

    Hero(sf::Sprite& spriteHero);

    sf::Vector2f getPosition() const;

    sf::FloatRect getBounds() const;

    void moveSpriteEntity(sf::RenderWindow& window, float time);

    void heroEntityCanJump();

    void update(float time, sf::RenderWindow& window);

    void updateX(float time, sf::RenderWindow& window);

    void drawHealthHero(sf::RenderWindow& window);

    void drawHero(sf::RenderWindow& window);
};