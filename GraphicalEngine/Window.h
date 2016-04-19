#pragma 

#include <SDL\SDL.h>
#include <string>

namespace GraphicalEngine
{
  enum WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

  class Window
  {
  public:
    Window();
    ~Window();

    //Create the window
    bool Create(const std::string& _windowName, int _screenWidth, int _screenHeight, unsigned int _currentFlags);

    //Set the window to null
    void SetNull() { m_sdlWindow = nullptr; }

    //Getters
    int GetScreenWidth() const { return m_screenWidth; };
    int GetScreenHeight() const { return m_screenHeight; };
    SDL_Window* GetWindow() const { return m_sdlWindow; }

  private:
    SDL_Window* m_sdlWindow = nullptr;
    int m_screenWidth, m_screenHeight;
  };
}

