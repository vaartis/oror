#include <iostream>
#include <cmath>
#include <map>
#include <functional>
#include <optional>

#include <SFML/Graphics.hpp>

class Player : public sf::Drawable {
    private:
        sf::Clock walkAnimationTimer;
    public:
        sf::RenderWindow &window;

        sf::Texture fullGirl;
        sf::Sprite sprite;

        sf::Vector2f velocity;

        bool isJumping = true;

        Player(sf::RenderWindow &wnd) : window(wnd) {
            fullGirl.loadFromFile("girl.png");
            sprite.setTexture(fullGirl);

            sf::IntRect rect(0, 0, 47, 53);
            sprite.setTextureRect(rect);
        }


        void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
            target.draw(sprite);
        }

        void move(float x, float y) {
            sprite.move(x, y);
        }

        void playerJump() {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !isJumping) {
                isJumping = true;
                velocity.y = -10;
            }
        }

        void everyFrame() {
            {
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

                for (const auto &kv : keyActions)
                    if (sf::Keyboard::isKeyPressed(kv.first))
                        kv.second();

            }

            playerJump();
            move(0, velocity.y);

            sf::FloatRect pos = sprite.getGlobalBounds();
            if (std::floor(pos.top + pos.height) >= 200) {
                velocity.y = 0;
                sprite.setPosition(pos.left, 200 - pos.height);
                isJumping = false;
            } else {
                velocity.y += 0.3;
            }
        }
};

int main() {
    auto spritesheet = sf::Image();
    spritesheet.loadFromFile("spritesheet.png");

    auto groundImage = sf::Image();
    groundImage.create(32, 32);
    groundImage.copy(spritesheet, 0, 0, sf::IntRect(0, 160, 32, 32));

    auto ladderImage = sf::Image();
    ladderImage.create(32, 32);
    ladderImage.copy(spritesheet, 0, 0, sf::IntRect(32, 384, 32, 32));
    ladderImage.createMaskFromColor(sf::Color(90, 82, 104));

    sf::RenderWindow window(sf::VideoMode(1280, 720), "RoRoR");
    window.setFramerateLimit(60);

    Player player(window);

    std::string lvlMapStr =
"####                     \
     #   p               \
     #                   \
     #                   \
     #                   \
     #                   \
     #                   \
     ###########|########\
     #          |        \
     ####################";


    auto lvlTexture = sf::Texture();
    lvlTexture.create(32 * 25, 32 * 10);

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
                player.sprite.setPosition(32 * j, 32 * i);
                break;
        }
    }

    auto lvlSprite = sf::Sprite();
    lvlSprite.setTexture(lvlTexture);

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
                }
            }
        }



        window.clear();
        window.draw(player);
        window.draw(lvlSprite);

        sf::View view(player.sprite.getPosition(), sf::Vector2f(640, 480));
        window.setView(view);

        window.display();
    }

    return 0;
}
