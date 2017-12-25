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

    rect = sf::IntRect(0, 0, 47, 53);
    sprite.setTextureRect(rect);

    debugHitbox.setSize({47, 53});
    debugHitbox.setFillColor(sf::Color::Transparent);
    debugHitbox.setOutlineColor(sf::Color::Red);
    debugHitbox.setOutlineThickness(0.5);
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite);
    target.draw(debugHitbox);
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
    const int spriteWidth = rect.width;

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
        if (rect.left == spriteWidth * frameCount) {
            rect.left = 0;
        } else {
            rect.left = spriteWidth * ((rect.left / spriteWidth) + 1);
        }
        sprite.setTextureRect(rect);

        walkAnimationTimer.restart();
    }

    sf::FloatRect pos = sprite.getGlobalBounds();

    float topY = pos.top,
        botY = pos.top + pos.height;
    float midY = Utils::average({topY, botY});

    float sideX = (walkDirection == WalkDirection::Right) ? (pos.left + pos.width) : pos.left - 1;
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
    float TY = pos.top;
    float BY = pos.top + pos.height;
    float LX = pos.left;
    float RX = pos.left + 16;

    // check fall collision
    if (game.level.isSolidGround(sf::Vector2f(LX, BY)) ||
        game.level.isSolidGround(sf::Vector2f(RX, BY))) {
        isJumping = false;
        velocity.y = 0;
        sf::Vector2i tile = game.level.clampToTile({LX, BY});
        sprite.setPosition(LX, tile.y - pos.height);
    } else {
        velocity.y += 0.3;
    }

    // check headbutt collision
    if (game.level.isSolidGround(sf::Vector2f(LX, TY - 1)) ||
        game.level.isSolidGround(sf::Vector2f(RX, TY - 1))) {
        move(0, -velocity.y + 0.1);
        velocity.y = 0;
    }

    // detect fall through the floor
    if (std::floor(BY) >= 500) {
        sprite.setPosition(spawn.x, spawn.y - pos.height);
    }

    debugHitbox.setPosition(sprite.getPosition());
}
