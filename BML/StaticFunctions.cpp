#include "StaticFunctions.h"
#include "Vectors.h"
#include "Quaternion.h"
#include <math.h>
#include <limits>

#ifndef PI
#define PI 3.14159265f
#endif

namespace BML
{
  float StaticFunctions::Clamp(float _number, float _min, float _max)
  {
    //clamp
    return fmax(_min, fmin(_number, _max));
  }
  Vector3D StaticFunctions::Cross(const Vector3D& _firstVec, const Vector3D& _secondVec)
  {
    //cross product
    Vector3D result(_firstVec.m_y * _secondVec.m_z - _firstVec.m_z * _secondVec.m_y,
      _firstVec.m_z * _secondVec.m_x - _firstVec.m_x * _secondVec.m_z,
      _firstVec.m_x * _secondVec.m_y - _firstVec.m_y * _secondVec.m_x);
    return result;
  }
  Vector4D StaticFunctions::Cross(const Vector4D& _firstVec, const Vector4D& _secondVec)
  {
    //cross product
    Vector4D result;
    result.m_x = _firstVec.m_y * _secondVec.m_z - _firstVec.m_z * _secondVec.m_y;
    result.m_y = _firstVec.m_z * _secondVec.m_x - _firstVec.m_x * _secondVec.m_z;
    result.m_z = _firstVec.m_x * _secondVec.m_y - _firstVec.m_y * _secondVec.m_x;
    result.m_w = 1.0f;
    return result;
  }

  float StaticFunctions::Dot(const Vector2D& _firstVec, const Vector2D& _secondVec)
  {
    //dot product
    return _firstVec.m_x * _secondVec.m_x + _firstVec.m_y * _secondVec.m_y;
  }
  float StaticFunctions::Dot(const Vector3D& _firstVec, const Vector3D& _secondVec)
  {
    //dot product
    return _firstVec.m_x * _secondVec.m_x + _firstVec.m_y * _secondVec.m_y + _firstVec.m_z * _secondVec.m_z;
  }
  float StaticFunctions::Dot(const Vector4D& _firstVec, const Vector4D& _secondVec)
  {
    //dot product
    return _firstVec.m_x * _secondVec.m_x + _firstVec.m_y * _secondVec.m_y + _firstVec.m_z * _secondVec.m_z + _firstVec.m_w * _secondVec.m_w;
  }
  float StaticFunctions::Dot(const Quaternion& _firstQuat, const Quaternion& _secondQuat)
  {
    //dot product
    return _firstQuat.m_x * _secondQuat.m_x + _firstQuat.m_y * _secondQuat.m_y + _firstQuat.m_z * _secondQuat.m_z + _firstQuat.m_w * _secondQuat.m_w;
  }

  float StaticFunctions::Angle(const Vector2D& _from, const Vector2D& _to)
  {
    //Get the angle between 2 vectors in radians
    //return acos(Dot(_from, _to) / (_from.GetMagnitude() * _to.GetMagnitude()));
    Vector2D vec1 = _from;
    vec1.Normalize();
    Vector2D vec2 = _to;
    vec2.Normalize();
    return acos(Dot(vec1, vec2));
  }
  float StaticFunctions::Angle(const Vector3D& _from, const Vector3D& _to)
  {
    //Get the angle between 2 vectors in radians
    return atan2((Cross(_from, _to)).GetMagnitude(), Dot(_from, _to));
  }
  float StaticFunctions::Angle(const Vector4D& _from, const Vector4D& _to)
  {
    //Get the angle between 2 vectors in radians
    BML::Vector3D v1(_from);
    BML::Vector3D v2(_to);

    return atan2((Cross(v1, v2)).GetMagnitude(), Dot(v1, v2));
  }
  float StaticFunctions::Angle(const Quaternion& _from, const Quaternion& _to)
  {
    //Get the angle between 2 quaternions in radians
    Quaternion inv = _from;
    inv.Inverse();
    Quaternion res = _to * inv;
    float result = acos(res.m_w) * 2.0f;
    return result;
  }

  float StaticFunctions::Lerp(float _start, float _end, float _percent)
  {
    return (_start + ((_end - _start) * Clamp(_percent, 0.0f, 1.0f)));
  }

  Vector2D StaticFunctions::Lerp(const Vector2D& _start, const Vector2D& _end, float _percent)
  {
    //linear interpolation
    return (_start + ((_end - _start) * Clamp(_percent, 0.0f, 1.0f)));
  }
  Vector2D StaticFunctions::SLerp(const Vector2D& _start, const Vector2D& _end, float _percent)
  {
    //spherical linear interpolation
    float dot = Dot(_start, _end);

    dot = Clamp(dot, -1.0f, 1.0f);

    float theta = acos(dot) * _percent;

    Vector2D relativeVec = _end - (_start * dot);

    relativeVec.Normalize();

    return ((_start * cos(theta)) + (relativeVec * sin(theta)));
  }
  Vector2D StaticFunctions::NLerp(const Vector2D& _start, const Vector2D& _end, float _percent)
  {
    //normalized linear interpolation
    Vector2D result = Lerp(_start, _end, Clamp(_percent, 0.0f, 1.0f));
    result.Normalize();
    return result;
  }

  Vector3D StaticFunctions::Lerp(const Vector3D& _start, const Vector3D& _end, float _percent)
  {
    //linear interpolation
    return (_start + ((_end - _start) * Clamp(_percent, 0.0f, 1.0f)));
  }
  Vector3D StaticFunctions::SLerp(const Vector3D& _start, const Vector3D& _end, float _percent)
  {
    //spherical linear interpolation
    float dot = Dot(_start, _end);

    dot = Clamp(dot, -1.0f, 1.0f);

    float theta = acos(dot) * _percent;

    Vector3D relativeVec = _end - (_start * dot);

    relativeVec.Normalize();

    return ((_start * cos(theta)) + (relativeVec * sin(theta)));
  }
  Vector3D StaticFunctions::NLerp(const Vector3D& _start, const Vector3D& _end, float _percent)
  {
    //normalized linear interpolation
    Vector3D result = Lerp(_start, _end, Clamp(_percent, 0.0f, 1.0f));
    result.Normalize();
    return result;
  }

  Vector4D StaticFunctions::Lerp(const Vector4D& _start, const Vector4D& _end, float _percent)
  {
    //linear interpolation
    return (_start + ((_end - _start) * Clamp(_percent, 0.0f, 1.0f)));
  }
  Vector4D StaticFunctions::SLerp(const Vector4D& _start, const Vector4D& _end, float _percent)
  {
    //spherical linear interpolation
    float dot = Dot(_start, _end);

    dot = Clamp(dot, -1.0f, 1.0f);

    float theta = acos(dot) * _percent;

    Vector4D relativeVec = _end - (_start * dot);

    relativeVec.Normalize();

    return ((_start * cos(theta)) + (relativeVec * sin(theta)));
  }
  Vector4D StaticFunctions::NLerp(const Vector4D& _start, const Vector4D& _end, float _percent)
  {
    //normalized linear interpolation
    Vector4D result = Lerp(_start, _end, Clamp(_percent, 0.0f, 1.0f));
    result.Normalize();
    return result;
  }
  float StaticFunctions::Distance(const Vector2D& _start, const Vector2D& _end)
  {
    //Get the distance (magnitude) between 2 vectors
    return (_end - _start).GetMagnitude();
  }
  float StaticFunctions::Distance(const Vector3D& _start, const Vector3D& _end)
  {
    //Get the distance (magnitude) between 2 vectors
    return (_end - _start).GetMagnitude();
  }
  float StaticFunctions::Distance(const Vector4D& _start, const Vector4D& _end)
  {
    //Get the distance (magnitude) between 2 vectors
    return (_end - _start).GetMagnitude();
  }
  Quaternion StaticFunctions::Euler(float _x, float _y, float _z)
  {
    //convert euler angle representation to a quaternion
    Quaternion result;
    float epsilon = std::numeric_limits<float>::epsilon();

    float cos1 = (abs((float)cos((_y * PI / 180.0) / 2.0f)) <= epsilon) ? 0.0f : (float)cos((_y * PI / 180.0f) / 2.0f);
    float sin1 = (abs((float)sin((_y * PI / 180.0) / 2.0f)) <= epsilon) ? 0.0f : (float)sin((_y * PI / 180.0f) / 2.0f);
    float cos2 = (abs((float)cos((_z * PI / 180.0) / 2.0f)) <= epsilon) ? 0.0f : (float)cos((_z * PI / 180.0f) / 2.0f);
    float sin2 = (abs((float)sin((_z * PI / 180.0) / 2.0f)) <= epsilon) ? 0.0f : (float)sin((_z * PI / 180.0f) / 2.0f);
    float cos3 = (abs((float)cos((_x * PI / 180.0) / 2.0f)) <= epsilon) ? 0.0f : (float)cos((_x * PI / 180.0f) / 2.0f);
    float sin3 = (abs((float)sin((_x * PI / 180.0) / 2.0f)) <= epsilon) ? 0.0f : (float)sin((_x * PI / 180.0f) / 2.0f);
    float cos1cos2 = cos1 * cos2;
    float sin1sin2 = sin1 * sin2;

    result.m_w = (abs(cos1cos2 * cos3 - sin1sin2 * sin3) <= epsilon) ? 0.0f : cos1cos2 * cos3 - sin1sin2 * sin3;
    result.m_x = (abs(cos1cos2 * sin3 + sin1sin2 * cos3) <= epsilon) ? 0.0f : cos1cos2 * sin3 + sin1sin2 * cos3;
    result.m_y = (abs(sin1 * cos2 * cos3 + cos1 * sin2 * sin3) <= epsilon) ? 0.0f : sin1 * cos2 * cos3 + cos1 * sin2 * sin3;
    result.m_z = (abs(cos1 * sin2 * cos3 - sin1 * cos2 * sin3) <= epsilon) ? 0.0f : cos1 * sin2 * cos3 - sin1 * cos2 * sin3;

    return result;
  }
  Quaternion StaticFunctions::Euler(const Vector3D& _eulerAngles)
  {
    //convert euler angle representation to a quaternion
    Quaternion result;
    float epsilon = std::numeric_limits<float>::epsilon();

    float cos1 = (abs((float)cos((_eulerAngles.m_y * PI / 180.0) / 2.0f)) <= epsilon) ? 0.0f : (float)cos((_eulerAngles.m_y * PI / 180.0f) / 2.0f);
    float sin1 = (abs((float)sin((_eulerAngles.m_y * PI / 180.0) / 2.0f)) <= epsilon) ? 0.0f : (float)sin((_eulerAngles.m_y * PI / 180.0f) / 2.0f);
    float cos2 = (abs((float)cos((_eulerAngles.m_z * PI / 180.0) / 2.0f)) <= epsilon) ? 0.0f : (float)cos((_eulerAngles.m_z * PI / 180.0f) / 2.0f);
    float sin2 = (abs((float)sin((_eulerAngles.m_z * PI / 180.0) / 2.0f)) <= epsilon) ? 0.0f : (float)sin((_eulerAngles.m_z * PI / 180.0f) / 2.0f);
    float cos3 = (abs((float)cos((_eulerAngles.m_x * PI / 180.0) / 2.0f)) <= epsilon) ? 0.0f : (float)cos((_eulerAngles.m_x * PI / 180.0f) / 2.0f);
    float sin3 = (abs((float)sin((_eulerAngles.m_x * PI / 180.0) / 2.0f)) <= epsilon) ? 0.0f : (float)sin((_eulerAngles.m_x * PI / 180.0f) / 2.0f);
    float cos1cos2 = cos1 * cos2;
    float sin1sin2 = sin1 * sin2;

    result.m_w = (abs(cos1cos2 * cos3 - sin1sin2 * sin3) <= epsilon) ? 0.0f : cos1cos2 * cos3 - sin1sin2 * sin3;
    result.m_x = (abs(cos1cos2 * sin3 + sin1sin2 * cos3) <= epsilon) ? 0.0f : cos1cos2 * sin3 + sin1sin2 * cos3;
    result.m_y = (abs(sin1 * cos2 * cos3 + cos1 * sin2 * sin3) <= epsilon) ? 0.0f : sin1 * cos2 * cos3 + cos1 * sin2 * sin3;
    result.m_z = (abs(cos1 * sin2 * cos3 - sin1 * cos2 * sin3) <= epsilon) ? 0.0f : cos1 * sin2 * cos3 - sin1 * cos2 * sin3;

    return result;
  }
  Vector3D StaticFunctions::Reflect(const Vector3D v1, const Vector3D v2)
  {
    Vector3D result;
    float p = 2.0f * Dot(v1, v2);
    result.m_x = v1.m_x - p * v2.m_x;
    result.m_y = v1.m_y - p * v2.m_y;
    result.m_z = v1.m_z - p * v2.m_z;
    return result;
  }
  Vector4D StaticFunctions::Reflect(const Vector4D v1, const Vector4D v2)
  {
    Vector4D result;
    float p = 2.0f * Dot(v1, v2);
    result.m_x = v1.m_x - p * v2.m_x;
    result.m_y = v1.m_y - p * v2.m_y;
    result.m_z = v1.m_z - p * v2.m_z;
    result.m_w = v1.m_w - p * v2.m_w;
    return result;
  }

  //returns the surface normal of 3 points ( a triangle)
  Vector3D StaticFunctions::GetSurfaceNormals(const Vector3D& _v1, const Vector3D& _v2, const Vector3D& _v3)
  {
    Vector3D polyVector1 = { _v2 - _v1 };
    Vector3D polyVector2 = { _v3 - _v1 };

    Vector3D cross = StaticFunctions::Cross(polyVector1, polyVector2);

    cross.Normalize();

    return cross;
  }
}