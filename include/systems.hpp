#pragma once

#include "SFML/Graphics.hpp"

#include "components.hpp"

class System {
public:
    virtual ~System() {}
};

class GraphicsSystem : public System {
public:
    GraphicsSystem(sf::RenderTarget &target) : target(target) { }

    void run(TransformComponent *trComponent) {

    }

    virtual ~GraphicsSystem() {}
private:
    sf::RenderTarget &target;
};
