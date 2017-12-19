#include <functional>

#include <SFML/Graphics.hpp>

#include "Player.hpp"
#include "Game.hpp"

Player::Player(sf::RenderWindow &wnd, const std::string &lvlMap) : window(wnd), lvlMapStr(lvlMap) {
    fullGirl.loadFromFile("girl.png");
    sprite.setTexture(fullGirl);

    sf::IntRect rect(0, 0, 47, 53);
    sprite.setTextureRect(rect);
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite);
}

void Player::move(float x, float y) {
    sprite.move(x, y);
}

void Player::jump() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !isJumping) {
        isJumping = true;
        velocity.y = -10;
    }
}

void Player::everyFrame() {
    using SKK = sf::Keyboard::Key;

    std::map<sf::Keyboard::Key, std::function<void()>> keyActions {
        {SKK::Right, [&]() {
                         sprite.setOrigin({0, 0});
                         sprite.setScale({1, 1});

                         if (walkAnimationTimer.getElapsedTime().asSeconds() >= 0.1) {
                             sf::IntRect rect = sprite.getTextureRect();
                             if (rect.left == 47 * 4) {
                                 rect.left = 0;
                             } else {
                                 rect.left = 47 * ((rect.left / 47) + 1);
                             }
                             sprite.setTextureRect(rect);

                             walkAnimationTimer.restart();
                         }

                         move(3, 0);
                     }},
        {SKK::Left, [&]() {
                        sprite.setOrigin({sprite.getLocalBounds().width, 0});
                        sprite.setScale({-1, 1});

                        if (walkAnimationTimer.getElapsedTime().asSeconds() >= 0.1) {
                            sf::IntRect rect = sprite.getTextureRect();
                            if (rect.left == 47 * 4) {
                                rect.left = 0;
                            } else {
                                rect.left = 47 * ((rect.left / 47) + 1);
                            }
                            sprite.setTextureRect(rect);

                            walkAnimationTimer.restart();
                        }

                        move(-3, 0);
                    }}
    };

    for (const auto &kv : keyActions) {
        if (sf::Keyboard::isKeyPressed(kv.first)) {
            kv.second();
        }
    }

    jump();
    move(0, velocity.y);

    sf::FloatRect pos = sprite.getGlobalBounds();
    //detect collision with the level
    float bY = pos.top + pos.height;
    float blX = pos.left;
    float brX = pos.left + 16;

    if (Game::onSolidGround(lvlMapStr, 25, sf::Vector2f(blX, bY)) ||
        Game::onSolidGround(lvlMapStr, 25, sf::Vector2f(brX, bY))) {
        isJumping = false;
        velocity.y = 0;
    } else {
        velocity.y += 0.3;
    }

    // detect fall through the floor
    if (std::floor(bY) >= 500) {
        sprite.setPosition(spawn.x, spawn.y - pos.height);
    }
}
