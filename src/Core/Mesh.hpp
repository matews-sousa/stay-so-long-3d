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

const bool CALCULATE_ILLUMINATION = true;
const bool SKIP_ILLUMINATION = false;

class Mesh
{
public:
  Mesh(std::string fileName);
  virtual ~Mesh();

  void render(glm::mat4 modelMatrix, bool calculateIllumination = false);
  void updateColorBufferThread(int start, int end);
  void updateColorBuffer();

  void setVertexColors(glm::vec3 color);

private:
  GLuint vbo;

  std::vector<Vertex> vertices;

  glm::mat4 modelMatrix;
};