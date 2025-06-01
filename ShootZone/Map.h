#pragma once
#include <SFML/Graphics.hpp>

const int height = 15;
const int width = 20;

// Функция отрисовки карты
void setMap(sf::Sprite& sprite, sf::RenderWindow& window) {
    std::string arr[height] = {
        "                    ",
        "                    ",
        "                    ",
        "                    ",
        "                    ",
        "                    ",
        "                    ",
        "                    ",
        "                    ",
        "                   0",
        "0                 00",
        "00 000   000   00000",
        "00000000000000000000",
        "00000000000000000000",
        "00000000000000000000"
    };

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (arr[i][j] == '0') {
                sprite.setTextureRect(sf::IntRect(64, 0, 32, 32));
            } else {
                sprite.setTextureRect(sf::IntRect(120, 0, 32, 32));
            }
            sprite.setPosition(j * 32, i * 32);
            window.draw(sprite);
        }
    }
}
