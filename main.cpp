#include <SDL2/SDL.h>
#include <cmath>
#include <complex>
#include <stdint.h>
#include <stdio.h>

int WIDTH = 800;
int HEIGHT = 600;

uint32_t buffer[800 * 600];

double map_pixel(int number, int map_pixel, int new_min, int new_max) {
  return new_min + ((new_max - new_min) * number) / map_pixel;
}

int main() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("SDL Error: %s\n", SDL_GetError());
    exit(1);
  }

  SDL_Window *window = SDL_CreateWindow(
      "Julia Set: Fractal", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      WIDTH * 2, HEIGHT * 2, SDL_WINDOW_SHOWN);

  SDL_StopTextInput();
  if (!window) {
    printf("Window Error: %s\n", SDL_GetError());
    exit(1);
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (!renderer) {
    printf("Renderer Error: %s\n", SDL_GetError());
    exit(1);
  }

  SDL_Texture *texture =
      SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                        SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
  bool quit = false;

  /* main render logic */
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      double y = map_pixel(i, HEIGHT, -2, 2);
      double x = map_pixel(j, WIDTH, -2, 2);

      std::complex<double> z(x, y);
      std::complex<double> a(-0.8, 0.156);
      for (int o = 0; o < 100; o++) {
        z = z * z;
        z += a;
        if (std::norm(z) >= 4) {
          // TODO: find a better way of doing this
          if (o <= 20)
            buffer[(WIDTH * i) + j] = 0x0000FFFF;
          else if (o <= 80)
            buffer[(WIDTH * i) + j] = 0x66CCFFFF;
          else if (o <= 100)
            buffer[(WIDTH * i) + j] = 0x00000000;
        }
      }
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
          quit = false;
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
