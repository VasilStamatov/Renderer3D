#include "Window.h"
#include <iostream>

namespace GraphicalEngine
{
  Window::Window()
  {
  }


  Window::~Window()
  {
  }

  bool Window::Create(const std::string& _windowName, int _screenWidth, int _screenHeight, unsigned int _currentFlags)
  {
    Uint32 flags = SDL_WINDOW_SHOWN;
    m_screenHeight = _screenHeight;
    m_screenWidth = _screenWidth;

    if (_currentFlags & INVISIBLE)
    {
      flags |= SDL_WINDOW_HIDDEN;
    }
    if (_currentFlags & FULLSCREEN)
    {
      flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    }
    if (_currentFlags & BORDERLESS)
    {
      flags |= SDL_WINDOW_BORDERLESS;
    }
    //create the window
    m_sdlWindow = SDL_CreateWindow(_windowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_screenWidth, m_screenHeight, flags);
    //error check
    if (m_sdlWindow == nullptr)
    {
      std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
      return false;
    }

    return true;
  }
}