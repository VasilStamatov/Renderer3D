#pragma once

#include <unordered_map>
#include <BML/Vector2D.h>
namespace GraphicalEngine
{
  class InputManager
  {
  public:
    InputManager();
    ~InputManager();

    //update the key map
    void Update();

    void PressKey(unsigned int _keyID);
    void ReleaseKey(unsigned int _keyID);
    void SetMouseCoords(float _x, float _y);

    ///return true if the key is held down
    bool IsKeyDown(unsigned int _keyID);

    ///returns true if the key is pressed this frame
    bool IsKeyPressed(unsigned int _keyID);

    //getters
    BML::Vector2D GetMouseCoords() const { return m_mouseCoords; }
  private:

    bool wasKeyDown(unsigned int _keyID);

    std::unordered_map<unsigned int, bool> m_keyMap;
    std::unordered_map<unsigned int, bool> m_previousKeyMap;

    BML::Vector2D m_mouseCoords;
  };

}