#include "Renderer.h"
#include "Window.h"
#include <iostream>
#include "Camera.h"

namespace GraphicalEngine
{
  Renderer::Renderer() : m_screenWidth(640), m_screenHeight(480)
  {
  }


  Renderer::~Renderer()
  {
  }
  bool Renderer::Create(SDL_Window* _window, int _index)
  {
    //Set the depth buffer size
    m_depthBuffer.resize(m_screenWidth * m_screenHeight);
    //Create renderer for window
    m_sdlRenderer = SDL_CreateRenderer(_window, _index, SDL_RENDERER_SOFTWARE);

    //error check
    if (m_sdlRenderer == nullptr)
    {
      std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
      return false;
    }
    else
    {
      //Init renderer color
      SDL_SetRenderDrawColor(m_sdlRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    }
    return true;
  }

  void Renderer::ClearScreen()
  {
    //Clear the screen
    SDL_SetRenderDrawColor(m_sdlRenderer, m_color.r, m_color.g, m_color.b, m_color.a);
    SDL_RenderClear(m_sdlRenderer);
    //refresh the buffer every screen clear
    for (int i = 0; i < m_depthBuffer.size(); i++)
    {
      m_depthBuffer[i] = UINT_MAX;
    }
  }

  void Renderer::Render(GraphicalEngine::Mesh& _mesh, const BML::Matrix4x4& _transformMatrix, const BML::Matrix4x4& _worldMatrix, const BML::Matrix4x4& _modelView)
  {
    //draw all the triangles through their faces (each face has 3 points: A, B, C which are gonna get connected)
    //int faceIndex = 0;
    for (GraphicalEngine::Face face : _mesh.m_faces)
    {
      //Attempted to implement backface culling
      //BML::Matrix4x4 mvp = _perspective * _modelView;

      //BML::Vector4D transformedNormal = mvp * BML::Vector4D(face.surfaceNormal, 1.0f);

      //if (transformedNormal.m_z >= 0)
      //{
      //  return; //cull
      //}

      //the 3 vertices of a triangle
      Vertex vertexA = _mesh.m_vertices[face.A];
      Vertex vertexB = _mesh.m_vertices[face.B];
      Vertex vertexC = _mesh.m_vertices[face.C];

      //Get their pixels in world coords
      /*Using _worldmatrix is incorrect as it should only be calculating it with rotation matrix, but since the mesh isn't moving it's fine
        Otherwise if it were to move just make a new matrix being equal to _worldMatrix and set its [0][3],[1][3],[2][3] values to 0.0f*/
      Vertex pixelA = GetProjectedVertex(vertexA, _transformMatrix, _worldMatrix);
      Vertex pixelB = GetProjectedVertex(vertexB, _transformMatrix, _worldMatrix);
      Vertex pixelC = GetProjectedVertex(vertexC, _transformMatrix, _worldMatrix);

      //apply a shade of grey for rasterization
      //float color = (0.25f + (faceIndex % _mesh.m_faces.size()) * 0.75f / _mesh.m_faces.size()) * 255.0f;

      SetColor(ColorRGBA8(255));

      DrawTriangle(pixelA, pixelB, pixelC, _modelView);
      //faceIndex++;
    }
  }
  //Drawing line between 2 points from left to right
  //point a, b -> point c, d
  //the points must be sorted first
  void Renderer::ProcessScanLine(ScanLineData& _data, const Vertex& _a, const Vertex& _b, const Vertex& _c, const Vertex& _d)
  {
    BML::Vector3D pA(_a.coordinates);
    BML::Vector3D pB(_b.coordinates);
    BML::Vector3D pC(_c.coordinates);
    BML::Vector3D pD(_d.coordinates);
    // Thanks to current Y (_y), we can compute the gradient to compute others values like
    // the starting X and ending X to draw between
    // if a.m_y == b.m_y or c.m_y == d.m_y, gradient is forced to 1
    float gradient1 = (pA.m_y != pB.m_y) ? (_data.currentY - pA.m_y) / (pB.m_y - pA.m_y) : 1.0f;
    float gradient2 = (pC.m_y != pD.m_y) ? (_data.currentY - pC.m_y) / (pD.m_y - pC.m_y) : 1.0f;

    int startX = (int)BML::StaticFunctions::Lerp(pA.m_x, pB.m_x, gradient1);
    int endX = (int)BML::StaticFunctions::Lerp(pC.m_x, pD.m_x, gradient2);

    // starting Z & ending Z
    float z1 = BML::StaticFunctions::Lerp(pA.m_z, pB.m_z, gradient1);
    float z2 = BML::StaticFunctions::Lerp(pC.m_z, pD.m_z, gradient2);

    float sn1 = BML::StaticFunctions::Lerp(_data.ndotla, _data.ndotlb, gradient1);
    float en1 = BML::StaticFunctions::Lerp(_data.ndotlc, _data.ndotld, gradient2);

    //SDL_SetRenderDrawColor(m_sdlRenderer, m_color.r , m_color.g , m_color.b , m_color.a);

    //drawing a line from left (startX) to right (endX)
    for (int x = startX; x < endX; x++)
    {
      if (x >= 0 && _data.currentY >= 0 && x < m_screenWidth && _data.currentY < m_screenHeight)
      {
        float gradient = (x - startX) / (float)(endX - startX);

        float z = BML::StaticFunctions::Lerp(z1, z2, gradient);

        //get the pixel index for the depth buffer
        float nDotL = BML::StaticFunctions::Lerp(sn1, en1, gradient);
        //changing the color value using the cosine of the angle
        // between the light vector and the normal vector

        int index = x + _data.currentY * m_screenWidth;

        if (m_depthBuffer[index] < z)
        {
          return; //discard this pixel if the depthbuffer index is higher
        }
        //set the depth buffer index if it was higher
        m_depthBuffer[index] = z;

        //Draw the pixel on the screen
        SDL_SetRenderDrawColor(m_sdlRenderer, m_color.r * nDotL, m_color.g * nDotL, m_color.b * nDotL, m_color.a);

        SDL_RenderDrawPoint(m_sdlRenderer, x, _data.currentY);
      }
      else
      {
        std::cout << "Could not render point, out of bound \n" << std::endl;
        return;
      }
    }
  }
  void Renderer::DrawTriangle(Vertex& _vertex1, Vertex& _vertex2, Vertex& _vertex3, const BML::Matrix4x4& _modelView)
  {
    // Algorithm learnt from
    // https://blogs.msdn.microsoft.com/davrous/2013/07/03/tutorial-part-5-learning-how-to-write-a-3d-software-engine-in-c-ts-or-js-flat-gouraud-shading/

    // Sorting the points in order to always have this order on screen p1, p2 & p3
    // with p1 always up (thus having the Y the lowest possible to be near the top screen)
    // then p2 between p1 & p3

    if (_vertex1.coordinates.m_y > _vertex2.coordinates.m_y)
    {
      Vertex temp = _vertex2;
      _vertex2 = _vertex1;
      _vertex1 = temp;
    }
    if (_vertex2.coordinates.m_y > _vertex3.coordinates.m_y)
    {
      Vertex temp = _vertex2;
      _vertex2 = _vertex3;
      _vertex3 = temp;
    }
    if (_vertex1.coordinates.m_y > _vertex2.coordinates.m_y)
    {
      Vertex temp = _vertex2;
      _vertex2 = _vertex1;
      _vertex1 = temp;
    }
    
    BML::Vector3D p1 = _vertex1.coordinates;
    BML::Vector3D p2 = _vertex2.coordinates;
    BML::Vector3D p3 = _vertex3.coordinates;

    // normal face's vector is the average normal between each vertex's normal
    // computing also the center point of the face
    //BML::Vector3D vnFace = (_vertex1.normal + _vertex2.normal + _vertex3.normal) / 3.0f;
    //BML::Vector3D centerPoint = (_vertex1.worldCoords + _vertex2.worldCoords + _vertex3.worldCoords) / 3.0f;

    //The light
    BML::Vector3D lightPos(0.0f, 10.0f, 10.0f);

    //Get the normalMatrix from the modeiView matrix
    BML::Matrix4x4 normalMat = _modelView;
    normalMat.Invert();
    normalMat.Transpose();

    // computing the cos of the angle between the light vector and the normal vector
    // it will return a value between 0 and 1 that will be used as the intensity of the color

    float nl1 = ComputeNDotL(_vertex1.worldCoords, _vertex1.normal, lightPos, normalMat);
    float nl2 = ComputeNDotL(_vertex2.worldCoords, _vertex2.normal, lightPos, normalMat);
    float nl3 = ComputeNDotL(_vertex3.worldCoords, _vertex3.normal, lightPos, normalMat);

    ScanLineData data;

    // inverse slopes to compute the lines' directions
    float dP1P2, dP1P3;

    // http://en.wikipedia.org/wiki/Slope
    // Computing inverse slopes

    if (p2.m_y - p1.m_y > 0.0f)
    {
      dP1P2 = (p2.m_x - p1.m_x) / (p2.m_y - p1.m_y);
    }
    else
    {
      dP1P2 = 0.0f;
    }

    if (p3.m_y - p1.m_y > 0.0f)
    {
      dP1P3 = (p3.m_x - p1.m_x) / (p3.m_y - p1.m_y);
    }
    else
    {
      dP1P3 = 0.0f;
    }

    // First case where triangles are like that:
    // P1
    // -
    // -- 
    // - -
    // -  -
    // -   - P2
    // -  -
    // - -
    // -
    // P3
    if (dP1P2 > dP1P3)
    {
      for (int y = (int)p1.m_y; y <= (int)p3.m_y; y++)
      {
        data.currentY = y;
        if (y < p2.m_y)
        {
          data.ndotla = nl1;
          data.ndotlb = nl3;
          data.ndotlc = nl1;
          data.ndotld = nl2;

          ProcessScanLine(data, _vertex1, _vertex3, _vertex1, _vertex2);
        }
        else
        {
          data.ndotla = nl1;
          data.ndotlb = nl3;
          data.ndotlc = nl2;
          data.ndotld = nl3;

          ProcessScanLine(data, _vertex1, _vertex3, _vertex2, _vertex3);
        }
      }
    }
    // First case where triangles are like that:
    //       P1
    //        -
    //       -- 
    //      - -
    //     -  -
    // P2 -   - 
    //     -  -
    //      - -
    //        -
    //       P3
    else
    {
      for (int y = (int)p1.m_y; y <= (int)p3.m_y; y++)
      {
        data.currentY = y;
        if (y < p2.m_y)
        {
          data.ndotla = nl1;
          data.ndotlb = nl2;
          data.ndotlc = nl1;
          data.ndotld = nl3;

          ProcessScanLine(data, _vertex1, _vertex2, _vertex1, _vertex3);
        }
        else
        {
          data.ndotla = nl2;
          data.ndotlb = nl3;
          data.ndotlc = nl1;
          data.ndotld = nl3;

          ProcessScanLine(data, _vertex2, _vertex3, _vertex1, _vertex3);
        }
      }
    }
  }
  Vertex Renderer::GetProjectedVertex(const Vertex& _coord3D, const BML::Matrix4x4& _transformMatrix, const BML::Matrix4x4& _worldMat)
  {
    BML::Vector4D homogeneousCoord(_coord3D.coordinates, 1.0f);
    //convert the model coordinate to clip space
    homogeneousCoord = _transformMatrix * homogeneousCoord;
    //then to normalized device coordinates
    homogeneousCoord /= homogeneousCoord.m_w;

    BML::Vector4D homogeneousWorld(_coord3D.coordinates, 1.0f);
    homogeneousWorld = _worldMat * homogeneousWorld;

    homogeneousWorld /= homogeneousWorld.m_w;

    BML::Vector4D normal3DWorld(_coord3D.normal, 1.0f);
    normal3DWorld = _worldMat * normal3DWorld;

    normal3DWorld /= normal3DWorld.m_w;
    //float x = (homogeneousCoord.m_x * m_screenWidth)/* / (homogeneousCoord.m_w * 2.0f)) */+ (m_screenWidth / 2.0f);
    //float y = (homogeneousCoord.m_y * m_screenHeight)/* / (homogeneousCoord.m_w * 2.0f))*/ + (m_screenHeight / 2.0f);

    //return the window coordinates
    BML::Vector3D point2D(homogeneousCoord.m_x + (m_screenWidth / 2.0f), (homogeneousCoord.m_y * -1.0f) + (m_screenHeight / 2.0f), homogeneousCoord.m_z);
    return Vertex(BML::Vector3D(point2D), normal3DWorld, homogeneousWorld);
    //return BML::Vector3D(x, y, homogeneousCoord.m_z);
  }
  void Renderer::UpdateScreen()
  {
    SDL_RenderPresent(m_sdlRenderer);
  }
  float Renderer::ComputeNDotL(const BML::Vector3D& _vertex, BML::Vector3D& _normal, const BML::Vector3D& _lightPos, BML::Matrix4x4 _normalMat)
  {
    BML::Vector3D lightDirection = _lightPos - _vertex;

    _normal.Normalize();
    lightDirection.Normalize();

    BML::Vector4D homogeneousNormal(_normal, 1.0f);

    BML::Vector3D normal(_normalMat * homogeneousNormal);

    return fmax(0, BML::StaticFunctions::Dot(normal, lightDirection));
  }
}
