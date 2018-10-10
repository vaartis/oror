#pragma once

#include <map>
#include <vector>
#include <iostream>
#include <typeindex>
#include <functional>
#include <memory>

#include "components.hpp"

class Entity final {
public:
    Entity(Chibi &chibi, SExp entity_object);

    Entity(const Entity&) = delete;
    Entity(Entity&&);

    Entity& operator=(const Entity&) = delete;
    Entity& operator=(Entity&&);

    /** Get the last added component of this type that was added. */
    template <typename T>
    T *get_component();

    template <typename T>
    void add_component(std::unique_ptr<T> &&);

private:
    std::string type;
    std::map<std::type_index, std::unique_ptr<Component>> components;
};

template <typename T>
T *Entity::get_component() {
    const auto& comp_it = components.find(typeid(T));
    if (comp_it != components.end()) {
        T* comp = dynamic_cast<T *>(comp_it->second.get());
        assert(comp != nullptr);
        return comp;
    } else {
        return nullptr;
    }
}
