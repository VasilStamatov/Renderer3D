#pragma once

#include <GraphicalEngine\Camera.h>
#include <GraphicalEngine/InputManager.h>
#include <GraphicalEngine/Mesh.h>
#include <GraphicalEngine/Renderer.h>
#include <GraphicalEngine/Window.h>
#include <GraphicalEngine\Timing.h>
#include <vector>

enum class ProgramState{ CONTINUE, EXIT };

class MainProgram
{
public:
  MainProgram();
  ~MainProgram();

  //Run this program
  void Run();

private:
  //Init things which need to be created before the main loop
  bool InitSystems();
  //The main loop
  void MainLoop();
  //Process inputs
  void ProcessInput();
  //Render to the screen
  void Render();

  int m_screenWidth;
  int m_screenHeight;

  //SDL window
  GraphicalEngine::Window m_window;
  //SDL renderer
  GraphicalEngine::Renderer m_renderer;
  //the camera
  GraphicalEngine::Camera m_camera;
  //Input manager
  GraphicalEngine::InputManager m_inputManager;
  //vector of meshes (even tho only 1 is made :D)
  std::vector<GraphicalEngine::Mesh> m_myMeshes;
  //The state of the program
  ProgramState m_programState = ProgramState::CONTINUE;
  //The fps limiter
  GraphicalEngine::FpsLimiter m_fpsLimiter;
  
  float m_maxFPS;
  float m_fps;

};

