#include <SDL2/SDL.h>
#include <cmath>
#include <stdio.h>

using namespace std;
#define WIDTH 800
#define HEIGHT 600

typedef struct {
  float left = -2.0;
  float right = 2.0;
  float top = -1.5;
  float bottom = 1.5;

} complex_constant;

SDL_Rect arr[WIDTH * HEIGHT];
int main() {

  bool display_running = true;
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("SDL Error: %s\n", SDL_GetError());
    exit(1);
  }

  SDL_Window *window = SDL_CreateWindow(
      "Game Boy: (DMG)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      WIDTH * 2, HEIGHT * 2, SDL_WINDOW_SHOWN);

  SDL_StopTextInput();
  if (!window) {
    printf("Window Error: %s\n", SDL_GetError());
    exit(1);
  }

  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

  if (!renderer) {
    printf("Renderer Error: %s\n", SDL_GetError());
    exit(1);
  }

  SDL_Texture *texture =
      SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                        SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);

  bool quit = false;

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

    /* main render logic */
    for (int i = 0; i < WIDTH; i++) {
      for (int j = 0; j < HEIGHT; j++) {
        /* TODO: use this to see if a value diviates from the origin
         * (Geometry tip: You use the Pythagorean theorem here. If your complex
         * number is x+yi, the distance squared is x2+y2. If that value is
         * greater than 4, your distance is greater than 2).
         */

        // For each pixel:
        //
        // Convert the pixel into a complex number:
        // z= x + yi
        // Repeatedly calculate:
        // z=z^ 2 +c
        // After each iteration check:
        // x^2 +y^2
        //
        // If: x^2 +y^2 >4
        //
        // then it escaped → that pixel is not in the Julia set.

        /* coordinates */
        /*  complex number */

        for

          int x = -2 + (i * 0.005);
        int y = -1.5 + (j * 0.005);
        if ((sqrt(x) + sqrt(y)) > 4) {
          SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
          SDL_RenderDrawPoint(renderer, x, y);
          break;
        } else {
          SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
          SDL_RenderDrawPoint(renderer, x, y);
        }
      }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(window);
    SDL_Quit();
  }

  return 0;
}
