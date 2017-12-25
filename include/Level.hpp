#pragma once

#include <string>

#include <SFML/Graphics.hpp>

class Level {
public:
    Level(const std::string &spritesheetPath, const sf::Vector2i &ground,
          const sf::Vector2i &ladder, const sf::Color &maskColor,
          uint32_t tileSize);

    void setLevelMapString(const std::string &map, uint32_t pitch);

    /// \brief Checks if the point is on the solid ground, e.g. platform
    bool isSolidGround(const sf::Vector2f &point) const;

    sf::Vector2i playerSpawn {0, 0};
    sf::Sprite sprite;
private:
    uint32_t pitch;
    uint32_t tileSize;

    std::string mapString;

    sf::Texture texture;

    sf::Image groundImage;
    sf::Image ladderImage;
    sf::Image spritesheet;

    void fillTexture();
};
