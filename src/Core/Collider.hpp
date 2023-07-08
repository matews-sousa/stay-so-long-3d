#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

class Collider
{
public:
  Collider(glm::vec3 position, glm::vec3 size);
  virtual ~Collider();

  bool testCollision(Collider &other);

  glm::vec3 getPosition() const { return position; }
  glm::vec3 getSize() const { return size; }

  void setPosition(glm::vec3 position) { this->position = position; }

protected:
  glm::vec3 position;
  glm::vec3 size;
};