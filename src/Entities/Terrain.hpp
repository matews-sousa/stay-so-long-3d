#pragma once

#include <GL/glew.h>
#include "../Core/Texture.hpp"
#include "../Core/Game.hpp"
#include "../Core/Light.hpp"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Terrain
{
public:
  Terrain(int gridX, int gridZ);
  virtual ~Terrain();

  void draw();

private:
  int size;
  int tileSize;
  int vertexCount;

  float x;
  float z;

  GLuint displayList;

  void generateTerrain();
};