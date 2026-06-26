#ifndef SRC_MATHUTILS_HPP_
#define SRC_MATHUTILS_HPP_

#include <SDL2/SDL.h>
#include <cmath>

class MathUtils {
public:
  inline SDL_FPoint calc_mid_point_vec(SDL_FPoint v1, SDL_FPoint v2) {
    // C = (A + B) / 2.
    SDL_FPoint v3 = {(v1.x + v2.x) / 2, (v1.y + v2.y) / 2};
    return v3;
  }
  inline float calc_distance_vec(SDL_FPoint v1, SDL_FPoint v2) {
    // d = √(x1 – x2)2 + (y1 – y2 )
    return sqrt(std::pow(v1.x - v2.x, 2) + std::pow(v1.y - v2.y, 2));
  }
  inline float calc_height_vec(SDL_FPoint v1, SDL_FPoint v2) {
    // h = (√3 / 2) * r

    // TODO: calculate r here
    float r;
    return sqrt(3) / 2 * r;
  }
};

#endif // SRC_MATHUTILS_HPP_
