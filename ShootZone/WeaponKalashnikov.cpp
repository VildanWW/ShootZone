#include <SFML/Graphics.hpp>
#include "WeaponKalashnikov.h"

void WeaponsKalashnikov::shoot(sf::RenderWindow& window, const sf::Vector2f& heroPos, const sf::FloatRect& heroBounds, 
	sf::Sprite spriteBullet, std::vector<Bullet>& bullets, bool shootRight) {
    if (ammo <= 0) return;
    ammo--;

    sf::Vector2f bulletStartPos;
    if (shootRight) {
        bulletStartPos = {
            heroPos.x + heroBounds.width * 0.9f - 10,
            heroPos.y + heroBounds.height * 0.5f - 40
        };
    }
    else {
        bulletStartPos = {
            heroPos.x + heroBounds.width * 0.1f,
            heroPos.y + heroBounds.height * 0.5f - 25
        };
    }

    bullets.emplace_back(*spriteBullet.getTexture(), bulletStartPos, shootRight);
}
