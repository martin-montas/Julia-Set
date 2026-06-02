#include <SDL2/SDL.h>
#include <stdio.h>

// Each pixel must correspond to a unique complex number z​ =x+iy
// then z^ 2 + c

#define HEIGHT 2
#define WIDTH 2

typedef struct {
  double real;
  double imaginary;

} Constant;

typedef struct {
  int x;
  int y;
  Constant c;
} Pixel;

int main() {
  Constant c;
  c.real = 0.4;
  c.imaginary = 0.156;
  Pixel p;
  p.c = c;
  Pixel screen[HEIGHT][WIDTH];
  for (int i= 0; i <HEIGHT; i++) {
    for (int j= 0; j <WIDTH; j++) {
      screen[i][j].c =  c;
    }
  }
  return 0;
}
