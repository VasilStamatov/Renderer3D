#include "Vector3D.h"
#include "Vector4D.h"
#include <math.h>
#include <limits>

#ifndef PI
#define PI 3.14159265f
#endif

namespace BML
{
  Vector3D::Vector3D(float _x, float _y, float _z) : m_x(_x), m_y(_y), m_z(_z)
  {
    //empty
  }
  Vector3D::Vector3D(const Vector3D& _newVec) : m_x(_newVec.m_x), m_y(_newVec.m_y), m_z(_newVec.m_z)
  {

  }
  Vector3D::Vector3D(const Vector4D& _newVec) : m_x(_newVec.m_x), m_y(_newVec.m_y), m_z(_newVec.m_z)
  {

  }
  Vector3D::Vector3D()
  {
    //empty
  }
  Vector3D::~Vector3D()
  {
  }

  void Vector3D::Scale(float _xScale, float _yScale, float _zScale)
  {
    //scale the vector
    if (_xScale != 0.0f)
    {
      m_x *= _xScale;
    }
    if (_yScale != 0.0f)
    {
      m_y *= _yScale;
    }
    if (_zScale != 0.0f)
    {
      m_z *= _zScale;
    }
  }

  void Vector3D::Translate(float _xTrans, float _yTrans, float _zTrans)
  {
    //translate the vector
    m_x += _xTrans;
    m_y += _yTrans;
    m_z += _zTrans;
  }

  Vector3D Vector3D::RotateAboutX(float _angle)
  {
    //rotate the vector about the x axis
    float epsilon = std::numeric_limits<float>::epsilon();
    float cosAngle = (abs((float)cos(_angle * PI / 180.0)) < epsilon) ? 0.0f : (float)cos(_angle * PI / 180.0);
    float sinAngle = (abs((float)sin(_angle * PI / 180.0)) < epsilon) ? 0.0f : (float)sin(_angle * PI / 180.0);
    Vector3D result;

    result.m_y = m_y * cosAngle - m_z * sinAngle;
    result.m_z = m_y * sinAngle + m_z * cosAngle;

    return result;
  }
  Vector3D Vector3D::RotateAboutY(float _angle)
  {
    //rotate the vector about the Y axis
    float epsilon = std::numeric_limits<float>::epsilon();
    float cosAngle = (abs((float)cos(_angle * PI / 180.0)) < epsilon) ? 0.0f : (float)cos(_angle * PI / 180.0);
    float sinAngle = (abs((float)sin(_angle * PI / 180.0)) < epsilon) ? 0.0f : (float)sin(_angle * PI / 180.0);
    Vector3D result;

    result.m_x = m_x * cosAngle + m_z * sinAngle;
    result.m_z = -m_x * sinAngle + m_z * cosAngle;
    return result;
  }
  Vector3D Vector3D::RotateAboutZ(float _angle)
  {
    //rotate the vector about the Z axis
    float epsilon = std::numeric_limits<float>::epsilon();
    float cosAngle = (abs((float)cos(_angle * PI / 180.0)) < epsilon) ? 0.0f : (float)cos(_angle * PI / 180.0);
    float sinAngle = (abs((float)sin(_angle * PI / 180.0)) < epsilon) ? 0.0f : (float)sin(_angle * PI / 180.0);
    Vector3D result;

    result.m_x = m_x * cosAngle - m_y * sinAngle;
    result.m_y = m_x * sinAngle + m_y * cosAngle;
    return result;
  }

  float Vector3D::GetMagnitude() const
  {
    //get the magnitude/norm of the vector
    return sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
  }
  float Vector3D::GetSquaredMagnitude() const
  {
    //get the squared magnitude/norm of the vector
    return (m_x * m_x + m_y * m_y + m_z * m_z);
  }
  void Vector3D::Normalize()
  {
    //normalize the vector
    float magnitude = GetMagnitude();

    *this /= magnitude;
  }

  Vector3D Vector3D::Normalized()
  {
    float magnitude = GetMagnitude();
    BML::Vector3D result;
    result.m_x = m_x / magnitude;
    result.m_y = m_y / magnitude;
    result.m_z = m_z / magnitude;
    return result;
  }
  
  //operator overloading below
  Vector3D Vector3D::operator+(const Vector3D& _addedVec) const
  {
    Vector3D result;
    result.m_x = m_x + _addedVec.m_x;
    result.m_y = m_y + _addedVec.m_y;
    result.m_z = m_z + _addedVec.m_z;
    return result;
  }

  void Vector3D::operator+=(const Vector3D& _addedVec)
  {
    m_x += _addedVec.m_x;
    m_y += _addedVec.m_y;
    m_z += _addedVec.m_z;
  }

  Vector3D Vector3D::operator-(const Vector3D& _subtractedVec) const
  {
    Vector3D result;
    result.m_x = m_x - _subtractedVec.m_x;
    result.m_y = m_y - _subtractedVec.m_y;
    result.m_z = m_z - _subtractedVec.m_z;
    return result;
  }

  void Vector3D::operator-=(const Vector3D& _subtractedVec)
  {
    m_x -= _subtractedVec.m_x;
    m_y -= _subtractedVec.m_y;
    m_z -= _subtractedVec.m_z;
  }

  Vector3D Vector3D::operator*(float _multipliedScalar) const
  {
    Vector3D result;
    result.m_x = m_x * _multipliedScalar;
    result.m_y = m_y * _multipliedScalar;
    result.m_z = m_z * _multipliedScalar;
    return result;
  }

  void Vector3D::operator*=(float _multipliedScalar)
  {
    m_x *= _multipliedScalar;
    m_y *= _multipliedScalar;
    m_z *= _multipliedScalar;
  }

  Vector3D Vector3D::operator/(float _dividedScalar) const
  {
    Vector3D result;
    result.m_x = m_x / _dividedScalar;
    result.m_y = m_y / _dividedScalar;
    result.m_z = m_z / _dividedScalar;
    return result;
  }

  void Vector3D::operator/=(float _dividedScalar)
  {
    m_x /= _dividedScalar;
    m_y /= _dividedScalar;
    m_z /= _dividedScalar;
  }

  void Vector3D::operator=(const Vector3D& _Vec)
  {
    m_x = _Vec.m_x;
    m_y = _Vec.m_y;
    m_z = _Vec.m_z;
  }
  bool Vector3D::operator!=(const Vector3D& _comp)
  {
    if (m_x != _comp.m_x || m_y != _comp.m_y || m_z != _comp.m_z)
    {
      return true;
    }
    return false;
  }
  bool Vector3D::operator==(const Vector3D& _comp)
  {
    if (m_x == _comp.m_x && m_y == _comp.m_y && m_z == _comp.m_z)
    {
      return true;
    }
    return false;
  }

}