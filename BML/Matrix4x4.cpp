#include "Matrix4x4.h"
#include "StaticFunctions.h"
#include "Vector4D.h"
#include "Vector3D.h"
#include "Quaternion.h"

#include <math.h>
#include <limits>

#ifndef PI
#define PI 3.14159265f
#endif

namespace BML
{
  Matrix4x4::Matrix4x4(const Matrix4x4& _newMat)
  {
    *this = _newMat;
  }
  Matrix4x4::Matrix4x4()
  {
    //zero matrix
    MakeZero();
  }

  Matrix4x4::~Matrix4x4()
  {
  }

  void Matrix4x4::MakeIdentity()
  {
    //Make the object an identity matrix
    for (size_t i = 0; i < 4; i++)
    {
      for (size_t j = 0; j < 4; j++)
      {
        if (i == j)
        {
          m_matrix[i][j] = 1.0f;
        }
        else
        {
          m_matrix[i][j] = 0.0f;
        }
      }
    }
  }

  void Matrix4x4::MakeZero()
  {
    //Make the object a zero matrix
    for (size_t i = 0; i < 4; i++)
    {
      for (size_t j = 0; j < 4; j++)
      {
        m_matrix[i][j] = 0.0f;
      }
    }
  }

  void Matrix4x4::Transpose()
  {
    //Transpose the matrix object
    for (size_t row = 0; row < 4; row++)
    {
      for (size_t col = 0; col < 4; col++)
      {
        if (col > row)
        {
          float tempVal = m_matrix[row][col];
          m_matrix[row][col] = m_matrix[col][row];
          m_matrix[col][row] = tempVal;
        }
      }
    }
  }

  void Matrix4x4::ConvertForScaling(float _xScale, float _yScale, float _zScale)
  {
    //make every element 0 except diagonal
    MakeIdentity();
    //set the scale values
    m_matrix[0][0] = _xScale;
    m_matrix[1][1] = _yScale;
    m_matrix[2][2] = _zScale;
  }
  void Matrix4x4::ConvertForTranslation(float _xTrans, float _yTrans, float _zTrans)
  {
    //make every element 0 except diagonal
    MakeIdentity();
    //set the translation values
    m_matrix[0][3] = _xTrans;
    m_matrix[1][3] = _yTrans;
    m_matrix[2][3] = _zTrans;
  }
  void Matrix4x4::ConvertForRotation(float _angleX, float _angleY, float _angleZ)
  {
    float epsilon = std::numeric_limits<float>::epsilon();
    MakeIdentity();
    //Getting the sin and cos values here, for better readibility below on the matrix creation
    float cosAngleX = (abs((float)cos(_angleX * PI / 180.0)) < epsilon) ? 0.0f : (float)cos(_angleX * PI / 180.0);
    float sinAngleX = (abs((float)sin(_angleX * PI / 180.0)) < epsilon) ? 0.0f : (float)sin(_angleX * PI / 180.0);
    float cosAngleY = (abs((float)cos(_angleY * PI / 180.0)) < epsilon) ? 0.0f : (float)cos(_angleY * PI / 180.0);
    float sinAngleY = (abs((float)sin(_angleY * PI / 180.0)) < epsilon) ? 0.0f : (float)sin(_angleY * PI / 180.0);
    float cosAngleZ = (abs((float)cos(_angleZ * PI / 180.0)) < epsilon) ? 0.0f : (float)cos(_angleZ * PI / 180.0);
    float sinAngleZ = (abs((float)sin(_angleZ * PI / 180.0)) < epsilon) ? 0.0f : (float)sin(_angleZ * PI / 180.0);

    m_matrix[0][0] = cosAngleY * cosAngleZ;
    m_matrix[0][1] = cosAngleZ * sinAngleX * sinAngleY - cosAngleX * sinAngleZ;
    m_matrix[0][2] = cosAngleX * cosAngleZ * sinAngleY + sinAngleX * sinAngleY;

    m_matrix[1][0] = cosAngleY * sinAngleZ;
    m_matrix[1][1] = cosAngleX * cosAngleZ + sinAngleX * sinAngleY * sinAngleZ;
    m_matrix[1][2] = -cosAngleZ * sinAngleX + cosAngleX * sinAngleY * sinAngleZ;

    m_matrix[2][0] = -sinAngleY;
    m_matrix[2][1] = cosAngleY * sinAngleX;
    m_matrix[2][2] = cosAngleX * cosAngleY;

  }
  void Matrix4x4::ConvertForRotationX(float _angle)
  {
    float epsilon = std::numeric_limits<float>::epsilon();
    //make every element 0
    MakeIdentity();
    //set the rotation values
    m_matrix[1][1] = (abs((float)cos(_angle * PI / 180.0)) < epsilon) ? 0.0f : (float)cos(_angle * PI / 180.0);
    m_matrix[2][2] = (abs((float)cos(_angle * PI / 180.0)) < epsilon) ? 0.0f : (float)cos(_angle * PI / 180.0);
    m_matrix[1][2] = (abs((float)-sin(_angle * PI / 180.0)) < epsilon) ? 0.0f : (float)-sin(_angle * PI / 180.0);
    m_matrix[2][1] = (abs((float)sin(_angle * PI / 180.0)) < epsilon) ? 0.0f : (float)sin(_angle * PI / 180.0);
  }
  void Matrix4x4::ConvertForRotationY(float _angle)
  {
    float epsilon = std::numeric_limits<float>::epsilon();
    //make every element 0
    MakeIdentity();
    //set the rotation values
    m_matrix[0][0] = (abs((float)cos(_angle * PI / 180.0)) < epsilon) ? 0.0f : (float)cos(_angle * PI / 180.0);
    m_matrix[2][2] = (abs((float)cos(_angle * PI / 180.0)) < epsilon) ? 0.0f : (float)cos(_angle * PI / 180.0);
    m_matrix[2][0] = (abs((float)-sin(_angle * PI / 180.0)) < epsilon) ? 0.0f : (float)-sin(_angle * PI / 180.0);
    m_matrix[0][2] = (abs((float)sin(_angle * PI / 180.0)) < epsilon) ? 0.0f : (float)sin(_angle * PI / 180.0);
  }
  void Matrix4x4::ConvertForRotationZ(float _angle)
  {
    float epsilon = std::numeric_limits<float>::epsilon();
    //make every element 0
    MakeIdentity();
    //set the rotation values
    m_matrix[0][0] = (abs((float)cos(_angle * PI / 180.0)) < epsilon) ? 0.0f : (float)cos(_angle * PI / 180.0);
    m_matrix[1][1] = (abs((float)cos(_angle * PI / 180.0)) < epsilon) ? 0.0f : (float)cos(_angle * PI / 180.0);
    m_matrix[0][1] = (abs((float)-sin(_angle * PI / 180.0)) < epsilon) ? 0.0f : (float)-sin(_angle * PI / 180.0);
    m_matrix[1][0] = (abs((float)sin(_angle * PI / 180.0)) < epsilon) ? 0.0f : (float)sin(_angle * PI / 180.0);

  }
  Vector4D Matrix4x4::GetRow(int _index) const
  {
    //returns a 4d vec of the specified matrix row (0-3)
    if (_index < 0 || _index > 3)
    {
      //Error
      throw;
    }
    else
    {
      Vector4D result(m_matrix[_index][0], m_matrix[_index][1], m_matrix[_index][2], m_matrix[_index][3]);
      return result;
    }
  }
  Vector4D Matrix4x4::GetCol(int _index) const
  {
    //returns a 4d vec of the specified matrix column (0-3)
    if (_index < 0 || _index > 3)
    {
      //Error
      throw;
    }
    else
    {
      Vector4D result(m_matrix[0][_index], m_matrix[1][_index], m_matrix[2][_index], m_matrix[3][_index]);
      return result;
    }
  }
  float Matrix4x4::GetDeterminant() const
  {
    //Calculate the determinant of the matrix
    float result =
      m_matrix[0][2] * m_matrix[1][1] * m_matrix[2][3] * m_matrix[3][0] - m_matrix[0][1] * m_matrix[1][2] * m_matrix[2][3] * m_matrix[3][0] -
      m_matrix[0][3] * m_matrix[1][2] * m_matrix[2][0] * m_matrix[3][1] + m_matrix[0][2] * m_matrix[1][3] * m_matrix[2][0] * m_matrix[3][1] +
      m_matrix[0][3] * m_matrix[1][0] * m_matrix[2][2] * m_matrix[3][1] - m_matrix[0][0] * m_matrix[1][3] * m_matrix[2][2] * m_matrix[3][1] -
      m_matrix[0][2] * m_matrix[1][0] * m_matrix[2][3] * m_matrix[3][1] + m_matrix[0][0] * m_matrix[1][2] * m_matrix[2][3] * m_matrix[3][1] +
      m_matrix[0][3] * m_matrix[1][1] * m_matrix[2][0] * m_matrix[3][2] - m_matrix[0][1] * m_matrix[1][3] * m_matrix[2][0] * m_matrix[3][2] -
      m_matrix[0][3] * m_matrix[1][0] * m_matrix[2][1] * m_matrix[3][2] + m_matrix[0][0] * m_matrix[1][3] * m_matrix[2][1] * m_matrix[3][2] +
      m_matrix[0][1] * m_matrix[1][0] * m_matrix[2][3] * m_matrix[3][2] - m_matrix[0][0] * m_matrix[1][1] * m_matrix[2][3] * m_matrix[3][2] -
      m_matrix[0][2] * m_matrix[1][1] * m_matrix[2][0] * m_matrix[3][3] + m_matrix[0][1] * m_matrix[1][2] * m_matrix[2][0] * m_matrix[3][3] +
      m_matrix[0][2] * m_matrix[1][0] * m_matrix[2][1] * m_matrix[3][3] - m_matrix[0][0] * m_matrix[1][2] * m_matrix[2][1] * m_matrix[3][3] -
      m_matrix[0][1] * m_matrix[1][0] * m_matrix[2][2] * m_matrix[3][3] + m_matrix[0][0] * m_matrix[1][1] * m_matrix[2][2] * m_matrix[3][3];

    return result;
  }
  void Matrix4x4::Invert()
  {
    //Using Linmath's algorhitm
    //Invert the matrix
    float s[6];
    float c[6];
    s[0] = m_matrix[0][0] * m_matrix[1][1] - m_matrix[1][0] * m_matrix[0][1];
    s[1] = m_matrix[0][0] * m_matrix[1][2] - m_matrix[1][0] * m_matrix[0][2];
    s[2] = m_matrix[0][0] * m_matrix[1][3] - m_matrix[1][0] * m_matrix[0][3];
    s[3] = m_matrix[0][1] * m_matrix[1][2] - m_matrix[1][1] * m_matrix[0][2];
    s[4] = m_matrix[0][1] * m_matrix[1][3] - m_matrix[1][1] * m_matrix[0][3];
    s[5] = m_matrix[0][2] * m_matrix[1][3] - m_matrix[1][2] * m_matrix[0][3];

    c[0] = m_matrix[2][0] * m_matrix[3][1] - m_matrix[3][0] * m_matrix[2][1];
    c[1] = m_matrix[2][0] * m_matrix[3][2] - m_matrix[3][0] * m_matrix[2][2];
    c[2] = m_matrix[2][0] * m_matrix[3][3] - m_matrix[3][0] * m_matrix[2][3];
    c[3] = m_matrix[2][1] * m_matrix[3][2] - m_matrix[3][1] * m_matrix[2][2];
    c[4] = m_matrix[2][1] * m_matrix[3][3] - m_matrix[3][1] * m_matrix[2][3];
    c[5] = m_matrix[2][2] * m_matrix[3][3] - m_matrix[3][2] * m_matrix[2][3];

    /* Assumes it is invertible */
    float idet = 1.0f / (s[0] * c[5] - s[1] * c[4] + s[2] * c[3] + s[3] * c[2] - s[4] * c[1] + s[5] * c[0]);

    m_matrix[0][0] = (m_matrix[1][1] * c[5] - m_matrix[1][2] * c[4] + m_matrix[1][3] * c[3]) * idet;
    m_matrix[0][1] = (-m_matrix[0][1] * c[5] + m_matrix[0][2] * c[4] - m_matrix[0][3] * c[3]) * idet;
    m_matrix[0][2] = (m_matrix[3][1] * s[5] - m_matrix[3][2] * s[4] + m_matrix[3][3] * s[3]) * idet;
    m_matrix[0][3] = (-m_matrix[2][1] * s[5] + m_matrix[2][2] * s[4] - m_matrix[2][3] * s[3]) * idet;

    m_matrix[1][0] = (-m_matrix[1][0] * c[5] + m_matrix[1][2] * c[2] - m_matrix[1][3] * c[1]) * idet;
    m_matrix[1][1] = (m_matrix[0][0] * c[5] - m_matrix[0][2] * c[2] + m_matrix[0][3] * c[1]) * idet;
    m_matrix[1][2] = (-m_matrix[3][0] * s[5] + m_matrix[3][2] * s[2] - m_matrix[3][3] * s[1]) * idet;
    m_matrix[1][3] = (m_matrix[2][0] * s[5] - m_matrix[2][2] * s[2] + m_matrix[2][3] * s[1]) * idet;

    m_matrix[2][0] = (m_matrix[1][0] * c[4] - m_matrix[1][1] * c[2] + m_matrix[1][3] * c[0]) * idet;
    m_matrix[2][1] = (-m_matrix[0][0] * c[4] + m_matrix[0][1] * c[2] - m_matrix[0][3] * c[0]) * idet;
    m_matrix[2][2] = (m_matrix[3][0] * s[4] - m_matrix[3][1] * s[2] + m_matrix[3][3] * s[0]) * idet;
    m_matrix[2][3] = (-m_matrix[2][0] * s[4] + m_matrix[2][1] * s[2] - m_matrix[2][3] * s[0]) * idet;

    m_matrix[3][0] = (-m_matrix[1][0] * c[3] + m_matrix[1][1] * c[1] - m_matrix[1][2] * c[0]) * idet;
    m_matrix[3][1] = (m_matrix[0][0] * c[3] - m_matrix[0][1] * c[1] + m_matrix[0][2] * c[0]) * idet;
    m_matrix[3][2] = (-m_matrix[3][0] * s[3] + m_matrix[3][1] * s[1] - m_matrix[3][2] * s[0]) * idet;
    m_matrix[3][3] = (m_matrix[2][0] * s[3] - m_matrix[2][1] * s[1] + m_matrix[2][2] * s[0]) * idet;
  }
  void Matrix4x4::Ortho(float _left, float _right, float _bottom, float _top, float _near, float _far)
  {
    //Convert the matrix to an ortho matrix
    m_matrix[0][0] = 2.0f / (_right - _left);
    m_matrix[0][1] = m_matrix[0][2] = 0.0f;
    m_matrix[0][3] = -(_right + _left) / (_right - _left);
    m_matrix[1][1] = 2.0f / (_top - _bottom);
    m_matrix[1][0] = m_matrix[1][2] = 0.0f;
    m_matrix[1][3] = -(_top + _bottom) / (_top - _bottom);
    m_matrix[2][2] = -2.0f / (_far - _near);
    m_matrix[2][0] = m_matrix[2][1] = 0.0f;
    m_matrix[2][3] = -(_far + _near) / (_far - _near);
    m_matrix[3][0] = m_matrix[3][1] = m_matrix[3][2] = 0.0f;
    m_matrix[3][3] = 1.0f;
  }
  void Matrix4x4::Perspective(float _fovY, float _aspect, float _near, float _far)
  {
    MakeZero();

    float const a = 1.0f / tan((_fovY * PI / 180.0f) / 2.0f);

    m_matrix[0][0] = a / _aspect;
    m_matrix[1][1] = a;
    m_matrix[2][2] = -((_far + _near) / (_far - _near));
    m_matrix[2][3] = -1.0f;
    m_matrix[3][2] = -((2.0f * _far * _near) / (_far - _near));
  }
  void Matrix4x4::LookAt(Vector3D _eye, Vector3D _center, Vector3D _up)
  {
    MakeIdentity();

    Vector3D zAxis = _eye - _center;
    zAxis.Normalize();
    Vector3D xAxis = StaticFunctions::Cross(_up, zAxis);
    xAxis.Normalize();
    Vector3D yAxis = StaticFunctions::Cross(zAxis, xAxis);

    m_matrix[0][0] = zAxis.m_z;
    m_matrix[0][1] = zAxis.m_y;
    m_matrix[0][2] = zAxis.m_x;
    m_matrix[0][3] = -(StaticFunctions::Dot(xAxis, _eye));
    m_matrix[1][0] = yAxis.m_z;
    m_matrix[1][1] = yAxis.m_y;
    m_matrix[1][2] = yAxis.m_x;
    m_matrix[1][3] = -(StaticFunctions::Dot(yAxis, _eye));
    m_matrix[2][0] = xAxis.m_z;
    m_matrix[2][1] = xAxis.m_y;
    m_matrix[2][2] = xAxis.m_x;
    m_matrix[2][3] = -(StaticFunctions::Dot(zAxis, _eye));
  }
  Quaternion Matrix4x4::GetQuaternion4D() const
  {
    //return the quaternion representation of the matrix
    Quaternion result;
    float trace = m_matrix[0][0] + m_matrix[1][1] + m_matrix[2][2];
    if (trace > 0.0f)
    {
      float s = 0.5f / sqrtf(trace + 1.0f);
      result.m_w = 0.25f / s;
      result.m_x = (m_matrix[2][1] - m_matrix[1][2]) * s;
      result.m_y = (m_matrix[0][2] - m_matrix[2][0]) * s;
      result.m_z = (m_matrix[1][0] - m_matrix[0][1]) * s;
    }
    else
    {
      if (m_matrix[0][0] > m_matrix[1][1] && m_matrix[0][0] > m_matrix[2][2])
      {
        float s = 2.0f * sqrtf(1.0f + m_matrix[0][0] - m_matrix[1][1] - m_matrix[2][2]);
        result.m_w = (m_matrix[2][1] - m_matrix[1][2]) / s;
        result.m_x = 0.25f * s;
        result.m_y = (m_matrix[0][1] + m_matrix[1][0]) / s;
        result.m_z = (m_matrix[0][2] + m_matrix[2][0]) / s;
      }
      else if (m_matrix[1][1] > m_matrix[2][2])
      {
        float s = 2.0f * sqrtf(1.0f + m_matrix[1][1] - m_matrix[0][0] - m_matrix[2][2]);
        result.m_w = (m_matrix[0][2] - m_matrix[2][0]) / s;
        result.m_x = (m_matrix[0][1] + m_matrix[1][0]) / s;
        result.m_y = 0.25f * s;
        result.m_z = (m_matrix[1][2] + m_matrix[2][1]) / s;
      }
      else
      {
        float s = 2.0f * sqrtf(1.0f + m_matrix[2][2] - m_matrix[0][0] - m_matrix[1][1]);
        result.m_w = (m_matrix[1][0] - m_matrix[0][1]) / s;
        result.m_x = (m_matrix[0][2] + m_matrix[2][0]) / s;
        result.m_y = (m_matrix[1][2] + m_matrix[2][1]) / s;
        result.m_z = 0.25f * s;
      }
    }
    return result;
  }
  Matrix4x4 Matrix4x4::operator+(const Matrix4x4& _addedMatrix) const
  {
    //operator addition overloading
    Matrix4x4 result;
    for (size_t i = 0; i < 4; i++)
    {
      for (size_t j = 0; j < 4; j++)
      {
        result.m_matrix[i][j] = m_matrix[i][j] + _addedMatrix.m_matrix[i][j];
      }
    }
    return result;
  }

  void Matrix4x4::operator+=(const Matrix4x4& _addedMatrix)
  {
    //operator addition overloading
    for (size_t i = 0; i < 4; i++)
    {
      for (size_t j = 0; j < 4; j++)
      {
        m_matrix[i][j] += _addedMatrix.m_matrix[i][j];
      }
    }
  }

  Matrix4x4 Matrix4x4::operator-(const Matrix4x4& _subtractedMatrix) const
  {
    //operator subtraction overloading
    Matrix4x4 result;
    for (size_t i = 0; i < 4; i++)
    {
      for (size_t j = 0; j < 4; j++)
      {
        result.m_matrix[i][j] = m_matrix[i][j] - _subtractedMatrix.m_matrix[i][j];
      }
    }
    return result;
  }

  void Matrix4x4::operator-=(const Matrix4x4& _subtractedMatrix)
  {
    //operator subtraction overloading
    for (size_t i = 0; i < 4; i++)
    {
      for (size_t j = 0; j < 4; j++)
      {
        m_matrix[i][j] -= _subtractedMatrix.m_matrix[i][j];
      }
    }
  }

  Matrix4x4 Matrix4x4::operator*(const Matrix4x4& _multipliedMatrix) const
  {
    //operator mult overloading
    Matrix4x4 result;
    for (size_t i = 0; i < 4; i++)
    {
      for (size_t j = 0; j < 4; j++)
      {
        result.m_matrix[i][j] = m_matrix[i][0] * _multipliedMatrix.m_matrix[0][j] +
          m_matrix[i][1] * _multipliedMatrix.m_matrix[1][j] +
          m_matrix[i][2] * _multipliedMatrix.m_matrix[2][j] +
          m_matrix[i][3] * _multipliedMatrix.m_matrix[3][j];
      }
    }
    return result;
  }

  void Matrix4x4::operator*=(const Matrix4x4& _multipliedMatrix)
  {
    //operator mult overloading
    for (size_t i = 0; i < 4; i++)
    {
      for (size_t j = 0; j < 4; j++)
      {
        m_matrix[i][j] = m_matrix[i][0] * _multipliedMatrix.m_matrix[0][j] +
          m_matrix[i][1] * _multipliedMatrix.m_matrix[1][j] +
          m_matrix[i][2] * _multipliedMatrix.m_matrix[2][j] +
          m_matrix[i][3] * _multipliedMatrix.m_matrix[3][j];
      }
    }
  }

  Matrix4x4 Matrix4x4::operator/(float _dividedScalar) const
  {
    //operator division overloading
    Matrix4x4 result;
    for (size_t i = 0; i < 4; i++)
    {
      for (size_t j = 0; j < 4; j++)
      {
        result.m_matrix[i][j] = m_matrix[i][j] / _dividedScalar;
      }
    }
    return result;
  }

  void Matrix4x4::operator/=(float _dividedScalar)
  {
    //operator division overloading
    for (size_t i = 0; i < 4; i++)
    {
      for (size_t j = 0; j < 4; j++)
      {
        m_matrix[i][j] /= _dividedScalar;
      }
    }
  }

  Matrix4x4 Matrix4x4::operator*(float _multipliedScalar) const
  {
    //operator mult overloading
    Matrix4x4 result;
    for (size_t i = 0; i < 4; i++)
    {
      for (size_t j = 0; j < 4; j++)
      {
        result.m_matrix[i][j] = m_matrix[i][j] * _multipliedScalar;
      }
    }
    return result;
  }

  void Matrix4x4::operator*=(float _multipliedScalar)
  {
    //operator mult overloading
    for (size_t i = 0; i < 4; i++)
    {
      for (size_t j = 0; j < 4; j++)
      {
        m_matrix[i][j] *= _multipliedScalar;
      }
    }
  }

  void Matrix4x4::operator=(const Matrix4x4& _Matrix)
  {
    //operator assign overloading
    for (size_t i = 0; i < 4; i++)
    {
      for (size_t j = 0; j < 4; j++)
      {
        m_matrix[i][j] = _Matrix.m_matrix[i][j];
      }
    }
  }

  Vector4D Matrix4x4::operator*(const Vector4D& _multipliedVec) const
  {
    //operator mult overloading
    Vector4D result;
    Vector4D matRow1(GetRow(0));
    Vector4D matRow2(GetRow(1));
    Vector4D matRow3(GetRow(2));
    Vector4D matRow4(GetRow(3));
    result.m_x = BML::StaticFunctions::Dot(matRow1, _multipliedVec);
    result.m_y = BML::StaticFunctions::Dot(matRow2, _multipliedVec);
    result.m_z = BML::StaticFunctions::Dot(matRow3, _multipliedVec);
    result.m_w = BML::StaticFunctions::Dot(matRow4, _multipliedVec);

    return result;
  }
}
