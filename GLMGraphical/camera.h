#pragma once

#include <BML/Vector3D.h>

class camera
{
public:
  //setters
  void SetPosition(BML::Vector3D _pos)
  {
    m_position = _pos;
  }
  void SetTarget(BML::Vector3D _target)
  {
    m_target = _target;
  }
  //getters
  BML::Vector3D GetPosition()
  {
    return m_position;
  }
  BML::Vector3D GetTarget()
  {
    return m_target;
  }
private:
  BML::Vector3D m_position;
  BML::Vector3D m_target;
};

