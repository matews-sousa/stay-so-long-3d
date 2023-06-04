#pragma once

#include <glm/glm.hpp>
#include <GL/gl.h>

class Camera
{
private:
  glm::vec3 pos;
  glm::vec3 target;
  glm::vec3 up;

public:
  Camera(glm::vec3 pos, glm::vec3 up);
  virtual ~Camera();

  void move(glm::vec3 direction);

  glm::mat4 getViewMatrix();

  void setTarget(glm::vec3 target) { this->target = target; }
  void setPos(glm::vec3 pos) { this->pos = pos; }

  glm::vec3 getPos() { return this->pos; }
};
