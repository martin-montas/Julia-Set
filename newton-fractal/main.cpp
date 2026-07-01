#include <SDL2/SDL.h>
#include <complex>
#include <stdint.h>
#include <cmath>
#include <stdio.h>

int WIDTH  = 800;
int HEIGHT = 600;

double map_pixel(int number, int map_pixel, double new_min, double new_max) {
    return new_min + ((new_max - new_min) * number) / map_pixel;
}

uint32_t buffer[800 * 600];
size_t   max_interations = 100;
bool     quit            = false;

std::complex<double> newton_formula(std::complex<double> c) {
    std::complex<double> n;
    n = c - ((c * c * c) - 2.0) / (3.0 * (c * c));
    return n;
}

bool is_close(std::complex<double> a, std::complex<double> b, double epsilon = 1e-7) {
    return std::abs(a - b) < epsilon;
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL Error: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_Window* window =
        SDL_CreateWindow("Julia Set: Fractal", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         WIDTH * 2, HEIGHT * 2, SDL_WINDOW_SHOWN);

    SDL_StopTextInput();
    if (!window) {
        printf("Window Error: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_Renderer* renderer =
        SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer) {
        printf("Renderer Error: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                                             SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);

    std::complex<double> root_1(std::pow(2.0, 1.0 / 3.0), 0.0);
    std::complex<double> root_2(-0.62996052, 1.09112364);
    std::complex<double> root_3(-0.62996052, -1.09112364);

    bool                 quit = false;
    uint32_t             curr_pix;
    std::complex<double> tmp;
    std::complex<double> b;
    /* main render logic */
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            double y = map_pixel(i, HEIGHT, -2.0, 2.0);
            double x = map_pixel(j, WIDTH, -2.0, 2.0);
            b        = {x, y};
            int iter = 0;
            while (iter < 100) {
                tmp = newton_formula(b);
                b   = tmp;
                if (is_close(b, root_2)) {
                    curr_pix = 0x000000FF;
                } else if (is_close(b, root_1)) {
                    curr_pix = 0x00000000;
                } else if (is_close(b, root_3)) {
                    curr_pix = 0x0000FF00;
                }

                iter += 1;
            }
            buffer[i * WIDTH + j] = curr_pix;
        }
    }
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                quit = false;
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    quit = true;
                }
                break;
            }
        }
        SDL_UpdateTexture(texture, nullptr, buffer, WIDTH * sizeof(uint32_t));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
