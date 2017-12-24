#pragma once

namespace sf {
class Texture;
};

struct Utils {
    /// \brief Zero every pixel in the texture, effectively clearing the
    ///        video memory garbage that may remain it it
    static void clearTexture(sf::Texture &t);
};
