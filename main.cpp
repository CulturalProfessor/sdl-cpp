#include <SDL2/SDL.h>
#include <SDL_error.h>
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_timer.h>
#include <SDL_video.h>
#include <ctime>
#include <iostream>

void randomizeColor(int &r, int &g, int &b) {
  r = rand() % 256;
  g = rand() % 256;
  b = rand() % 256;
}

int main(int argx, char *argv[]) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL Error: " << SDL_GetError() << std::endl;
    return 1;
  }
  srand(time(0));

  int screenWidth = 1000, screenHeight = 600, rectWidth = 200, rectHeight = 150,
      x = 0, y = 0;
  float xSpeed = 300, ySpeed = 300;
  SDL_Event event;
  bool running = true;
  float dx = 300; // pixels/sec
  float dy = 300;
  Uint32 lastTime = SDL_GetTicks();
  int r, g, b;
  randomizeColor(r, g, b);

  SDL_Window *window = SDL_CreateWindow("HOME SCREEN", SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED, screenWidth,
                                        screenHeight, SDL_WINDOW_SHOWN);

  if (!window) {
    std::cout << "SDL Error: " << SDL_GetError() << std::endl;
    return 1;
  }

  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if (!renderer) {
    std::cout << "Renderer Error: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
      }
    }

    Uint32 currentTime = SDL_GetTicks();
    float deltaTime = (currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;

    // Playground
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // RED Rectangle
    SDL_Rect rect = {x, y, rectWidth, rectHeight};
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderFillRect(renderer, &rect);

    SDL_RenderPresent(renderer);

    // Right wall
    if (x + rectWidth >= screenWidth) {
      x = screenWidth - rectWidth; // prevent sticking
      dx = -dx;
      randomizeColor(r, g, b);
    }

    // Left wall
    if (x <= 0) {
      x = 0;
      dx = -dx;
      randomizeColor(r, g, b);
    }

    // Bottom wall
    if (y + rectHeight >= screenHeight) {
      y = screenHeight - rectHeight;
      dy = -dy;
      randomizeColor(r, g, b);
    }

    // Top wall
    if (y <= 0) {
      y = 0;
      dy = -dy;
      randomizeColor(r, g, b);
    }
    x += dx * deltaTime;
    y += dy * deltaTime;

    SDL_Delay(16);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}