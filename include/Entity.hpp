#pragma once

#include <map>
#include <vector>
#include <iostream>
#include <typeindex>
#include <functional>
#include <memory>

#include "components.hpp"

class Entity {
public:
    Entity(Chibi &chibi, SExp entity_bject);

    /** Get the last added component of this type that was added. */
    template <typename T>
    std::optional<T *> getComponent();

    /** Get all the components of this type. */
    /*
    template <typename T>
    std::vector<T> getComponents();
    */

    void addComponent(std::unique_ptr<Component> component);

private:
    std::string type;
    std::multimap<std::type_index, std::unique_ptr<Component>> components;
};

template <typename T>
std::optional<T *> Entity::getComponent() {
    auto component_i = components.find(std::type_index(typeid(T)));

    if (component_i != components.end()) {
        return dynamic_cast<T *>(component_i->second.get());
    } else {
        return std::nullopt;
    }
}


/*
template <typename T>
std::vector<T> Entity::getComponents() {
    std::vector<std::reference_wrapper<Component>> found_components;

    auto range = components.equal_range(std::type_index(typeid(T)));

    std::copy(range.first, range.second, std::back_inserter(found_components));

    return found_components;
}
*/
