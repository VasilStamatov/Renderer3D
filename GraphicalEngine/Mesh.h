#pragma once

#include <BML\Vector3D.h>
#include <BML\StaticFunctions.h>
#include <string>
#include <vector>

namespace GraphicalEngine
{
  //The face struct (contains ints for the triangle indexes)
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
    BML::Vector3D surfaceNormal;
  };

  struct Vertex
  {
    Vertex()
    {
      //empty
    }
    Vertex(BML::Vector3D _coordinates, BML::Vector3D _normal, BML::Vector3D _worldCoords) :
      coordinates(_coordinates), normal(_normal), worldCoords(_worldCoords)
    {
    }
    BML::Vector3D coordinates;
    BML::Vector3D normal;
    BML::Vector3D worldCoords;
  };

  class Mesh
  {
  public:
    Mesh(const std::string& _name, int _verticesCount, int _facesCount)
    {
      m_vertices.resize(_verticesCount);

      m_faces.resize(_facesCount);

      m_name = _name;
    }

    //setters
    void SetPosition(const BML::Vector3D& _pos)
    {
      m_position = _pos;
    }
    void SetRotation(const BML::Vector3D& _rotation)
    {
      m_rotation = _rotation;
    }
    void SetName(const std::string& _name)
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

    //The vectors of vertices and faces
    std::vector<Vertex> m_vertices;
    std::vector<Face> m_faces;

    void ComputeMeshNormals()
    {
      //computes per vertex normal
      for (Face& face : m_faces)
      {
        //the 3 vertices of a triangle
        Vertex vertexA = m_vertices[face.A];
        Vertex vertexB = m_vertices[face.B];
        Vertex vertexC = m_vertices[face.C];

        face.surfaceNormal = BML::StaticFunctions::GetSurfaceNormals(vertexA.coordinates, vertexB.coordinates, vertexC.coordinates);

        m_vertices[face.A].normal += face.surfaceNormal;
        m_vertices[face.B].normal += face.surfaceNormal;
        m_vertices[face.C].normal += face.surfaceNormal;
      }
      for (Vertex& vertex : m_vertices)
      {
        vertex.normal.Normalize();
      }
    }
  private:
    std::string m_name;
    BML::Vector3D m_position;
    BML::Vector3D m_rotation;
  };

}