#include <cmath>

#include <SFML/Graphics.hpp>

#include "Game.hpp"

Game::Game()
    : window(sf::VideoMode(1280, 720), "ORoR")
    , player(window, *this)
    , level("spritesheet.png", {0, 160}, {32, 384}, {90, 82, 104}, 32)

{
    window.setFramerateLimit(60);
    level.setLevelMapString(lvlMapStr, 100);
    player.spawn = level.playerSpawn;
    player.sprite.setPosition(player.spawn.x, player.spawn.y);
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
                switch (event.key.code) {
                case sf::Keyboard::Key::Left:
                case sf::Keyboard::Key::Right: {
                    sf::IntRect rect = player.sprite.getTextureRect();
                    rect.left = 0;
                    player.sprite.setTextureRect(rect);
                    break;
                }
                case sf::Keyboard::Key::R:
                    player.sprite.setPosition(player.spawn.x, player.spawn.y);
                    break;
                }

                break;
            }
            default: { /* Nothing */ }
            }
        }
        window.clear();
        window.draw(player);
        window.draw(level.sprite);

        sf::View view(player.sprite.getPosition(), sf::Vector2f(640, 480));
        window.setView(view);

        window.display();
    }
}
