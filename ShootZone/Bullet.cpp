#include "Bullet.h"

sf::FloatRect Bullet::getBounds() const {
	return sprite.getGlobalBounds();
}

Bullet::Bullet(const sf::Texture& texture, const sf::Vector2f& startPos, bool facingRight) {
    sprite.setTexture(texture);
    sprite.setScale(0.02f, 0.02f);        // уменьшаем спрайт
    sprite.setPosition(startPos);         // ставим в нужную позицию

    if (facingRight) {
        velocity = sf::Vector2f(speed, 0.f);  // летит вправо
        sprite.setRotation(90);             // смотрит вправо
    }
    else {
        velocity = sf::Vector2f(-speed, 0.f); // летит влево
        sprite.setRotation(-90);           // смотрит влево
    }
}

void Bullet::update(float deltaTime) {
    sprite.move(velocity * deltaTime);
}

void Bullet::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

bool Bullet::isOffScreen(const sf::RenderWindow& window) const {
    sf::FloatRect bounds = sprite.getGlobalBounds();
    if (bounds.left > window.getSize().x || bounds.top > window.getSize().y
        || bounds.left + bounds.width < 0 || bounds.top + bounds.height < 0) {
        return true;
    }
    else {
        return false;
    }
}


