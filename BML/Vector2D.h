#ifndef _VECTOR_2_D_H_
#define _VECTOR_2_D_H_

#include "ostream"

namespace BML
{
  class Vector2D
  {
  public:
    Vector2D(float _x, float _y);
    Vector2D(const Vector2D& _newVec);
    Vector2D();
    ~Vector2D();
    //scale the vector (basically scalar multiplication, but you can add different values for each component x,y)
    void Scale(float _xScale, float _yScale);
    //translate the vector with scalar values rather than using the overload operator of vec+vec
    void Translate(float _xTranslation, float _yTranslation);
    //rotate the vector by x degrees
    Vector2D Rotate(float _angle);
    //gets the magnitude
    float GetMagnitude() const;
    //gets the squared magnitude (sqrt isn't used )
    float GetSquaredMagnitude() const;
    //normalize the vector
    void Normalize();
    //returns the normalized version of the vec (doesn't change it tho)
    Vector2D Normalized();

    Vector2D operator+(const Vector2D& _addedVec) const;

    void operator+=(const Vector2D& _addedVec);

    Vector2D operator-(const Vector2D& _subtractedVec) const;

    void operator-=(const Vector2D& _subtractedVec);

    Vector2D operator*(float _multipliedScalar) const;

    void operator*=(float _multipliedScalar);

    Vector2D operator/(float _dividedScalar) const;

    void operator/=(float _dividedScalar);

    void operator=(const Vector2D& _Vec);

    bool operator!=(const Vector2D& _comp);

    bool operator==(const Vector2D& _comp);

    friend std::ostream &operator<<(std::ostream &out, const Vector2D& _vec)
    {
      out << "(" << _vec.m_x << ", " << _vec.m_y << ")";
      return out;
    }

    float m_x = 0.0f;
    float m_y = 0.0f;
  };
}

#endif