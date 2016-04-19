#ifndef STATIC_FUNCTIONS_H_
#define STATIC_FUNCTIONS_H_

namespace BML
{
  class Vector2D;
  class Vector3D;
  class Vector4D;
  class Quaternion;

  class StaticFunctions
  {
  public:
    //Clamp
    static float Clamp(float _number, float _min, float _max);

    //Returns the cross product of 2 vectors
    static Vector3D Cross(const Vector3D& _firstVec, const Vector3D& _secondVec);
    static Vector4D Cross(const Vector4D& _firstVec, const Vector4D& _secondVec);

    //returns the dot product of 2 vectors
    static float Dot(const Vector2D& _firstVec, const Vector2D& _secondVec);
    static float Dot(const Vector3D& _firstVec, const Vector3D& _secondVec);
    static float Dot(const Vector4D& _firstVec, const Vector4D& _secondVec);
    //returns the dot product of 2 quats
    static float Dot(const Quaternion& _firstQuat, const Quaternion& _secondQuat);

    //Returns the angle between 2 vectors
    static float Angle(const Vector2D& _from, const Vector2D& _to);
    static float Angle(const Vector3D& _from, const Vector3D& _to);
    static float Angle(const Vector4D& _from, const Vector4D& _to);
    //Returns the angle between 2 quats
    static float Angle(const Quaternion& _from, const Quaternion& _to);

    //floating point number lerp
    static float Lerp(float _start, float _end, float _percent);

    //2D linear interpolation
    static Vector2D Lerp(const Vector2D& _start, const Vector2D& _end, float _percent);
    //2D spherical linear interpolation
    static Vector2D SLerp(const Vector2D& _start, const Vector2D& _end, float _percent);
    //2D normalized linear interpolation
    static Vector2D NLerp(const Vector2D& _start, const Vector2D& _end, float _percent);

    //3D linear interpolation
    static Vector3D Lerp(const Vector3D& _start, const Vector3D& _end, float _percent);
    //3D spherical linear interpolation
    static Vector3D SLerp(const Vector3D& _start, const Vector3D& _end, float _percent);
    //3D normalized linear interpolation
    static Vector3D NLerp(const Vector3D& _start, const Vector3D& _end, float _percent);

    //4D linear interpolation
    static Vector4D Lerp(const Vector4D& _start, const Vector4D& _end, float _percent);
    //4D spherical linear interpolation
    static Vector4D SLerp(const Vector4D& _start, const Vector4D& _end, float _percent);
    //4D normalized linear interpolation
    static Vector4D NLerp(const Vector4D& _start, const Vector4D& _end, float _percent);

    //Gets the distance between 2 vectors
    static float Distance(const Vector2D& _start, const Vector2D& _end);
    static float Distance(const Vector3D& _start, const Vector3D& _end);
    static float Distance(const Vector4D& _start, const Vector4D& _end);

    //converts euler angles to a quat
    static Quaternion Euler(float _x, float _y, float _z);
    static Quaternion Euler(const Vector3D& _eulerAngles);

    //gets the reflect of a vector
    static Vector3D Reflect(const Vector3D v1, const Vector3D v2);
    static Vector4D Reflect(const Vector4D v1, const Vector4D v2);

    static Vector3D GetSurfaceNormals(const Vector3D& _v1, const Vector3D& _v2, const Vector3D& _v3);
  };
}
#endif // !STATIC_FUNCTIONS_H_
