#include "GameObject.hpp"

GameObject::GameObject()
{
  this->position = glm::vec3(0.0f, 0.0f, 0.0f);
  this->scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

GameObject::GameObject(glm::vec3 position, glm::vec3 scale)
{
  this->position = position;
  this->scale = scale;
}

GameObject::~GameObject()
{
}

