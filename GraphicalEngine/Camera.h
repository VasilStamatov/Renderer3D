#pragma once

#include <BML/BML.h>

namespace GraphicalEngine
{
  class Camera
  {
  public:
    Camera();
    ~Camera();

    //Initialize the camera
    void Init(float _fov, int _screenWidth, int _screenHeight);
    //Compute the ModelViewProjection Matrix
    BML::Matrix4x4 ComputeMVP(const BML::Vector3D& _meshPos, const BML::Vector3D& _meshRot);

    //setters
    void SetPosition(const BML::Vector3D& _pos)
    {
      m_position = _pos;
    }
    void SetTarget(const BML::Vector3D& _target)
    {
      m_target = _target;
    }
    //getters
    BML::Vector3D GetPosition() const
    {
      return m_position;
    }
    BML::Vector3D GetTarget() const
    {
      return m_target;
    }
    float GetAspectRatio() const
    {
      return (float)m_screenWidth / (float)m_screenHeight;
    }
    BML::Matrix4x4 GetCurrentMVP() const
    {
      return m_MVP;
    }
    BML::Matrix4x4 GetCurrentWorld() const
    {
      return m_worldMatrix;
    }
    BML::Matrix4x4 GetCurrentModelView() const
    {
      return m_modelView;
    }
    BML::Matrix4x4 GetCurrentPRojection() const
    {
      return m_projectionMatrix;
    }
  private:
    BML::Matrix4x4 m_viewMatrix; //used for eye space
    BML::Matrix4x4 m_projectionMatrix; //used for clip space
    BML::Matrix4x4 m_worldMatrix; //used to get out of model space
    BML::Matrix4x4 m_MVP; // ModelViewProjection
    BML::Matrix4x4 m_modelView;
    //Position of the camera
    BML::Vector3D m_position;
    //Target of the camera
    BML::Vector3D m_target;

    int m_screenWidth;
    int m_screenHeight;

    float m_fov;
  };
}

