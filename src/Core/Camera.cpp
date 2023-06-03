#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 pos, glm::vec3 up)
{
  this->pos = pos;
  this->at = glm::vec3(0.0f, 0.0f, 0.0f);
  this->up = up;
}

Camera::~Camera()
{
}

glm::mat4 Camera::getViewMatrix()
{
  return glm::lookAt(this->pos, this->at, this->up);
}