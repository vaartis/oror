#pragma once

#include <SFML/Graphics.hpp>

class Player : public sf::Drawable {
private:
    sf::Clock walkAnimationTimer;
public:
    const std::string &lvlMapStr;

    sf::RenderWindow &window;

    sf::Texture fullGirl;
    sf::Sprite sprite;

    sf::Vector2f velocity;
    sf::Vector2i spawn {0, 0};

    bool isJumping = true;

    Player(sf::RenderWindow &wnd, const std::string &lvlMap);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void move(float x, float y);

    void jump();

    void everyFrame();
};
