#ifndef _MATRIX_4_X_4_H
#define _MATRIX_4_X_4_H

#include "ostream"

namespace BML
{
  class Vector3D;
  class Vector4D;
  class Quaternion;
  ///Matrix class used to define 4 by 4 matrices
  class Matrix4x4
  {
  public:
    Matrix4x4(const Matrix4x4& _newMat);
    Matrix4x4();
    ~Matrix4x4();
    ///Converts to identity matrix
    void MakeIdentity();
    ///Converts to zero matrix
    void MakeZero();
    ///Transposes the matrix
    void Transpose();
    ///Converts to scale matrix
    void ConvertForScaling(float _xScale, float _yScale, float _zScale);
    ///Converts to translation matrix
    void ConvertForTranslation(float _xTrans, float _yTrans, float _zTrans);
    ///Converts to rotation matrix about each angle
    void ConvertForRotation(float _angleX, float _angleY, float _angleZ);
    ///Converts to rotation matrix about x axis
    void ConvertForRotationX(float _angle);
    ///Converts to rotation matrix about y axis
    void ConvertForRotationY(float _angle);
    ///Converts to rotation matrix about z axis
    void ConvertForRotationZ(float _angle);
    ///Converts to ortho matrix
    void Ortho(float _left, float _right, float _bottom, float _top, float _near, float _far);
    ///Converts to perspective matrix
    /// \param _fovY the frield of view Y
    /// \param _aspect tha aspect ratio
    /// \param _near the near clipping
    /// \param _far the far clipping
    void Perspective(float _fovY, float _aspect, float _near, float _far);
    ///Converts to lookat matrix (for the view matrix)
    void LookAt(Vector3D _eye, Vector3D _center, Vector3D _up);
    ///gets a row from the matrix
    Vector4D GetRow(int _index) const;
    ///gets a col from the matrix
    Vector4D GetCol(int _index) const;
    ///gets the determinant of the matrix
    float GetDeterminant() const;
    ///inverts the matrix
    void Invert();
    ///gets the quaternion representation of the matrix
    Quaternion GetQuaternion4D() const;

    /// \brief operator overload for matrix addition
    /// Used for matrix addition
    /// \param _addedMatrix the matrix that will be added to the left hand side matrix
    Matrix4x4 operator+(const Matrix4x4& _addedMatrix) const;

    void operator+=(const Matrix4x4& _addedMatrix);

    Matrix4x4 operator-(const Matrix4x4& _subtractedMatrix) const;

    void operator-=(const Matrix4x4& _subtractedMatrix);

    Matrix4x4 operator*(const Matrix4x4& _multipliedMatrix) const;

    void operator*=(const Matrix4x4& _multipliedMatrix);

    Matrix4x4 operator/(float _dividedScalar) const;

    void operator/=(float _dividedScalar);

    Matrix4x4 operator*(float _multipliedScalar) const;

    void operator*=(float _multipliedScalar);

    void operator=(const Matrix4x4& _Matrix);

    Vector4D operator*(const Vector4D& _multipliedVec) const;

    friend std::ostream &operator<<(std::ostream &out, const Matrix4x4& _mat)
    {
      for (int i = 0; i < 4; i++)
      {
        for (int j = 0; j < 4; j++)
        {
          out << _mat.m_matrix[i][j] << "|";
        }
        out << std::endl;
      }
      return out;
    }
    ///4 by 4 array representing the matrix
    float m_matrix[4][4];
  };
}

#endif
