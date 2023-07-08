#include "Collider.hpp"

Collider::Collider(glm::vec3 position, glm::vec3 size)
{
  this->position = position;
  this->size = size;
}

Collider::~Collider()
{
}

bool Collider::testCollision(Collider &other)
{
  return false;
}