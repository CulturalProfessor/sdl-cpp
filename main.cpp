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
  g = rand() % 156;
  b = rand() % 256;
}

void drawFilledCircle(SDL_Renderer *renderer, int cx, int cy, int radius) {
  for (int w = 0; w < radius * 2; w++) {
    for (int h = 0; h < radius * 2; h++) {
      int dx = radius - w;
      int dy = radius - h;

      // x2+y2=r2
      if ((dx * dx + dy * dy) <= (radius * radius)) {
        SDL_RenderDrawPoint(renderer, cx + dx, cy + dy);
      }
    }
  }
}

int main(int argx, char *argv[]) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL Error: " << SDL_GetError() << std::endl;
    return 1;
  }
  srand(time(0));

  int screenWidth = 1200, screenHeight = 800, rectWidth = 20, rectHeight = 120,
      x1 = 10, y1 = 10, x2 = screenWidth - rectWidth - 10, y2 = 10, ballX = 500,
      ballY = 300, ballRadius = 10;
  float speed = 600; // control speed
  SDL_Event event;
  bool running = true;
  float ballDX = 300; // pixels/sec
  float ballDY = 300;
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
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);
    Uint32 currentTime = SDL_GetTicks();
    float deltaTime = (currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;

    // Playground
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Rect rect1 = {x1, y1, rectWidth, rectHeight};
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderFillRect(renderer, &rect1);

    SDL_Rect rect2 = {x2, y2, rectWidth, rectHeight};
    SDL_RenderFillRect(renderer, &rect2);
    SDL_SetRenderDrawColor(renderer, b, g, r, 255);

    drawFilledCircle(renderer, ballX, ballY, ballRadius);

    SDL_RenderPresent(renderer);

    ballX += ballDX * deltaTime;
    ballY += ballDY * deltaTime;

    // Ball Left Paddle Collision
    if (ballX - ballRadius <= x1 + rectWidth && ballY >= y1 &&
        ballY <= y1 + rectHeight) {

      ballX = x1 + rectWidth + ballRadius;
      ballDX = -ballDX;
    }

    // Ball Right Paddle Collision
    if (ballX + ballRadius >= x2 && ballY >= y2 && ballY <= y2 + rectHeight) {

      ballX = x2 - ballRadius;
      ballDX = -ballDX;
    }

    // Ball Top Wall Collision
    if (ballY - ballRadius <= 0) {
      ballY = ballRadius;
      ballDY = -ballDY;
    }

    // Ball Bottom Wall Collision
    if (ballY + ballRadius >= screenHeight) {
      ballY = screenHeight - ballRadius;
      ballDY = -ballDY;
    }

    // Left Paddle
    if (y1 + rectHeight >= screenHeight) {
      y1 = screenHeight - rectHeight;
    }

    if (y1 <= 0) {
      y1 = 0;
    }

    // Right Paddle
    if (y2 + rectHeight >= screenHeight) {
      y2 = screenHeight - rectHeight;
    }

    if (y2 <= 0) {
      y2 = 0;
    }

    if (keystate[SDL_SCANCODE_W]) {
      y1 -= speed * deltaTime;
    }
    if (keystate[SDL_SCANCODE_S]) {
      y1 += speed * deltaTime;
    }
    if (keystate[SDL_SCANCODE_UP]) {
      y2 -= speed * deltaTime;
    }
    if (keystate[SDL_SCANCODE_DOWN]) {
      y2 += speed * deltaTime;
    }

    if (ballX < 0 || ballX > screenWidth) {
      ballX = screenWidth / 2;
      ballY = screenHeight / 2;

      SDL_Delay(100);
    }

    SDL_Delay(16);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}