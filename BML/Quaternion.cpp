#include "Quaternion.h"
#include "Matrix4x4.h"
#include "Vector3D.h"

#include <math.h>
#include <numeric>

#ifndef PI
#define PI 3.14159265f
#endif

namespace BML
{
  Quaternion::Quaternion()
  {
    MakeIdentity();
  }

  Quaternion::Quaternion(float _x, float _y, float _z, float _w) : m_x(_x), m_y(_y), m_z(_z), m_w(_w)
  {
  }
  Quaternion::Quaternion(const Quaternion& _quat) : m_x(_quat.m_x), m_y(_quat.m_y), m_z(_quat.m_z), m_w(_quat.m_w)
  {
  }
  Quaternion::~Quaternion()
  {
  }

  void Quaternion::MakeIdentity()
  {
    //makes the quaternion an identity quat
    m_x = m_y = m_z = 0.0f;
    m_w = 1.0f;
  }
  float Quaternion::GetMagnitude() const
  {
    //gets the magnitude/norm of the quat
    return sqrtf(m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w);
  }
  void Quaternion::Conjugate(Quaternion _quat)
  {
    //this quat object becomes the conjugate of some other quat
    m_x = -_quat.m_x;
    m_y = -_quat.m_y;
    m_z = -_quat.m_z;
    m_w = _quat.m_w;
  }
  void Quaternion::Conjugate()
  {
    //the quat conjugates itself
    m_x *= -1.0f;
    m_y *= -1.0f;
    m_z *= -1.0f;
  }
  void Quaternion::Inverse()
  {
    //Inverse the quat
    Quaternion conj = *this;
    conj.Conjugate();
    *this = conj / powf(GetMagnitude(), 2.0f);
  }
  void Quaternion::Normalize()
  {
    //Normalize the quat
    float magnitude = GetMagnitude();
    m_x /= magnitude;
    m_y /= magnitude;
    m_z /= magnitude;
    m_w /= magnitude;
  }

  Matrix4x4 Quaternion::GetMatrix4D()
  {
    //Return the matrix representation of the quat
    Matrix4x4 result;

    float ww = m_w*m_w;
    float xx = m_x*m_x;
    float yy = m_y*m_y;
    float zz = m_z*m_z;

    /*Result[0][0] = 1 - 2 * (qyy + qzz);
    Result[0][1] = 2 * (qxy + qwz);
    Result[0][2] = 2 * (qxz - qwy);

    Result[1][0] = 2 * (qxy - qwz);
    Result[1][1] = 1 - 2 * (qxx + qzz);
    Result[1][2] = 2 * (qyz + qwx);

    Result[2][0] = 2 * (qxz + qwy);
    Result[2][1] = 2 * (qyz - qwx);
    Result[2][2] = 1 - 2 * (qxx + qyy);*/

    // invs (inverse square length) is only required if quaternion is not already normalised
    if (GetMagnitude() != 1.0f)
    {
      float invs = 1.0f / (xx + yy + zz + ww);
      result.m_matrix[0][0] = (xx - yy - zz + ww) * invs; // since ww + xx + yy + zz =1/invs*invs
      result.m_matrix[1][1] = (-xx + yy - zz + ww) * invs;
      result.m_matrix[2][2] = (-xx - yy + zz + ww) * invs;

      float tmp1 = m_x * m_y;
      float tmp2 = m_z * m_w;
      result.m_matrix[1][0] = 2.0f * (tmp1 + tmp2) * invs;
      result.m_matrix[0][1] = 2.0f * (tmp1 - tmp2) * invs;

      tmp1 = m_x * m_z;
      tmp2 = m_y * m_w;
      result.m_matrix[2][0] = 2.0f * (tmp1 - tmp2) * invs;
      result.m_matrix[0][2] = 2.0f * (tmp1 + tmp2) * invs;
      tmp1 = m_y * m_z;
      tmp2 = m_x * m_w;
      result.m_matrix[2][1] = 2.0f * (tmp1 + tmp2) * invs;
      result.m_matrix[1][2] = 2.0f * (tmp1 - tmp2) * invs;
      result.m_matrix[3][3] = 1.0f;
    }
    else
    {
      result.m_matrix[0][0] = (xx - yy - zz + ww);
      result.m_matrix[1][1] = (-xx + yy - zz + ww);
      result.m_matrix[2][2] = (-xx - yy + zz + ww);

      float tmp1 = m_x * m_y;
      float tmp2 = m_z * m_w;
      result.m_matrix[1][0] = 2.0f * (tmp1 + tmp2);
      result.m_matrix[0][1] = 2.0f * (tmp1 - tmp2);

      tmp1 = m_x * m_z;
      tmp2 = m_y * m_w;
      result.m_matrix[2][0] = 2.0f * (tmp1 - tmp2);
      result.m_matrix[0][2] = 2.0f * (tmp1 + tmp2);
      tmp1 = m_y * m_z;
      tmp2 = m_x * m_w;
      result.m_matrix[2][1] = 2.0f * (tmp1 + tmp2);
      result.m_matrix[1][2] = 2.0f * (tmp1 - tmp2);
      result.m_matrix[3][3] = 1.0f;
    }
    return result;
  }
  Vector3D Quaternion::GetEulerAngles()
  {
    //returns a vector3d representing the rotations in the x, y and z coordinates in radians
    Vector3D result;
    float ww = m_w * m_w;
    float xx = m_x * m_x;
    float yy = m_y * m_y;
    float zz = m_z * m_z;

    float unit = xx + yy + zz + ww; // if normalised is one, otherwise is correction factor

    float test = m_w * m_y + m_z * m_w;

    if (test > 0.499f * unit) 
    {
      // singularity at north pole
      result.m_y = 2.0f * atan2(m_x, m_w);
      result.m_z = (float)PI / 2.0f;
      result.m_x = 0.0f;
      return result;
    }
    if (test < -0.499f * unit) 
    {
      // singularity at south pole
      result.m_y = -2.0f * atan2(m_x, m_w);
      result.m_z = (float)-PI / 2.0f;
      result.m_x = 0.0f;
      return result;
    }
    result.m_y = atan2(2.0f * m_y * m_w - 2 * m_x * m_z, xx - yy - zz + ww);
    result.m_z = asin(2.0f * test / unit);
    result.m_x = atan2(2.0f * m_x * m_w - 2 * m_y * m_z, -xx + yy - zz + ww);
    return result;
  }
  Quaternion Quaternion::operator+(const Quaternion& _addedQuat) const
  {
    //addition overload
    Quaternion result;

    result.m_x = m_x + _addedQuat.m_x;
    result.m_y = m_y + _addedQuat.m_y;
    result.m_z = m_z + _addedQuat.m_z;
    result.m_w = m_w + _addedQuat.m_w;

    return result;
  }

  void Quaternion::operator+=(const Quaternion& _addedQuat)
  {
    //addition overload
    m_x += _addedQuat.m_x;
    m_y += _addedQuat.m_y;
    m_z += _addedQuat.m_z;
    m_w += _addedQuat.m_w;
  }

  Quaternion Quaternion::operator-(const Quaternion& _subtractedQuat) const
  {
    float epsilon = std::numeric_limits<float>::epsilon();
    //subtraction overload
    Quaternion result;

    result.m_x = (abs(m_x - _subtractedQuat.m_x) < epsilon) ? 0.0f : m_x - _subtractedQuat.m_x;
    result.m_y = (abs(m_y - _subtractedQuat.m_y) < epsilon) ? 0.0f : m_y - _subtractedQuat.m_y;
    result.m_z = (abs(m_z - _subtractedQuat.m_z) < epsilon) ? 0.0f : m_z - _subtractedQuat.m_z;
    result.m_w = (abs(m_w - _subtractedQuat.m_w) < epsilon) ? 0.0f : m_w - _subtractedQuat.m_w;

    return result;
  }

  void Quaternion::operator-=(const Quaternion& _subtractedQuat)
  {
    float epsilon = std::numeric_limits<float>::epsilon();
    //subtraction overload
    m_x = (abs(m_x - _subtractedQuat.m_x) < epsilon) ? 0.0f : m_x - _subtractedQuat.m_x;
    m_y = (abs(m_y - _subtractedQuat.m_y) < epsilon) ? 0.0f : m_y - _subtractedQuat.m_y;
    m_z = (abs(m_z - _subtractedQuat.m_z) < epsilon) ? 0.0f : m_z - _subtractedQuat.m_z;
    m_w = (abs(m_w - _subtractedQuat.m_w) < epsilon) ? 0.0f : m_w - _subtractedQuat.m_w;
  }

  Quaternion Quaternion::operator*(const Quaternion& _multipliedQuat) const
  {
    //mult overload
    Quaternion result;
    result.m_x = m_x * _multipliedQuat.m_w + m_y * _multipliedQuat.m_z - m_z * _multipliedQuat.m_y + m_w * _multipliedQuat.m_x;
    result.m_y = -m_x * _multipliedQuat.m_z + m_y * _multipliedQuat.m_w + m_z * _multipliedQuat.m_x + m_w * _multipliedQuat.m_y;
    result.m_z = m_x * _multipliedQuat.m_y - m_y * _multipliedQuat.m_x + m_z * _multipliedQuat.m_w + m_w * _multipliedQuat.m_z;
    result.m_w = -m_x * _multipliedQuat.m_x - m_y * _multipliedQuat.m_y - m_z * _multipliedQuat.m_z + m_w * _multipliedQuat.m_w;

    return result;
  }

  void Quaternion::operator*=(const Quaternion& _multipliedQuat)
  {
    //mult overload
    //need to use a temp quat so I don't change any of this ones values while calculating (to not ruin the calculations for the rest of the elements)
    Quaternion tempQuat(*this);

    m_x = tempQuat.m_x * _multipliedQuat.m_w + tempQuat.m_y * _multipliedQuat.m_z - tempQuat.m_z * _multipliedQuat.m_y + tempQuat.m_w * _multipliedQuat.m_x;
    m_y = -tempQuat.m_x * _multipliedQuat.m_z + tempQuat.m_y * _multipliedQuat.m_w + tempQuat.m_z * _multipliedQuat.m_x + tempQuat.m_w * _multipliedQuat.m_y;
    m_z = tempQuat.m_x * _multipliedQuat.m_y - tempQuat.m_y * _multipliedQuat.m_x + tempQuat.m_z * _multipliedQuat.m_w + tempQuat.m_w * _multipliedQuat.m_z;
    m_w = -tempQuat.m_x * _multipliedQuat.m_x - tempQuat.m_y * _multipliedQuat.m_y - tempQuat.m_z * _multipliedQuat.m_z + tempQuat.m_w * _multipliedQuat.m_w;
  }

  Quaternion Quaternion::operator/(float _dividedScalar) const
  {
    //division overload
    Quaternion result;

    result.m_x = m_x / _dividedScalar;
    result.m_y = m_y / _dividedScalar;
    result.m_z = m_z / _dividedScalar;
    result.m_w = m_w / _dividedScalar;

    return result;

  }

  void Quaternion::operator/=(float _dividedScalar)
  {
    //division overload
    m_x /= _dividedScalar;
    m_y /= _dividedScalar;
    m_z /= _dividedScalar;
    m_w /= _dividedScalar;
  }

  Quaternion Quaternion::operator*(float _multipliedScalar) const
  {
    //mult overload
    Quaternion result;
    result.m_x = m_x * _multipliedScalar;
    result.m_y = m_y * _multipliedScalar;
    result.m_z = m_z * _multipliedScalar;
    result.m_w = m_w * _multipliedScalar;
    return result;
  }

  void Quaternion::operator*=(float _multipliedScalar)
  {
    //mult overload
    m_x *= _multipliedScalar;
    m_y *= _multipliedScalar;
    m_z *= _multipliedScalar;
    m_w *= _multipliedScalar;
  }

  void Quaternion::operator=(const Quaternion& _quat)
  {
    //assignment overload
    m_x = _quat.m_x;
    m_y = _quat.m_y;
    m_z = _quat.m_z;
    m_w = _quat.m_w;
  }

  Quaternion Quaternion::operator/(const Quaternion& _dividedQuat) const
  {
    //division overload
    Quaternion result;
    if (_dividedQuat.GetMagnitude() == 1.0f)
    {
      Quaternion conj = _dividedQuat;
      conj.Conjugate();
      result = (*this) * conj;
    }
    else
    {
      Quaternion conj = _dividedQuat;
      conj.Conjugate();
      conj /= (_dividedQuat.GetMagnitude() * _dividedQuat.GetMagnitude());
      result = (*this) * conj;
    }
    return result;
  }

  void Quaternion::operator/=(const Quaternion& _dividedQuat)
  {
    if (_dividedQuat.GetMagnitude() == 1.0f)
    {
      Quaternion conj = _dividedQuat;
      conj.Conjugate();
      *this *= conj;
    }
    else
    {
      Quaternion conj = _dividedQuat;
      conj.Conjugate();
      conj /= (_dividedQuat.GetMagnitude() * _dividedQuat.GetMagnitude());
      *this *= conj;
    }
  }
}