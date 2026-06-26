#include <SDL2/SDL.h>
#include <math.h>
#include "mathutils.hpp"

float calc_mid_point_vec(SDL_FPoint v1, SDL_FPoint v2) {
    // C = (A + B) / 2.
    float mid_point = (v1.x + v2.x) / 2, (v1.y + v2.y) / 2;
    return mid_point;
}

float calc_distance_vec(SDL_FPoint v1, SDL_FPoint v2) {
    // d = √(x1 – x2)2 + (y1 – y2 )
    return sqrt(std::pow(v1.x - v2.x, 2) + std::pow(v1.y - v2.y, 2));
}

float calc_height_vec(SDL_FPoint v1, SDL_FPoint v2) {
    // h = (√3 / 2) * r
    float r = calc_distance_vec(v1, v2);
    return sqrt(3) / 2 * r;
}

SDL_FPoint calc_p2_vec(SDL_FPoint v1, SDL_FPoint v2) {
    // P2 = C + h × nˆ
    // Now let’s put those variables in terms that you know. First, C is the
    // mid- point of line AB, so C = (A + B) / 2. Next, h is the height of an
    // equilateral triangle with side length r. The Pythagorean theorem tells
    // you:
    // TODO you are here
    float mid    = calc_mid_point_vec(v1, v2);
    float height = calc_height_vec(v1, v2)

        return SDL_FPoint{};
}
