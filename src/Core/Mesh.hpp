#pragma once

#include <vector>
#include <unordered_map>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <GL/glew.h>
#include "../Vertex.hpp"
#include <iostream>
#include "OBJLoader.hpp"
#include "Game.hpp"
#include "Light.hpp"

class Mesh
{
public:
  Mesh(std::string fileName);
  virtual ~Mesh();

  void render(glm::mat4 modelMatrix);
  void updateColorBufferThread(int start, int end);
  void updateColorBuffer();

private:
  std::unordered_map<int, glm::vec3> illuminationCache;

  GLuint vbo;

  std::vector<Vertex> vertices;

  glm::mat4 modelMatrix;
};