#pragma once

#include <SFML/Graphics.hpp>

#include "Level.hpp"
#include "Player.hpp"
#include "Utils.hpp"
#include "Entity.hpp"
#include "systems.hpp"

/// \brief Main game class
class Game {
public:
    Game();
    void run();
    Level level;
private:
    long nextEntityId = 0;
    std::map<long, Entity> entities;
    std::vector<std::unique_ptr<System>> systems;

    Chibi chibi;

    const std::string lvlMapStr =
"\
######                                                                                    #         \
     #   p                                                                                 #        \
     #                  ###############################||                                   #       \
     #                  #                              ||                                    #      \
     #                                     #   #       ||    #############################    #     \
     #                                            ##   ||                                      #    \
     #                                                 ||                                       #   \
     ##########||########   ##    ##   ##   ##  ##  ## ||                                        #  \
     #         ||                                      ||                                           \
     ###############################################################################################";

    sf::RenderWindow window;
    Player player;
};
