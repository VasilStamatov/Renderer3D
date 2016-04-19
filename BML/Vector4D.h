#ifndef _VECTOR_4_D_H_
#define _VECTOR_4_D_H_

#include "ostream"

namespace BML
{
  class Matrix4x4;
  class Vector3D;
  class Vector2D;

  class Vector4D
  {
  public:
    Vector4D(float _x, float _y, float _z, float _w);
    Vector4D(const Vector4D& _newVec);
    Vector4D(const Vector3D& _newVec, float _w);
    Vector4D(const Vector2D& _newVec, float _z, float _w);

    Vector4D();
    ~Vector4D();

    //gets the magnitude
    float GetMagnitude()  const;

    //gets the squared magnitude (sqrt not applied)
    float GetSquaredMagnitude()  const;

    //normalize the vec
    void Normalize();

    //returns the normalized version of the vec (doesn't change it tho)
    Vector4D Normalized();

    Vector4D operator+(const Vector4D& _addedVec) const;

    void operator+=(const Vector4D& _addedVec);

    Vector4D operator-(const Vector4D& _subtractedVec) const;

    void operator-=(const Vector4D& _subtractedVec);

    Vector4D operator*(float _multipliedScalar) const;

    void operator*=(float _multipliedScalar);

    Vector4D operator/(float _dividedScalar) const;

    void operator/=(float _dividedScalar);

    void operator=(const Vector4D& _Vec);

    Vector4D operator*(const Matrix4x4& _multipliedMat4) const;

    void operator*=(const Matrix4x4& _multipliedMat4);

    bool operator!=(const Vector4D& _comp);

    bool operator==(const Vector4D& _comp);

    friend std::ostream &operator<<(std::ostream &out, const Vector4D& _vec)
    {
      out << "(" << _vec.m_x << ", " << _vec.m_y << ", " << _vec.m_z << ", " << _vec.m_w << ")";
      return out;
    }

    float m_x = 0.0f;
    float m_y = 0.0f;
    float m_z = 0.0f;
    float m_w = 0.0f;
  };
}

#endif