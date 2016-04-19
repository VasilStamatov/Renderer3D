#include "InputManager.h"

namespace GraphicalEngine
{
  InputManager::InputManager() : m_mouseCoords(0.0f, 0.0f)
  {
  }


  InputManager::~InputManager()
  {
  }
  void InputManager::Update()
  {
    //loop through key map using a for-each loop and copy it over to m_previousKeyMap
    for (auto& it : m_keyMap)
    {
      //use .first to access the first element of the keymap (uint), and .second to access the second (bool)
      m_previousKeyMap[it.first] = it.second;
    }
  }

  void InputManager::PressKey(unsigned int _keyID)
  {
    // Here we are treating _keyMap as an associative array.
    // if keyID doesn't already exist in _keyMap, it will get added
    m_keyMap[_keyID] = true;
  }
  void InputManager::ReleaseKey(unsigned int _keyID)
  {
    // Here we are treating _keyMap as an associative array.
    // switch the pressed button from true (being pressed) to false (released)
    m_keyMap[_keyID] = false;
  }
  void InputManager::SetMouseCoords(float _x, float _y)
  {
    m_mouseCoords.m_x = _x;
    m_mouseCoords.m_y = _y;
  }
  bool InputManager::IsKeyDown(unsigned int _keyID)
  {
    // We dont want to use the associative array approach here
    // because we don't want to create a key if it doesnt exist.
    // So we do it manually
    auto it = m_keyMap.find(_keyID);
    if (it != m_keyMap.end())
    {
      // Found the key
      return it->second;
    }
    else
    {
      // Didn't find the key
      return false;
    }
  }

  bool InputManager::IsKeyPressed(unsigned int _keyID)
  {
    //check if it was pressed this frame, and wasn't pressed last frame
    if (IsKeyDown(_keyID) == true && wasKeyDown(_keyID) == false)
    {
      return true;
    }
    return false;
  }

  bool InputManager::wasKeyDown(unsigned int _keyID)
  {
    // We dont want to use the associative array approach here
    // because we don't want to create a key if it doesnt exist.
    // So we do it manually
    auto it = m_previousKeyMap.find(_keyID);
    if (it != m_previousKeyMap.end())
    {
      // Found the key
      return it->second;
    }
    else
    {
      // Didn't find the key
      return false;
    }
  }
}
