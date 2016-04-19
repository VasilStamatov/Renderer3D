#include <SDL\SDL.h>
#include "SDL_Init.h"
#include <iostream>

namespace GraphicalEngine
{
  int Init()
  {
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
      std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
      return -1;
    }
    return 0;
  }
}