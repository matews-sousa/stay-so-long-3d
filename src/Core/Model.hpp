#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <GL/gl.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Texture.hpp"

struct Face
{
  std::vector<glm::vec3> vertices;
  std::vector<glm::vec3> normals;
  std::vector<glm::vec2> texCoords;

  glm::vec3 faceCenter;
  glm::vec3 faceNormal;

  bool isQuad = false;
};

class Model
{
public:
  Model(std::string fileName);
  virtual ~Model();

  void drawModel();
  void drawFace(Face &face);

  bool loadObject(std::string fileName);

  float getRadius() { return radius; }
  glm::vec3 getCenter() { return center; }
  GLuint getDisplayList() { return displayList; }
  std::string getFileName() { return fileName; }

private:
  std::vector<Face> faces;

  glm::vec3 boundingPoints[8];

  float radius;
  glm::vec3 center;

  bool objectLoaded;

  GLuint displayList;

  std::string fileName;
};