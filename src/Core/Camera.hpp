#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>

class Camera
{
private:
  glm::vec3 position;
  glm::vec3 target;
  glm::vec3 up;

public:
  Camera(glm::vec3 position, glm::vec3 up);
  virtual ~Camera();

  void move(glm::vec3 playerPos);

  glm::mat4 getViewMatrix();

  void setTarget(glm::vec3 target) { this->target = target; }
  void setPosition(glm::vec3 position) { this->position = position; }

  glm::vec3 getPosition() { return this->position; }
};
