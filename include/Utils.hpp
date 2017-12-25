#pragma once

#include <functional>
#include <numeric>
#include <initializer_list>

namespace sf {
class Texture;
};

struct Utils {
    /// \brief Zero every pixel in the texture, effectively clearing the
    ///        video memory garbage that may remain it it
    static void clearTexture(sf::Texture &t);

    // \brief Calculate number average
    template<typename T> static float average(std::initializer_list<T> args) {
        static_assert(std::is_arithmetic<T>::value, "Average only makes sense on arithmetic types");

        return std::accumulate(args.begin(), args.end(), 0, std::plus<T>()) / args.size();
    }
};
