#pragma once
#include <SFML/Graphics.hpp>

class Entity {
protected:
	sf::Sprite spriteEntity;
	int health = 0;
};

class Hero : public Entity {
private:
	sf::Font fontHero;
	sf::Text textHealthHero;
	
	float CurrentFrame = 0;
	
	bool notMove = true;
	bool facingRight = true;
	
public:
	Hero(sf::Sprite& spriteHero) {
		spriteEntity = spriteHero;
		spriteEntity.setTextureRect(sf::IntRect(0, 0, 143, 150));
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

	void moveSpriteEntity(sf::RenderWindow& window, float time) {
		notMove = true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			notMove = false;
			facingRight = true;

			CurrentFrame += 8 * time;
			if (CurrentFrame > 6) CurrentFrame -= 6;
			spriteEntity.setTextureRect(sf::IntRect(143 * int(CurrentFrame), 0, 143, 164));
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
			spriteEntity.setTextureRect(sf::IntRect(143 * int(CurrentFrame), 0, 143, 164));
			spriteEntity.setScale(-1.f, 1.f);
			spriteEntity.setOrigin(143.f, 0.f);
			spriteEntity.move(-200 * time, 0);
			textHealthHero.move(-200 * time, 0);
		}

		// Если персонаж не двигается — ставим текстуру покоя
		if (notMove) {
			spriteEntity.setTextureRect(sf::IntRect(0, 159, 143, 164)); // Кадр покоя (например, первый)

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
	
	int drawHealthHero(sf::RenderWindow& window) {
		textHealthHero.setString("Health: " + std::to_string(health));
		window.draw(textHealthHero);
		return 0;
	}

	void drawHero(sf::RenderWindow& window) {
		window.draw(spriteEntity);
	}
};
