#include <cmath>

#include <SFML/Graphics.hpp>

#include "Game.hpp"

Game::Game() : window(sf::VideoMode(1280, 720), "RoRoR"), player(window, lvlMapStr) {
    window.setFramerateLimit(60);

    spritesheet.loadFromFile("spritesheet.png");

    groundImage.create(32, 32);
    groundImage.copy(spritesheet, 0, 0, sf::IntRect(0, 160, 32, 32));

    ladderImage.create(32, 32);
    ladderImage.copy(spritesheet, 0, 0, sf::IntRect(32, 384, 32, 32));
    ladderImage.createMaskFromColor(sf::Color(90, 82, 104));

    fillLevelTexture();
}

void Game::fillLevelTexture() {
    lvlTexture.create(25 * tileSize, 25 * tileSize);
    Utils::clearTexture(lvlTexture);

    int j = 0, i = 0;
    for (int p = 0; p < lvlMapStr.length(); p++) {
        if (p % 25 == 0 && p > 0) {
            i++;
        }

        j = p % 25;

        switch (lvlMapStr[p]) {
        case '#':
            lvlTexture.update(groundImage, 32 * j, 32 * i);
            break;
        case '|':
            lvlTexture.update(ladderImage, 32 * j, 32 * i);
            break;
        case 'p':
            player.spawn = sf::Vector2i(32 * j, 32 * i);
            player.sprite.setPosition(32 * j, 32 * i);
            break;
        }
    }

    lvlSprite.setTexture(lvlTexture);
}

void Game::run() {
    while (window.isOpen()) {
        sf::Event event;

        player.everyFrame();

        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed: {
                window.close();
                break;
            }
            case sf::Event::KeyReleased: {
                if (event.key.code == sf::Keyboard::Key::Left || event.key.code == sf::Keyboard::Key::Right) {
                    sf::IntRect rect = player.sprite.getTextureRect();
                    rect.left = 0;
                    player.sprite.setTextureRect(rect);
                }
                break;
            }
            default: { /* Nothing */ }
            }
        }
        window.clear();
        window.draw(player);
        window.draw(lvlSprite);

        sf::View view(player.sprite.getPosition(), sf::Vector2f(640, 480));
        window.setView(view);

        window.display();
    }
}

bool Game::onSolidGround(const std::string &lvlMap,
                                int lvlPitch,
                                const sf::Vector2f &point) {
    int x = std::floor(point.x / 32);
    int y = std::floor(point.y / 32);
    if (x < 0 || y < 0) return false;

    return lvlMap[y * lvlPitch + x] == '#';
}
