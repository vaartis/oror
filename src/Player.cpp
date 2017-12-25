#include <cmath>
#include <functional>

#include <SFML/Graphics.hpp>

#include "Player.hpp"
#include "Game.hpp"
#include "Utils.hpp"

Player::Player(sf::RenderWindow &wnd, Game &game)
    : window(wnd)
    , game(game)
 {
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

void Player::walk(WalkDirection walkDirection) {
    const int frameCount = 4; // FIXME

    if (walkDirection == WalkDirection::Right) {
        sprite.setOrigin({0, 0});
        sprite.setScale({1, 1});
    } else {
        // Mirror the sprite, so it will seem like we are walking to the left
        sprite.setOrigin({sprite.getLocalBounds().width, 0});
        sprite.setScale({-1, 1});
    }

    if (walkAnimationTimer.getElapsedTime().asSeconds() >= 0.1) {
        sf::IntRect rect = sprite.getTextureRect();
        if (rect.left == 47 * frameCount) {
            rect.left = 0;
        } else {
            rect.left = 47 * ((rect.left / 47) + 1);
        }
        sprite.setTextureRect(rect);

        walkAnimationTimer.restart();
    }

    sf::FloatRect pos = sprite.getGlobalBounds();

    float topY = pos.top,
        botY = pos.top + pos.height;
    float midY = Utils::average({topY, botY});

    float sideX = (walkDirection == WalkDirection::Right) ? (pos.left + pos.width) : pos.left;
    int moveXCount = (walkDirection == WalkDirection::Right) ? 3 : -3;

    if (!(game.level.isSolidGround({sideX, topY}) ||
          game.level.isSolidGround({sideX, midY}))) {
        move(moveXCount, 0);
    }
}

void Player::everyFrame() {
    using SKK = sf::Keyboard::Key;

    std::map<sf::Keyboard::Key, std::function<void()>> keyActions {
        {SKK::Right, [&]() { walk(WalkDirection::Right); }},
        {SKK::Left, [&]() { walk(WalkDirection::Left); }}
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
    float botY = pos.top + pos.height;
    float botLX = pos.left;
    float botRX = pos.left + 16;

    if (game.level.isSolidGround(sf::Vector2f(botLX, botY)) ||
        game.level.isSolidGround(sf::Vector2f(botRX, botY))) {
        isJumping = false;
        velocity.y = 0;
    } else {
        velocity.y += 0.3;
    }

    // detect fall through the floor
    if (std::floor(botY) >= 500) {
        sprite.setPosition(spawn.x, spawn.y - pos.height);
    }
}
