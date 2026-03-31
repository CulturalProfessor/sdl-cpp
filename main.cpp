#include <SDL2/SDL.h>
#include <SDL_error.h>
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_timer.h>
#include <SDL_video.h>
#include <iostream>

int main(int argx, char *argv[]) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL Error: " << SDL_GetError() << std::endl;
    return 1;
  }

  int screenWidth = 1000, screenHeight = 600, rectWidth = 200, rectHeight = 150,
      x = 0;
      float speed = 300;
  SDL_Event event;
  bool running = true;
  bool flag = true;
  Uint32 lastTime = SDL_GetTicks();

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
    int randomNum1 = rand() % 255;
    int randomNum2 = rand() % 255;
    int randomNum3 = rand() % 255;
    Uint32 currentTime = SDL_GetTicks();
    float deltaTime = (currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;

    // Playground
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // RED Rectangle
    SDL_Rect rect = {x, 200, rectWidth, rectHeight};
    SDL_SetRenderDrawColor(renderer, randomNum1, randomNum2, randomNum3, 255);
    SDL_RenderFillRect(renderer, &rect);

    SDL_RenderPresent(renderer);

    if (x + rectWidth >= screenWidth) {
      flag = false;
    }
    if (x <= 0) {
      flag = true;
    }

    if (flag) {
    x += speed * deltaTime;

    } else {
     x -= speed * deltaTime;
    }

    SDL_Delay(16);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
