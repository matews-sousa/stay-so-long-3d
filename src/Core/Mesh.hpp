#pragma once

#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <GL/glew.h>
#include "../Vertex.hpp"
#include <iostream>
#include "OBJLoader.hpp"
#include "Game.hpp"

class Mesh
{
public:
  Mesh(std::string fileName);
  virtual ~Mesh();

  void render();
  void updateColorBuffer();

private:
  GLuint vbo;

  std::vector<Vertex> vertices;
};