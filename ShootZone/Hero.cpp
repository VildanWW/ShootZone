#include <iostream>
#include "Hero.h"
#include "Map.h"

bool Hero::isFacingRight() const {
    return facingRight;
}

Hero::Hero(sf::Sprite& spriteHero) {
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

sf::Vector2f Hero::getPosition() const {
    return this->spriteEntity.getPosition();
}

sf::FloatRect Hero::getBounds() const {
    return this->spriteEntity.getGlobalBounds();
}

void Hero::moveSpriteEntity(sf::RenderWindow& window, float time) {
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

void Hero::heroEntityCanJump() {
    velocityY = -400;
    onGround = false;
}

void Hero::update(float time, sf::RenderWindow& window) {
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

        float x2 = footHitbox.left + footHitbox.width / 2;
        float yFoot = footHitbox.top + footHitbox.height - 15;
        int tileY = int(yFoot / 32);
        int tileX2 = int(x2 / 32);
        bool contact = false;

        if (tileY >= 0 && tileY < 34) {
            if (tileX2 >= 0 && tileX2 < 100 && arr[tileY][tileX2] == '0') contact = true;
        }

        textHealthHero.setPosition(spriteEntity.getPosition().x, tileY * 32 - bounds.height + footHeight - 20);
        if (contact && moveY > 0) {
            // Опускаем героя ровно на уровень блока, учитывая хитбокс ног
            spriteEntity.setPosition(bounds.left, tileY * 32 - bounds.height + footHeight);
            velocityY = 0;
            onGround = true;
            break;
        }

        // Выводим 3 точки по хитбоксу ног для коллизии
        sf::CircleShape footPoint(3);
        footPoint.setFillColor(sf::Color::Yellow);
        footPoint.setPosition(x2, yFoot);
        window.draw(footPoint);
    }
}

void Hero::updateX(float time, sf::RenderWindow& window) {
    // Хитбокс героя(потом убрать)
    sf::FloatRect bounds = spriteEntity.getGlobalBounds();
    hitboxShape.setPosition(bounds.left, bounds.top);
    hitboxShape.setSize(sf::Vector2f(bounds.width, bounds.height));
    hitboxShape.setFillColor(sf::Color::Transparent);  // прозрачный заливка, чтобы не мешал
    hitboxShape.setOutlineColor(sf::Color::Red);       // красная обводка для видимости
    hitboxShape.setOutlineThickness(1.f);

    if (facingRight) {
        // Проверяем 3 точки по хитбоксу вертикали справа для коллизии
        float xCheckTop = bounds.left + bounds.width - 60;
        float xCheckMiddle = bounds.left + bounds.width - 30;
        float xCheckBottom = bounds.left + bounds.width - 70;

        float yTop = bounds.top + 5;
        float yMiddle = bounds.top + bounds.height / 2 - 35;
        float yBottom = bounds.top + bounds.height - 50;

        int tileXTop = int(xCheckTop / 32);
        int tileXMiddle = int(xCheckMiddle / 32);
        int tileXBottom = int(xCheckBottom / 32);

        int tileY1 = int(yTop / 32);
        int tileY2 = int(yMiddle / 32);
        int tileY3 = int(yBottom / 32);

        // Если есть столкновение, то отменить движение
        if (arr[tileY1][tileXTop] == '0') {
            spriteEntity.setPosition(tileXTop * 32 - bounds.width + 20, bounds.top);
        }
        else if (arr[tileY2][tileXMiddle] == '0') {
            spriteEntity.setPosition(tileXMiddle * 32 - bounds.width + 30, bounds.top);
        }
        else if (arr[tileY3][tileXBottom] == '0') {
            spriteEntity.setPosition(tileXBottom * 32 - bounds.width + 50, bounds.top);
        }

        // Вывод точек соприкосновения для проверок
        sf::CircleShape pointShape(3);
        pointShape.setFillColor(sf::Color::Red);

        pointShape.setPosition(xCheckTop, yTop);
        window.draw(pointShape);

        pointShape.setPosition(xCheckMiddle, yMiddle);
        window.draw(pointShape);

        pointShape.setPosition(xCheckBottom, yBottom);
        window.draw(pointShape);
    }

    else {
        // Проверяем 3 точки по хитбоксу вертикали слева для коллизии
        float xCheckTop = bounds.left + 50;
        float xCheckMiddle = bounds.left + 10;
        float xCheckBottom = bounds.left + 70;

        float yTop = bounds.top + 5;
        float yMiddle = bounds.top + bounds.height / 2 - 35;
        float yBottom = bounds.top + bounds.height - 50;

        int tileXTop = int(xCheckTop / 32);
        int tileXMiddle = int(xCheckMiddle / 32);
        int tileXBottom = int(xCheckBottom / 32);

        int tileY1 = int(yTop / 32);
        int tileY2 = int(yMiddle / 32);
        int tileY3 = int(yBottom / 32);

        // Если есть столкновение, то отменить движение
        if (arr[tileY1][tileXTop] == '0') {
            spriteEntity.setPosition(tileXTop * 32 - 10, bounds.top);
        }
        else if (arr[tileY2][tileXMiddle] == '0') {
            spriteEntity.setPosition(tileXMiddle * 32 - 15, bounds.top);
        }
        else if (arr[tileY3][tileXBottom] == '0') {
            spriteEntity.setPosition(tileXBottom * 32 - 30, bounds.top);
        }

        // Вывод точек соприкосновения для проверок
        sf::CircleShape pointShape(3);
        pointShape.setFillColor(sf::Color::Green);

        pointShape.setPosition(xCheckTop, yTop);
        window.draw(pointShape);

        pointShape.setPosition(xCheckMiddle, yMiddle);
        window.draw(pointShape);

        pointShape.setPosition(xCheckBottom, yBottom);
        window.draw(pointShape);
    }
}

void Hero::drawHealthHero(sf::RenderWindow& window) {
    textHealthHero.setString("Health: " + std::to_string(health));
    window.draw(textHealthHero);
}

void Hero::drawHero(sf::RenderWindow& window) {
    window.draw(spriteEntity);
    window.draw(hitboxShape);
}


