#include <unordered_map>
#include <functional>
#include <iostream>

#include "Entity.hpp"

Entity::Entity(Chibi &chibi, SExp entity_object) {
    RTD entity_rtd(chibi, "entity");
    SExp rtd_name = chibi.env_ref("rtd-name");
    SExp record_rtd = chibi.env_ref("record-rtd");
    SExp scm_map = chibi.env_ref("map");

    if (!entity_rtd.obj_is(entity_object))
        throw std::invalid_argument("Trying to create an entity from a non-entity type");

    SExp components = entity_rtd.get_field_from(entity_object, "components").value();
    components.for_each([&](SExp component) {
                            auto comp_rtd = *record_rtd.apply(component);
                            auto comp_name = *rtd_name.apply(comp_rtd)->to<Symbol>();

                            if (comp_name == "graphics-component") {
                                addComponent(
                                    std::make_unique<GraphicsComponent>(RTD(chibi, comp_rtd), component)
                                );
                            } else if (comp_name == "transform-component") {
                                addComponent(
                                    std::make_unique<TransformComponent>(RTD(chibi, comp_rtd), component)
                                );
                            }
                        }
    );
}

void Entity::addComponent(std::unique_ptr<Component> component) {
    components.emplace(std::type_index(typeid(component)), std::move(component));
}
