#pragma once

#include <cmath>

#include <SFML/Graphics.hpp>

#include "Player.hpp"
#include "Utils.hpp"

/// \brief Main game class
class Game {
public:
    Game();

    void run();

    /// \brief Checks if the point is on the solid ground, e.g. platform
    static bool onSolidGround(const std::string &lvlMap, int lvlPitch, const sf::Vector2f &point);
private:
    const std::string lvlMapStr =
"######                   \
     #   p               \
     #                   \
     #                   \
     #                   \
     #                   \
     #                   \
     ###########|########\
     #          |        \
     ####################";

    sf::RenderWindow window;
    Player player;

    sf::Image spritesheet;

    sf::Texture lvlTexture;
    sf::Sprite lvlSprite;

    sf::Image groundImage;
    sf::Image ladderImage;

    static const int tileSize = 32;

    void fillLevelTexture();
};
