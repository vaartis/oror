#include <vector>

#include <SFML/Graphics.hpp>

#include "Utils.hpp"

void Utils::clearTexture(sf::Texture &t) {
    sf::Vector2u size = t.getSize();
    std::vector<sf::Uint8> data(size.x * size.y * 4, 0);
    t.update(data.data());
}
