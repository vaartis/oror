#include <map>
#include <vector>
#include <typeindex>
#include <functional>

#include "components/Component.hpp"

class Entity {
public:

    /** Get the last added component of this type that was added. */
    template <typename T>
    std::optional<T> getComponent();

    /** Get all the components of this type. */
    template <typename T>
    std::vector<T> getComponents();

    template <typename T>
    void addComponent(T &component);

private:
    std::string type;
    std::multimap<std::type_index, std::reference_wrapper<Component>> components;
};

template <typename T>
void Entity::addComponent(T &component) {
    components.emplace(component);
}

template <typename T>
std::optional<T> Entity::getComponent() {
    auto component = components.find(typeid(T));

    return component != components.end()
        ? std::make_optional(component)
        : std::nullopt;
}


template <typename T>
std::vector<T> Entity::getComponents() {
    std::vector<std::reference_wrapper<Component>> found_components;

    auto range = components.equal_range(typeid(T));

    std::copy(range.first, range.second, std::back_inserter(found_components));

    return found_components;
}
