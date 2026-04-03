#include <OpenGL/gl3.h>
#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char *argv[]) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL Error: " << SDL_GetError() << std::endl;
    return 1;
  }

  // Tell SDL we want OpenGL
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  SDL_Window *window =
      SDL_CreateWindow("OpenGL Window", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, 1000, 600, SDL_WINDOW_OPENGL);

  if (!window) {
    std::cout << SDL_GetError() << std::endl;
    return 1;
  }

  SDL_GLContext glContext = SDL_GL_CreateContext(window);

  if (!glContext) {
    std::cout << "OpenGL Context Error: " << SDL_GetError() << std::endl;
    return 1;
  }

  bool running = true;
  SDL_Event event;

  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
      }
    }

    // OpenGL rendering
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Swap buffers
    SDL_GL_SwapWindow(window);
  }

  SDL_GL_DeleteContext(glContext);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}