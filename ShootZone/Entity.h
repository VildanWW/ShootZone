#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

class Entity {
protected:
    sf::Sprite spriteEntity;
    int health = 0;
};

class Hero : public Entity {
private:
    sf::Font fontHero;
    sf::Text textHealthHero;

    // Для оживления анимации
    float CurrentFrame = 0;

    // Для правильного поворота героя
    bool notMove = true;
    bool facingRight = true;

    // Для реализации физика
    float velocityY = 0;
    const float gravity = 981; // пикселей/сек^2
    bool onGround = false;

    // Размер спрайта героя
    const int frameWidth = 143;
    const int frameHeight = 164;

public:
    bool isFacingRight() const { return facingRight; }
    
    // Создаём героя
    Hero(sf::Sprite& spriteHero) {
        spriteEntity = spriteHero;
        spriteEntity.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
        spriteEntity.setPosition(10, 725);
        health = 100;

        if (!fontHero.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf")) {
            std::cerr << "Ошибка загрузки шрифта!" << std::endl;
        }

        textHealthHero.setFont(fontHero);
        textHealthHero.setCharacterSize(24);
        textHealthHero.setFillColor(sf::Color::White);
        textHealthHero.setPosition(10, 700);
    }

    // Получаем позицию героя и его хитбокс
    sf::Vector2f getPosition() const {
        return this->spriteEntity.getPosition();
    }
    sf::FloatRect getBounds() const {
        return this->spriteEntity.getGlobalBounds();
    }

    // Движение
    void moveSpriteEntity(sf::RenderWindow& window, float time) {
        notMove = true;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            notMove = false;
            facingRight = true;

            CurrentFrame += 8 * time;
            if (CurrentFrame > 6) CurrentFrame -= 6;
            spriteEntity.setTextureRect(sf::IntRect(143 * int(CurrentFrame), 0, frameWidth, frameHeight));
            spriteEntity.setScale(1.f, 1.f);
            spriteEntity.setOrigin(0.f, 0.f);
            spriteEntity.move(200 * time, 0);
            textHealthHero.move(200 * time, 0);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            notMove = false;
            facingRight = false;

            CurrentFrame += 8 * time;
            if (CurrentFrame > 6) CurrentFrame -= 6;
            spriteEntity.setTextureRect(sf::IntRect(143 * int(CurrentFrame), 0, frameWidth, frameHeight));
            spriteEntity.setScale(-1.f, 1.f);
            spriteEntity.setOrigin(143.f, 0.f);
            spriteEntity.move(-200 * time, 0);
            textHealthHero.move(-200 * time, 0);
        }

        // Если не двигаемся, то правильно устанавливаем его позицию
        if (notMove) {
            spriteEntity.setTextureRect(sf::IntRect(0, 159, frameWidth, frameHeight)); // Устанавливаем спрайт базовый и поворачиваем

            if (facingRight) {
                spriteEntity.setScale(1.f, 1.f);
                spriteEntity.setOrigin(0.f, 0.f);
            }
            else {
                spriteEntity.setScale(-1.f, 1.f);
                spriteEntity.setOrigin(143.f, 0.f);
            }
        }
    }
    
    void update(float time) {
        velocityY += gravity * time;

        float moveY = velocityY * time;
        float step = 1;
        float moved = 0;
        onGround = false;

        while (std::abs(moved) < std::abs(moveY)) {
            float dy = std::min(step, std::abs(moveY - moved));
            if (moveY < 0) dy = -dy;
            spriteEntity.move(0, dy);
            moved += dy;

            // Получаем хитбокс ног: узкий прямоугольник в нижней части спрайта
            sf::FloatRect bounds = spriteEntity.getGlobalBounds();
            float footHeight = 30.f; // высота хитбокса ног (настрой по своему спрайту)
            sf::FloatRect footHitbox(bounds.left + 20, bounds.top + bounds.height - footHeight, bounds.width - 40, footHeight);

            // Проверяем 3 точки по хитбоксу ног для коллизии
            float x1 = footHitbox.left + 5;
            float x2 = footHitbox.left + footHitbox.width / 2;
            float x3 = footHitbox.left + footHitbox.width - 5;
            float yFoot = footHitbox.top + footHitbox.height;

            int tileY = int(yFoot / 32);
            int tileX1 = int(x1 / 32);
            int tileX2 = int(x2 / 32);
            int tileX3 = int(x3 / 32);

            bool contact = false;

            if (tileY >= 0 && tileY < 34) {
                if (tileX1 >= 0 && tileX1 < 100 && arr[tileY][tileX1] == '0') contact = true;
                if (tileX2 >= 0 && tileX2 < 100 && arr[tileY][tileX2] == '0') contact = true;
                if (tileX3 >= 0 && tileX3 < 100 && arr[tileY][tileX3] == '0') contact = true;
            }

            if (contact && moveY > 0) {
                // Опускаем героя ровно на уровень блока, учитывая хитбокс ног
                textHealthHero.setPosition(spriteEntity.getPosition().x, tileY * 32 - bounds.height + footHeight-20);
                spriteEntity.setPosition(bounds.left, tileY * 32 - bounds.height + footHeight);
                velocityY = 0;
                onGround = true;
                break;
            }
        }
    }

    void drawHealthHero(sf::RenderWindow& window) {
        textHealthHero.setString("Health: " + std::to_string(health));
        window.draw(textHealthHero);
    }

    void drawHero(sf::RenderWindow& window) {
        window.draw(spriteEntity);
    }
};
