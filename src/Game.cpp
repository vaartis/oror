#include <cmath>
#include <vector>

#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "Chibi.hpp"

#include "Game.hpp"

Game::Game()
    : window(sf::VideoMode(1280, 720), "ORoR")
    , player(window, *this)
    , level("spritesheet.png", {0, 160}, {32, 384}, {90, 82, 104}, 32)

{
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    level.setLevelMapString(lvlMapStr, 100);
    player.spawn = level.playerSpawn;
    player.sprite.setPosition(player.spawn.x, player.spawn.y);
}

void Game::run() {
    sf::Clock deltaClock;
    Chibi chibi;

    std::string repl_output;
    std::string str_to_eval;

    while (window.isOpen()) {
        sf::Event event;

        player.everyFrame();

        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

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

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Debug");

        ImGui::InputTextMultiline("Output", repl_output.data(), repl_output.size(), sf::Vector2f({300, ImGui::GetTextLineHeight() * 16}), ImGuiInputTextFlags_ReadOnly);

        char st[256];
        ImGui::InputText("##eval_code", st, 256);
        if (ImGui::Button("Eval")) {
            std::string result = chibi.eval_string(st).dump_to_string();

            std::copy(result.begin(), result.end(), std::back_inserter(repl_output));
        }

        ImGui::End();

        window.clear();
        window.draw(player);
        window.draw(level.sprite);

        sf::View view(player.sprite.getPosition(), sf::Vector2f(640, 480));
        window.setView(view);

        ImGui::SFML::Render(window);

        window.display();
    }

    ImGui::SFML::Shutdown();
}
