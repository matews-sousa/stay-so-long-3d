#pragma once

#include <glm/vec3.hpp>

class GameObject
{
protected:
  glm::vec3 position;
  glm::vec3 scale;

public:
  GameObject();
  GameObject(glm::vec3 position, glm::vec3 scale);
  virtual ~GameObject();

  glm::vec3 getPosition() { return this->position; }
  glm::vec3 getScale() { return this->scale; }

  void setPosition(glm::vec3 position) { this->position = position; }
  void setScale(glm::vec3 scale) { this->scale = scale; }
};