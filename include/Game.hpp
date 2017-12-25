#pragma once

#include <SFML/Graphics.hpp>

#include "Level.hpp"
#include "Player.hpp"
#include "Utils.hpp"

/// \brief Main game class
class Game {
public:
    Game();
    void run();
    Level level;
private:
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
