/* A small SDL project showcasing my math library */

#include "Mesh.h"
#include "camera.h"

#include <SDL\SDL.h>
#include <BML\BML.h>
#include <iostream>

const int SCREEN_HEIGHT = 480;
const int SCREEN_WIDTH = 640;

struct Color
{
  //default constructor = white
  Color()
  {
    r = 255;
    g = 255;
    b = 255;
    a = 255;
  }
  //custom colored constructor
  Color(Uint8 _r, Uint8 _g, Uint8 _b, Uint8 _a)
  {
    //custom
    r = _r;
    g = _g;
    b = _b;
    a = _a;
  }
  Uint8 r;
  Uint8 g;
  Uint8 b;
  Uint8 a;
};

bool InitSDL(SDL_Window* &_window, SDL_Renderer* &_renderer);

void Close(SDL_Window* &_window, SDL_Renderer* &_renderer);

BML::Matrix4x4 ComputeTransformMatrix(camera& _camera, Mesh& _mesh);

BML::Vector2D ProjectTo2D(const BML::Vector3D& _coord3D, const BML::Matrix4x4& _transformMatrix);

void Render(std::vector<Mesh> _meshes, const BML::Matrix4x4& _transformMatrix, SDL_Renderer* &_renderer, const Color& _color);

bool HandleEvents(SDL_Event* _e, Mesh& _myMesh, camera& _camera);

int main(int argc, char* argv[])
{
  //the SDL window
  SDL_Window* window = nullptr;

  //the SDL renderer
  SDL_Renderer* renderer = nullptr;

  //Init SDL
  if (!InitSDL(window, renderer))
  {
    std::cout << "Failed to init SDL =[" << std::endl;
  }
  else
  {
    //useful constants
    const float ROTATION_SPEED = 0.1f;

    //main loop flag
    bool quit = false;

    //event handler
    SDL_Event e;

    //The vector of meshes (even though I make only one)
    std::vector<Mesh> myMeshes;

    //The mesh.
    Mesh myMesh("Cube", 8, 12);

    //The camera
    camera cam;

    //set up the mesh vertices to make a cube
    myMesh.m_vertices[0] = BML::Vector3D(-1.0f, 1.0f, 1.0f);
    myMesh.m_vertices[1] = BML::Vector3D(1.0f, 1.0f, 1.0f);
    myMesh.m_vertices[2] = BML::Vector3D(-1.0f, -1.0f, 1.0f);
    myMesh.m_vertices[3] = BML::Vector3D(1.0f, -1.0f, 1.0f);
    myMesh.m_vertices[4] = BML::Vector3D(-1.0f, 1.0f, -1.0f);
    myMesh.m_vertices[5] = BML::Vector3D(1.0f, 1.0f, -1.0f);
    myMesh.m_vertices[6] = BML::Vector3D(1.0f, -1.0f, -1.0f);
    myMesh.m_vertices[7] = BML::Vector3D(-1.0f, -1.0f, -1.0f);

    //set up the mesh faces for the triangles (12 triangles as there are 6 quads in a cube)
    myMesh.m_faces[0] = Face(0, 1, 2);
    myMesh.m_faces[1] = Face(1, 2, 3);
    myMesh.m_faces[2] = Face(1, 3, 6);
    myMesh.m_faces[3] = Face(1, 5, 6);
    myMesh.m_faces[4] = Face(0, 1, 4);
    myMesh.m_faces[5] = Face(1, 4, 5);
    myMesh.m_faces[6] = Face(2, 3, 7);
    myMesh.m_faces[7] = Face(3, 6, 7);
    myMesh.m_faces[8] = Face(0, 2, 7);
    myMesh.m_faces[9] = Face(0, 4, 7);
    myMesh.m_faces[10] = Face(4, 5, 6);
    myMesh.m_faces[11] = Face(5, 6, 7);

    //push it back to the vector
    myMeshes.push_back(myMesh);

    //set up camera position
    cam.SetPosition(BML::Vector3D(0.0f, 0.0f, 10.0f));

    //set up the direction where the camera is looking at (the origin)
    cam.SetTarget(BML::Vector3D(0.0f, 0.0f, 0.0f));

    //main loop
    while (!quit)
    {
      //handle events
      quit = HandleEvents(&e, myMesh, cam);

      //Clear the screen
      Color color; //< white default color
      SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
      SDL_RenderClear(renderer);

      //increment the rotation a little bit every iteration to get the rotating effect
      myMesh.SetRotation(BML::Vector3D(myMesh.GetRotation().m_x + ROTATION_SPEED, myMesh.GetRotation().m_y + ROTATION_SPEED, myMesh.GetRotation().m_z));

      //compute the transform matrix
      BML::Matrix4x4 transformMatrix = ComputeTransformMatrix(cam, myMesh);

      //Render stuff
      Render(myMeshes, transformMatrix, renderer, Color(0, 0, 0, 255));

      //Update screen
      SDL_RenderPresent(renderer);
    }
  }
  Close(window, renderer);
  return 0;
}

bool InitSDL(SDL_Window* &_window, SDL_Renderer* &_renderer)
{
  bool wasSuccess = true;

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    wasSuccess = false;
  }
  else
  {
    _window = SDL_CreateWindow("BML Graphical", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (_window == nullptr)
    {
      std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
      wasSuccess = false;
    }
    else
    {
      //Create renderer for window
      _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
      if (_renderer == nullptr)
      {
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        wasSuccess = false;
      }
      else
      {
        //Init renderer color
        SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
      }
    }
  }
  return wasSuccess;
}

void Close(SDL_Window* &_window, SDL_Renderer* &_renderer)
{
  SDL_DestroyRenderer(_renderer);
  SDL_DestroyWindow(_window);
  _window = nullptr;
  _renderer = nullptr;

  SDL_Quit();
}

BML::Matrix4x4 ComputeTransformMatrix(camera& _camera, Mesh& _mesh)
{
  //View matrix
  BML::Matrix4x4 viewMatrix;
  viewMatrix.LookAt(_camera.GetPosition(), _camera.GetTarget(), BML::Vector3D(0.0f, 1.0f, 0.0f));

  //projection matrix
  BML::Matrix4x4 projectionMatrix;

  projectionMatrix.Perspective(45.0f * M_PI / 180.0f, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

  //quaternnion orientation
  BML::Quaternion orientation = BML::StaticFunctions::Euler(_mesh.GetRotation());

  //rotation matrix thanks to the quaternion
  BML::Matrix4x4 rotationMat = orientation.GetMatrix4D();

  //translation matrix
  BML::Matrix4x4 translationMat;
  translationMat.ConvertForTranslation(_mesh.GetPosition().m_x, _mesh.GetPosition().m_y, _mesh.GetPosition().m_z);

  //world matrix (rotation on the left so it's done first)
  BML::Matrix4x4 worldMatrix = translationMat * rotationMat;

  //Create the transform matrix
  BML::Matrix4x4 transformMatrix = projectionMatrix * viewMatrix  * worldMatrix;
  return transformMatrix;
}

BML::Vector2D ProjectTo2D(const BML::Vector3D& _coord3D, const BML::Matrix4x4& _transformMatrix)
{
  BML::Vector4D homogeneousCoord(_coord3D, 1.0f);

  homogeneousCoord = _transformMatrix * homogeneousCoord;

  homogeneousCoord /= homogeneousCoord.m_w;

  //float x = ((homogeneousCoord.m_x * SCREEN_WIDTH) / (homogeneousCoord.m_w * 2.0f)) + (SCREEN_WIDTH / 2.0f);
  //float y = ((homogeneousCoord.m_y * SCREEN_HEIGHT) / (homogeneousCoord.m_w * 2.0f)) + (SCREEN_HEIGHT / 2.0f);


  return BML::Vector2D(homogeneousCoord.m_x + (SCREEN_WIDTH / 2.0f), (homogeneousCoord.m_y * -1.0f) + (SCREEN_HEIGHT / 2.0f));
  //return BML::Vector2D(x, y);
}

void Render(std::vector<Mesh> _meshes, const BML::Matrix4x4& _transformMatrix, SDL_Renderer* &_renderer, const Color& _color)
{
  //draw all the triangles through their faces (each face has 3 points: A, B, C which are gonna get connected)
  for (Mesh mesh : _meshes)
  {
    for (Face face : mesh.m_faces)
    {
      BML::Vector3D vertexA = mesh.m_vertices[face.A];
      BML::Vector3D vertexB = mesh.m_vertices[face.B];
      BML::Vector3D vertexC = mesh.m_vertices[face.C];


      BML::Vector2D pixelA = ProjectTo2D(vertexA, _transformMatrix);
      BML::Vector2D pixelB = ProjectTo2D(vertexB, _transformMatrix);
      BML::Vector2D pixelC = ProjectTo2D(vertexC, _transformMatrix);

      //check if the points are in bounds
      if (pixelA.m_x >= 0 && pixelA.m_y >= 0 && pixelA.m_x < SCREEN_WIDTH && pixelA.m_y < SCREEN_HEIGHT &&
        pixelB.m_x >= 0 && pixelB.m_y >= 0 && pixelB.m_x < SCREEN_WIDTH && pixelB.m_y < SCREEN_HEIGHT &&
        pixelC.m_x >= 0 && pixelC.m_y >= 0 && pixelC.m_x < SCREEN_WIDTH && pixelC.m_y < SCREEN_HEIGHT)
      {
        //set the render color to black
        SDL_SetRenderDrawColor(_renderer, _color.r, _color.g, _color.b, _color.a);
        //render triangle from point A to B, B to C and C to A
        if (SDL_RenderDrawLine(_renderer, pixelA.m_x, pixelA.m_y, pixelB.m_x, pixelB.m_y) == -1)
        {
          std::cout << "SDL could not draw point! SDL_Error: " << SDL_GetError() << std::endl;
        }
        if (SDL_RenderDrawLine(_renderer, pixelB.m_x, pixelB.m_y, pixelC.m_x, pixelC.m_y) == -1)
        {
          std::cout << "SDL could not draw point! SDL_Error: " << SDL_GetError() << std::endl;
        }
        if (SDL_RenderDrawLine(_renderer, pixelC.m_x, pixelC.m_y, pixelA.m_x, pixelA.m_y) == -1)
        {
          std::cout << "SDL could not draw point! SDL_Error: " << SDL_GetError() << std::endl;
        }
      }
      else
      {
        std::cout << "Could not render point, out of bound \n" << std::endl;
      }
    }
  }
}

bool HandleEvents(SDL_Event* _e, Mesh& _myMesh, camera& _camera)
{
  const float TRANSLATION_SPEED = 0.1f;

  while (SDL_PollEvent(_e) != 0)
  {
    switch (_e->type)
    {
    case SDL_QUIT:
    {
      return true;
    }
    case SDL_MOUSEBUTTONDOWN:
    {
      int x, y;
      SDL_GetMouseState(&x, &y);
      std::cout << "x: " << x << " y: " << y << std::endl;
      break;
    }
    case SDL_KEYDOWN:
    {
      switch (_e->key.keysym.sym)
      {
      case SDLK_r:
      {
        std::cout << "Current frame rotation: " << _myMesh.GetRotation() << std::endl;
        break;
      }
      case SDLK_a:
      {
        BML::Vector3D newPos(_camera.GetTarget().m_x + TRANSLATION_SPEED, _camera.GetTarget().m_y, _camera.GetTarget().m_z);
        _camera.SetTarget(newPos);
        break;
      }
      case SDLK_d:
      {
        BML::Vector3D newPos(_camera.GetTarget().m_x - TRANSLATION_SPEED, _camera.GetTarget().m_y, _camera.GetTarget().m_z);
        _camera.SetTarget(newPos);
        break;
      }
      case SDLK_w:
      {
        BML::Vector3D newPos(_camera.GetTarget().m_x, _camera.GetTarget().m_y - TRANSLATION_SPEED, _camera.GetTarget().m_z);
        _camera.SetTarget(newPos);
        break;
      }
      case SDLK_s:
      {
        BML::Vector3D newPos(_camera.GetTarget().m_x, _camera.GetTarget().m_y + TRANSLATION_SPEED, _camera.GetTarget().m_z);
        _camera.SetTarget(newPos);
        break;
      }
      case SDLK_q:
      {
        BML::Vector3D newPos(_camera.GetPosition().m_x, _camera.GetPosition().m_y, _camera.GetPosition().m_z + TRANSLATION_SPEED);
        _camera.SetPosition(newPos);
        break;
      }
      case SDLK_e:
      {
        BML::Vector3D newPos(_camera.GetPosition().m_x, _camera.GetPosition().m_y, _camera.GetPosition().m_z - TRANSLATION_SPEED);
        _camera.SetPosition(newPos);
        break;
      }
      default:
        break;
      }
      break;
    }
    default:
      break;
    }
  }
  return false;
}