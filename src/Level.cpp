#include <cmath>

#include "Level.hpp"
#include "Utils.hpp"

Level::Level(const std::string &spritesheetPath, const sf::Vector2i &ground,
             const sf::Vector2i &ladder, const sf::Color &maskColor,
             uint32_t tileSize)
    : tileSize(tileSize)
{
    spritesheet.loadFromFile(spritesheetPath);

    groundImage.create(tileSize, tileSize);
    groundImage.copy(spritesheet, 0, 0, sf::IntRect(ground.x, ground.y,
                                                    tileSize, tileSize));

    ladderImage.create(tileSize, tileSize);
    ladderImage.copy(spritesheet, 0, 0, sf::IntRect(ladder.x, ladder.y,
                                                    tileSize, tileSize));
    ladderImage.createMaskFromColor(maskColor);
}

void Level::fillTexture() {
    texture.create(pitch * tileSize, pitch * tileSize);
    Utils::clearTexture(texture);

    int j = 0, i = 0;
    for (int p = 0; p < mapString.length(); p++) {
        if (p % pitch == 0 && p > 0) {
            i++;
        }

        j = p % pitch;

        switch (mapString[p]) {
        case '#':
            texture.update(groundImage, tileSize * j, tileSize * i);
            break;
        case '|':
            texture.update(ladderImage, tileSize * j, tileSize * i);
            break;
        case 'p':
            playerSpawn = sf::Vector2i(tileSize * j, tileSize * i);
            break;
        }
    }

    sprite.setTexture(texture);
}

void Level::setLevelMapString(const std::string &map, uint32_t newPitch) {
    pitch = newPitch;
    mapString = map;
    fillTexture();
}

bool Level::isSolidGround(const sf::Vector2f &point) const {
    int x = std::floor(point.x / tileSize);
    int y = std::floor(point.y / tileSize);
    if (x < 0 || y < 0) return false;

    return mapString[y * pitch + x] == '#';
}
