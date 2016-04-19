#ifndef _QUATERNION_H_ 
#define _QUATERNION_H_

#include "ostream"

namespace BML
{
  class Matrix4x4;
  class Vector3D;

  class Quaternion
  {
  public:
    Quaternion();
    Quaternion(float _x, float _y, float _z, float _w);
    Quaternion(const Quaternion& _quat);

    ~Quaternion();
    //Converts to identity quat
    void MakeIdentity();
    //gets the magnitude
    float GetMagnitude() const;
    //converts the quat to the conj of another quat
    void Conjugate(Quaternion _quat);
    //Conjugates the current quat
    void Conjugate();
    //Inverses the quat
    void Inverse();
    //Normalizes the quat
    void Normalize();
    //Gets the matrix representation of the quat
    Matrix4x4 GetMatrix4D();
    //gets the euler angle representation of the quat as a vec3
    Vector3D GetEulerAngles();

    Quaternion operator+(const Quaternion& _addedQuat) const;

    void operator+=(const Quaternion& _addedQuat);

    Quaternion operator-(const Quaternion& _subtractedQuat) const;

    void operator-=(const Quaternion& _subtractedQuat);

    Quaternion operator*(const Quaternion& _multipliedQuat) const;

    void operator*=(const Quaternion& _multipliedQuat);

    Quaternion operator/(float _dividedScalar) const;

    void operator/=(float _dividedScalar);

    Quaternion operator*(float _multipliedScalar) const;

    void operator*=(float _multipliedScalar);

    void operator=(const Quaternion& _quat);

    Quaternion operator/(const Quaternion& _dividedQuat) const;

    void operator/=(const Quaternion& _dividedQuat);

    friend std::ostream &operator<<(std::ostream &out, const Quaternion& _quat)
    {
      out << "(x:" << _quat.m_x << ", y:" << _quat.m_y << ", z:" << _quat.m_z << ", real:" << _quat.m_w << ")";
      return out;
    }

    float m_x = 0.0f;
    float m_y = 0.0f;
    float m_z = 0.0f;
    float m_w = 0.0f;
  };
}
#endif