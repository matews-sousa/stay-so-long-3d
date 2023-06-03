#pragma once

#include <glm/glm.hpp>
#include <GL/gl.h>

class Camera
{
private:
  glm::vec3 pos;
  glm::vec3 at;
  glm::vec3 up;

public:
  Camera(glm::vec3 pos, glm::vec3 up);
  virtual ~Camera();

  glm::mat4 getViewMatrix();
};
