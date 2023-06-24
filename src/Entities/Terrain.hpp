#pragma once

#include <GL/glew.h>
#include "../Core/Texture.hpp"

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