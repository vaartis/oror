#pragma once

#include <SFML/Graphics.hpp>

class Game;

class Player : public sf::Drawable {
public:
    Player(sf::RenderWindow &wnd, Game &game);

    sf::RenderWindow &window;

    sf::Texture fullGirl;
    sf::Sprite sprite;

    sf::Vector2f velocity;
    sf::Vector2i spawn {0, 0};

    bool isJumping = true;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void move(float x, float y);

    void jump();

    enum class WalkDirection {
        Left,
        Right
    };
    void walk(WalkDirection walkDirection);

    void everyFrame();
private:
    sf::Clock walkAnimationTimer;
    const Game &game;
};
