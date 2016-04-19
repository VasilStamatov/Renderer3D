#include "Vector2D.h"
#include <cmath>
#include <limits>

#ifndef PI
#define PI 3.14159265f
#endif

namespace BML
{
  Vector2D::Vector2D(float _x, float _y) : m_x(_x), m_y(_y)
  {
    //empty
  }
  Vector2D::Vector2D(const Vector2D& _newVec) : m_x(_newVec.m_x), m_y(_newVec.m_y)
  {
  }
  Vector2D::Vector2D()
  {
    //empty
  }
  Vector2D::~Vector2D()
  {
  }
  void Vector2D::Scale(float _xScale, float _yScale)
  {
    //scale the vector
    //make sure it doesnt multiply by 0
    if (_xScale != 0.0f)
    {
      m_x *= _xScale;
    }
    if (_yScale != 0.0f)
    {
      m_y *= _yScale;
    }
  }
  void Vector2D::Translate(float _xTranslation, float _yTranslation)
  {
    //translate the vector
    m_x += _xTranslation;
    m_y += _yTranslation;
  }
  Vector2D Vector2D::Rotate(float _angle)
  {
    //rotate the vector
    float epsilon = std::numeric_limits<float>::epsilon();
    Vector2D result;
    float cosAngle = (abs((float)cos(_angle * PI / 180.0)) < epsilon) ? 0.0f : (float)cos(_angle * PI / 180.0);
    float sinAngle = (abs((float)sin(_angle * PI / 180.0)) < epsilon) ? 0.0f : (float)sin(_angle * PI / 180.0);

    result.m_x = m_x * cosAngle - m_y * sinAngle;
    result.m_y = m_x * sinAngle + m_y * cosAngle;

    return result;
  }
  float Vector2D::GetMagnitude() const
  {
    //get the magnitude/norm of the vector
    return sqrt(m_x * m_x + m_y * m_y);
  }
  float Vector2D::GetSquaredMagnitude() const
  {
    //get the squared magnitude/norm of the vector
    return (m_x * m_x + m_y * m_y);
  }
  void Vector2D::Normalize()
  {
    //normalize the vector
    float magnitude = GetMagnitude();

    *this /= magnitude;
  }
  Vector2D Vector2D::Normalized()
  {
    float magnitude = GetMagnitude();
    BML::Vector2D result;
    result.m_x = m_x / magnitude;
    result.m_y = m_y / magnitude;
    return result;
  }
  //operator overloading below
  Vector2D Vector2D::operator+(const Vector2D& _addedVec) const
  {
    Vector2D result;
    result.m_x = m_x + _addedVec.m_x;
    result.m_y = m_y + _addedVec.m_y;
    return result;
  }

  void Vector2D::operator+=(const Vector2D& _addedVec)
  {
    m_x += _addedVec.m_x;
    m_y += _addedVec.m_y;
  }

  Vector2D Vector2D::operator-(const Vector2D& _subtractedVec) const
  {
    Vector2D result;
    result.m_x = m_x - _subtractedVec.m_x;
    result.m_y = m_y - _subtractedVec.m_y;
    return result;
  }

  void Vector2D::operator-=(const Vector2D& _subtractedVec)
  {
    m_x -= _subtractedVec.m_x;
    m_y -= _subtractedVec.m_y;
  }

  Vector2D Vector2D::operator*(float _multipliedScalar) const
  {
    Vector2D result;
    result.m_x = m_x * _multipliedScalar;
    result.m_y = m_y * _multipliedScalar;
    return result;
  }

  void Vector2D::operator*=(float _multipliedScalar)
  {
    m_x *= _multipliedScalar;
    m_y *= _multipliedScalar;
  }

  Vector2D Vector2D::operator/(float _dividedScalar) const
  {
    Vector2D result;
    result.m_x = m_x / _dividedScalar;
    result.m_y = m_y / _dividedScalar;
    return result;
  }

  void Vector2D::operator/=(float _dividedScalar)
  {
    m_x /= _dividedScalar;
    m_y /= _dividedScalar;
  }

  void Vector2D::operator=(const Vector2D& _Vec)
  {
    m_x = _Vec.m_x;
    m_y = _Vec.m_y;
  }
  bool Vector2D::operator!=(const Vector2D& _comp)
  {
    if (m_x != _comp.m_x || m_y != _comp.m_y)
    {
      return true;
    }
    return false;
  }
  bool Vector2D::operator==(const Vector2D& _comp)
  {
    if (m_x == _comp.m_x && m_y == _comp.m_y)
    {
      return true;
    }
    return false;
  }
}
