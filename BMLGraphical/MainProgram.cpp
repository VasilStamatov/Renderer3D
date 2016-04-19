#include "MainProgram.h"
#include <GraphicalEngine/SDL_Init.h>

MainProgram::MainProgram() :
m_screenWidth(640),
m_screenHeight(480),
m_maxFPS(60.0f)
{
}


MainProgram::~MainProgram()
{
}

void MainProgram::Run()
{
  //Init stuff which are needed before the main loop
  if (InitSystems())
  {
    //if the systems initialized properly
    //Enter the loop
    MainLoop();
  }

  //end program
  SDL_DestroyRenderer(m_renderer.GetRenderer());
  SDL_DestroyWindow(m_window.GetWindow());

  m_window.SetNull();
  m_renderer.SetNull();

  SDL_Quit();
}
bool MainProgram::InitSystems()
{
  //Init GraphicalEngine (SDL actually)
  if (GraphicalEngine::Init() != 0)
  {
    //error initializing sdl
    return false;
  }

  if (!m_window.Create("BLM Graphical", m_screenWidth, m_screenHeight, 0))
  {
    //error creating renderer
    return false;
  }

  if (!m_renderer.Create(m_window.GetWindow(), -1))
  {
    //error creating renderer
    return false;
  }

  //Init the camera
  m_camera.Init(45.0f, m_screenWidth, m_screenHeight);

  //Init the fps limiter
  m_fpsLimiter.Init(m_maxFPS);

  //Create the cube
  GraphicalEngine::Mesh myMesh("Cube", 8, 12);

  //set up the mesh vertices to make a cube
  myMesh.m_vertices[0].coordinates = BML::Vector3D(-1.0f, 1.0f, 1.0f);
  myMesh.m_vertices[1].coordinates = BML::Vector3D(1.0f, 1.0f, 1.0f);
  myMesh.m_vertices[2].coordinates = BML::Vector3D(-1.0f, -1.0f, 1.0f);
  myMesh.m_vertices[3].coordinates = BML::Vector3D(1.0f, -1.0f, 1.0f);
  myMesh.m_vertices[4].coordinates = BML::Vector3D(-1.0f, 1.0f, -1.0f);
  myMesh.m_vertices[5].coordinates = BML::Vector3D(1.0f, 1.0f, -1.0f);
  myMesh.m_vertices[6].coordinates = BML::Vector3D(1.0f, -1.0f, -1.0f);
  myMesh.m_vertices[7].coordinates = BML::Vector3D(-1.0f, -1.0f, -1.0f);

  //set up the mesh faces for the triangles (12 triangles as there are 6 quads in a cube)
  myMesh.m_faces[0] = GraphicalEngine::Face(0, 1, 2);
  myMesh.m_faces[1] = GraphicalEngine::Face(1, 2, 3);
  myMesh.m_faces[2] = GraphicalEngine::Face(1, 3, 6);
  myMesh.m_faces[3] = GraphicalEngine::Face(1, 5, 6);
  myMesh.m_faces[4] = GraphicalEngine::Face(0, 1, 4);
  myMesh.m_faces[5] = GraphicalEngine::Face(1, 4, 5);
  myMesh.m_faces[6] = GraphicalEngine::Face(2, 3, 7);
  myMesh.m_faces[7] = GraphicalEngine::Face(3, 6, 7);
  myMesh.m_faces[8] = GraphicalEngine::Face(0, 2, 7);
  myMesh.m_faces[9] = GraphicalEngine::Face(0, 4, 7);
  myMesh.m_faces[10] = GraphicalEngine::Face(4, 5, 6);
  myMesh.m_faces[11] = GraphicalEngine::Face(5, 6, 7);

  //computes the per vertex normals
  myMesh.ComputeMeshNormals();

  //push it back to the vector
  m_myMeshes.push_back(myMesh);

  //set up camera position
  m_camera.SetPosition(BML::Vector3D(0.0f, 0.0f, 10.0f));

  //set up the direction where the camera is looking at (the origin)
  m_camera.SetTarget(BML::Vector3D(0.0f, 0.0f, 0.0f));

  return true;
}
void MainProgram::MainLoop()
{
  while (m_programState != ProgramState::EXIT)
  {
    //The beggining of the frame (gets the current ticks)
    m_fpsLimiter.BeginFrame();

    //Process input
    ProcessInput();

    //Render to the screen
    Render();

    //get the fps at the end of the frame
    m_fps = m_fpsLimiter.End();

    //print only once every 10 frames
    static int frameCount = 0;
    frameCount++;
    if (frameCount == 10)
    {
      printf("fps: %f \n", m_fps);
      frameCount = 0;
    }
  }
}
void MainProgram::ProcessInput()
{
  //Camera speed
  const float CAMERA_SPEED = 0.1f;
  //SDL events
  SDL_Event evnt;
  while (SDL_PollEvent(&evnt))
  {
    switch (evnt.type)
    {
    case SDL_QUIT:
    {
      m_programState = ProgramState::EXIT;
      break;
    }
    case SDL_MOUSEMOTION:
    {
      m_inputManager.SetMouseCoords(evnt.motion.x, evnt.motion.y);
      break;
    }
    case SDL_KEYDOWN:
    {
      m_inputManager.PressKey(evnt.key.keysym.sym);
      break;
    }
    case SDL_KEYUP:
    {
      m_inputManager.ReleaseKey(evnt.key.keysym.sym);
      break;
    }
    case SDL_MOUSEBUTTONDOWN:
    {
      m_inputManager.PressKey(evnt.button.button);
      break;
    }
    case SDL_MOUSEBUTTONUP:
    {
      m_inputManager.ReleaseKey(evnt.button.button);
      break;
    }
    default:
      break;
    }
  }
  //Check for presses
  if (m_inputManager.IsKeyDown(SDLK_w))
  {
    m_camera.SetTarget(m_camera.GetTarget() + BML::Vector3D(0.0f, -CAMERA_SPEED, 0.0f));
  }
  if (m_inputManager.IsKeyDown(SDLK_s))
  {
    m_camera.SetTarget(m_camera.GetTarget() + BML::Vector3D(0.0f, CAMERA_SPEED, 0.0f));
  }
  if (m_inputManager.IsKeyDown(SDLK_a))
  {
    m_camera.SetTarget(m_camera.GetTarget() + BML::Vector3D(CAMERA_SPEED, 0.0f, 0.0f));
  }
  if (m_inputManager.IsKeyDown(SDLK_d))
  {
    m_camera.SetTarget(m_camera.GetTarget() + BML::Vector3D(-CAMERA_SPEED, 0.0f, 0.0f));
  }
  if (m_inputManager.IsKeyDown(SDLK_q))
  {
    m_camera.SetPosition(m_camera.GetPosition() + BML::Vector3D(0.0f, 0.0f, CAMERA_SPEED));
  }
  if (m_inputManager.IsKeyDown(SDLK_e))
  {
    m_camera.SetPosition(m_camera.GetPosition() + BML::Vector3D(0.0f, 0.0f, -CAMERA_SPEED));
  }
}
void MainProgram::Render()
{
  //Rotation speed
  const float ROTATION_SPEED = 0.1f;
  //Set the color to white
  m_renderer.SetColor(GraphicalEngine::ColorRGBA8(255));
  //Clear the screen
  m_renderer.ClearScreen();

  //Render all the meshes (only 1 for now)
  for (int i = 0; i < m_myMeshes.size(); i++)
  {
    //increment the rotation a little bit every iteration to get the rotating effect
    m_myMeshes[i].SetRotation(m_myMeshes[i].GetRotation() + BML::Vector3D(ROTATION_SPEED, ROTATION_SPEED, 0.0f));
    //m_myMeshes[i].SetPosition(m_myMeshes[i].GetPosition() + BML::Vector3D(0.00001, 0.0f, 0.0f));

    //Get the MVP matrix
    BML::Matrix4x4 MVP = m_camera.ComputeMVP(m_myMeshes[i].GetPosition(), m_myMeshes[i].GetRotation());

    BML::Matrix4x4 worldMat = m_camera.GetCurrentWorld();

    BML::Matrix4x4 modelView = m_camera.GetCurrentModelView();
    //Render the current mesh
    m_renderer.Render(m_myMeshes[i], MVP, worldMat, modelView);
  }
  //Update the screen
  m_renderer.UpdateScreen();
}
