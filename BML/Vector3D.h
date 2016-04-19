#ifndef _VECTOR_3_D_H_
#define _VECTOR_3_D_H_

#include "ostream"

namespace BML
{
  class Vector4D;

  class Vector3D
  {
  public:
    Vector3D(float _x, float _y, float _z);
    Vector3D(const Vector3D& _newVec);
    Vector3D(const Vector4D& _newVec);

    Vector3D();
    ~Vector3D();

    //scale the vector (basically scalar multiplication, but you can add different values for each component x,y,z)
    void Scale(float _xScale, float _yScale, float _zScale);

    //translate the vector with scalar values rather than using the overload operator of vec+vec
    void Translate(float _xTrans, float _yTrans, float _zTrans);

    //rotate about the x axis
    Vector3D RotateAboutX(float _angle);
    //rotate about the y axis
    Vector3D RotateAboutY(float _angle);
    //rotate about the z axis
    Vector3D RotateAboutZ(float _angle);

    //gets the magnitude
    float GetMagnitude() const;

    //gets the squared magnitude (sqrt not applied)
    float GetSquaredMagnitude() const;

    //normalize the vector
    void Normalize();

    //returns the normalized version of the vec (doesn't change it tho)
    Vector3D Normalized();


    Vector3D operator+(const Vector3D& _addedVec) const;

    void operator+=(const Vector3D& _addedVec);

    Vector3D operator-(const Vector3D& _subtractedVec) const;

    void operator-=(const Vector3D& _subtractedVec);

    Vector3D operator*(float _multipliedScalar) const;

    void operator*=(float _multipliedScalar);

    Vector3D operator/(float _dividedScalar) const;

    void operator/=(float _dividedScalar);

    void operator=(const Vector3D& _Vec);

    bool operator!=(const Vector3D& _comp);

    bool operator==(const Vector3D& _comp);

    friend std::ostream &operator<<(std::ostream &out, const Vector3D& _vec)
    {
      out << "(" << _vec.m_x << ", " << _vec.m_y << ", " << _vec.m_z << ")";
      return out;
    }

    float m_x = 0.0f;
    float m_y = 0.0f;
    float m_z = 0.0f;
  };
}

#endif