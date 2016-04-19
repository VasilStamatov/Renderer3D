#include "Camera.h"

#define PI 3.14159265f

namespace GraphicalEngine
{
  Camera::Camera() :
    m_position(0.0f, 0.0f, 10.0f),
    m_target(0.0f, 0.0f, 0.0f),
    m_fov(45.0f),
    m_screenWidth(500.0f),
    m_screenHeight(500.0f)
  {
    m_viewMatrix.MakeIdentity();
    m_projectionMatrix.MakeIdentity();
    m_worldMatrix.MakeIdentity();
    m_MVP.MakeIdentity();
    m_modelView.MakeIdentity();
  }

  Camera::~Camera()
  {
  }
  void Camera::Init(float _fov, int _screenWidth, int _screenHeight)
  {
    m_screenWidth = _screenWidth;
    m_screenHeight = _screenHeight;
    //convert the degrees to radians (only once!)
    m_fov = _fov * PI / 180.0f;
    //projection matrix
    m_projectionMatrix.Perspective(m_fov, GetAspectRatio(), 0.1f, 100.0f);
  }

  BML::Matrix4x4 Camera::ComputeMVP(const BML::Vector3D& _meshPos, const BML::Vector3D& _meshRot)
  {
    //view matrix
    m_viewMatrix.LookAt(GetPosition(), GetTarget(), BML::Vector3D(0.0f, 1.0f, 0.0f));
    // quaternnion orientation
    BML::Quaternion orientation = BML::StaticFunctions::Euler(_meshRot);

    //rotation matrix thanks to the quaternion
    BML::Matrix4x4 rotationMat = orientation.GetMatrix4D();

    //translation matrix
    BML::Matrix4x4 translationMat;
    translationMat.ConvertForTranslation(_meshPos.m_x, _meshPos.m_y, _meshPos.m_z);

    //world matrix (rotation on the left so it's done first)
    m_worldMatrix = translationMat * rotationMat;

    m_modelView = m_viewMatrix  * m_worldMatrix;
    //Create the transform matrix
    m_MVP = m_projectionMatrix * m_modelView;

    return m_MVP;
  }

}