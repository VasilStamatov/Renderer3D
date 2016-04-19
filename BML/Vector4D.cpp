#include "Vector4D.h"
#include "Vector3D.h"
#include "Vector2D.h"
#include "Matrix4x4.h"
#include "StaticFunctions.h"
#include <math.h>

namespace BML
{
  Vector4D::Vector4D(float _x, float _y, float _z, float _w) : m_x(_x), m_y(_y), m_z(_z), m_w(_w)
  {
    //empty
  }
  Vector4D::Vector4D(const Vector4D& _newVec) : m_x(_newVec.m_x), m_y(_newVec.m_y), m_z(_newVec.m_z), m_w(_newVec.m_w)
  {

  }
  Vector4D::Vector4D(const Vector3D& _newVec, float _w) : m_x(_newVec.m_x), m_y(_newVec.m_y), m_z(_newVec.m_z), m_w(_w)
  {

  }
  Vector4D::Vector4D(const Vector2D& _newVec, float _z, float _w) : m_x(_newVec.m_x), m_y(_newVec.m_y), m_z(_z), m_w(_w)
  {

  }
  Vector4D::Vector4D()
  {
    //empty
  }
  Vector4D::~Vector4D()
  {
  }

  float Vector4D::GetMagnitude() const
  {
    //get the magnitude/norm of the vector
    return sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
  }
  float Vector4D::GetSquaredMagnitude() const
  {
    //get the squared magnitude/norm of the vector
    return (m_x * m_x + m_y * m_y + m_z * m_z);
  }
  void Vector4D::Normalize()
  {
    //Normalize the vector
    float magnitude = GetMagnitude();

    m_x /= magnitude;
    m_y /= magnitude;
    m_z /= magnitude;
    m_w /= magnitude;
  }
  Vector4D Vector4D::Normalized()
  {
    float magnitude = GetMagnitude();
    BML::Vector4D result;
    result.m_x = m_x / magnitude;
    result.m_y = m_y / magnitude;
    result.m_z = m_z / magnitude;
    result.m_w = m_w / magnitude;
    return result;
  }

  //Operator overloading below
  Vector4D Vector4D::operator+(const Vector4D& _addedVec) const
  {
    Vector4D result;
    result.m_x = m_x + _addedVec.m_x;
    result.m_y = m_y + _addedVec.m_y;
    result.m_z = m_z + _addedVec.m_z;
    result.m_w = m_w + _addedVec.m_w;

    return result;
  }

  void Vector4D::operator+=(const Vector4D& _addedVec)
  {
    m_x += _addedVec.m_x;
    m_y += _addedVec.m_y;
    m_z += _addedVec.m_z;
    m_z += _addedVec.m_w;

  }

  Vector4D Vector4D::operator-(const Vector4D& _subtractedVec) const
  {
    Vector4D result;
    result.m_x = m_x - _subtractedVec.m_x;
    result.m_y = m_y - _subtractedVec.m_y;
    result.m_z = m_z - _subtractedVec.m_z;
    result.m_w = m_w - _subtractedVec.m_w;

    return result;
  }

  void Vector4D::operator-=(const Vector4D& _subtractedVec)
  {
    m_x -= _subtractedVec.m_x;
    m_y -= _subtractedVec.m_y;
    m_z -= _subtractedVec.m_z;
    m_w -= _subtractedVec.m_w;
  }

  Vector4D Vector4D::operator*(float _multipliedScalar) const
  {
    Vector4D result;
    result.m_x = m_x * _multipliedScalar;
    result.m_y = m_y * _multipliedScalar;
    result.m_z = m_z * _multipliedScalar;
    result.m_w = m_w * _multipliedScalar;

    return result;
  }

  void Vector4D::operator*=(float _multipliedScalar)
  {
    m_x *= _multipliedScalar;
    m_y *= _multipliedScalar;
    m_z *= _multipliedScalar;
    m_w *= _multipliedScalar;

  }

  Vector4D Vector4D::operator/(float _dividedScalar) const
  {
    Vector4D result;
    result.m_x = m_x / _dividedScalar;
    result.m_y = m_y / _dividedScalar;
    result.m_z = m_z / _dividedScalar;
    result.m_w = m_w / _dividedScalar;

    return result;
  }

  void Vector4D::operator/=(float _dividedScalar)
  {
    m_x /= _dividedScalar;
    m_y /= _dividedScalar;
    m_z /= _dividedScalar;
    m_w /= _dividedScalar;

  }

  void Vector4D::operator=(const Vector4D& _Vec)
  {
    m_x = _Vec.m_x;
    m_y = _Vec.m_y;
    m_z = _Vec.m_z;
    m_w = _Vec.m_w;
  }

  Vector4D Vector4D::operator*(const Matrix4x4& _multipliedMat4) const
  {
    Vector4D result;
    Vector4D matRow1(_multipliedMat4.GetRow(0));
    Vector4D matRow2(_multipliedMat4.GetRow(1));
    Vector4D matRow3(_multipliedMat4.GetRow(2));
    Vector4D matRow4(_multipliedMat4.GetRow(3));

    result.m_x = StaticFunctions::Dot(matRow1, (*this));
    result.m_y = StaticFunctions::Dot(matRow2, (*this));
    result.m_z = StaticFunctions::Dot(matRow3, (*this));
    result.m_w = StaticFunctions::Dot(matRow4, (*this));

    return result;
  }

  void Vector4D::operator*=(const Matrix4x4& _multipliedMat4)
  {
    Vector4D tempVec(*this);

    Vector4D matRow1(_multipliedMat4.GetRow(0));
    Vector4D matRow2(_multipliedMat4.GetRow(1));
    Vector4D matRow3(_multipliedMat4.GetRow(2));
    Vector4D matRow4(_multipliedMat4.GetRow(3));

    m_x = StaticFunctions::Dot(matRow1, tempVec);
    m_y = StaticFunctions::Dot(matRow2, tempVec);
    m_z = StaticFunctions::Dot(matRow3, tempVec);
    m_w = StaticFunctions::Dot(matRow4, tempVec);
  }

  bool Vector4D::operator!=(const Vector4D& _comp)
  {
    if (m_x != _comp.m_x || m_y != _comp.m_y || m_z != _comp.m_z || m_w != m_w)
    {
      return true;
    }
    return false;
  }
  bool Vector4D::operator==(const Vector4D& _comp)
  {
    if (m_x == _comp.m_x && m_y == _comp.m_y && m_z == _comp.m_z && m_w == m_w)
    {
      return true;
    }
    return false;
  }
}
