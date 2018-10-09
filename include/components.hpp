#pragma once

#include <string>

#include "sexp.hpp"
#include "RTD.hpp"

class Component {
public:    
    virtual ~Component() { }
};

class GraphicsComponent : public Component {
public:
    GraphicsComponent(RTD rtd, SExp component) {
        filename = rtd.get_field_from(component, "filename")->to<std::string>().value();
    }

    std::string filename;

    virtual ~GraphicsComponent() { }
};

class TransformComponent : public Component {
public:
    TransformComponent(RTD rtd, SExp component) {
        x = rtd.get_field_from(component, "x")->to<sexp_sint_t>().value();
        y = rtd.get_field_from(component, "y")->to<sexp_sint_t>().value();
    }

    sexp_sint_t x;
    sexp_sint_t y;

    virtual ~TransformComponent() { }
};
