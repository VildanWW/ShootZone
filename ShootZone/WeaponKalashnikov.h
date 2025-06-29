#pragma once
#include "Weapon.h"

class WeaponsKalashnikov : public Weapons {
private:
	int ammo = 1000;
public:
	void shoot(sf::RenderWindow& window, const sf::Vector2f& heroPos, const sf::FloatRect& heroBounds,
		sf::Sprite spriteBullet, std::vector<Bullet>& bullets, bool shootRight) override;
};