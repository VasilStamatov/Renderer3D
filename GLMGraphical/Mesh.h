#pragma once

#include <string>
#include <vector>
#include <BML/Vector3D.h>

struct Face
{
  Face()
  {
    A = 0;
    B = 0;
    C = 0;
  }
  Face(int _A, int _B, int _C)
  {
    A = _A;
    B = _B;
    C = _C;
  }
  int A;
  int B;
  int C;
};

class Mesh
{
public:
  Mesh(std::string _name, int _verticesCount, int _facesCount)
  {
    m_vertices.resize(_verticesCount);

    m_faces.resize(_facesCount);

    m_name = _name;
  }

  //setters
  void SetPosition(BML::Vector3D _pos)
  {
    m_position = _pos;
  }
  void SetRotation(BML::Vector3D _rotation)
  {
    m_rotation = _rotation;
  }
  void SetName(std::string _name)
  {
    m_name = _name;
  }

  //getters
  BML::Vector3D GetPosition()
  {
    return m_position;
  }
  BML::Vector3D GetRotation()
  {
    return m_rotation;
  }
  std::string GetName()
  {
    return m_name;
  }

  std::vector<BML::Vector3D> m_vertices;
  std::vector<Face> m_faces;

private:
  std::string m_name;
  BML::Vector3D m_position;
  BML::Vector3D m_rotation;
};
