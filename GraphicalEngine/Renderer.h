#pragma once

#include <BML\Matrix4x4.h>
#include <BML\Vectors.h>
#include <SDL\SDL.h>

#include <vector>
#include "ColorRGBA8.h"
#include "Mesh.h"

namespace GraphicalEngine
{
  struct ScanLineData
  {
    //current y
    int currentY;
    //normals dot product with light
    float ndotla;
    float ndotlb;
    float ndotlc;
    float ndotld;
  };

  class Renderer
  {
  public:
    Renderer();
    ~Renderer();

    //Creates the renderer
    bool Create(SDL_Window* _window, int _index);
    //Renders a mesh
    void Render(GraphicalEngine::Mesh& _mesh, const BML::Matrix4x4& _transformMatrix, const BML::Matrix4x4& _worldMatrix, const BML::Matrix4x4& _modelView);
    void ProcessScanLine(ScanLineData& _data, const Vertex& _a, const Vertex& _b, const Vertex& _c, const Vertex& _d);
    void DrawTriangle(Vertex& _vertex1, Vertex& _vertex2, Vertex& _vertex3, const BML::Matrix4x4& _modelView);
    //Clear the screen
    void ClearScreen();
    //Update the screen
    void UpdateScreen();

    //Project your model space point into window coordinates
    Vertex GetProjectedVertex(const Vertex& _coord3D, const BML::Matrix4x4& _transformMatrix, const BML::Matrix4x4& _worldMat);

    //Set the color
    void SetColor(const ColorRGBA8& _color) { m_color = _color; }
    //Sets the renderer to null
    void SetNull() { m_sdlRenderer = nullptr; }
    //Gets the curent color
    ColorRGBA8 GetColor() const { return m_color; }
    //Gets the renderer
    SDL_Renderer* GetRenderer() const { return m_sdlRenderer; }

  private:
    float ComputeNDotL(const BML::Vector3D& _vertex, BML::Vector3D& _normal, const BML::Vector3D& _lightPos, BML::Matrix4x4 _normalMat);

    SDL_Renderer* m_sdlRenderer = nullptr;

    ColorRGBA8 m_color;

    std::vector<float> m_depthBuffer;

    int m_screenHeight = 480;
    int m_screenWidth = 640;
  };
}


